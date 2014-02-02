/*
  switchTest Sketch
  Author: UP Robotics
  
  This sketch probes particular input pins to see if
  the buttons are closed. If they are, the program
  outputs to turn on an LED.
  
 */
 
 //PIN CONSTANTS
 int SW0 = 3;
 int SW1 = 4;
 int SW2 = 5;
 int LED0 = 8;
 
 boolean probeSwitches();
 //Sets up the program
 void setup(){
   pinMode(SW0,INPUT);
   pinMode(SW1,INPUT);
   pinMode(SW2,INPUT);
   pinMode(LED0,OUTPUT);
 }//setup
 
 //The main loop
 void loop(){
  if (probeSwitches())
   digitalWrite(LED0,HIGH);
 else 
   digitalWrite(LED0,LOW);
 }//loop
 
 //Probes the switches, returning 1 if all closed
 //and 0 otherwise
 boolean probeSwitches(){
   if ( !digitalRead(SW0) && !digitalRead(SW1) && !digitalRead(SW2))
     return true;
   else 
      return false;
 }//probeSwitches
 
