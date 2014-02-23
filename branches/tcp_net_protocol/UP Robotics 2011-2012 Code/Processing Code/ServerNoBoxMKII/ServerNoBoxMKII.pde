/* Server:
 * This processing program runs on the computer inside the Mission Control Room
 * It's purpose is to check the Arduino for operating mode, poll the joystick, and
 * send the data over the network to the client onboard the Robot
 *  
 * Intial Network Functionality: Ryan Gasik
 * Last Modified: 3/13/12: Jess Tate- Added Joystick Functionality
 */

//--------------- Library Imports ---------------\\
import hypermedia.net.*;    //For UDP Functions
import procontroll.*;       //For Joystick functionality
import java.io.*;           //Not actually sure if we need this
import processing.serial.*;   //For Serial Communication to Arduino

//--------------- Constants ---------------\\
//Operating mode constants
byte STOP = 0;
byte AUTO = 1;
byte MAN  = 2;

int SNDLEN = 9;  //Length of data packet array


//--------------- Variables ---------------\\

byte[] joy;      //For storing the joystick values
/*
joy[0] is joystick a, x position.
joy[1] is joystick a, Y position.
joy[2] is joystick b, X position.
joy[3] is joystick b, Y position.
joy[4] is joystick a trigger.
joy[5] is joystick b trigger.
joy[6] is the operating mode.
joy[7] is joystick b, button 2.
joy[8] is joystick b, button 3.
*/ 

UDP udp; //UDP Connection

Serial arduinoM; //For communicating with the Arduino in 'M'ission control


byte mode;
/* Operating Mode:
    0 = Stopped       (STOP)
    1 = Autonomous    (AUTO)
    2 = Manual        (MAN)
*/

// Joystick Variables:
ControllIO controll;
ControllDevice joystickA;
ControllSlider sliderXA;
ControllSlider sliderYA;
ControllButton triggerA;

ControllDevice joystickB;
ControllSlider sliderXB;
ControllSlider sliderYB;
ControllButton triggerB;

ControllButton joystickBButton2;
ControllButton joystickBButton3;

float xPosA;
float xPosB;
float yPosA;
float yPosB;

byte trigA;
byte trigB;

byte jBb2; //Joystick B, Button 2
byte jBb3; //Joystick B, Button 3



//--------------- Primary Functions ---------------\\
void setup()
{
        //Set up a multicast UDP connection.
        udp = new UDP( this, 6000, "224.0.0.1" );
        joy = new byte[SNDLEN];
        udp.listen(true);
        
        //Setup Arduino Connection. 
        println(Serial.list());
        //IMPORTANT!!! Make sure that correct Serial.list() is selected
        //arduinoM = new Serial(this, Serial.list()[1], 9600);
        
        //Setup the joysticks
        setUpJoysticks();
        
        mode = STOP; //Initialize to Stopped mode.
}

void draw()
{
        checkMode();
        printMode();
	getJoystickData();
        //joy[6]=MAN;
        udp.send(joy);
}

//--------------- Helper Functions ---------------\\
void setUpJoysticks()
{
  // Create a controll device
  controll = ControllIO.getInstance(this);
  // Print out available devices
  controll.printDevices();
  // Grab the joystick. This needs to be changed if there is another joystick/gamepad
  joystickA = controll.getDevice(2);
  joystickB = controll.getDevice(3);
  // Print out the attributes of the joystick
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
  
  // Get the Joystick B Buttons
  joystickBButton2 = joystickB.getButton(1);
  joystickBButton3 = joystickB.getButton(2);
}

//Check the operating Mode (based on the switches connected to the Arduino)
void checkMode()
{
    //Commented for testing
    //Check the mode from the Arduino
    /*
    if(arduinoM.available() > 0)
    {
      mode = (byte)arduinoM.read();
      if(arduinoM.available() > 15)
        arduinoM.clear();
    }
    */
    
    
    mode = MAN;
    
}

// Prints out the operating mode
void printMode()
{
    if (mode == STOP)
    {
       println("STOP");
    }
    else if (mode == AUTO)
    {
       println("AUTONOMOUS"); 
    }
    else if (mode == MAN)
    {
       println("MANUAL"); 
    }
}
//Get the Joystick position and trigger values
void getJoystickData()
{
  
  //Grab the new X and Y values from the sliders
  xPosA = -1*sliderXA.getValue();
  xPosB = -1*sliderXB.getValue();
  yPosA = sliderYA.getValue(); 
  yPosB = sliderYB.getValue();
  
  // Calibrate the values such that if they are close to zero,
  // they will be rounded to zero
  if(xPosA < 0.1 && xPosA > -0.1)
  {
    xPosA = 0;
  }
  if(xPosB < 0.1 && xPosB > -0.1)
  {
    xPosB = 0;
  }
  if(yPosA < 0.05 && yPosA > -0.05)
  {
    yPosA = 0;
  }
  if(yPosB < 0.05 && yPosB > -0.05)
  {
    yPosB = 0;
  }
  
  // Now let's see if the triggers are pressed
  if(triggerA.pressed())
  {
    trigA = (byte)255; 
  } 
  else
  {
    trigA = 0;
  }
  if(triggerB.pressed())
  {
    trigB = (byte)255;
  }
  else
  {
    trigB = 0;
  }
  if(joystickBButton2.pressed())
  {
    jBb2 = (byte)255;
  }
  else
  {
    jBb2 = 0;
  }
  if(joystickBButton3.pressed())
  {
    jBb3 = (byte)255;
  }
  else
  {
    jBb3 = 0;
  }
  
  // Okay, we have the data. Now let's fill in the joy array
  joy[0] = (byte)(xPosA * 50 + 50);
  joy[1] = (byte)(yPosA * 50 + 50);
  joy[2] = (byte)(xPosB * 50 + 50);
  joy[3] = (byte)(yPosB * 50 + 50);
  joy[4] = trigA;
  joy[5] = trigB;
  joy[6] = mode;
  joy[7] = jBb2;
  joy[8] = jBb3;
  
  
  
}


