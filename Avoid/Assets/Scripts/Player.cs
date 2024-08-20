using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    private UIManager uIManager;


    //����ġ �ѷ�
    public  int _AllExpCount { get; private set; }

    //���� ����
    public int _level { get; private set; }


    //�������� �ʿ��� ����ġ ��ġ
    //private int expToLevelUp2 = 30;
    //private int expToLevelUp3 = 60;
    //private int expToLevelUp4 = 90;
    //private int expToLevelUp5 = 130;

    //�迭�� Level 1~ Level 7���� �� ����
    //ex) level1���� �������Ϸ��� 30�� �ʿ��ϴٴ� ��
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
        uIManager = FindObjectOfType<UIManager>();  // UIManager�� ã�Ƽ� ����
        if (uIManager == null)
        {
            Debug.LogError("UIManager�� ã�� �� �����ϴ�!");
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

    //�÷��̾ ���͸� �׿����� �ο��ϴ� ����ġ �Լ�
    public void OnPlayerKillGrantExperience(Monster monster)
    {
        Debug.Log("����ġ ȹ��");
        _AllExpCount += monster.expPoints;
        //����ġ�� ȹ���� �� ���� �������� �������� Ȯ���ϴ� �Լ� �߰�
        CheckLevel();
    }

    public void CheckLevel()
    {
        //���� level�� �������ǥ�� ���� �����ȿ� �־���ϰ�
        //���� ����ġ�ѷ��� ���� �������� �������� �ʿ��� ����ġ���� ���ų� ũ�ٸ� 
        while(_level < expToLevelUp.Length && _AllExpCount>= expToLevelUp[_level])
        {
            //������!
            _level++;
            //�������� �ʿ��� ����ġ��ŭ�� ����
            _AllExpCount -= expToLevelUp[_level];
            Debug.Log("���� ��!");
        }
    }
}
