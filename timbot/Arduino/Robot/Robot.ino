

//--------------- Constants ---------------\\


const byte BUFFER_SYNC = 101;

//Motor controller pin defs
const int ARM = 4;             //Digital
const int BUCKET = 6;          //Digital

//Pin to check if E-Button has been pressed
const int E_BUTTON = 10;       //Digital

//IR sensor pin defs
const int IR_FRONT = 2;        //Analog
const int IR_BACK = 3;         //Analog
const int IR_RIGHT = 4;        //Analog
const int IR_LEFT = 5;         //Analog

//Gyroscope pin defs
const int GYRO = 6;            //Analog

//Potentiometer pin defs
const int POT_ARM = 8;        //Analog
const int POT_BUCKET = 9;      //Analog

//------Global Vars------\\


boolean hasStarted = false;  //if EStop button is pressed after operations have started then we need to shutdown the computer
int Shutdown = 0;

int GyroPitch = 0;
int GyroYaw = 0;

int FrontIR = 0;
int BackIR = 0;
int LeftIR = 0;
int RightIR = 0;

int ArmPotentiometer = 0;
int BucketPotentiometer = 0;

const float DRIVEMAX = 0.49;  // Up to 0.5 as max


//------Code N Stuff------\\


void setup() {
 //Set up pin modes
    pinMode(ARM,          OUTPUT);
    pinMode(BUCKET,       OUTPUT);
    pinMode(E_BUTTON,     INPUT);
    
    
    Serial.begin(9600);
}

void loop() {
  
//  updateSensorValues();
  recieveInstructions();
}

/*
 * Read instructions from the bot top
 * execute them as needed
 */
void recieveInstructions() {
  
  //Read from serial
  if (Serial.available() <= 1) {return;}
  hasStarted = true;  //operations have begun

  if (Serial.read() != BUFFER_SYNC) {return;}  
  
  byte recieve[2];
  recieve[0] = byte(Serial.read()); //Actuate Arm
  recieve[1] = byte(Serial.read()); //Actuate Bucket
  
  float a = (recieve[0]-50)/50.0;
  float b = (recieve[1]-50)/50;
//  Serial.println(recieve[0]);
//  Serial.println(a);
  actuateArm(a);
  
  //actuate and drive if needed
  

}

/*
 * read our values from sensors
 * convert them to standard units
 * send them to the bot-top
*/
void updateSensorValues() {
   
  readEStop();
  
  readGyro();
  
  readArmPotentiometer();
  readBucketPotentiometer();
  
  readFrontIR();
  readBackIR();
  readLeftIR();
  readRightIR();
    
  byte collected[9];
  
  //Does the BotTop need to preform an emergency shutdown?
  collected[0] = byte(Shutdown);
  
  collected[1] = byte(GyroPitch);
  collected[2] = byte(GyroYaw);
  
  collected[3] = byte(FrontIR);
  collected[4] = byte(BackIR);
  collected[5] = byte(LeftIR);
  collected[6] = byte(RightIR);
  
  
  collected[7] = byte(ArmPotentiometer);
  collected[8] = byte(BucketPotentiometer);
  
  Serial.write(collected,9);
}

void readGyro() {}

void readArmPotentiometer() {}
void readBucketPotentiometer() {}

void readFrontIR() {}
void readBackIR() {}
void readLeftIR() {}
void readRightIR() {}


/*
 * Checks if the EStop button is pressed
 * if the state changes and the button is down then
 * the EStop button has been pressed and a signal
 * the BotTop to shutdown
 */
void readEStop() {
  hasStarted = true;
  Shutdown = 0;
  /*
  int button = digitalRead(E_BUTTON);
  
   if (button == HIGH) {
      hasStarted = true;
   } else if (button == LOW) {
     
      if (hasStarted == false) {
         hasStarted = true;
      } else {
         Shutdown = 1;
      }
   }
   */
}

/* 
 * Actuate components of the arm to the desired distance
 * based on potentiomater readings
 * 
 * Arm given priority over bucket, regarding avoidance of
 * hitting the bot body
 */
//void actuateArm(int desiredDistance) {}
//void actuateBucket(int desiredDistance) {}


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
  //*
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

