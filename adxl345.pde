import processing.serial.*;
import java.awt.event.KeyEvent;
import java.io.IOException;

Serial myPort;

String data="";
float roll, pitch;

PShape vehicle; 

void setup() {
  size (960, 640, P3D);
  myPort = new Serial(this, "COM5", 9600); // starts the serial communication
  myPort.bufferUntil('\n');
  
  //vehicle = loadShape("vehicle.obj");
  
}

void draw() {
  translate(width/2, height/2, 0);// this moves the origin point(0,0,0) from the top-left corner to the center of the screen. This way, the box rotates around its center, not a corner..
  background(80);// this clears the screen with a dark grey color in every frame. this is essential for animation, as it earses the previous frame's drawing. 
  textSize(22);
  text("Roll: " + int(roll) + "     Pitch: " + int(pitch), -100, 265);

  // Rotate the object
  rotateX(radians(roll));
  rotateZ(radians(-pitch));
  
  // 3D 0bject
  textSize(30);  
  fill(0, 76, 153);
  box (386, 40, 200); // Draw box
  textSize(25);
  fill(255, 255, 255);
  text("E-21 Aswariders", -183, 10, 101);

  //delay(10);
  //println("ypr:\t" + angleX + "\t" + angleY); // Print the values to check whether we are getting proper values
}

// Read data from the Serial Port
void serialEvent (Serial myPort) { 
  // reads the data from the Serial Port up to the character '.' and puts it into the String variable "data".
  data = myPort.readStringUntil('\n');

  // if you got any bytes other than the linefeed:
  if (data != null) {
    data = trim(data);
    // split the string at "/"
    String items[] = split(data, '/');
    if (items.length > 1) {

      //--- Roll,Pitch in degrees
      roll = float(items[0]);
      pitch = float(items[1]);
    }
  }
}
