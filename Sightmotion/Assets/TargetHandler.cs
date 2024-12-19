using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TargetHandler : MonoBehaviour {

    [Header("Gameplay Settings")]
    public float fieldOfViewVertical = 60.0f;
    public float fieldOfViewHorizontal = 120.0f;
    public float targetSpawnInterval = 10.0f;
    public float targetMaxTime = 60.0f;
    public float lookAtTimeScale = 10.0f;

    [Header("Target Settings")]
    public float targetDistance = 10.0f;
    public float targetScale = 1f;
    [Tooltip("The distance from the target that the raycast will hit")]
    public float allowance = 0.2f;

    // List of targets and timers
    private float startTime = 0.0f;
    private float targetSpawnTimer = 0.0f;
    private Dictionary<GameObject, float> targetTimers = new Dictionary<GameObject, float>();
    private HashSet<Vector3> targetPositions = new HashSet<Vector3>();

    private bool running = false;

    public GameObject StartMenu;
    public GameObject GameOverMenu;

    public GameObject gameOverText;

    public GameObject audioSource;

    public GameObject camera;

    void Start() {
        StartMenu.SetActive(true);
        GameOverMenu.SetActive(false);

        // Seed random consistently
        Random.InitState((int)5723751);
    }

    // Update is called once per frame
    void Update() {
        if (!running) { return; }

        transform.position = camera.transform.position;

        // Update target spawn timer
        targetSpawnTimer -= Time.deltaTime;

        // Add target if interval has passed
        if (targetSpawnTimer <= 0.0f) {
            AddTarget();
            targetSpawnTimer = targetSpawnInterval;
        }

        // Update target timers and colors
        GameObject[] targets = new GameObject[targetTimers.Count];
        targetTimers.Keys.CopyTo(targets, 0);
        foreach (GameObject target in targets) {
            targetTimers[target] += Time.deltaTime;
            target.GetComponent<Renderer>().material.color = Color.Lerp(Color.white, Color.red, targetTimers[target] / targetMaxTime);

            if (targetTimers[target] >= targetMaxTime) {
                GameOver();
            }
        }
    }

    // Updates target timer if hit
    public void RayCastHit(Vector3 target) {
        if (!running) { return; }
        if (Physics.Raycast(Camera.main.transform.position, target - Camera.main.transform.position, out RaycastHit hit)) {
            if (targetTimers.ContainsKey(hit.collider.gameObject)) {
                targetTimers[hit.collider.gameObject] = Mathf.Max(0.0f, targetTimers[hit.collider.gameObject] - Time.deltaTime * lookAtTimeScale);
            }
        }
    }

    // Add target
    public void AddTarget() {
        GameObject target = GameObject.CreatePrimitive(PrimitiveType.Sphere);

        // Add collider and tag for raycast
        SphereCollider collider = target.AddComponent<SphereCollider>();
        collider.radius *= (1 + allowance);
        target.name = "Target";

        int n = 0;
        while (n < 100) {
            Vector3 position = new Vector3(Random.Range(-5, 5) / 5.0f, Random.Range(-3, 3) / 3.0f, 1.0f);
            if (!targetPositions.Contains(position)) {
                targetPositions.Add(position);

                float angleX = position.x * fieldOfViewHorizontal / 2.0f;
                float angleY = position.y * fieldOfViewVertical / 2.0f;

                // Rotate around camera
                Vector3 targetPosition = Quaternion.Euler(-angleY, angleX, 0) * Camera.main.transform.forward;

                // Set position
                target.transform.position = transform.position + targetPosition * targetDistance;
                target.transform.localScale *= targetScale;
                target.transform.parent = transform;

                // Add to list
                targetTimers.Add(target, 0.0f);

                // Play sound on spawn position
                audioSource.transform.position = target.transform.position;
                audioSource.GetComponent<AudioSource>().Play();

                return;
            }
            n++;
        }
    }

    // Game over
    public void GameOver() {

        // Set game over text
        gameOverText.GetComponent<Text>().text = "Game Over\nTargets Activated: " + targetTimers.Count + "\nTime: " + (Time.time - startTime).ToString("F2") + "s";

        // Stop game
        StartMenu.SetActive(false);
        GameOverMenu.SetActive(true);

        running = false;
    }

    public void RestartGame() {
        StartMenu.SetActive(true);
        GameOverMenu.SetActive(false);

        // Destroy all
        GameObject[] targets = new GameObject[targetTimers.Count];
        targetTimers.Keys.CopyTo(targets, 0);
        foreach (GameObject target in targets) {
            Destroy(target);
        }

        // Clear list
        targetTimers = new Dictionary<GameObject, float>();
        targetPositions = new HashSet<Vector3>();
    }

    // Start game
    public void StartGame() {
        startTime = Time.time;
        targetSpawnTimer = targetSpawnInterval;

        // Start game
        StartMenu.SetActive(false);
        GameOverMenu.SetActive(false);

        running = true;
    }
}
