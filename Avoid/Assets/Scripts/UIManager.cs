using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class UIManager : MonoBehaviour
{

    public Button RetryButton;
    public Button ExitButton;
    public Image EndBG;
    public Canvas Canvas;


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
        
    }

    public void RetryButtonOnClick()
    {
        Canvas.gameObject.SetActive(false);
        SceneManager.LoadScene("GameScene");
    }

    public void ExitButtonOnClick()
    {
        Canvas.gameObject.SetActive(false);
        SceneManager.LoadScene("TitleScene");
    }
}
