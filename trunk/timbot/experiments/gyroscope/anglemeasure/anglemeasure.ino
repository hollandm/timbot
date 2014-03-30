#include <Wire.h>

//device Hex codes to retrieve various values.
//codes can be found in the datasheet linked above
#define REFERENCE_MPU  0x69
#define ARM_MPU        0x68

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

//define different things that can go wrong
//(for debugging purposes)
#define SUCCESS              0
#define MPU_DETECTION_ERROR  -1
#define MPU_READ_ERROR       -2
#define MPU_WRITE_ERROR      -3
#define MPU_ADDR_REQ_ERROR   -4

#define MPU1_AD0_PIN 2
#define MPU2_AD0_PIN 3

#define SQ(x) (x)*(x)

typedef struct dataStorage{
  int accelX;
  int accelY;
  int accelZ;

  int zeroX;
  int zeroY;
  int zeroZ;

  long posX;
  long posY;
  long posZ;

  int gyroX;
  int gyroY;
  int gyroZ;
  int gyroZprev;

  long angleX;
  long angleY;
  long angleZ;

  int tempC;
  int tempF;
}
DataSet;

DataSet ref;
DataSet arm;
int loopCount;

void setup(){
  Wire.begin();  //set up I2C bus
  Serial.begin(9600); //set us up to recieve data

  pinMode(MPU1_AD0_PIN, OUTPUT);
  digitalWrite(MPU1_AD0_PIN, LOW); //MPU1 will be 0x68
  pinMode(MPU2_AD0_PIN, OUTPUT);
  digitalWrite(MPU2_AD0_PIN, HIGH); //MPU2 will be 0x69

  //scan for an available device
  Serial.println("Scanning for available devices...");
  for(byte addr = 0; addr < 127; addr++){
    Wire.beginTransmission(addr);
    byte error = Wire.endTransmission();
    if(error == 0){
      Serial.print("Device found at address 0x");
      Serial.println(addr,HEX);
    }
  }
  Serial.print("Waking the Sensors...");
  byte clr = 0;
  MPUWrite(REFERENCE_MPU, SLEEP, &clr);
  MPUWrite(ARM_MPU, SLEEP, &clr);
  Serial.println(" done!\n");
  Serial.println("Calibrating, do not move the sensors.");
  Serial.print("Calibrating in 3");
  delay(1000);
  Serial.print(" 2");
  delay(1000);
  Serial.println(" 1");
  delay(1000);
  getZeroValues(&ref, REFERENCE_MPU);
  getZeroValues(&arm, ARM_MPU);
}

void loop(){

  int accelData[3];
  getAccel(REFERENCE_MPU, (byte *)accelData);
  ref.accelX = accelData[0];
  ref.accelY = accelData[1];

  getAccel(ARM_MPU, (byte *)accelData);
  arm.accelX = accelData[0];
  arm.accelY = accelData[1];

  int gyroData[3];
  getGyro(ARM_MPU, (byte *)gyroData);
  arm.gyroZprev = arm.gyroZ;
  arm.gyroZ = gyroData[2]; //rotational velocity in x-y plane

  //float trueArmY = arm.accelY - SQ(arm.gyroZ)*ARM_RADIUS;

  double angle = atan2(arm.accelY,arm.accelX-arm.zeroX)
    -atan2(ref.accelY,ref.accelX-ref.zeroX);

  if(loopCount % 100 == 0){
    Serial.print("Angle measurement:\t");
    Serial.println(angle*360/(2*PI), DEC);
  }
  loopCount++;
}


int getZeroValues(struct dataStorage * dataPtr, byte addr){
  int accelData[3];
  getAccel(addr, (byte *)accelData);
  (*dataPtr).zeroX = accelData[0];
  (*dataPtr).zeroY = accelData[1];
  (*dataPtr).zeroZ = accelData[2];
  return 0;
}


