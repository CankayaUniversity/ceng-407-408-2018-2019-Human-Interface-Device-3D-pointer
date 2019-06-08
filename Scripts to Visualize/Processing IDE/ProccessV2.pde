import processing.serial.*;
Serial myPort;
String val;
void setup()
{
  myPort = new Serial(this, "COM6", 9600);

}
void draw()
{
  if ( myPort.available() > 0) 
  {  // If data is available,
      String s = myPort.readString(); 
      String[] arrOfStr = s.split("#",3);
        for (String a : arrOfStr) {
            System.out.println(a); 
  }
}
}
