using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameController : MonoBehaviour
{
    public bool gameStart = false;
    public bool running = false;
    public GameObject prefabToSpawn;
    public float spawnDistance = 1f;
    public int currentNumOfCircles = 0;
    public int maxCircles = 5;
    public float spawnDelay = 3f;
    private float playerHeight;

    private Dictionary<int, GameObject> spawnedObjects = new Dictionary<int, GameObject>();
    private int currentID = 0;

    void Start()
    {
        
    }

    void Update()
    {
        if(gameStart == true && !running)
        {   
            Debug.Log("Started");
            running = true;
            playerHeight = GameObject.Find("Main Camera").transform.position.y;
            transform.position = new Vector3(0, playerHeight, 0);
            StartCoroutine(SpawnWithDelay());
        }
    }

    IEnumerator SpawnWithDelay()
    {
        while (running) // Infinite loop
        {   
            if(currentNumOfCircles <= maxCircles)
            {   
                TrySpawnPrefab();
                //
            }
            
            yield return new WaitForSeconds(spawnDelay); // Wait for the specified delay
        }
    }

    void TrySpawnPrefab()
    {
        Vector3 spawnPosition = GenerateRandomPosition();

        // Check if the spawn position is clear
        if (!Physics.CheckSphere(spawnPosition, spawnDistance))
        {
            SpawnCircle(spawnPosition);
        }
        else
        {
            Debug.Log("Spawn position blocked, skipping this spawn attempt.");
        }
    }

    Vector3 GenerateRandomPosition()
    {
        // Generate a random angle in radians
        float randomAngle = Random.Range(0f, 2f * Mathf.PI);
        
        // Calculate the position based on the angle and distance
        return new Vector3(
            Mathf.Cos(randomAngle) * spawnDistance,
            Random.Range(-0.3f, 0.3f), // Adding random offset
            Mathf.Sin(randomAngle) * spawnDistance
        ) + transform.position; // Offset by the spawner's position
    }

    void SpawnCircle(Vector3 spawnPosition)
    {
        // Instantiate the prefab as a child of this GameObject
        GameObject spawnedPrefab = Instantiate(prefabToSpawn, spawnPosition, Quaternion.identity, this.transform);

        // Make the prefab face the center (this GameObject's position)
        Vector3 directionToCenter = (this.transform.position - spawnedPrefab.transform.position).normalized;
        spawnedPrefab.transform.rotation = Quaternion.LookRotation(directionToCenter);

        // Add the spawned object to the dictionary with a unique ID
        spawnedObjects.Add(currentID, spawnedPrefab);
        Debug.Log($"Spawned object with ID: {currentID}");

        currentID++;
        currentNumOfCircles++;
    }
}
