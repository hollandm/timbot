// Basic functions
// Version 0.2
// 0.1:  Add some basic functions -- R. Gasik
// 0.11: Brought in the pin definitions, 
//       added some functionality and comments -- J. Tate
// 0.2:  Implemented manual drive functionality (UNTESTED) -- J. Tate (3/14/12)
 

//--------------- Constants ---------------\\

const float DRIVEMAX = 0.49;  // Up to 0.5 as max

//Operating mode constants

const byte STOP = 0;
const byte FORW = 1;
const byte MAN  = 2;
const byte BACK = 3;

const int SHUTDOWN = 42;

//Moved the pin definitions inside this file -- JT
//Motor controller pin defs -- RG
const int WHEELS_RIGHT = 3;    //Digital
const int WHEELS_LEFT = 4;     //Digital
const int ARM = 5;             //Digital
const int BUCKET = 6;          //Digital

//Pin to check if E-Button has been pressed
const int E_BUTTON = 10;       //Digital

//IR sensor pin defs -- RG
const int IR_FRONT = A2;        //Analog
const int IR_BACK = 3;         //Analog
const int IR_RIGHT = 4;        //Analog
const int IR_LEFT = 5;         //Analog
//Gyroscope pin defs -- RG
const int GYRO = 6;            //Analog
//Potentiometer pin defs -- RG
const int POT_ARMR = 7;        //Analog
const int POT_ARML = 8;        //Analog
const int POT_BUCKET = 9;      //Analog


//Autonomous Magic Number Constants
const float AUTO_DRIVE_FORWARD_SPEED = 1;
const float AUTO_DRIVE_REVERSE_SPEED = -1;
const float WALL_DISTANCE = 30;     // Inches. Drive until we are less than 30" from the walls (Will need to fine-tune this number)
const float AUTO_TURN_SPEED = 0.7;

//IR Sensor Constants
float voltStep = 0.004882815; //(5V/1024)
//adjust calibrationNum and power to calibrate the sensor to actual values
int calibrationNum = 55;     
float power = -1.1;

//Gyroscope Constans  (From Tim Vanderwerf and MEs)
int gyroPin = 0;                           //Gyro is connected to analog pin 0
float gyroVoltage = 0;                     //Gyro is supposed to run at 3.3V
float arduinoVoltage = 5;                  //Arduino voltage is 5
float gyroZeroVoltage = 1.16;              //Gyro is zeroed at 1.23V
float gyroSensitivityCW = 0.002244448137;  //  Our gyro is supposed to be 10mV/deg/sec clockwise
float gyroSensitivityCC = 0.002463151468;  //   Our gyro is supposed to be 10mV/deg/sec counterclockwise
float rotationThreshold = 4;               //Minimum deg/sec to keep track of - helps with gyro drifting
float maxrotationThreshold = 100;          //Minimum deg/sec to keep track of - helps with gyro drifting
float minrotationThreshold = -100;         //Minimum deg/sec to keep track of - helps with gyro drifting
int multiplier = 0 ;                       //Used with currentAngle to keep it between 0 - 360 degrees
float gyroTime = 0;                        //Track time from the first recorded data point of test run



//--------------- Variables ---------------\\

boolean hasStarted;
byte joy[7] = {50, 50, 50, 50, 0, 0, STOP};    //Used for storing the mode and joystick values 

//joy[0] is joystick a, x position.
//joy[1] is joystick a, Y position.
//joy[2] is joystick b, X position.
//joy[3] is joystick b, Y position.
//joy[4] is joystick a trigger.
//joy[5] is joystick b trigger.
//joy[6] is operating mode.
 

byte joyConfig;  // Used to determine what configuration the joysticks are in
      // 0 = drive mode (Each joystick controls 1 side of robot)
      // 1 = dig mode   (Joystick A controls driving straight, B controls arms/bucket)

int mode;   //Used to determine what operating mode we are in
// Operating Mode:
//    0 = Stopped       (STOP)
//    1 = Autonomous    (AUTO)
//    2 = Manual        (MAN)


//Autonomous Variables:
int phase;    //Determines which phase in the autonomous program the robot is currently in
int subphase; //Determines which subphase within the phase that the autonomous program is in

unsigned long phStartTime;    //Used to store time of starting a phase's driving.

