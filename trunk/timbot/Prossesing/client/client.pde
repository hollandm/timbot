/* Client:
 * This processing program runs on the computer on the Robot
 * It's purpose is to receive the joystick data over the network, and send
 * it to the Arduino that controls the robot
 *
 * Intial Network Functionality: Ryan Gasik
 * Last Modified: 3/13/12: Jess Tate- Updated
 */

//--------------- Library Imports ---------------\\
import hypermedia.net.*;      //For UDP Functions
import processing.serial.*;   //For Serial Communication to Arduino
import java.io.*;             //Not actually sure if we need this

//--------------- Constants ---------------\\
//Operating mode constants
const byte STOP = 0;
const byte FORW = 1;
const byte MAN  = 2;
const byte BACK = 3;

int RCVLEN = 7;  //Length of the received data packets
int SHUTDOWN = 42;
//--------------- Variables ---------------\\
UDP udp;        //UDP Connection
byte[] joy;     //For storing the joystick values sent over the UDP connection
boolean needToShutdown;
boolean hasShutdown;
/*
joy[0] is joystick a, x position.
joy[1] is joystick a, Y position.
joy[2] is joystick b, X position.
joy[3] is joystick b, Y position.
joy[4] is joystick a trigger.
joy[5] is joystick b trigger.
joy[6] is operating mode.
*/ 

Serial arduinoR; //For communicating with the Arduino on the 'R'obot


int SHUTDOWNON = 0;   // Set to 0 for not shutting down

//--------------- Primary Functions ---------------\\

void setup()
{
  udp = new UDP(this, 6000, "224.0.0.1");
  udp.listen(true);
  joy = new byte[RCVLEN];
  arduinoR = new Serial(this, Serial.list()[0], 9600);
  needToShutdown=false;
  hasShutdown = false;
}

void draw()
{
  int input;
  sendToArduino();
  if (arduinoR.available() > 0)
  {
    input = arduinoR.read();
    if (input == SHUTDOWN && !hasShutdown)
    {
       needToShutdown = true;
       shutdown();
    }
    println("Input: " + input);
  }
}

// Shuts down the computer
void shutdown()
{
   hasShutdown = true;
   if (SHUTDOWNON != 0)
   {
     open("rundll32 SHELL32.DLL,ShellExec_RunDLL " + "shutdown -s");
   }
   else
   {
      println("Shutdown"); 
   }
}

// Required Function to receive data over the UDP Connection
void receive(byte[] data)
{
  for(int i =0; i < RCVLEN; i++)
  {
    joy[i] = data[i];
    
  }
  
  println(joy[0] + " " + joy[1] + " " + joy[2] + " " + joy[3] + " " + joy[4]);
}

//--------------- Helper Functions ---------------\\
void sendToArduino()
{
  delay(100);
  arduinoR.write('a');
  arduinoR.write(joy[0]);
  
  arduinoR.write('b');
  arduinoR.write(joy[1]);
  
  arduinoR.write('c');
  arduinoR.write(joy[2]);
  
  arduinoR.write('d');
  arduinoR.write(joy[3]);
  
  arduinoR.write('e');
  arduinoR.write((-1)*joy[4]);
  
  arduinoR.write('f');
  arduinoR.write((-1)*joy[5]);
  
  arduinoR.write('m');
  arduinoR.write(joy[6]);    //Operating Mode
  
  
  //delayMicroseconds(100);
  //delay(1);
  //arduinoR.write(joy[2]);
  delay(1);
  /*
  // Send operating Mode first
  //arduinoR.write('m');
  //arduinoR.write(joy[6]);    //Operating Mode
  // Now send the rest
  //arduinoR.write('a');
  arduinoR.write(joy[0]);    //Joystick A, X Position
  //arduinoR.write('b');
  arduinoR.write(joy[1]);    //Joystick A, Y Position
  //arduinoR.write('c');
  arduinoR.write(joy[2]);    //Joystick B, X Position
  //arduinoR.write('d');
  arduinoR.write(joy[3]);    //Joystick B, Y Position
  //arduinoR.write('e');
  arduinoR.write(joy[4]);    //Joystick A Trigger
  //arduinoR.write('f');
  arduinoR.write(joy[5]);    //Joystick B Trigger
  
  arduinoR.write(joy[6]);
  */
}

