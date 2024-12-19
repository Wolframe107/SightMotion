using System.Collections;
using System.Collections.Generic;
using UnityEngine;

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

    // Update is called once per frame
    void Update() {
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
    }

    // Updates target timer if hit
    public void RayCastHit(RaycastHit hit) {
        if (targetTimers.ContainsKey(hit.collider.gameObject)) {
            targetTimers[hit.collider.gameObject] = Mathf.Max(0.0f, targetTimers[hit.collider.gameObject] - Time.deltaTime * lookAtTimeScale);
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
        float angle = (i / 2) * (fieldOfView / (targetCount + 1)) * Mathf.Deg2Rad * (i % 2 == 0 ? 1 : -1) + Mathf.PI / 2;
        angle -= 0.5f * (fieldOfView / (targetCount + 1)) * Mathf.Deg2Rad * (i % 2 == 0 ? 1 : -1) * (targetCount % 2 == 0 ? 1 : 0);
        
        // Set position
        target.transform.position = transform.position + targetDistance * new Vector3(Mathf.Cos(angle), 0, Mathf.Sin(angle));
        target.transform.localScale *= targetScale;
        target.transform.parent = transform;

        // Add to list
        targetTimers.Add(target, 0.0f);
    }

    // Game over
    public void GameOver() {
        Debug.Log("Game Over, Time survived: " + (Time.time - startTime));
    }

    // Start game
    public void StartGame() {
        startTime = Time.time;
        targetSpawnTimer = targetSpawnInterval;
        targetTimers.Clear();
    }
}
