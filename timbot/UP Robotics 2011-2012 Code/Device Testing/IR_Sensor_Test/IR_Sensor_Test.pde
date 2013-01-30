/*
  AnalogReadSerial
 Reads an analog input on pin 0, prints the result to the serial monitor 
 
 This example code is in the public domain.
 */

float voltStep = 0.004882815; //(5V/1024)
//adjust calibrationNum and power to calibrate the sensor to actual values
int calibrationNum = 55;     
float power = -1.1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float sensorValue = analogRead(A3);
  //convert analogRead value into volts
  float volts = sensorValue * voltStep;
  
  //calculate distance in centimeters
  float distance = calibrationNum * pow(volts, power);
  float distancein = distance / 2.54;
  /*
  if (distancein < 12)
  {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }
  */
  //print distance to serial
  Serial.println(distancein);
  delay(1000);  //wait one second before next reading.
}
