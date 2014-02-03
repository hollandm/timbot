/*
* The MPU-6050 is a combination sensor including temp, gyro and accel.
 * http://invensense.com/mems/gyro/documents/RM-MPU-6000A.pdf
 * 
 * Author: Jaimiey Sears
 */

#include <Wire.h>

//device Hex codes to retrieve various values
#define SLEEP 0x6B
#define ACCEL_X_H  0x3B
#define ACCEL_X_L  0x3C
#define ACCEL_Y_H  0x3D
#define ACCEL_Y_L  0x3E
#define ACCEL_Z_H  0x3F
#define ACCEL_Z_L  0x40

//define different things that can go wrong
//(for debugging purposes)
#define SUCCESS              0
#define MPU_DETECTION_ERROR  -1
#define MPU_READ_ERROR       -2
#define MPU_WRITE_ERROR      -3

int deviceI2CAddress;

void setup(){
  Wire.begin();  //set up I2C bus
  Serial.begin(9600); //set up to recieve data

  //scan for an available device
  Serial.println("Scanning for an available device...");

  //try to find at device
  int addressFound;
  while (addressFound != 0){
    addressFound = scanForI2C(&deviceI2CAddress);
    if(addressFound == -1) {
      Serial.println("Device not found, trying again...");
    }
  }
  //print the good news once a device is found
  Serial.print("Success! Device found at\t0x");
  Serial.println(deviceI2CAddress,HEX);
  Serial.println("Done scanning.");
  Serial.println();

  //wake the sensor
}

void loop(){
  int error;
  //Serial.println("Requesting data...");

  byte accelData[6];
  
  
  //read the sensor values, storing them in the struct.
  //check for errors at the same time
  if (MPUread(ACCEL_X_H,1,&accelData[0]) != SUCCESS){
    Serial.println("Read Error");
  }
  if (MPUread(ACCEL_X_L,1,&accelData[1]) != SUCCESS){
    Serial.println("Read Error");
  }
  if (MPUread(ACCEL_Y_H,1,&accelData[2]) != SUCCESS){
    Serial.println("Read Error");
  }
  if (MPUread(ACCEL_Y_L,1,&accelData[3]) != SUCCESS){
    Serial.println("Read Error");
  }
  if (MPUread(ACCEL_Z_H,1,&accelData[4]) != SUCCESS){
    Serial.println("Read Error");
  }
  if (MPUread(ACCEL_Z_L,1,&accelData[5]) != SUCCESS){
    Serial.println("Read Error");
  }
  
  int16_t * ptr = (int16_t *)&accelData[0];
 
  //print values
  Serial.print("Accelleration (x y z):\t");
  Serial.print(*ptr,DEC);
  ptr = (int16_t *)&accelData[1];
  Serial.print("\t");
  Serial.print(*ptr,DEC);
  ptr = (int16_t *)&accelData[2];
  Serial.print("\t");
  Serial.println(*ptr,DEC);
  
  delay(1000);
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

