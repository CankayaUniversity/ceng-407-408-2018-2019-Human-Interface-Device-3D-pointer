#include <NewPing.h>
#include <Wire.h>

struct Vector3{

  int x ;
  int y ;
  int z ;
}BackSensor,TopSensor,LeftSensor,Result;

//Sensor At Back
#define BACK_ECHO_PIN 9
#define BACK_TRIG_PIN 8

//Sensor At Top
#define TOP_ECHO_PIN 6
#define TOP_TRIG_PIN 5

//Sensor At Left
#define RIGHT_ECHO_PIN 3
#define RIGHT_TRIG_PIN 2

#define MAX_DISTANCE 49

NewPing sonar1(BACK_TRIG_PIN,BACK_ECHO_PIN,MAX_DISTANCE);
NewPing sonar2(TOP_TRIG_PIN,TOP_ECHO_PIN,MAX_DISTANCE);
NewPing sonar3(RIGHT_TRIG_PIN,RIGHT_ECHO_PIN,MAX_DISTANCE);




void setup() {
  
  Serial.begin(9600);
  Serial.flush();
  BackSensor.x = 0;
  BackSensor.y = 0;
  BackSensor.z = 0;
  
  TopSensor.x = 0;
  TopSensor.y = 0;
  TopSensor.z = 0;
  
  LeftSensor.x = 0;
  LeftSensor.y = 0;
  LeftSensor.z = 0;
}

void loop() {
  unsigned int uS1 = sonar1.ping_cm();
  unsigned int uS2 = sonar2.ping_cm();
  unsigned int uS3 = sonar3.ping_cm();
  

  //double num = 23.345;
  //int intpart = (int)num;
  //double decpart = num - intpart;

  
  byte arr[3] = {uS1,uS2,uS3};
  
  //Serial.write(arr[0]);
    Serial.write( (uint8_t*)arr , sizeof(arr));
  
  

  
  //Serial.write("#");
  //Serial.write(String(Result.y));
  //Serial.write("#");
  //Serial.write(String(Result.z));
  //Serial.write("\n");
  
  
  
  //Serial.write(vector);
  /*
  Serial.print(" Back:");
  Serial.print(uS1);
  Serial.print(", Top: ");
  Serial.print(uS2);
  Serial.print(", Left: ");
  Serial.print(uS3);
  Serial.print(", Result Point:");
  Serial.print(Result.x);
  Serial.print(", ");
  Serial.print(Result.y);
  Serial.print(", ");
  Serial.print(Result.z);
  Serial.print("\n");
  
  
  */

  
}


void trilaterate2(float *L)
    {
        //caluculate coords in plane of stations
        double LB1 = sqrt((TopSensor.x - BackSensor.x) * (TopSensor.x - BackSensor.x) + (TopSensor.y - BackSensor.y) * (TopSensor.y - BackSensor.y) + (TopSensor.z - BackSensor.z) * (TopSensor.z - BackSensor.z));
        double LB2 = sqrt((LeftSensor.x - TopSensor.x) * (LeftSensor.x - TopSensor.x) + (LeftSensor.y - TopSensor.y) * (LeftSensor.y - TopSensor.y) + (LeftSensor.z - TopSensor.z) * (LeftSensor.z - TopSensor.z));
        double LB3 = sqrt((BackSensor.x - LeftSensor.x) * (BackSensor.x - LeftSensor.x) + (BackSensor.y - LeftSensor.y) * (BackSensor.y - LeftSensor.y) + (BackSensor.z - LeftSensor.z) * (BackSensor.z - LeftSensor.z));

        double X = (L[0] * L[0] - L[1] * L[1] + LB1 * LB1) / (2 * LB1);
        double C1 = sqrt(L[0] * L[0] - X * X);

        if (L[0] * L[0] - X * X < 0) { Serial.print("no solution"); return;}

        double XB = (LB3 * LB3 - LB2 * LB2 + LB1 * LB1) / (2 * LB1);

        if (LB3 * LB3 - XB * XB < 0) { Serial.print("no solution"); return;}

        double CB = sqrt(LB3 * LB3 - XB * XB);

        if (C1 * C1 + (XB - X) * (XB - X) < 0) { Serial.print("no solution"); return;}

        double D1 = sqrt(C1 * C1 + (XB - X) * (XB - X));
        double Y = (D1 * D1 - L[2] * L[2] + CB * CB) / (2 * CB);

        if (C1 * C1 - Y * Y < 0) { Serial.print("no solution"); return;}

        double Z = sqrt(C1 * C1 - Y * Y);

        //Now transform X,Y,Z to x,y,z
        //Find the unit vectors in X,Y,Z
        double Xx = (TopSensor.x - BackSensor.x);
        double Xy = (TopSensor.y - BackSensor.y);
        double Xz = (TopSensor.z - BackSensor.z);
        double Xl = sqrt(Xx * Xx + Xy * Xy + Xz * Xz);
        Xx = Xx / Xl;
        Xy = Xy / Xl;
        Xz = Xz / Xl;

        double t = -((BackSensor.x - LeftSensor.x) * (TopSensor.x - BackSensor.x) + (BackSensor.y - LeftSensor.y) * (TopSensor.y - BackSensor.y) + (BackSensor.z - LeftSensor.z) * (TopSensor.z - BackSensor.z)) / (LB1 * LB1);
        double Yx = (BackSensor.x + (TopSensor.x - BackSensor.x) * t - LeftSensor.x);
        double Yy = (BackSensor.y + (TopSensor.y - BackSensor.y) * t - LeftSensor.y);
        double Yz = (BackSensor.z + (TopSensor.z - BackSensor.z) * t - LeftSensor.z);
        double Yl = sqrt(Yx * Yx + Yy * Yy + Yz * Yz);
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

        Result.x = x;
        Result.y = y;
        Result.z = z;
        
    }
