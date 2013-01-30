import procontroll.*;
import java.io.*;
import processing.serial.*;

ControllIO controll;
ControllDevice joystickA, joystickB;
ControllSlider sliderXA, sliderYA, sliderXB, sliderYB;
ControllButton triggerA, triggerB;
float xPosA, yPosA, xPosB, yPosB;

Serial arduino;  //Serial port to arduino

void setup()
{
  // Set up screen size, background color, and smooth graphics
  size(400, 400);
  background(192, 64, 0);
  smooth();  
  
  arduino = new Serial(this, Serial.list()[0], 9600);
  
  // Create a controll device
  controll = ControllIO.getInstance(this);
  
  // Print out available devices
  controll.printDevices();
  
  // Grab the joystick. This needs to be changed if there is another joystick/gamepad
  joystickA = controll.getDevice(2);
  joystickB = controll.getDevice(3);
  
  // Print out the attributes of joystick A
  println("Joystick A has: " + joystickA.getNumberOfSliders() + " sliders");
  println(joystickA.getNumberOfButtons() + " buttons");
  println(joystickA.getNumberOfSticks() + " sticks");
  joystickA.printSliders();
  joystickA.printButtons();
  joystickA.printSticks();
  
  // Print out the attributes of joystick A
  println("Joystick B has: " + joystickB.getNumberOfSliders() + " sliders");
  println(joystickB.getNumberOfButtons() + " buttons");
  println(joystickB.getNumberOfSticks() + " sticks");
  joystickB.printSliders();
  joystickB.printButtons();
  joystickB.printSticks();
  
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
  // Save the old state of the slider values
  float xPosOldA = xPosA;
  float yPosOldA = yPosA;
  float xPosOldB = xPosB;
  float yPosOldB = yPosB;
  
  // Redraw the background to give the appearance of one circle
  background(192, 64, 0);
  
  //Grab the new xPos value from the slider
  xPosA = sliderXA.getValue();
  xPosB = sliderXB.getValue();
  yPosA = sliderYA.getValue();
  yPosB = sliderYB.getValue();
  
  // Calibrate the values such that if they are close to zero,
  // they will be rounded to zero
  if(xPosA < 0.05 && xPosA > -0.05)
  {
    xPosA = 0;
  }
  
  //yPosA = sliderYA.getValue();
  if(yPosA < 0.05 && yPosA > -0.05)
  {
    yPosA = 0;
  }
  
  if(xPosB < 0.05 && xPosB > -0.05)
  {
    xPosB = 0;
  }
  
  //yPosB = sliderYB.getValue();
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
  
  //Color for trigger A
  if (triggerA.pressed())
  {
    fill(0);
  }
  else 
  {
    fill(255);
  }

  // Draw a circle showing the position of the joystick sliders
  line(width/2, height/2, width/2 + width/2 *yPosA, height/2 + height/2 * xPosA);
  ellipse(width/2 + width/2 *yPosA, height/2 + height/2 * xPosA, 15, 15);
  
  int iXA = (int)(xPosA * 100 + 100);
  arduino.write(iXA);
  //println(iXA);
  
  //Color for trigger B
  if (triggerB.pressed())
  {
    fill(0);
  }
  else 
  {
    fill(255);
  }

  // Draw a circle showing the position of the joystick sliders
  line(width/2, height/2, width/2 + width/2 *yPosB, height/2 + height/2 * xPosB);
  ellipse(width/2 + width/2 *yPosB, height/2 + height/2 * xPosB, 15, 15);
  
  
  int iXB = (int)(xPosB * 100 + 100);
  arduino.write(iXB);
  //println(iXB);
  
  // Check if the user wishes to quit
  if (key == ESC)
  {
    exit();
  }
  
}
