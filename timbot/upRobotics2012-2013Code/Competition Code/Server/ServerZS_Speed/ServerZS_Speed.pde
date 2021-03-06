/* Server:
 * This processing program runs on the computer inside the Mission Control Room
 * It's purpose is to check the Arduino for operating mode, poll the joystick, and
 * send the data over the network to the client onboard the Robot
 *  
 * 
 */

//--------------- Library Imports ---------------\\
import hypermedia.net.*;    //For UDP Functions
import procontroll.*;       //For Joystick functionality
import java.io.*;           //Not actually sure if we need this
import processing.serial.*;   //For Serial Communication to Arduino

//--------------- Constants ---------------\\
//Operating mode constants
byte STOP = 0;
byte FORW = 1;
byte MAN  = 2;
byte BACK = 3;

int SNDLEN = 7;  //Length of data packet array

int USECONSOLE = 0;  // Set to 0 to not use Console Box
                     // Set to 1 (or any other int) to use Console Box

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
*/ 

UDP udp; //UDP Connection

Serial arduinoM; //For communicating with the Arduino in 'M'ission control


byte mode;
/* Operating Mode:
    0 = Stopped       (STOP)
    1 = Forward       (FORW)
    2 = Manual        (MAN)
    3 = Backward      (BACK)
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

ControllButton button3B;
ControllButton button2B;

ControllButton zsButton;

float xPosA;
float xPosB;
float yPosA;
float yPosB;

byte trigA;
byte trigB;

byte zs;

ControllSlider speed;
float speedMult;

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
        if (USECONSOLE != 0)
        {
           arduinoM = new Serial(this, Serial.list()[1], 9600);
        }
        //Setup the joysticks
        setUpJoysticks();
        
        mode = STOP; //Initialize to Stopped mode.
}

void draw()
{
        
  getJoystickData();
        checkMode();
        //joy[6]=MAN;
        //printMode();
//        delay(10);
//          delay(100);
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
  joystickA = controll.getDevice(0);
  joystickB = controll.getDevice(1);
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
  
  //get the bucket buttons
  button2B = joystickB.getButton(1);
  button3B = joystickB.getButton(2);
  
  
  zsButton = joystickB.getButton(3);
  
  speed = joystickA.getSlider(2);
}

//Check the operating Mode (based on the switches connected to the Arduino)
void checkMode()
{

    //Check the mode from the Arduino
    if (USECONSOLE != 0)
    {
       if(arduinoM.available() > 0)
       {
          mode = MAN;  // Hardcode manual
          int tempMode = arduinoM.read(); // Check if autonomous
          
          if (tempMode == FORW)
          {
             joy[0] = 100;
             joy[2] = 100;
             println("Forward");
          }
          else if (tempMode == BACK)
          {
             joy[0] = 0;
             joy[2] = 0;
             println("Backward");
          }
          else
          {
             println("Manual");
             // Do nothing 
          }
          //mode = (byte)arduinoM.read();
          // Clear the buffer if it is too full
          if(arduinoM.available() > 15)
          {
              arduinoM.clear();
          }
       }
    }
    else
    {
       mode = MAN;
    }
}

/*
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

*/

//Get the Joystick position and trigger values
void getJoystickData()
{
  
  speedMult = (speed.getValue() + 1)/4 + 0.5;
  println("Speed: "+(byte)(speedMult*100) + "%");
  
  //Grab the new X and Y values from the sliders
  xPosA = -1*sliderXA.getValue()*speedMult;
  xPosB = -1*sliderXB.getValue()*speedMult;
  yPosA = sliderYA.getValue()*speedMult; 
  yPosB = sliderYB.getValue()*speedMult;
  
  
  
  
  // Calibrate the values such that if they are close to zero,
  // they will be rounded to zero
  if(xPosA < 0.15 && xPosA > -0.15)
  {
    xPosA = 0;
  }
  if(xPosB < 0.15 && xPosB > -0.15)
  {
    xPosB = 0;
  }
  if(yPosA < 0.15 && yPosA > -0.15)
  {
    yPosA = 0;
  }
  if(yPosB < 0.15 && yPosB > -0.15)
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
  
  int bucketMod = 0;
  if(button2B.pressed())
  {
    bucketMod += 1;
  }
  if(button3B.pressed())
  {
    bucketMod -= 1;
  }
  
  if (zsButton.pressed()) {
    zs = (byte)255;
  } else {
    zs = (byte)0;
  }
  
  // Okay, we have the data. Now let's fill in the joy array
  if (trigA > 0) {
    //println("test");
    joy[0] = (byte)(xPosA * 50 + 50);
    joy[1] = (byte)(yPosA * 50 + 50);
    joy[2] = (byte)(xPosB * 50 + 50);
    //joy[3] = (byte)(yPosB * 50 + 50);
    
    joy[3] = (byte)(bucketMod * 50 + 50);
  } else {
    joy[0] = (byte)(xPosA * -50 + 50);
    joy[1] = (byte)(yPosA * -50 + 50);
    joy[2] = (byte)(xPosB * -50 + 50);
    //joy[3] = (byte)(yPosB * 50 + 50);
    
    joy[3] = (byte)(bucketMod * -50 + 50);
  }
  /*
  joy[0] = (byte)(xPosA * 50 + 50);
  joy[1] = (byte)(yPosA * 50 + 50);
  joy[2] = (byte)(xPosB * 50 + 50);
  //joy[3] = (byte)(yPosB * 50 + 50);
  
  joy[3] = (byte)(bucketMod * 50 + 50);
  */
  joy[4] = trigA;
  joy[5] = trigB;
//  joy[6] = mode;
  joy[6] = zs;
}


