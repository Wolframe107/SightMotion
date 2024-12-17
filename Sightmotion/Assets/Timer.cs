using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Timer : MonoBehaviour
{   
    private float time;
    public float maxTime = 5f;
    
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        time += Time.deltaTime;

        if(time > maxTime){
            Debug.Log("Out of time :(");
            //GameObject.Find("Circles").GetComponent<GameController>().currentNumOfCircles -= 1;
            //Destroy(gameObject);
        }
    }
}
