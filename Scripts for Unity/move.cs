using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;
using System;

public class move : MonoBehaviour
{

    public float speed;

    int temp=0;

    private float amountToMove;

    SerialPort sp = new SerialPort("COM4", 9600);

    // Use this for initialization
    void Start()
    {
        sp.Open();
        sp.ReadTimeout = 1;
        

    }

    // Update is called once per frame
    void Update()
    {

        amountToMove = speed * Time.deltaTime;

        if (sp.IsOpen)
        {
            try
            {
                MoveObject(sp.ReadByte());
            }
            catch(System.Exception)
            {

            }
        }
    }
    void MoveObject(int Direction)
    {

        if (Direction != 0)
        {

            if (Direction < temp)
            {
                transform.Translate(Vector3.left * amountToMove, Space.World);
            }
            if (Direction >= temp)
            {
                transform.Translate(Vector3.right * amountToMove, Space.World);
                temp = Direction;
            }
            Debug.Log(Direction);
        }

    }
}