unsigned long ph0TotalTime;    //Used to store elapsed phase 1 drive time.
unsigned long ph2TotalTime;    //Used to store elapsed phase 2 drive time.

unsigned long elapsedTime;      //Used when turning a specified angle
unsigned long previousReadTime; //Also used when turning a specified angle

// Variables for storing IR sensor readings
float irFront;
float irBack;
float irLeft;
float irRight;

float turnAngle;


//--------------- Primary Functions ---------------\\

void setup()
{
   //Set up pin modes
    pinMode(WHEELS_LEFT,  OUTPUT);
    pinMode(WHEELS_RIGHT, OUTPUT);
    pinMode(ARM,          OUTPUT);
    pinMode(BUCKET,       OUTPUT);
    pinMode(E_BUTTON,     INPUT);
    
    pinMode(48, OUTPUT);
    
    mode = MAN;    // Default to stopped
    joyConfig = 0;  // Initialize to driver mode 
    
    phase = 0;
    subphase = 0;
    
    // Set up serial port for communication with computer
    Serial.begin(9600);  //9600 baud
    hasStarted = false;

}

void loop()
{
   rcv();
   interpret();
   
   //Serial.write(joy[0]);
   
   int battery = digitalRead(E_BUTTON);
   if (battery == HIGH) 
   {
      hasStarted = true;
   } 
   else if (battery == LOW) 
   {
      if (hasStarted == false) 
      {
         hasStarted = true;
      } 
      else 
      {
         Serial.write(SHUTDOWN);
      }
   }
   
   // Run autonomous mode if necessary
   if(mode == FORW)
   {
      autonomous(FORW);
   }
   else if (mode == BACK)
   {
      autonomous(BACK); 
   }
}

//--------------- Helper Functions ---------------\\

///////// Basic Drive and Actuate Functions \\\\\\\\\\

/*
 * drivePulse
 * Used to create a pulse of specified width
 * Params: pin = Digital Output pin to write the pulse to
 *         us  = Width of pulse in microseconds
 */
void drivePulse(int pin, int us) 
{
	digitalWrite(pin, HIGH);
	delayMicroseconds(us);
        digitalWrite(pin, LOW);
        //delay(12);
}

/*
 * driveLeft
 * Drive the left side wheels
 * Param: spd is the speed, from -1 to 1
 *        where -1 is full speed in reverse
 *        and 1 is full speed forward
 */
void driveLeft(float spd)
{
  float aspeed = spd;
  //If the speed is greater than 1, then cap it at full speed of 1
  //(or negative 1 if in the reverse direction
  if ( spd > 1)
  {
    aspeed=1;
  }
  else if ( spd < -1)
  {
    aspeed=-1;
  }
  //Now convert the speed into a pulse duration in microseconds
  int us = (int)((( aspeed * DRIVEMAX ) + 1.5) * 1000 );
  drivePulse(WHEELS_LEFT, us);  //Drive the left side wheels
}

/*
 * driveRight
 * Same as driveLeft, except with the right side wheels
 * These two functions will be useful for taking the two joystick inputs
 */
void driveRight(float spd)
{
  float aspeed = spd;
  if ( spd > 1)
  {
    aspeed=1;
  }
  else if ( spd < -1)
  {
    aspeed=-1;
  }
  int us = (int)((( aspeed * DRIVEMAX ) + 1.5) * 1000 );
  drivePulse(WHEELS_RIGHT, us);
}

/*
 * driveStraight
 * Drive straight at the specified speed
 */
void driveStraight(float spd)
{
  driveLeft(spd);
  driveRight(spd);
}

/*
 * turnRight
 * Rotate to the right
 */
void turnRight(float spd )
{
  driveLeft(spd);
  driveRight(-spd);
}

/*
 * turnLeft
 * Rotate to the left
 */
void turnLeft(float spd )
{
  driveLeft(-spd);
  driveRight(spd);
}

/*
 * actuateArm
 * Raises or lowers the arms
 */
void actuateArm(float spd)
{
  float aspeed = spd;
  if ( spd > 1)
  {
    aspeed = 1;
  }
  else if ( spd < -1)
  {
    aspeed = -1;
  }
  int us = (int)((( aspeed * DRIVEMAX ) + 1.5) * 1000 );
  drivePulse(ARM, us);
  
}

