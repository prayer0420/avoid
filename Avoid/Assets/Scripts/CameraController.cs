using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{
    public Player _target;

    public Player Target
    {
        get { return _target; }
        set { _target = value; }
    }

    private void Start()
    {
        Camera.main.orthographicSize = 9.0f;
    }

    private void LateUpdate()
    {
        if (Target == null) return;

        Vector3 targetPosition = new Vector3(Target.centerPosition.x, Target.centerPosition.y, -10f);
        transform.position = targetPosition;
        //Debug.Log(targetPosition);
    }

}
