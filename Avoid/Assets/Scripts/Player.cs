using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    private UIManager uIManager;


    //경험치 총량
    public  int _AllExpCount { get; private set; }

    //현재 레벨
    public int _level { get; private set; }


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

    void Start()
    {
        _level = 1;
        _AllExpCount = 0;

        Hp = 100;
        moveDirX = 0;
        moveDirY = 0;
        moveSpeed = 10.0f;

        GameManager.Instance.OnPlayerKillMonster += OnPlayerKillGrantExperience;
    }

    void Update()
    {
        moveDirX = Input.GetAxis("Horizontal");
        moveDirY = Input.GetAxis("Vertical");

        transform.Translate(new Vector3(moveSpeed*moveDirX * Time.deltaTime , moveSpeed * moveDirY * Time.deltaTime, 0));
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
            //레벨업!
            _level++;
            //레벨업에 필요한 경험치만큼을 빼줌
            _AllExpCount -= expToLevelUp[_level];
            Debug.Log("레벨 업!");
        }
    }
}
