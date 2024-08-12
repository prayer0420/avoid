using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class UIManager : MonoBehaviour
{

    public Button RetryButton;
    public Button ExitButton;
    public Image EndBG;
    public Canvas Canvas;
    public TextMeshProUGUI elapsedTimeText;
    float elapsedTime;
    private void Awake()
    {
        Canvas.gameObject.SetActive(false);
    }

    void Start()
    {
        
        RetryButton.onClick.AddListener(RetryButtonOnClick);
        ExitButton.onClick.AddListener(ExitButtonOnClick);
    }

    void Update()
    {
        // 게임 시작 후 경과 시간
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
}