/*
 * actuateBucket
 * Raises or lowers the bucket
 */
void actuateBucket(float spd)
{
  float aspeed = spd;
  /*
  if ( spd > 1)
  {
    aspeed=1;
  }
  else if ( spd < -1)
  {
    aspeed=-1;
  }
  //*/
  int us = (int)((( aspeed * DRIVEMAX ) + 1.5) * 1000 );
  drivePulse(BUCKET, us); 
  
}

/*
 * stopDrive
 * Stops the drive motors (but does not stop linear actuators)
 */
void stopDrive()
{
    driveStraight(0);
}

/*
 * stopArm
 * Stops linear actuators of the arm
 */
void stopArm()
{
  drivePulse(ARM, 1500);  //Send a pulse of 1.5ms
}

/*
 * stopBucket
 * Stops linear actuators of the bucket
 */
void stopBucket()
{
  drivePulse(BUCKET, 1500); //Send a pulse of 1.5ms
}

/*
 * stopAll
 * Stops all motors, including linear actuators
 */
void stopAll()
{
  stopDrive();
  stopArm();
  stopBucket();
}


///////// Communication and Interpretation Functions \\\\\\\\\\

/*
 * rcv
 * Receives serial data from computer and stores that data 
 * in the state array
 * 
 */
int rcv()
{
  
  if(Serial.available() >= 2)  // Make sure that there are at least two bytes waiting in the serial
  {
    int incomingByte;

    incomingByte = byte(Serial.read());

    switch (incomingByte)
    {
      case 'm':
          joy[6] = Serial.read();
          Serial.write(joy[6]);
          break;
      case 'a': 
          joy[0] = Serial.read();
          //Serial.write(joy[0]);
          break;
      case 'b':
          joy[1] = Serial.read();
          break;
      case 'c':
          joy[2] = Serial.read();
          break;
      case 'd':
          joy[3] = Serial.read();
          break;
      case 'e':
          joy[4] = Serial.read();
          //Serial.write(joy[4]);
          break;
      case 'f':  
          joy[5] = Serial.read();
          break;
      default:   // Hopefully we shouldn't get here, but if we do, read the next one.
          break;
          
    }
    //Serial.write(joy[4]);
  }
  
  
}

/*
 * interpret
 * Interprets the joy array, and calls the necessary drive functions
 * if we are in manual (or stop) mode
 */
void interpret()
{

  // First let's load up the proper variables
  //mode = MAN;
  mode = joy[6];

  if (joy[4] != 0 && joy[5] != 0)    // Both triggers are pressed
  {
     joyConfig = 1;        // Dig Mode
  }
  else 
  {
     joyConfig = 0;        // Drive Mode
  } 
  
  // Now let's act on them
  if(mode == STOP)  
  {
     stopAll(); // Stop everything
  }
  else if(mode == MAN)  // Manual override mode
  {
     if (joyConfig == 0)  // Drive Mode
     {
        float spdR = ((float)(joy[0] - 50)/50);    //Joy A, X Pos
        float spdL = ((float)(joy[2] - 50)/50);    //Joy B, X Pos
        driveRight(spdR);
        driveLeft(spdL);
        
     }
     else                 // Dig Mode
     {
        float spd = ((float)(joy[0] - 50)/50);     //Joy A, X Pos
        float arm = ((float)(joy[2] - 50)/50);     //Joy B, X Pos
        float buc = ((float)(joy[3] - 50)/50);     //Joy B, Y Pos
        
        //driveLeft(spd);
        //driveRight(spd);
        driveStraight(spd);
        actuateArm(-1*arm);
        actuateBucket(buc);
        
     }
    
  }
  else
  {
      // We are in Autonomous Mode. Currently do nothing 
  }
  
  
}

///////// Autonomous Functions \\\\\\\\\\

/*
 * autonomous
 * This is the main autonomous program
 * Depending on the phase and variable, it calls the appropriate subroutines
 */
void autonomous(byte autoMode)
{
   if (autoMode == FORW)
   {
      driveStraight(AUTO_DRIVE_FORWARD_SPEED);
   }
   else if (autoMode == BACK)
   {
      driveStraight(AUTO_DRIVE_REVERSE_SPEED);
   }

}

