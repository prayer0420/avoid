using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class UIManager : MonoBehaviour
{
    private static UIManager instance;
    public static UIManager Instance
    {
        get
        {
            if (instance == null)
                instance = FindObjectOfType<UIManager>();
            return instance;
        }
    }


    public Button RetryButton;
    public Button ExitButton;
    public Image EndBG;
    public Canvas Canvas;
    public TextMeshProUGUI elapsedTimeText;
    public TextMeshProUGUI stageText;
    float elapsedTime;
    public TextMeshProUGUI moneyText;
    public TextMeshProUGUI ItemCountText;
    public Image ItemUI;
    public TextMeshProUGUI LevelText;
    public TextMeshProUGUI ExpText;

    private void Awake()
    {
        Canvas.gameObject.SetActive(false);
    }

    void Start()
    {
        RetryButton.onClick.AddListener(RetryButtonOnClick);
        ExitButton.onClick.AddListener(ExitButtonOnClick);
        //StageManager.Instance.OnStageCleared += ShowStageClearMessage;
        Debug.Log($"{this.GetType().Name}.{nameof(ShowStageClearMessage)} has subscribed to OnStageChanged.");

    }

    void Update()
    {
        // ���� ���� �� ��� �ð�
        elapsedTime = TimeManager.Instance().elpasedTime;

        elapsedTimeText.text = $"Time: {elapsedTime:F1}s";
        if(elapsedTime > 50 )
        {
            elapsedTimeText.color = Color.red;
            elapsedTimeText.fontSize = 50;
        }
    }

    public void RetryButtonOnClick()
    {
        Canvas.gameObject.SetActive(false);
        TimeManager.Instance().ResetTime();
        SceneManager.LoadScene("GameScene");
    }

    public void ExitButtonOnClick()
    {
        Canvas.gameObject.SetActive(false);
        SceneManager.LoadScene("TitleScene");
    }

    public void ShowStageClearMessage(int StageLevel)
    {
        //Ÿ��UI��� ����
        elapsedTimeText.gameObject.SetActive(false);

        stageText.gameObject.SetActive(true);


        //StageŬ����! �����ֱ�
        stageText.text = $"Stage{StageLevel} Clear!!";
    }

    public IEnumerator ShowStageChangeMessage(int StageLevel)
    {
        stageText.text = $"Stage{StageLevel}Move!";
        stageText.gameObject.SetActive(true);

        yield return new WaitForSecondsRealtime(1.0f);

        //Ÿ��UI �ѱ�
        stageText.text = " ";
        stageText.gameObject.SetActive(false);
        elapsedTimeText.gameObject.SetActive(true);
    }


}
