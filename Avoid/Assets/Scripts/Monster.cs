using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum DropItem
{
    Money,
    Item
}
public class Monster : MonoBehaviour
{
    int dropItem = (int)DropItem.Money;
    public int randomSpeed;
    public int expPoints; //죽으면 플레이어에게 줄 경험치 값
    public DropItem[] dropItemArr;
    void Start()
    {
        expPoints = 10;
        dropItemArr = (DropItem[])System.Enum.GetValues(typeof(DropItem));
    }

    private int hp = 30;
    public int Hp
    {
        get
        {
            return hp;
        }
        set 
        { 
            hp = value; 
            if(hp<0)
            {
                hp = 0;
                Debug.Log("DIe");
                OnDie();
            }
        }
    }

    void Update()
    {
       // transform.position += Vector3.down * randomSpeed * Time.deltaTime;
    }

    public void OnDie()
    {
        //플레이어가 이겼음을 구독자들에게 알림
        //플레이어는 이겼으므로, 구독자에서 경험치를 올리자.
        GameManager.Instance.OnPlayerKillMonster(this);


        //몬스터는 랜덤으로 돈, 아이템(필살기)을 떨굼
        //랜덤 돌려서 드롭할 아이템 결정하기
        int random = UnityEngine.Random.RandomRange(0, dropItemArr.Length);
        DropItem dropitem = dropItemArr[random];
        //아이템 드롭하기
        DropedItem(dropitem);


        //플레이어가 적과 충돌하면 플레이어가 이긴 것으로, 몬스터를 파괴함
        Debug.Log("destroy");
        //몬스터의 총 수 1개 줄임
        ObjectManager.Instance.capacity--;
        Destroy(this.gameObject);
    }

    // 체크할 레이어를 저장할 변수
    public LayerMask groundLayer;
    public LayerMask playerLayer;

    // 충돌이 발생할 때 호출되는 메서드
    public void OnTriggerEnter2D(Collider2D collision)
    {
        if (playerLayer == 1 << collision.gameObject.layer)
        {
            Debug.Log("DIe");
        }
    }


    //아이템 드롭
    public void DropedItem(DropItem dropItem)
    {
        //Resources폴더 안에 dropItem이름에 맞는 오브젝트 가져오기
        GameObject go = Resources.Load<GameObject>($"{dropItem}");

        //이름에 맞는 오브젝트가 있다면
        if(go !=null)
        {
            //자기자신 기준으로 x+3, y+5떨어진 만큼에 아이템 생성
            //Vector2 position = new Vector3(this.transform.position.x+3, this.transform.position.y+5, 5);
            GameObject instance = Instantiate(go, this.transform.position, Quaternion.identity);
            Debug.Log($"Instantiate : {instance.name}");
        }
        else
        {
            Debug.LogError("Prefab with name " + dropItem + " not found in Resources folder.");
        }
    }
}
