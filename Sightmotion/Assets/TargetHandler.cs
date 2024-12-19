using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TargetHandler : MonoBehaviour {

    [Header("Gameplay Settings")]
    public float fieldOfView = 180.0f;
    public float targetSpawnInterval = 10.0f;
    public float targetMaxTime = 60.0f;
    public float lookAtTimeScale = 10.0f;

    [Header("Target Settings")]
    public int targetCount = 10;
    public float targetDistance = 10.0f;
    public float targetScale = 1f;
    [Tooltip("The distance from the target that the raycast will hit")]
    public float allowance = 0.2f;

    // List of targets and timers
    private float startTime = 0.0f;
    private float targetSpawnTimer = 0.0f;
    private Dictionary<GameObject, float> targetTimers = new Dictionary<GameObject, float>();

    private bool running = false;

    public GameObject StartMenu;
    public GameObject GameOverMenu;

    public GameObject gameOverText;

    public SaveData saveData;

    void Start() {
        StartMenu.SetActive(true);
        GameOverMenu.SetActive(false);
        saveData = GameObject.Find("SaveObject").GetComponent<SaveData>();    
    }

    // Update is called once per frame
    void Update() {
        if (!running) { return; }

        // Update target spawn timer
        targetSpawnTimer -= Time.deltaTime;

        // Add target if interval has passed
        if (targetSpawnTimer <= 0.0f && targetTimers.Count < targetCount) {
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

        saveData.WriteData("head", Camera.main.transform.eulerAngles);
    }

    // Updates target timer if hit
    public void RayCastHit(Vector3 target) {
        if (!running) { return; }
        if (Physics.Raycast(Camera.main.transform.position, target - Camera.main.transform.position, out RaycastHit hit)) {
            if (targetTimers.ContainsKey(hit.collider.gameObject)) {
                saveData.WriteData("gaze", Quaternion.LookRotation(Camera.main.transform.forward).eulerAngles);
                
                saveData.WriteData("eye", Quaternion.LookRotation(hit.point - Camera.main.transform.position).eulerAngles);

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
        
        // Calculate angle, evenly spaces targets around player
        int i = targetTimers.Count + (targetCount % 2 == 0 ? 2 : 1);
        float angle = (i / 2) * (fieldOfView / (targetCount / 2 + 1)) * Mathf.Deg2Rad * (i % 2 == 0 ? 1 : -1) + Mathf.PI / 2;
        angle -= 0.5f * (fieldOfView / (targetCount / 2 + 1)) * Mathf.Deg2Rad * (i % 2 == 0 ? 1 : -1) * (targetCount % 2 == 0 ? 1 : 0);
        angle -= fieldOfView * (i % 2 == 0 ? 1 : -1) * (i / targetCount);
        
        // Set position
        target.transform.position = transform.position + targetDistance * new Vector3(Mathf.Cos(angle), ((i / 2) % 2 == 0 ? 1 : -1) * (i / 2) / targetCount, Mathf.Sin(angle));
        target.transform.localScale *= targetScale;
        target.transform.parent = transform;

        // Add to list
        targetTimers.Add(target, 0.0f);
    }

    // Game over
    public void GameOver() {

        // Set game over text
        gameOverText.GetComponent<Text>().text = "Game Over\nTargets Activated: " + targetTimers.Count + "\nTime: " + (Time.time - startTime).ToString("F2") + "s";

        // Stop game
        StartMenu.SetActive(false);
        GameOverMenu.SetActive(true);

        running = false;

        // Save data
        saveData.WriteData("result", Vector3.zero, (Time.time - startTime).ToString("F2"));
        
        //saveData.WriteData("head", Vector3.zero, (Time.time - startTime).ToString("F2"));

        saveData.SaveAllData();
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
