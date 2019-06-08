import processing.serial.*;
Serial myPort;  // Create object from Serial class
String val;     // Data received from the serial port
void setup()
{
  myPort = new Serial(this, "COM6", 9600);
  
}
void draw()
{
  //String[] spls = new String[3];
  if ( myPort.available() > 0) 
  {  // If data is available,
      //String s = myPort.readString();       // read it and store it in val
      byte[] buff = new byte[3];
      int a = myPort.readBytes(buff);
      println(buff[0] + "xxx" + buff[1] + "xxx" + buff[2]);
  } 

}
