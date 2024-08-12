using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TimeManager : MonoBehaviour
{
    static private TimeManager instance;
    static public TimeManager Instance()
    {
        
        if(instance == null)
            instance = FindObjectOfType<TimeManager>();

        return instance;
    }

    public float elpasedTime;
    public float startTime;
    public void Start()
    {
        ResetTime();
    }

    public void Update()
    {
        elpasedTime = Time.time - startTime;
    }

    public void ResetTime()
    {
        startTime = Time.time;
    }


}
