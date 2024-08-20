using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Monster : MonoBehaviour
{
    public int randomSpeed;
    public int expPoints; //죽으면 플레이어에게 줄 경험치 값
    void Start()
    {
        expPoints = 10;
    }

    void Update()
    {
       // transform.position += Vector3.down * randomSpeed * Time.deltaTime;

    }

    // 체크할 레이어를 저장할 변수
    public LayerMask groundLayer;
    public LayerMask playerLayer;

    // 충돌이 발생할 때 호출되는 메서드
    public void OnTriggerEnter2D(Collider2D collision)
    {
        if (playerLayer == 1 << collision.gameObject.layer)
        {
            Player player = collision.gameObject.GetComponent<Player>();
            //플레이어가 이겼음을 구독자들에게 알림
            //플레이어는 이겼으므로, 구독자에서 경험치를 올리자.
            GameManager.Instance.OnPlayerKillMonster(this);


            //몬스터는 랜덤으로 돈, 아이템(필살기)을 떨굼



            //랜덤으로 돌려서 UI

            //플레이어가 적과 충돌하면 플레이어가 이긴 것으로, 몬스터를 파괴함
            Debug.Log("destroy");
            //몬스터의 총 수 1개 줄임
            ObjectManager.Instance.capacity--;
            Destroy(this.gameObject);
        }
    }
}
