/*
* getAccel()
* Description: gets all three values of acceleration (x,y,z)
* and stores them in an array
* dataLoc: a pointer to the 1st element in the array
*/
int getAccel(byte * dataLoc) {
  //read the sensor values, storing them in the array.
  //check for errors at the same time.
  //NOTE: because the MPU values are "backwards",
  //(L should be the 1st element in the array for conversion to int)
  //the values are stored {X_L, X_H, Y_L, Y_H, Z_L, Z_H}
  
  if (MPUread(ACCEL_X_L, &dataLoc[0]) != SUCCESS){
    return MPU_READ_ERROR;
  }
  if (MPUread(ACCEL_X_H, &dataLoc[1]) != SUCCESS){
    return MPU_READ_ERROR;
  }
  
  if (MPUread(ACCEL_Y_L, &dataLoc[2]) != SUCCESS){
    return MPU_READ_ERROR;
  }
  if (MPUread(ACCEL_Y_H, &dataLoc[3]) != SUCCESS){
    return MPU_READ_ERROR;
  }
  
  if (MPUread(ACCEL_Z_L, &dataLoc[4]) != SUCCESS){
    return MPU_READ_ERROR;
  }
  if (MPUread(ACCEL_Z_H, &dataLoc[5]) != SUCCESS){
    return MPU_READ_ERROR;
  }
  
  return SUCCESS;
};

int getTemp(byte * dataLoc) {
  if (MPUread(TEMP_L, &dataLoc[0]) != SUCCESS){
    return MPU_READ_ERROR;
  }
  if (MPUread(TEMP_H, &dataLoc[1]) != SUCCESS) {
    return MPU_READ_ERROR;
  }
  return SUCCESS;
};

/*
* MPUread()
* Description: read data from the MPU
* addr: the address of the value to read
* numBytes: the number of bytes to read
* data: a pointer to the place to store data
*/
int MPUread(int addr, byte * data){
  int n;
  int numBytes = 1;
  
  Wire.beginTransmission(deviceI2CAddress);
  if (Wire.write(addr) != 1){
    return MPU_READ_ERROR;
  }
  if (Wire.endTransmission(false) != 0){ //hold the I2C-bus
    return MPU_DETECTION_ERROR;
  }
  
  Wire.requestFrom(deviceI2CAddress,numBytes,true); //release bus
  
  //get data
  int i = 0;
  while(Wire.available()){
    data[i] = Wire.read();
    i++;
  }
  if(i != numBytes){
    return MPU_READ_ERROR;
  }
};


