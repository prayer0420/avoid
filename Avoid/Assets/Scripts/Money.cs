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

    //player�� �����ߴٸ� �ڱ��ڽ��� �ı��ϰ� �÷��̾�� ���� ��
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
