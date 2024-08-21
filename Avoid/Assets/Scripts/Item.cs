using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Item : MonoBehaviour
{
    public LayerMask playerMask;

    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (playerMask == 1 << collision.gameObject.layer)
        {
            ItemManager.Instance.ItemCount += 1;
            Destroy(this.gameObject);

        }
    }
            
}
