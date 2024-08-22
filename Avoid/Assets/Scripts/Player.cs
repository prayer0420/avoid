using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class Player : MonoBehaviour
{
    private UIManager uIManager;

    public GameObject missilePrefab; //�̻��� ������
    public GameObject missileSpawnPoint; //�������� �߻�� ��ġ
    public float missileSpeed = 10f; 


    public Vector3 centerPosition;

    //����ġ �ѷ�
    public int _AllExpCount { get; private set; }
    CircleCollider2D circleCollider;
    //���� ����
    public int _level { get; private set; }
    public int Item {  get; private set; }

    public float direction;
    public int money { get; set; }
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

    SpriteRenderer render;

    private Vector2 lastMoveDirection = Vector2.right; // ������ �̵� ���� (�ʱⰪ�� ������)

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
        //ĳ���� �̵�����
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

        //UI����
        UIManager.Instance.moneyText.text = $"Money: {money}";

        UIManager.Instance.ExpText.text = $"Exp: {_AllExpCount} / {expToLevelUp[_level]}";

        UIManager.Instance.LevelText.text = $"Level: {_level}";

        //ī�޶� ���� ����������
        centerPosition = transform.position + Vector3.up * circleCollider.radius;

        //�̻��� �߻�

        // ������ �Էµ� ���� �Ǵ� ���� ������ ����
        if (moveDirX > 0)
        {
            lastMoveDirection = Vector2.right; // ������
        }
        else if (moveDirX < 0)
        {
            lastMoveDirection = Vector2.left; // ����
        }
        else if (moveDirY > 0)
        {
            lastMoveDirection = Vector2.up; // ����
        }
        else if (moveDirY < 0)
        {
            lastMoveDirection = Vector2.down; // �Ʒ���
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

    //���� �ֿ�����
    public void GetMoney()
    {

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
            //�������� �ʿ��� ����ġ��ŭ�� ����
            _AllExpCount -= expToLevelUp[_level];
            //������!
            _level++;
            Debug.Log("���� ��!");
        }
    }


}
