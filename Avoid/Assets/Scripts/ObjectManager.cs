using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectManager : MonoBehaviour
{
    //생성할 프리팹
    public GameObject[] prefabs;
    //생성할 위치
    public Vector2 spawnPosition;

    float sumtTime = 0;
    float spawnTime;
    float elapsedTime;


    public void Start()
    {
        spawnTime = 1.0f;
    }
    // Update is called once per frame
    void Update()
    {
        elapsedTime = TimeManager.Instance().elpasedTime;

        bool Leve1 = elapsedTime >= 10 && elapsedTime < 20;
        bool Leve2 = elapsedTime >= 20 && elapsedTime < 30;
        bool Leve3 = elapsedTime >= 30 && elapsedTime < 40;
        bool Leve4 = elapsedTime >= 40 && elapsedTime < 50;
        bool Leve5 = elapsedTime >= 50 && elapsedTime < 60;

        sumtTime += Time.deltaTime;

        Debug.Log(spawnTime);

        if(sumtTime > spawnTime)
        {
            Spawn();   
            sumtTime = 0;
        }

        if(Time.time >= 10 && Time.time < 20)
            spawnTime = 0.7f;
        if (Leve2)
            spawnTime = 0.5f;
        else if (Leve3)
            spawnTime = 0.4f;
        else if (Leve4)
            spawnTime = 0.3f;
        else if (Leve5)
            spawnTime = 0.2f;
    }

    void Spawn()
    {
        //스폰위치X좌표 랜덤
        float spawnPositionX = Random.Range(-9.5f, 9.5f);
        
        //스폰위치
        spawnPosition = new Vector2(spawnPositionX, 9);

        Instantiate(prefabs[0], spawnPosition, transform.rotation);
    }
}

