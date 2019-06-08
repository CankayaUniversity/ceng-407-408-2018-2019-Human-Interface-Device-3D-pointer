#include <NewPing.h>
#define Trigger_Pin 13
#define Echo_Pin 12
#define MAX_DISTANCE 400
 int result;

NewPing sonar(Trigger_Pin,Echo_Pin,MAX_DISTANCE);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Trigger_Pin, OUTPUT);
  pinMode(Echo_Pin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);
  Serial.write(sonar.ping_cm());
  Serial.flush();
  

}
