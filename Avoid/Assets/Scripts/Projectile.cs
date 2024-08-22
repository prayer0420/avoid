using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Projectile : MonoBehaviour
{
    Rigidbody2D rb;
    public float speed = 10f; // 미사일의 이동 속도
    public float lifetime = 5f; // 미사일이 존재하는 시간

    void Start()
    {
        Destroy(gameObject, lifetime);
    }

    // Update is called once per frame
    void Update()
    {
        transform.Translate(Vector3.forward * speed * Time.deltaTime);
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.gameObject.CompareTag("Monster"))
        {
            Debug.Log("몬스터공격");
            Monster monster =  collision.gameObject.GetComponent<Monster>();
            monster.Hp -= 10;
            Destroy(gameObject);
        }
    }
}
