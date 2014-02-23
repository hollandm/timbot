import procontroll.*;
import java.io.*;

ControllIO controll;
ControllDevice joystickA;
ControllSlider sliderXA;
ControllSlider sliderYA;
ControllButton triggerA;

ControllDevice joystickB;
ControllSlider sliderXB;
ControllSlider sliderYB;
ControllButton triggerB;

float xPosA;
float yPosA;

float xPosB;
float yPosB;


void setup()
{
  // Set up screen size, background color, and smooth graphics
  size(400, 400);
  background(192, 64, 0);
  smooth();
  
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
  
  // Calibrate the values such that if they are close to zero,
  // they will be rounded to zero
  if(xPosA < 0.1 && xPosA > -0.1)
  {
    xPosA = 0;
  }
  if(xPosB< 0.1 && xPosB > -0.1)
  {
    xPosB = 0;
  }
  
  yPosA = sliderYA.getValue();
  yPosB = sliderYB.getValue();
  if(yPosA < 0.05 && yPosA > -0.05)
  {
    yPosA = 0;
  }
  if(yPosB < 0.05 && yPosB > -0.05)
  {
    yPosB = 0;
  }
  // Checked if the new values have changed 
  // and if so, print out the values
  if (xPosA != xPosOldA || yPosA != yPosOldA)
  {
    println("A:x position: " + xPosA);
    println("A:y position: " + yPosA);
  }
  
  if (xPosB != xPosOldB || yPosB != yPosOldB)
  {
    println("B:x position: " + xPosB);
    println("B:y position: " + yPosB);
  }
  
  if (triggerA.pressed())
  {
    fill(0);
  }
  else 
  {
    fill(255);
  }

  // Draw a circle showing the position of the joystick sliders
  ellipse(width/2 + width/2 *yPosA, height/2 + height/2 * xPosA, 15, 15);
  
  
  if (triggerB.pressed())
  {
    fill(0);
  }
  else 
  {
    fill(255);
  }
  ellipse(width/2 + width/2 *yPosB, height/2 + height/2 * xPosB, 15, 15);
  
  //line(width/2, height/2, width/2 + width/2 *yPos, height/2 + height/2 * xPos);
  
  // Check if the user wishes to quit
  if (key == ESC)
  {
    exit();
  }
  
}
