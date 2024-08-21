using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Money : MonoBehaviour
{
    // Start is called before the first frame update
    public LayerMask playerMask;
    public int value;
    void Start()
    {
        value = 10;
    }


    // Update is called once per frame
    void Update()
    {
        

    }

    //player와 접촉했다면 자기자신을 파괴하고 플레이어에게 돈을 줌
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(playerMask == 1<<collision.gameObject.layer)
        {
            Player player = collision.gameObject.GetComponent<Player>();

            player.money += value;

            
            Destroy(this.gameObject);
        }

    }
}
