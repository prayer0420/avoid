using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StageManager : MonoBehaviour
{
    private static StageManager instance;
    public static StageManager Instance
    {
        get
        {
            if (instance == null)
                instance = FindObjectOfType<StageManager>();
            return instance;
        }
    }

    private  float stageDuration = 40f; //각 스테이지의 지속 시간
    private float transitionDuration = 3f; // 각 스테이지 전환시 대기 시간
    public int StageLevel = 1; //현재 스테이지 레벨

    private float elapsedTime;
    public event Action<int> OnStageCleared;

    private bool isTransitioning = false; // 스테이지 전환 중인지 여부를 나타내는 플래그

    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        elapsedTime = TimeManager.Instance().elpasedTime;

        //stageDuration초 넘어가면 잠깐 멈췄다가 다음스테이지로
        if (elapsedTime > stageDuration && isTransitioning == false)
        {
            isTransitioning = true;
            StartCoroutine(TransitionToNextStage());
        }
    }

    IEnumerator TransitionToNextStage()
    {

        //스테이지 전환 동안 게임을 멈추기
        Time.timeScale = 0f;

        OnStageCleared?.Invoke(StageLevel);

        //transitionDuration만큼 기다렸다가 다음 코드 실행
        yield return new WaitForSecondsRealtime(transitionDuration);

        UIManager.Instance.stageText.gameObject.SetActive(false);
        StageLevel++;

        yield return StartCoroutine(UIManager.Instance.ShowStageChangeMessage(StageLevel));
        //스테이지 설정
        SetupNewStage();
        
        //게임 재시작
        Time.timeScale = 1f;

        isTransitioning = false;
        Debug.Log($"{isTransitioning}");


    }

    //새로운 스테이지 난이도 설정
    public void SetupNewStage()
    {


        //elapsedTime 초기화
        TimeManager.Instance().ResetTime();

        //StageLevel++;

        //스테이지 레벨에 따라 스폰되는 양 증가  
        ObjectManager.Instance.spawnCount = StageLevel;
        ObjectManager.Instance.spawnTime = 1.0f;
    }
}
