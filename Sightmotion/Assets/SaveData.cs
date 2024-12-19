using UnityEngine;
using System;
using System.Collections.Generic;
using System.IO;

public class SaveData : MonoBehaviour
{
    public GameObject posVec;
    private TargetHandler handlerScript;
    private string positionDataFilePath; // ändra till rätt data
    private List<string> positionData;

    void Start()
    {

        handlerScript = posVec.GetComponent<TargetHandler>();
        positionData = new List<string>();
        positionDataFilePath = Path.Combine(Application.persistentDataPath, "TEST.csv");
        if (File.Exists(positionDataFilePath)){
            File.Delete(positionDataFilePath);
        }
        Debug.Log(positionDataFilePath);


        // Write the header line to the position data file
        File.WriteAllText(positionDataFilePath, "TimeStamp, PosX, PosY, PosZ\n"); // ändra till rätt grejer
        Debug.Log("Completed Start");
    }

    void Update()
    {
        Vector3 currentTrackerPosition = handlerScript.resultPoint;

        // Format the current positions into a string for the CSV file
        string positionDataLine = string.Format(
            "{0},{1},{2},{3}",
            DateTime.Now,
            currentTrackerPosition.x, currentTrackerPosition.y, currentTrackerPosition.z
        );

        // Store the formatted string in the list
        positionData.Add(positionDataLine);
    }

    public void SavePositionData()
    {
        Debug.Log(positionDataFilePath);
        // Write the list of position data lines to the CSV file after each round
        File.AppendAllLines(positionDataFilePath, positionData);

        // Clear the list after saving
        positionData.Clear();
    }
}