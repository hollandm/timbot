/*
* The MPU-6050 is a combination sensor including temp, gyro and accel.
 * Device datasheet: http://invensense.com/mems/gyro/documents/RM-MPU-6000A.pdf
 * 
 * Author: Jaimiey Sears
 * Revision: 2-3-2014
 */

#include <Wire.h>

#define SAMPLE_AMOUNT 5

//device Hex codes to retrieve various values.
//codes can be found in the datasheet linked above
#define SLEEP      0x6B
#define ACCEL_X_H  0x3B
#define ACCEL_X_L  0x3C
#define ACCEL_Y_H  0x3D
#define ACCEL_Y_L  0x3E
#define ACCEL_Z_H  0x3F
#define ACCEL_Z_L  0x40

#define TEMP_H     0x41
#define TEMP_L     0x42

#define GYRO_X_H   0x43
#define GYRO_X_L   0x44
#define GYRO_Y_H   0x45
#define GYRO_Y_L   0x46
#define GYRO_Z_H   0x47
#define GYRO_Z_L   0x48

//defined input commands
#define CMD_GO      'g'
#define CMD_STOP    's'
#define CMD_REPORT  'd'
#define CMD_CLR     'c'

//define different things that can go wrong
//(for debugging purposes)
#define SUCCESS               0
#define MPU_DETECTION_ERROR  -1
#define MPU_READ_ERROR       -2
#define MPU_WRITE_ERROR      -3
#define MPU_ADDR_REQ_ERROR   -4


//analysis constants
#define STOPPED   0
#define STARTING  1
#define GOING     2
#define STOPPING  3
#define UNCHANGED 4

int deviceI2CAddress;
boolean recording = false;

//used for a running average
int avgX[SAMPLE_AMOUNT] = {
  0};
int avgY[SAMPLE_AMOUNT] = {
  0};
int avgZ[SAMPLE_AMOUNT] = {
  0};
  
//used for data analysis
int averaged[2] = {0};
int loopCount = 0;
int mode = STOPPED;
int vel = 0;

void setup(){
  Wire.begin();  //set up I2C bus
  Serial.begin(9600); //set up to recieve data

  //scan for an available device
  Serial.println("Scanning for an available device...");

  //try to find at device
  int addressNotFound = true;
  while (addressNotFound){
    addressNotFound = scanForI2C(&deviceI2CAddress) == MPU_DETECTION_ERROR;
    if(addressNotFound) {
      delay(500);
      Serial.println("Device not found, trying again...");
    }
  }
  //print the good news once a device is found
  Serial.print("Success! Device found at\t0x");
  Serial.println(deviceI2CAddress,HEX);
  Serial.println("Done scanning.");

  //wake the sensor
  Serial.print("Waking the Sensor...");
  byte clr = 0;
  MPUWrite(SLEEP, &clr);
  Serial.println(" done!\n");


}

//==============================================================
void loop(){
  int error;
  
  //get the sensor values, checking for errors
  int accelData[3];  //place to store values
  //get accel values
  error = getAccel((byte *)accelData);
  if (error != SUCCESS){
    Serial.print("Error reading accellerometer: ");
    Serial.println(error,DEC);
  }

  int gyroData[3];
  error = getGyro((byte *)gyroData);
  if (error != SUCCESS){
    Serial.print("Error reading gyroscope: ");
    Serial.println(error,DEC);
  }

  int tempData[1];
  error = getTemp((byte *)tempData);
  if (error != SUCCESS) {
    Serial.print("Error reading temperature: ");
    Serial.println(error,DEC);
  }

  //convert to Celsius
  double tempC = tempData[0]/340.0 + 36.53;
  //convert to Ferenheight
  double tempF = tempC*1.8 + 32.0;

  int averagedAccel[3];
  //take the running average
  shiftArray(avgX,accelData[0],SAMPLE_AMOUNT);
  averagedAccel[0] = sumArray(avgX)/SAMPLE_AMOUNT;
  shiftArray(avgY,accelData[1],SAMPLE_AMOUNT);
  averagedAccel[1] = sumArray(avgY)/SAMPLE_AMOUNT;
  shiftArray(avgZ,accelData[2],SAMPLE_AMOUNT);
  averagedAccel[2] = sumArray(avgZ)/SAMPLE_AMOUNT;

  //put y into the averaged array
  shiftArray(averaged,averagedAccel[1],2);
  if (analyze(averaged)!= UNCHANGED){
    mode = analyze(averaged);
  }
  if (mode == STARTING){
    vel += averaged[0];
  }
  if (mode == STOPPED){
    vel = 0;
  }
  //assume it is opposite (still adding them)
  if (mode == STOPPING){
    vel += averaged[0];
  }
  

  if(loopCount < 250){
    Serial.print(loopCount);
    Serial.print("\t");
    Serial.print(averagedAccel[0]);
    Serial.print("\t");
    Serial.print(averagedAccel[1]);
    Serial.print("\t");
    Serial.print(averagedAccel[2]);
    Serial.print("\t");
    Serial.print(vel);
    Serial.println();
  }
  delay(50);

  loopCount++;
}







