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

    // üũ�� ���̾ ������ ����
    public LayerMask groundLayer;
    public LayerMask playerLayer;

    // �浹�� �߻��� �� ȣ��Ǵ� �޼���
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
