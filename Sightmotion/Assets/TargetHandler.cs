using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TargetHandler : MonoBehaviour {

    [Header("Debug Raycast Settings")]
    public Vector3 position = new Vector3(0, 0, 0);
    public Vector3 direction = new Vector3(0, 0, 1);

    [Header("Target Settings")]
    public int targetCount = 10;
    public float targetDistance = 10.0f;
    public float targetScale = 1f;

    // List of targets and timers
    private GameObject[] targets;
    private float[] targetTimers;

    // Raycast variables
    public Vector3 resultPoint = new Vector3(0, 0, 0);
    private float closestDistance = 9999999.0f;
    private GameObject closestTarget;

    // Start is called before the first frame update
    void Start() {
        targets = new GameObject[targetCount];
        targetTimers = new float[targetCount];
        
        // Generate a list of targets
        for (int i = 0; i < targetCount; i++) {
            GameObject target = GameObject.CreatePrimitive(PrimitiveType.Sphere);

            // Add collider and tag for raycast
            target.AddComponent<SphereCollider>();
            target.name = "Target" + i.ToString();
            target.GetComponent<MeshRenderer>().material.color = new Color(Random.value, Random.value, Random.value);
            
            // Set position
            float angle = i * 2 * Mathf.PI / targetCount;
            target.transform.position = transform.position + targetDistance * new Vector3(Mathf.Cos(angle), 0, Mathf.Sin(angle));
            target.transform.localScale *= targetScale;
            target.transform.parent = transform;

            // Add to list
            targets[i] = target;
            targetTimers[i] = 0.0f;
        }
    }

    // Update is called once per frame
    void Update() {

        // Set raycast position and direction for testing
        position = Camera.main.transform.position;
        direction = Camera.main.transform.forward;
        
        // Raycast and update target color if hit
        /*
        if (Physics.Raycast(new Ray(position, direction), out RaycastHit hit)) {
            if (hit.collider.gameObject.name == "Target") {
                int index = System.Array.IndexOf(targets, hit.collider.gameObject);
                targetTimers[index] = Mathf.Max(0.0f, targetTimers[index] - Time.deltaTime * 10.0f);
            }
        }
        
        */
        // Use resultPoint to know which target is looked at
        
        if (resultPoint != Vector3.zero)
        {   
            Debug.Log("Target Hit!" + resultPoint);
            //closestTarget = targets[0];
            closestDistance = 9999999.0f;
            foreach (GameObject target in targets)
            {
                float distance = Vector3.Distance(target.transform.position, resultPoint);

                // If this target is closer than the previously found target, update closestTarget
                if (distance < closestDistance)
                {
                    closestDistance = distance;
                    closestTarget = target;

                    //Debug.Log("new target! " + closestTarget);
                }
            }

            //Debug.Log("Closest Target: " + closestTarget);

            int index = System.Array.IndexOf(targets, closestTarget);
            Debug.Log("Index of closest target: " + index);
            if (index != -1)
            {
                targetTimers[index] = Mathf.Max(0.0f, targetTimers[index] - Time.deltaTime * 10.0f);
                //Debug.Log("Cooling Down Target " + index);
            }
        }
        

        // Update target timers and colors
        for (int i = 0; i < targets.Length; i++) {
            targetTimers[i] += Time.deltaTime;
            targets[i].GetComponent<MeshRenderer>().material.color = new Color(1.0f, 1.0f - targetTimers[i] / 10.0f, 1.0f - targetTimers[i] / 10.0f);
        }
    }
}
