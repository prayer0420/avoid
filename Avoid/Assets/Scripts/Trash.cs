using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Trash : MonoBehaviour
{
    void Start()
    {
    }

    void Update()
    {
        
    }

    // 체크할 레이어를 저장할 변수
    public LayerMask groundLayer;
    public LayerMask playerLayer;

    // 충돌이 발생할 때 호출되는 메서드
    public void OnTriggerEnter2D(Collider2D collision)
    {
        if(groundLayer == 1<<collision.gameObject.layer)
        {
            Destroy(this.gameObject);
        }

        if (playerLayer == 1 << collision.gameObject.layer)
        {
            Player.Instance.Hp -= 10;
        }
    }
}
