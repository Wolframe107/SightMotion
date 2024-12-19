using UnityEngine;
using System;
using System.Collections.Generic;
using System.IO;

public class SaveData : MonoBehaviour
{   
    private string headPath;
    private string gazePath;
    private string eyePath;
    private string resultPath;

    private List<string> headData;
    private List<string> gazeData;
    private List<string> eyeData;
    private List<string> resultData;

    void Start()
    {
        headData = new List<string>();
        gazeData = new List<string>();
        eyeData = new List<string>();
        resultData = new List<string>();

        headPath = Path.Combine(Application.persistentDataPath, "headData.csv");
        gazePath = Path.Combine(Application.persistentDataPath, "gazeData.csv");
        eyePath = Path.Combine(Application.persistentDataPath, "eyeData.csv");
        resultPath = Path.Combine(Application.persistentDataPath, "resultData.csv");
        //positionDataFilePath = Path.Combine(Application.persistentDataPath, "testData.csv");

        // Wipe old test
        if (File.Exists(headPath)){
            File.Delete(headPath);
        }

        if (File.Exists(gazePath)){
            File.Delete(gazePath);
        }

        if (File.Exists(eyePath)){
            File.Delete(eyePath);
        }

        if (File.Exists(resultPath)){
            File.Delete(resultPath);
        }

        //Debug.Log(positionDataFilePath);

        // Write the header line to the position data file
        File.WriteAllText(headPath, "TimeStamp, PosX, PosY, PosZ\n");
        File.WriteAllText(gazePath, "TimeStamp, PosX, PosY, PosZ\n");
        File.WriteAllText(eyePath, "TimeStamp, PosX, PosY, PosZ\n");
        File.WriteAllText(resultPath, "TimeStamp, Result\n");

        Debug.Log("Completed Start");
    }

    public void WriteData(string mode, Vector3 pos, string FinalResult=""){
        switch (mode) {
            case "head":
                string headDataLine = string.Format(
                    "{0},{1},{2},{3}",
                    DateTime.Now,
                    pos.x, pos.y, pos.z
                );
                headData.Add(headDataLine);
                break;

            case "gaze":
                string gazeDataLine = string.Format(
                    "{0},{1},{2},{3}",
                    DateTime.Now,
                    pos.x, pos.y, pos.z
                );
                gazeData.Add(gazeDataLine);
                break;

            case "eye":
                string eyeDataLine = string.Format(
                    "{0},{1},{2},{3}",
                    DateTime.Now,
                    pos.x, pos.y, pos.z
                );
                eyeData.Add(eyeDataLine);
                break;

            case "result":
                string resultDataLine = string.Format(
                    "{0},{1}",
                    DateTime.Now,
                    FinalResult
                );
                resultData.Add(resultDataLine);
                break;
        }
    }

    public void SaveAllData()
    {
        // Write the list of position data lines to the CSV file after each round
        File.AppendAllLines(headPath, headData);

        File.AppendAllLines(gazePath, gazeData);

        File.AppendAllLines(eyePath, eyeData);

        File.AppendAllLines(resultPath, resultData);

        Debug.Log("Saved Data");

        // Clear the list after saving
        headData.Clear();
        gazeData.Clear();
        eyeData.Clear();
        resultData.Clear();
    }
}