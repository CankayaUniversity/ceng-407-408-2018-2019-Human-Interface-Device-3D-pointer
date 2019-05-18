float a1; 
 
void setup() {
  size(1200, 600, P3D);
  background(0);
}
 
void draw() {
 
  background(0);
 
  // everything looks better with lights
  lights(); 
 
  fill(255, 0, 0); // red 
  displaySphere(width/2, height/2, 0, 19);
 
  fill(0, 255, 0); // green 
  displaySphere(44, 44, 0, 19);
 
  fill(0, 255, 0); // green 
  displayBox(width/2, 99, 0, 39);
 
  fill(0, 0, 255); // blue 
  displayBox(width/2, 99, -439, 39); // blue box is same x, same, y, same size 
  // but farer away than the green box (-439 instead of 0)
 
  fill(0, 255, 0); // green 
  displayText(30, height-30, 0);
 
  fill(255, 235, 10); // yellow  
  displayText(width-118, height-30, 0);
 
  fill(255, 0, 255); // blue  
  displayText(width-118, height-30, -60); // same x and y, but more far away
}
 
//---------------------------------------------------------- 
 
void displaySphere(float x, float y, float z, 
  float r) {
 
  // sphere
 
  noStroke();
  pushMatrix();
  translate(x, y, z);
  sphere(r);
  popMatrix();
}
 
void displayBox(float x, float y, float z, 
  float r) {
 
  // box 
 
  noStroke();
  pushMatrix();
  translate(x, y, z); // translate and rotate 
  rotateY(a1); 
  box(r);
  popMatrix();
 
  // rotation 
  a1+=.012;
}
 
void displayText(float x, float y, float z) {
 
  // Text of the coordinates at coordinates:
 
  // This function shows the coordinates x,y,z as text at the screen position 
  // of the coordinates.  
 
  pushMatrix();
  translate(x, y, z); // translate and rotate 
  text(x+","+y+","+z, 
    0, 0);
  popMatrix();
}
