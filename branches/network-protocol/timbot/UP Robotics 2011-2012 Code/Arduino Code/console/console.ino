/* Console:
 * This Arduino program runs on the Arduino inside the Mission Control Room Console
 * Box. It checks the state of the switches to determine operating mode,
 * and transmits this over the Serial to the Server program running on the computer.
 *
 */ 


//--------------- Constants ---------------\\
//Operating mode constants
const byte STOP = 0;
const byte FORW = 1;
const byte MAN  = 2;
const byte BACK = 3;

//Input Pins
const int P_AUT  = 2;    // Begin Autonomous Pin 
const int P_KEY  = 3;    // Key Swtiches
const int P_RED  = 4;    // Big Red Button
const int P_NUM  = 5;    // Number Pad
const int P_MIS  = 6;    // Missile Switch

//Output Pins
const int P_NUM_LED = 8; // LED for Number Pad
const int P_RED_LED = 9; // LED for Red Button (Only on if Manual mode)


const int AuthorizationLength = 6;   // Number of times the num pad needs to be pressed

//--------------- Variables ---------------\\

// For storing the state of the switches:
int s_auto;        // State of the autonomous switch
int s_key;         // State of the key switches
int s_red;         // State of the red button switch
int s_missile;     // State of the missle switch
int s_numPad;      // State of the number pad

int numbersPressed; // Keeps track of the number of times a number is pressed
boolean wasPressed; // For telling if the button was pressed previously

byte mode;         // Which Operating mode are we in?
/* Operating Mode:
    0 = Stopped       (STOP)
    1 = Autonomous    (AUTO)
    2 = Manual        (MAN)
*/

void setup() 
{
  int index;
  // Define the input pins
  for (index = 2; index < 7; index++)
  {
     pinMode(index, INPUT); 
  }
  
  // Define the output pin
  pinMode(P_NUM_LED, OUTPUT);
  pinMode(P_RED_LED, OUTPUT);
  
  // Setupt the serial connection to the computer
  Serial.begin(9600);
  
  mode = STOP;
  numbersPressed = 0;
  wasPressed = false;
}

void loop() 
{
  readPins();
  interpret();
  if (numbersPressed == AuthorizationLength)
  {
     digitalWrite(P_NUM_LED, HIGH);
  }
  else if (numbersPressed > AuthorizationLength)
  {
     digitalWrite(P_NUM_LED, LOW);
     numbersPressed = 0;
  }
  else
  {
     digitalWrite(P_NUM_LED, LOW);
  }
  
  
  if (mode == MAN)
  {
     digitalWrite(P_RED_LED, HIGH);
  }
  else
  {
     digitalWrite(P_RED_LED, LOW);
  }
  
  
  Serial.write((byte)mode);
  /*
  int pinRead = digitalRead(InputPin);
  delay(10);
  if (pinRead) {
    Serial.write((byte)1);
    //Serial.println((byte)1);
    digitalWrite(OutputPin,HIGH);
  } else {
    Serial.write((byte)0);
    //Serial.println((byte)0);
     digitalWrite(OutputPin,LOW);
  }
  */
  
}

// Read in all of the switch pins and set the proper global variables
void readPins()
{
  s_auto    = digitalRead(P_AUT);
  s_key     = digitalRead(P_KEY);
  s_red     = digitalRead(P_RED);
  s_missile = digitalRead(P_MIS);
  s_numPad  = digitalRead(P_NUM);
  
}

// Interprets the state of the pins
void interpret()
{
  // For the keypad:
  if (!s_numPad)  // If it is not pressed, lets clear it
  {
     wasPressed = false; 
  }
  else if (s_numPad && !wasPressed)  // First time the button is pressed
  {
     numbersPressed++;
     wasPressed = true;
  }
  else     // Button is pressed, but was read as pressed previously
  {
     // Do nothing
  }
  
  boolean drivable = false;
  // Check that we can drive
  if (s_key && s_missile)
  {
     drivable = true;
  }
  else
  {
     drivable = false; 
  }
  // Now check if we are manual, forward autonomous, reverse autonomous
  if (drivable)
  {
     if(!s_red)
     {
        mode = MAN; 
     }
     else if (s_red && s_auto)  // If auto switch (first switch) is up, drive forward
     {
        mode = FORW; 
     }
     else if (s_red && !s_auto) // drive in reverse
     {
        mode = BACK; 
     }
     else  // Shouldn't actually get here
     {
        mode = STOP; 
     }
  }
  else
  {
     mode = STOP; 
  }
  
  /*
  // For the operating mode:
  if (s_auto && !(s_key && s_missile && s_red) && !s_red)
  {
     mode = AUTO; // Autononomous switch, and none of the others
  }
  else if (s_key && s_missile && s_red)
  {
     mode = MAN;  // key swiches, missile switch, and red button are pressed
  }
  else if (s_red)  // Red stop button without missile and key switches
  {
     mode = STOP; 
  }
  else   // Just in case
  {
     mode = STOP; 
  }
  */
}
