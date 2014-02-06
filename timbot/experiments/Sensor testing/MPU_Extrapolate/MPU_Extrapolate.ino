/*
* The MPU-6050 is a combination sensor including temp, gyro and accel.
 * Device datasheet: http://invensense.com/mems/gyro/documents/RM-MPU-6000A.pdf
 * 
 * Author: Jaimiey Sears
 * Revision: 2-3-2014
 */

#include <Wire.h>

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
#define CMD_GO  'g'
#define CMD_STOP  's'
#define CMD_REPORT  'd'

//define different things that can go wrong
//(for debugging purposes)
#define SUCCESS               0
#define MPU_DETECTION_ERROR  -1
#define MPU_READ_ERROR       -2
#define MPU_WRITE_ERROR      -3
#define MPU_ADDR_REQ_ERROR   -4
#define ALREADY_RECORDING    -5

int deviceI2CAddress;
boolean recording = false;

int * mostRecentA = NULL;
int * mostRecentV = NULL;
int * mostRecentS = NULL;

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
  Serial.println(" done!");
}

void loop(){
  int error;

  //listen for serial commands
  byte msg;
  if (Serial.available() > 0){
    msg = Serial.read();
    
    //how to react
    switch (msg) {
    case CMD_GO:
      beginRecording();
    case CMD_STOP:
      endRecording();
      Serial.println("...stopped.");
      break;
    case CMD_REPORT:
      Serial.println("Sending data...");
      reportData();
      break;
    default:
      Serial.println("I don't understand that command.");
    }
  }

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
  double tempF = tempC*1.8 + 32.0;

  *mostRecentA = accelData[1]; //y
  if(recording){
    extrapolate(mostRecentA,mostRecentV,mostRecentS);
  }
  delay(50);
}

/*
* The function looks for a device
 * @param  a the address of the variable to write the device address to.
 * @return  0 success
 * @return  -1 failure
 */
int scanForI2C(int * a){
  byte error;
  for(byte addr = 1; addr < 127; addr++){
    Wire.beginTransmission(addr);
    error = Wire.endTransmission();
    if(error == 0){
      *a = (int)addr; //write the address found to the global var
      return SUCCESS;
    }
  }
  //if no devices found, return the error
  return MPU_DETECTION_ERROR;
}


