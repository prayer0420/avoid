using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class Player : MonoBehaviour
{
    private UIManager uIManager;

    public GameObject missilePrefab; //미사일 프리팹
    public GameObject missileSpawnPoint; //마시일이 발사될 위치
    public float missileSpeed = 10f; 


    public Vector3 centerPosition;

    //경험치 총량
    public int _AllExpCount { get; private set; }
    CircleCollider2D circleCollider;
    //현재 레벨
    public int _level { get; private set; }
    public int Item {  get; private set; }

    public float direction;
    public int money { get; set; }
    //레벨업에 필요한 경험치 수치
    //private int expToLevelUp2 = 30;
    //private int expToLevelUp3 = 60;
    //private int expToLevelUp4 = 90;
    //private int expToLevelUp5 = 130;

    //배열로 Level 1~ Level 7까지 값 셋팅
    //ex) level1에서 레벨업하려면 30이 필요하다는 뜻
    private int[] expToLevelUp = { 0, 30, 60, 90, 130, 180, 270 };

    private int hp;
    public int Hp 
    {
        get
        {
            return hp;
        }
        set
        {
            hp = value;
            if (hp < 0)
            {
              Debug.Log("end");
              moveSpeed = 0;
              uIManager.Canvas.gameObject.SetActive(true);
            }

        }
    }
    private void Awake()
    {
        uIManager = FindObjectOfType<UIManager>();  // UIManager를 찾아서 참조
        if (uIManager == null)
        {
            Debug.LogError("UIManager를 찾을 수 없습니다!");
        }
    }
    public float moveDirX;
    public float moveDirY;
    public float moveSpeed;

    SpriteRenderer render;

    private Vector2 lastMoveDirection = Vector2.right; // 마지막 이동 방향 (초기값은 오른쪽)

    void Start()
    {
        render = GetComponent<SpriteRenderer>();

        _level = 1;
        _AllExpCount = 0;

        Hp = 100;
        moveDirX = 0;
        moveDirY = 0;
        moveSpeed = 10.0f;
        money = 0;
        GameManager.Instance.OnPlayerKillMonster += OnPlayerKillGrantExperience;

        circleCollider = GetComponent<CircleCollider2D>();
        //public Vector3 CenterPosition { get { return transform.position + Vector3.up * ColliderRadius; } }
        Debug.Log("centerPosition");

    }

    void Update()
    {
        //캐릭터 이동관련
        moveDirX = Input.GetAxis("Horizontal");
        moveDirY = Input.GetAxis("Vertical");

        if(moveDirX>0)
        {
            render.flipX = false;
            
        }
        else if(moveDirX<0)
        {
            render.flipX = true;
        }

        transform.Translate(new Vector3(moveSpeed*moveDirX * Time.deltaTime , moveSpeed * moveDirY * Time.deltaTime, 0));

        //UI관련
        UIManager.Instance.moneyText.text = $"Money: {money}";

        UIManager.Instance.ExpText.text = $"Exp: {_AllExpCount} / {expToLevelUp[_level]}";

        UIManager.Instance.LevelText.text = $"Level: {_level}";

        //카메라를 위한 센터포지션
        centerPosition = transform.position + Vector3.up * circleCollider.radius;

        //미사일 발사

        // 마지막 입력된 수평 또는 수직 방향을 저장
        if (moveDirX > 0)
        {
            lastMoveDirection = Vector2.right; // 오른쪽
        }
        else if (moveDirX < 0)
        {
            lastMoveDirection = Vector2.left; // 왼쪽
        }
        else if (moveDirY > 0)
        {
            lastMoveDirection = Vector2.up; // 위쪽
        }
        else if (moveDirY < 0)
        {
            lastMoveDirection = Vector2.down; // 아래쪽
        }

        if (Input.GetMouseButtonDown(0))
        {
            FireMisiile();
        }
    }

    public void FireMisiile()
    {
        GameObject go = Instantiate(missilePrefab, missileSpawnPoint.transform.position, Quaternion.identity);
        Rigidbody2D rb= go.GetComponent<Rigidbody2D>();
        rb.velocity = lastMoveDirection* missileSpeed;
        //Debug.Log($"Missile fired in direction: {lastMoveDirection} with speed: {missileSpeed}");
    }

    //돈을 주웠을때
    public void GetMoney()
    {

    }

    //플레이어가 몬스터를 죽였을때 부여하는 경험치 함수
    public void OnPlayerKillGrantExperience(Monster monster)
    {
        Debug.Log("경험치 획득");
        _AllExpCount += monster.expPoints;
        
        //경험치를 획득할 때 마다 레벨업이 가능한지 확인하는 함수 추가
        CheckLevel();
    }

    public void CheckLevel()
    {
        //현재 level이 레벨목록표의 레벨 범위안에 있어야하고
        //현재 경험치총량이 현재 레벨에서 레벨업에 필요한 경험치보다 같거나 크다면 
        while(_level < expToLevelUp.Length && _AllExpCount>= expToLevelUp[_level])
        {
            //레벨업에 필요한 경험치만큼을 빼줌
            _AllExpCount -= expToLevelUp[_level];
            //레벨업!
            _level++;
            Debug.Log("레벨 업!");
        }
    }


}
