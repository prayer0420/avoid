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

    Monster _Monster;
    public DropItem[] dropItemArr;

    //������ ������
    public GameObject[] prefabs;
    //������ ��ġ
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
        dropItemArr = (DropItem[])System.Enum.GetValues(typeof(DropItem));
        _Monster = FindObjectOfType<Monster>(); 

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

        //�������� ��ŭ ����(� �������� ���������� ���� ����)
        for (int i = 0; i < spawnCount; i++)
        {
            //������ġX��ǥ ����
            float spawnPositionX = Random.Range(-9.0f, 9.0f);
            float spawnPositionY = Random.Range(-4.0f, 4.0f);
        
            //������ġ
            spawnPosition = new Vector2(spawnPositionX, spawnPositionY);
            GameObject go = Instantiate(prefabs[i], spawnPosition, Quaternion.identity);
            trash = go.GetComponent<Monster>();
            capacity++;
        }
    }

    public void AllDelete()
    {
        GameObject[] monsters = GameObject.FindGameObjectsWithTag("Monster");
        foreach (GameObject monster in monsters)
        {
            ObjectManager.Instance.capacity--;
            int random = UnityEngine.Random.RandomRange(0, dropItemArr.Length);
            DropItem dropitem = dropItemArr[random];
            //������ ����ϱ�
            Monster _monster = monster.GetComponent<Monster>();
            _monster.DropedItem(dropitem);
            GameManager.Instance.OnPlayerKillMonster(_monster);
            Destroy(monster.gameObject);
        }
    }
}

