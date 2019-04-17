

#include <NewPing.h>
#include <Wire.h>
int arr[3];

struct Vector3{

  int x ;
  int y ;
  int z ;
}BackSensor,TopSensor,RightSensor,Result;

//Sensor At Back
#define BACK_ECHO_PIN 9
#define BACK_TRIG_PIN 8

//Sensor At Top
#define TOP_ECHO_PIN 6
#define TOP_TRIG_PIN 5

//Sensor At Right
#define RIGHT_ECHO_PIN 3
#define RIGHT_TRIG_PIN 2

#define MAX_DISTANCE 49

NewPing sonar1(BACK_TRIG_PIN,BACK_ECHO_PIN,MAX_DISTANCE);
NewPing sonar2(TOP_TRIG_PIN,TOP_ECHO_PIN,MAX_DISTANCE);
NewPing sonar3(RIGHT_TRIG_PIN,RIGHT_ECHO_PIN,MAX_DISTANCE);




void setup() {
  
  Serial.begin(2000000);

  BackSensor.x = 37;
  BackSensor.y = 0;
  BackSensor.z = 13;
  
  TopSensor.x = 37;
  TopSensor.y = 37;
  TopSensor.z = 50;
  
  RightSensor.x = 0;
  RightSensor.y = 37;
  RightSensor.z = 13;
}

void loop() {
  unsigned int uS1 = sonar1.ping_cm();
  unsigned int uS2 = sonar2.ping_cm();
  unsigned int uS3 = sonar3.ping_cm();

  float L[3];


  if(uS1 > 0)
    L[0] = uS1;
  if(uS2 > 0)
    L[1] = uS2;
  if(uS3 > 0)
    L[2] = uS3;

  trilaterate2(L);
 
  //Serial.write(vector);
  Serial.print(" Back:");
  Serial.print(uS1);
  Serial.print(", Top: ");
  Serial.print(uS2);
  Serial.print(", Right: ");
  Serial.print(uS3);
  Serial.print(", Result Point:");
  Serial.print(Result.x);
  Serial.print(", ");
  Serial.print(Result.y);
  Serial.print(", ");
  Serial.print(Result.z);
  Serial.print("\n");
  
  
  
  Serial.print("cm\n"); 


  
}


void trilaterate2(float *L)
    {
        //caluculate coords in plane of stations
        double LB1 = sqrt((TopSensor.x - BackSensor.x) * (TopSensor.x - BackSensor.x) + (TopSensor.y - BackSensor.y) * (TopSensor.y - BackSensor.y) + (TopSensor.z - BackSensor.z) * (TopSensor.z - BackSensor.z));
        double LB2 = sqrt((RightSensor.x - TopSensor.x) * (RightSensor.x - TopSensor.x) + (RightSensor.y - TopSensor.y) * (RightSensor.y - TopSensor.y) + (RightSensor.z - TopSensor.z) * (RightSensor.z - TopSensor.z));
        double LB3 = sqrt((BackSensor.x - RightSensor.x) * (BackSensor.x - RightSensor.x) + (BackSensor.y - RightSensor.y) * (BackSensor.y - RightSensor.y) + (BackSensor.z - RightSensor.z) * (BackSensor.z - RightSensor.z));

        double X = (L[0] * L[0] - L[1] * L[1] + LB1 * LB1) / (2 * LB1);
        double C1 = sqrt(L[0] * L[0] - X * X);

        if (L[0] * L[0] - X * X < 0) { Serial.print("no solution"); }

        double XB = (LB3 * LB3 - LB2 * LB2 + LB1 * LB1) / (2 * LB1);

        if (LB3 * LB3 - XB * XB < 0) { Serial.print("no solution"); }

        double CB = sqrt(LB3 * LB3 - XB * XB);

        if (C1 * C1 + (XB - X) * (XB - X) < 0) { Serial.print("no solution"); }

        double D1 = sqrt(C1 * C1 + (XB - X) * (XB - X));
        double Y = (D1 * D1 - L[2] * L[2] + CB * CB) / (2 * CB);

        if (C1 * C1 - Y * Y < 0) { Serial.print("no solution"); }

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

        double t = -((BackSensor.x - RightSensor.x) * (TopSensor.x - BackSensor.x) + (BackSensor.y - RightSensor.y) * (TopSensor.y - BackSensor.y) + (BackSensor.z - RightSensor.z) * (TopSensor.z - BackSensor.z)) / (LB1 * LB1);
        double Yx = (BackSensor.x + (TopSensor.x - BackSensor.x) * t - RightSensor.x);
        double Yy = (BackSensor.y + (TopSensor.y - BackSensor.y) * t - RightSensor.y);
        double Yz = (BackSensor.z + (TopSensor.z - BackSensor.z) * t - RightSensor.z);
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
