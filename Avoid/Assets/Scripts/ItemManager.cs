using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemManager : MonoBehaviour
{
    private static ItemManager _instance;
    public static ItemManager Instance
    {
        get
        {
            if (_instance == null)
                _instance = FindObjectOfType<ItemManager>();
            return _instance;
        }
    }

    public bool IsItem;
    public int ItemCount {  get; set; }  

    void Start()
    {
        IsItem = false;
        ItemCount = 0;
    }

    // Update is called once per frame
    void Update()
    {

        if (ItemCount > 0)
        {
            IsItem = true;
            UIManager.Instance.ItemCountText.text = $"{ItemCount}";
        }
        else if(ItemCount<=0)
        {
            GameObject go = UIManager.Instance.ItemUI.gameObject;
            go.SetActive(false);
            IsItem = false;
        }

        if(IsItem)
        {
            //Item UI활성화
            GameObject go = UIManager.Instance.ItemUI.gameObject;
            go.SetActive(true);
            UseItem();
        }
    }

    public void UseItem()
    {
        if(Input.GetKeyDown(KeyCode.Space))
        {
            //아이템 개수 감소
            ItemCount -= 1;
            ObjectManager.Instance.AllDelete();
        }
    }
}
