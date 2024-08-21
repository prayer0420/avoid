using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemDrop : MonoBehaviour
{
    //public float dropSpeed = 5f;
    //public float gravity = -9.8f;
    //public float dropAngle = 45f;

    //private Vector2 velocity; //아이템 속도
    //private Vector2 startPosition; //시작 위치
    //private bool isDropping = false; //드롭 상태

    //void Start()
    //{
    //    startPosition = transform.position;
    //    float radius = dropAngle * Mathf.Rad2Deg; //각도를 라디안으로 변환
    //    velocity = new Vector2(dropSpeed * Mathf.Cos(radius), dropSpeed * Mathf.Sin(radius)); //초기속도 설정
    //    isDropping = true;
    //}

    //// Update is called once per frame
    //void Update()
    //{

    //    if(isDropping)
    //    {
    //        //중력 적용
    //        velocity.y += gravity * Time.deltaTime;

    //        //시간에 따른 위치 업데이트
    //        Vector2 currentPosition = transform.position;
    //        currentPosition += velocity * Time.deltaTime;
    //        transform.position = currentPosition;

    //        //땅에 닿았을때 
    //        if(transform.position.y <= startPosition.y)
    //        {
    //            isDropping = false;
    //            transform.position = new Vector2(transform.position.x, transform.position.y);// 땅에 고정
    //        }
    //    }

    //}

    public float dropSpeed = 5f; // 초기 속도
    public float dropAngle = 45f; // 드롭 각도 (도 단위)
    private Vector2 startPosition; //시작 위치
    public float decelerationRate = 0.98f;


    private Rigidbody2D rb;
    CircleCollider2D circleCollider2D;
    BoxCollider2D boxCollider2D;

    void Start()
    {
        // Rigidbody2D 컴포넌트를 가져오기
        rb = GetComponent<Rigidbody2D>();

        // 각도를 라디안으로 변환
        float radians = dropAngle * Mathf.Deg2Rad;

        // 초기 속도 벡터 계산
        Vector2 initialVelocity = new Vector2(dropSpeed * Mathf.Cos(radians), dropSpeed * Mathf.Sin(radians));

        // Rigidbody2D에 초기 속도 설정
        rb.velocity = initialVelocity;
        startPosition = transform.position;


        //처음 시작할때 충돌기능 끄기
        //CircleCollider갖고있는지 , BoxCollider갖고있는지 확인
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

            //x와y의 속도 천천히 감속
            rb.velocity = new Vector2(rb.velocity.x * decelerationRate, rb.velocity.y * decelerationRate);


            if (Mathf.Abs(rb.velocity.x) < 0.1f)
            {
                rb.velocity = Vector2.zero;
                rb.isKinematic = true; // 완전히 멈추게 설정

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
