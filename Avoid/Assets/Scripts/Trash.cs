using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Trash : MonoBehaviour
{
    public int randomSpeed;

    void Start()
    {
    }

    void Update()
    {
        transform.position += Vector3.down * randomSpeed * Time.deltaTime;

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
            Player player = collision.gameObject.GetComponent<Player>();
            player.Hp -= 10;
        }
    }
}
