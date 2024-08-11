using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{

    public float moveDir;
    public float moveSpeed;
    void Start()
    {
        moveDir = 0;
        moveSpeed = 10.0f;
    }

    // Update is called once per frame
    void Update()
    {
        moveDir = Input.GetAxis("Horizontal");

        transform.Translate(new Vector3(moveSpeed*moveDir * Time.deltaTime ,0,0));

    }


}
