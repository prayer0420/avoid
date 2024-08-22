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
    public int expPoints; //������ �÷��̾�� �� ����ġ ��
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
        //�÷��̾ �̰����� �����ڵ鿡�� �˸�
        //�÷��̾�� �̰����Ƿ�, �����ڿ��� ����ġ�� �ø���.
        GameManager.Instance.OnPlayerKillMonster(this);


        //���ʹ� �������� ��, ������(�ʻ��)�� ����
        //���� ������ ����� ������ �����ϱ�
        int random = UnityEngine.Random.RandomRange(0, dropItemArr.Length);
        DropItem dropitem = dropItemArr[random];
        //������ ����ϱ�
        DropedItem(dropitem);


        //�÷��̾ ���� �浹�ϸ� �÷��̾ �̱� ������, ���͸� �ı���
        Debug.Log("destroy");
        //������ �� �� 1�� ����
        ObjectManager.Instance.capacity--;
        Destroy(this.gameObject);
    }

    // üũ�� ���̾ ������ ����
    public LayerMask groundLayer;
    public LayerMask playerLayer;

    // �浹�� �߻��� �� ȣ��Ǵ� �޼���
    public void OnTriggerEnter2D(Collider2D collision)
    {
        if (playerLayer == 1 << collision.gameObject.layer)
        {
            Debug.Log("DIe");
        }
    }


    //������ ���
    public void DropedItem(DropItem dropItem)
    {
        //Resources���� �ȿ� dropItem�̸��� �´� ������Ʈ ��������
        GameObject go = Resources.Load<GameObject>($"{dropItem}");

        //�̸��� �´� ������Ʈ�� �ִٸ�
        if(go !=null)
        {
            //�ڱ��ڽ� �������� x+3, y+5������ ��ŭ�� ������ ����
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
