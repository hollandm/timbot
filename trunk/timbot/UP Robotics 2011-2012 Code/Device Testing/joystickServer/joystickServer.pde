/**
 * Shared Drawing Canvas (Server) 
 * by Alexander R. Galloway. 
 * 
 * A server that shares a drawing canvas between two computers. 
 * In order to open a socket connection, a server must select a 
 * port on which to listen for incoming clients and through which 
 * to communicate. Once the socket is established, a client may 
 * connect to the server and send or receive commands and data.
 * Get this program running and then start the Shared Drawing
 * Canvas (Client) program so see how they interact.
 */


import processing.net.*;
import procontroll.*;
import java.io.*;

ControllIO controll;
ControllDevice joystickA;
ControllSlider sliderXA;
ControllSlider sliderYA;
ControllButton triggerA;
float xPosA;
float yPosA;

ControllDevice joystickB;
ControllSlider sliderXB;
ControllSlider sliderYB;
ControllButton triggerB;
float xPosB;
float yPosB;



Server s;
Client c;
String input;
int data[];

void setup() 
{
  size(450, 255);
  background(204);
  stroke(0);
  frameRate(5); // Slow it down a little
  s = new Server(this, 12345); // Start a simple server on a port
  
  // Create a controll device
  controll = ControllIO.getInstance(this);
  // Print out available devices
  controll.printDevices();
  // Grab the joystick. This needs to be changed if there is another joystick/gamepad
  joystickA = controll.getDevice(2);
  joystickB = controll.getDevice(3);
  // Print out the attributes of the joystic
  /*
  println("Joystick has: " + joystick.getNumberOfSliders() + " sliders");
  println(joystick.getNumberOfButtons() + " buttons");
  println(joystick.getNumberOfSticks() + " sticks");
  joystick.printSliders();
  joystick.printButtons();
  joystick.printSticks();
  */
  // Set up the X and Y sliders
  sliderXA = joystickA.getSlider(1);
  sliderYA = joystickA.getSlider(2);
  sliderXB = joystickB.getSlider(1);
  sliderYB = joystickB.getSlider(2);
  // Initialize the xPos and yPos values
  xPosA = sliderXA.getValue();
  yPosA = sliderYA.getValue();
  xPosB = sliderXB.getValue();
  yPosB = sliderYB.getValue();
  // Get the trigger
  triggerA = joystickA.getButton(0);
  triggerB = joystickB.getButton(0);
}

void draw() 
{
 
  float xPosOldA = xPosA;
  float yPosOldA = yPosA;
  float xPosOldB = xPosB;
  float yPosOldB = yPosB;
  
 
   xPosA = sliderXA.getValue();
  
  // Calibrate the values such that if they are close to zero,
  // they will be rounded to zero
  if(xPosA < 0.05 && xPosA > -0.05)
  {
    xPosA = 0;
  }
  
   xPosB = sliderXB.getValue();
  
  // Calibrate the values such that if they are close to zero,
  // they will be rounded to zero
  if(xPosB < 0.05 && xPosB > -0.05)
  {
    xPosB = 0;
  }
  
  yPosA = sliderYA.getValue();
  if(yPosA < 0.05 && yPosA > -0.05)
  {
    yPosA = 0;
  }
  
  yPosB = sliderYB.getValue();
  if(yPosB < 0.05 && yPosB > -0.05)
  {
    yPosB = 0;
  }
  
  // Checked if the new values have changed 
  // and if so, print out the values
  if (xPosA != xPosOldA || yPosA != yPosOldA)
  {
    //println("x position: " + xPos);
    //println("y position: " + yPos);
  }
  int triggerColorA;
  if (triggerA.pressed())
  {
    triggerColorA = 0;
  }
  else 
  {
    triggerColorA = 255;
  }
    
  int triggerColorB;
  if (triggerB.pressed())
  {
    triggerColorB = 0;
  }
  else 
  {
    triggerColorB = 255;
  }
  
  s.write(xPosA + " " + yPosA + " " + triggerColorA +" " + xPosB + " " + yPosB + " " + triggerColorB + "\n");
  
  // Receive data from client
  c = s.available();
  if (c != null) {
    input = c.readString();
    input = input.substring(0, input.indexOf("\n")); // Only up to the newline
    data = int(split(input, ' ')); // Split values into an array
    // Draw line using received coords
    stroke(0);
    line(data[0], data[1], data[2], data[3]);
  }
  
  if (key == ESC)
  {
    s.stop();
    exit();
  }
}
