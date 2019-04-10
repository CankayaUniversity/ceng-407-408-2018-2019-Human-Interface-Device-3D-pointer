using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;
using System;
using UnityEngine.UI;

public class move : MonoBehaviour
{
    public Text BackText { get; set; }
    public Text TopText { get; set; }
    public Text RightText { get; set; }

    private static Vector3 BackSensor { get; set; }
    private static Vector3 TopSensor { get; set; }
    private static Vector3 RightSensor { get; set; }

    SerialPort sp = new SerialPort("COM4", 9600);

    // Use this for initialization
    void Start()
    {
        // the order in SerialPort > Back Top Right
        BackSensor = new Vector3(0, 37, 37); // returns Y
        TopSensor = new Vector3(37, 37, 50); // returns Z
        RightSensor = new Vector3(37, 0, 37); // returns X

        sp.Open();
        sp.ReadTimeout = 1;
    }

    // Update is called once per frame
    void Update()
    {

        if (sp.IsOpen)
        {
            try
            {
                float[] L = new float[3];
                float value = sp.ReadByte();
                L[0] = value;
                BackText.text = value.ToString();

                value = sp.ReadByte();
                L[1] = value;
                TopText.text = value.ToString();

                value = sp.ReadByte();
                L[2] = value;
                RightText.text = value.ToString();

                Vector3 Loc = trilaterate2(L);

                MoveObject(Loc);


            }
            catch (System.Exception)
            {

            }
        }
    }
    void MoveObject(Vector3 Loc)
    {
        


    }

    public static Vector3 trilaterate2(float[] L)
    {
        //caluculate coords in plane of stations
        double LB1 = Math.Sqrt((TopSensor.x - BackSensor.x) * (TopSensor.x - BackSensor.x) + (TopSensor.y - BackSensor.y) * (TopSensor.y - BackSensor.y) + (TopSensor.z - BackSensor.z) * (TopSensor.z - BackSensor.z));
        double LB2 = Math.Sqrt((RightSensor.x - TopSensor.x) * (RightSensor.x - TopSensor.x) + (RightSensor.y - TopSensor.y) * (RightSensor.y - TopSensor.y) + (RightSensor.z - TopSensor.z) * (RightSensor.z - TopSensor.z));
        double LB3 = Math.Sqrt((BackSensor.x - RightSensor.x) * (BackSensor.x - RightSensor.x) + (BackSensor.y - RightSensor.y) * (BackSensor.y - RightSensor.y) + (BackSensor.z - RightSensor.z) * (BackSensor.z - RightSensor.z));

        double X = (L[0] * L[0] - L[1] * L[1] + LB1 * LB1) / (2 * LB1);
        double C1 = Math.Sqrt(L[0] * L[0] - X * X);

        if (L[0] * L[0] - X * X < 0) { Console.Write("no solution"); }

        double XB = (LB3 * LB3 - LB2 * LB2 + LB1 * LB1) / (2 * LB1);

        if (LB3 * LB3 - XB * XB < 0) { Console.Write("no solution"); }

        double CB = Math.Sqrt(LB3 * LB3 - XB * XB);

        if (C1 * C1 + (XB - X) * (XB - X) < 0) { Console.Write("no solution"); }

        double D1 = Math.Sqrt(C1 * C1 + (XB - X) * (XB - X));
        double Y = (D1 * D1 - L[2] * L[2] + CB * CB) / (2 * CB);

        if (C1 * C1 - Y * Y < 0) { Console.Write("no solution"); }

        double Z = Math.Sqrt(C1 * C1 - Y * Y);

        //Now transform X,Y,Z to x,y,z
        //Find the unit vectors in X,Y,Z
        double Xx = (TopSensor.x - BackSensor.x);
        double Xy = (TopSensor.y - BackSensor.y);
        double Xz = (TopSensor.z - BackSensor.z);
        double Xl = Math.Sqrt(Xx * Xx + Xy * Xy + Xz * Xz);
        Xx = Xx / Xl;
        Xy = Xy / Xl;
        Xz = Xz / Xl;

        double t = -((BackSensor.x - RightSensor.x) * (TopSensor.x - BackSensor.x) + (BackSensor.y - RightSensor.y) * (TopSensor.y - BackSensor.y) + (BackSensor.z - RightSensor.z) * (TopSensor.z - BackSensor.z)) / (LB1 * LB1);
        double Yx = (BackSensor.x + (TopSensor.x - BackSensor.x) * t - RightSensor.x);
        double Yy = (BackSensor.y + (TopSensor.y - BackSensor.y) * t - RightSensor.y);
        double Yz = (BackSensor.z + (TopSensor.z - BackSensor.z) * t - RightSensor.z);
        double Yl = Math.Sqrt(Yx * Yx + Yy * Yy + Yz * Yz);
        Yx = -(Yx / Yl);
        Yy = -(Yy / Yl);
        Yz = -(Yz / Yl);

        double Zx = (Xy * Yz - Xz * Yy);
        double Zy = (Xz * Yx - Xx * Yz);
        double Zz = (Xx * Yy - Xy * Yx);

        //document.write(' Zx='+Zx.toFixed(5)+' Zy='+Zy.toFixed(5)+' Zz='+Zz.toFixed(5)+'<br>')

        double x = (BackSensor.x + X * Xx + Y * Yx + Z * Zx);
        double y = (BackSensor.y + X * Xy + Y * Yy + Z * Zy);
        double z = (BackSensor.z + X * Xz + Y * Yz + Z * Zz);

        x = (BackSensor.x + X * Xx + Y * Yx - Z * Zx);
        y = (BackSensor.y + X * Xy + Y * Yy - Z * Zy);
        z = (BackSensor.z + X * Xz + Y * Yz - Z * Zz);

        Vector3 Loc = new Vector3((float)x, (float)y, (float)z);
        return Loc;
    }
}
