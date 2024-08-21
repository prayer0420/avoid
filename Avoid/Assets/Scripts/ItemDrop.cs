using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemDrop : MonoBehaviour
{
    //public float dropSpeed = 5f;
    //public float gravity = -9.8f;
    //public float dropAngle = 45f;

    //private Vector2 velocity; //������ �ӵ�
    //private Vector2 startPosition; //���� ��ġ
    //private bool isDropping = false; //��� ����

    //void Start()
    //{
    //    startPosition = transform.position;
    //    float radius = dropAngle * Mathf.Rad2Deg; //������ �������� ��ȯ
    //    velocity = new Vector2(dropSpeed * Mathf.Cos(radius), dropSpeed * Mathf.Sin(radius)); //�ʱ�ӵ� ����
    //    isDropping = true;
    //}

    //// Update is called once per frame
    //void Update()
    //{

    //    if(isDropping)
    //    {
    //        //�߷� ����
    //        velocity.y += gravity * Time.deltaTime;

    //        //�ð��� ���� ��ġ ������Ʈ
    //        Vector2 currentPosition = transform.position;
    //        currentPosition += velocity * Time.deltaTime;
    //        transform.position = currentPosition;

    //        //���� ������� 
    //        if(transform.position.y <= startPosition.y)
    //        {
    //            isDropping = false;
    //            transform.position = new Vector2(transform.position.x, transform.position.y);// ���� ����
    //        }
    //    }

    //}

    public float dropSpeed = 5f; // �ʱ� �ӵ�
    public float dropAngle = 45f; // ��� ���� (�� ����)
    private Vector2 startPosition; //���� ��ġ
    public float decelerationRate = 0.98f;


    private Rigidbody2D rb;
    CircleCollider2D circleCollider2D;
    BoxCollider2D boxCollider2D;

    void Start()
    {
        // Rigidbody2D ������Ʈ�� ��������
        rb = GetComponent<Rigidbody2D>();

        // ������ �������� ��ȯ
        float radians = dropAngle * Mathf.Deg2Rad;

        // �ʱ� �ӵ� ���� ���
        Vector2 initialVelocity = new Vector2(dropSpeed * Mathf.Cos(radians), dropSpeed * Mathf.Sin(radians));

        // Rigidbody2D�� �ʱ� �ӵ� ����
        rb.velocity = initialVelocity;
        startPosition = transform.position;


        //ó�� �����Ҷ� �浹��� ����
        //CircleCollider�����ִ��� , BoxCollider�����ִ��� Ȯ��
        if(this.gameObject.GetComponent<CircleCollider2D>())
        {
            circleCollider2D = this.GetComponent<CircleCollider2D>();
            circleCollider2D.enabled = false;
        }
        else if(this.gameObject.GetComponent<BoxCollider2D>())
        {
            boxCollider2D= this.GetComponent<BoxCollider2D>();
            boxCollider2D.enabled = false;
        }


    }

    private void Update()
    {
        if(transform.position.y <= startPosition.y)
        {
            transform.position = new Vector2(transform.position.x, startPosition.y);

            //x��y�� �ӵ� õõ�� ����
            rb.velocity = new Vector2(rb.velocity.x * decelerationRate, rb.velocity.y * decelerationRate);


            if (Mathf.Abs(rb.velocity.x) < 0.1f)
            {
                rb.velocity = Vector2.zero;
                rb.isKinematic = true; // ������ ���߰� ����

                if (this.gameObject.GetComponent<CircleCollider2D>())
                {
                    circleCollider2D.enabled = true;
                }
                else if (this.gameObject.GetComponent<BoxCollider2D>())
                {
                    boxCollider2D = this.GetComponent<BoxCollider2D>();
                    boxCollider2D.enabled = true;
                }
            }

        }
    }
}
