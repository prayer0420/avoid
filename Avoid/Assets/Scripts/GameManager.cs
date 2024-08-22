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
    //충돌했을 때
    public delegate void PlayerWin(Monster monster); //대리자 타입 정의
    public PlayerWin OnPlayerKillMonster; //플레이어가 이겼을 때 구독자들에게 알림을 주는 대리자 변수 정의
}
