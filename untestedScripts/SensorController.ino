#include <NewPing.h>
#include <Wire.h>

//Sensor At Back
#define BACK_ECHO_PIN 9
#define BACK_TRIG_PIN 8

//Sensor At Top
#define TOP_ECHO_PIN 6
#define TOP_TRIG_PIN 5

//Sensor At Right
#define RIGHT_ECHO_PIN 3
#define RIGHT_TRIG_PIN 2

#define MAX_DISTANCE 50

NewPing sonar1(BACK_TRIG_PIN,BACK_ECHO_PIN,MAX_DISTANCE);
NewPing sonar2(TOP_TRIG_PIN,TOP_ECHO_PIN,MAX_DISTANCE);
NewPing sonar3(RIGHT_TRIG_PIN,RIGHT_ECHO_PIN,MAX_DISTANCE);


void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(10);
  unsigned int uS1 = sonar1.ping();
  unsigned int uS2 = sonar2.ping();
  unsigned int uS3 = sonar3.ping();

  Serial.print("BACK: ");
  Serial.print(uS1 / US_ROUNDTRIP_CM);
  Serial.print("cm"); 
  Serial.print(",\tTOP: ");
  Serial.print(uS2 / US_ROUNDTRIP_CM);
  Serial.print("cm");
  Serial.print(",\tRIGHT: ");
  Serial.print(uS3 / US_ROUNDTRIP_CM);
  Serial.print("cm\n");
  
  Serial.write(uS1 / US_ROUNDTRIP_CM);
  Serial.write(uS2 / US_ROUNDTRIP_CM);
  Serial.write(uS3 / US_ROUNDTRIP_CM);
}
