using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class TitleUIManager : MonoBehaviour
{

    public Button GameStart;
    public Button EndGame;


    void Start()
    {
        GameStart.onClick.AddListener(GameStartOnClick);
        EndGame.onClick.AddListener(EndGameOnClick);
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void GameStartOnClick()
    {
        SceneManager.LoadScene("GameScene");
    }

    void EndGameOnClick()
    {
        #if UNITY_EDITOR
                UnityEditor.EditorApplication.isPlaying = false;
        #else
            Application.Quit();
        #endif
    }
}
