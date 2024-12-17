using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TriggerStart : MonoBehaviour
{   
    public GameObject UI_start;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.X))
        {
            StartGame();
        }
    }

    void StartGame()
    {
        UI_start.SetActive(false);
        GameObject.Find("Circles").GetComponent<GameController>().gameStart = true;
    }
}
