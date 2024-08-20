using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Monster : MonoBehaviour
{
    public int randomSpeed;
    public int expPoints; //������ �÷��̾�� �� ����ġ ��
    void Start()
    {
        expPoints = 10;
    }

    void Update()
    {
       // transform.position += Vector3.down * randomSpeed * Time.deltaTime;

    }

    // üũ�� ���̾ ������ ����
    public LayerMask groundLayer;
    public LayerMask playerLayer;

    // �浹�� �߻��� �� ȣ��Ǵ� �޼���
    public void OnTriggerEnter2D(Collider2D collision)
    {
        if (playerLayer == 1 << collision.gameObject.layer)
        {
            Player player = collision.gameObject.GetComponent<Player>();
            //�÷��̾ �̰����� �����ڵ鿡�� �˸�
            //�÷��̾�� �̰����Ƿ�, �����ڿ��� ����ġ�� �ø���.
            GameManager.Instance.OnPlayerKillMonster(this);


            //���ʹ� �������� ��, ������(�ʻ��)�� ����



            //�������� ������ UI

            //�÷��̾ ���� �浹�ϸ� �÷��̾ �̱� ������, ���͸� �ı���
            Debug.Log("destroy");
            //������ �� �� 1�� ����
            ObjectManager.Instance.capacity--;
            Destroy(this.gameObject);
        }
    }
}
