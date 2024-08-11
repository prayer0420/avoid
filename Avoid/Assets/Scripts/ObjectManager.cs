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
    float spawnTime = 2000;
    public void Start()
    {

    }
    // Update is called once per frame
    void Update()
    {
        sumtTime += Time.time;
        Debug.Log(sumtTime);
        if(sumtTime > spawnTime)
        {
            Spawn();   
            sumtTime = 0;
        }


    }

    void Spawn()
    {
        //생성주기
        //int spawnRand = Random.RandomRange(0, 100);

        //스폰위치X좌표 랜덤
        float spawnPositionX = Random.Range(-9.5f, 9.5f);
        
        //스폰위치
        spawnPosition = new Vector2(spawnPositionX, 9);

        Instantiate(prefabs[0], spawnPosition, transform.rotation);

    }

}

