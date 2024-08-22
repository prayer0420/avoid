using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    static private GameManager _instance;
    static public GameManager Instance
    {
        get
        {
            if (_instance == null)
            {
                _instance = FindObjectOfType<GameManager>();
            }
            return _instance;
        }
    }

    void Start()
    {
 
    }

    void Update()
    {
        
     
    }
    //�浹���� ��
    public delegate void PlayerWin(Monster monster); //�븮�� Ÿ�� ����
    public PlayerWin OnPlayerKillMonster; //�÷��̾ �̰��� �� �����ڵ鿡�� �˸��� �ִ� �븮�� ���� ����
}
