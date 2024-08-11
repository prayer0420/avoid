using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    private static Player instance;
    public static Player Instance
    {
        get
        {
            if (instance == null)
            {
                instance = FindObjectOfType<Player>();

            }
            return instance;
        }
    }

    private int hp;
    public int Hp 
    {
        get
        {
            return hp;
        }
        set
        { 
            hp = value;
            Debug.Log(hp);
            if (hp < 0)
              Debug.Log("end");
        }
    }
    public float moveDir;
    public float moveSpeed;

    void Start()
    {
        Hp = 100;
        moveDir = 0;
        moveSpeed = 10.0f;
    }

    // Update is called once per frame
    void Update()
    {
        moveDir = Input.GetAxis("Horizontal");

        transform.Translate(new Vector3(moveSpeed*moveDir * Time.deltaTime ,0,0));

    }


}
