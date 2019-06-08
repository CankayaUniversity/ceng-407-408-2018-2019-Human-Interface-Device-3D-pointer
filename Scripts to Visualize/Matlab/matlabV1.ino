
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println('a');
char a = 'b';
while(a != 'a')
{
  a=Serial.read();
  }

}

void loop() {
  // put your main code here, to run repeatedly:
 
  

}
