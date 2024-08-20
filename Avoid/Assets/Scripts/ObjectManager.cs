using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting.Antlr3.Runtime.Tree;
using UnityEngine;

public class ObjectManager : MonoBehaviour
{
    private static ObjectManager instance;
    public static ObjectManager Instance
    {
        get
        {
            if (instance == null)
                instance = FindObjectOfType<ObjectManager>();
            return instance;
        }
    }

    //생성할 프리팹
    public GameObject[] prefabs;
    //생성할 위치
    public Vector2 spawnPosition;

    float sumtTime;
    public float spawnTime;
    float elapsedTime;
    public int spawnCount;
    public int maxSpeed = 10;
    Monster trash;
    public int capacity;
    public void Start()
    {
        spawnTime = 2.0f;
        capacity = 0;

    }
    // Update is called once per frame
    void Update()
    {
        elapsedTime = TimeManager.Instance().elpasedTime;

        sumtTime += Time.deltaTime;

        if(sumtTime > spawnTime && capacity<6)
        {
            Spawn();   
            sumtTime = 0;
            
        }


    }

    void Spawn()
    {

        //생성수량 만큼 생성(어떤 프리팹을 생성할지도 선택 가능)
        for (int i = 0; i < spawnCount; i++)
        {
            //스폰위치X좌표 랜덤
            float spawnPositionX = Random.Range(-9.0f, 9.0f);
            float spawnPositionY = Random.Range(-4.0f, 4.0f);
        
            //스폰위치
            spawnPosition = new Vector2(spawnPositionX, spawnPositionY);
            GameObject go = Instantiate(prefabs[i], spawnPosition, Quaternion.identity);
            trash = go.GetComponent<Monster>();
            capacity++;
        }
    }

}

