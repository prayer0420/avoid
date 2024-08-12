using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    private UIManager uIManager;

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
            {
              Debug.Log("end");
              uIManager.Canvas.gameObject.SetActive(true);
            }

        }
    }
    private void Awake()
    {
        uIManager = FindObjectOfType<UIManager>();  // UIManager�� ã�Ƽ� ����
        if (uIManager == null)
        {
            Debug.LogError("UIManager�� ã�� �� �����ϴ�!");
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

    void Update()
    {
        moveDir = Input.GetAxis("Horizontal");

        transform.Translate(new Vector3(moveSpeed*moveDir * Time.deltaTime ,0,0));
    }
}
