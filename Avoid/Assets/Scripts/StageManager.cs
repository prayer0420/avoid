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

    private  float stageDuration = 40f; //�� ���������� ���� �ð�
    private float transitionDuration = 3f; // �� �������� ��ȯ�� ��� �ð�
    public int StageLevel = 1; //���� �������� ����

    private float elapsedTime;
    public event Action<int> OnStageCleared;

    private bool isTransitioning = false; // �������� ��ȯ ������ ���θ� ��Ÿ���� �÷���

    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        elapsedTime = TimeManager.Instance().elpasedTime;

        //stageDuration�� �Ѿ�� ��� ����ٰ� ��������������
        if (elapsedTime > stageDuration && isTransitioning == false)
        {
            isTransitioning = true;
            StartCoroutine(TransitionToNextStage());
        }
    }

    IEnumerator TransitionToNextStage()
    {

        //�������� ��ȯ ���� ������ ���߱�
        Time.timeScale = 0f;

        OnStageCleared?.Invoke(StageLevel);

        //transitionDuration��ŭ ��ٷȴٰ� ���� �ڵ� ����
        yield return new WaitForSecondsRealtime(transitionDuration);

        UIManager.Instance.stageText.gameObject.SetActive(false);
        StageLevel++;

        yield return StartCoroutine(UIManager.Instance.ShowStageChangeMessage(StageLevel));
        //�������� ����
        SetupNewStage();
        
        //���� �����
        Time.timeScale = 1f;

        isTransitioning = false;
        Debug.Log($"{isTransitioning}");


    }

    //���ο� �������� ���̵� ����
    public void SetupNewStage()
    {


        //elapsedTime �ʱ�ȭ
        TimeManager.Instance().ResetTime();

        //StageLevel++;

        //�������� ������ ���� �����Ǵ� �� ����  
        ObjectManager.Instance.spawnCount = StageLevel;
        ObjectManager.Instance.spawnTime = 1.0f;
    }
}
