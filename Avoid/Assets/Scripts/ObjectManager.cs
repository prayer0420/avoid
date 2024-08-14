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

    //������ ������
    public GameObject[] prefabs;
    //������ ��ġ
    public Vector2 spawnPosition;

    float sumtTime;
    public float spawnTime;
    float elapsedTime;
    public int spawnCount;
    public int maxSpeed = 10;
    Trash trash;
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

        sumtTime += Time.deltaTime;

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
            spawnTime = 0.25f;
    }

    void Spawn()
    {

        //�������� ��ŭ ����(� �������� ���������� ���� ����)
        for (int i = 0; i < spawnCount; i++)
        {
            //������ġX��ǥ ����
            float spawnPositionX = Random.Range(-9.5f, 9.5f);
        
            //������ġ
            spawnPosition = new Vector2(spawnPositionX, 9);
            GameObject go = Instantiate(prefabs[i], spawnPosition, Quaternion.identity);
            trash = go.GetComponent<Trash>();
            trash.randomSpeed = Random.Range(5, maxSpeed * i + 10);

        }
    }

    void StageChangeHandler()
    {
        
    }
}

