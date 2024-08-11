using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectManager : MonoBehaviour
{
    //������ ������
    public GameObject[] prefabs;
    //������ ��ġ
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
        //�����ֱ�
        //int spawnRand = Random.RandomRange(0, 100);

        //������ġX��ǥ ����
        float spawnPositionX = Random.Range(-9.5f, 9.5f);
        
        //������ġ
        spawnPosition = new Vector2(spawnPositionX, 9);

        Instantiate(prefabs[0], spawnPosition, transform.rotation);

    }

}

