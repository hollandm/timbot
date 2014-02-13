/*
* getAccel()
* Description: gets all three values of acceleration (x,y,z)
* and stores them in an array
* dataLoc: a pointer to the 1st element in the array
* the array should be at least 6 bytes in size
*/
int getAccel(byte * dataLoc) {
  int error;
  //read the sensor values, storing them in the array.
  //check for errors at the same time.
  //NOTE: because the MPU values are "backwards",
  //(L should be the 1st element in the array for conversion to int)
  //the values are stored {X_L, X_H, Y_L, Y_H, Z_L, Z_H}
  
  if (error = MPURead(ACCEL_X_L, &dataLoc[0]) != SUCCESS){
    return error;
  }
  if (error = MPURead(ACCEL_X_H, &dataLoc[1]) != SUCCESS){
    return error;
  }
  
  if (error = MPURead(ACCEL_Y_L, &dataLoc[2]) != SUCCESS){
    return error;
  }
  if (error = MPURead(ACCEL_Y_H, &dataLoc[3]) != SUCCESS){
    return error;
  }
  
  if (MPURead(ACCEL_Z_L, &dataLoc[4]) != SUCCESS){
    return error;
  }
  if (MPURead(ACCEL_Z_H, &dataLoc[5]) != SUCCESS){
    return error;
  }
  return SUCCESS;
};

/*==============================================================
* getGyro()
* Description: Gets the raw gyro values (x,y,z)
* dataLoc: the location where the data should be stored.
* should be at least 6 bytes in size
*/
int getGyro(byte * dataLoc) {
  if (MPURead(GYRO_X_L, &dataLoc[0]) != SUCCESS){
    return MPU_READ_ERROR;
  }
  if (MPURead(GYRO_X_H, &dataLoc[1]) != SUCCESS){
    return MPU_READ_ERROR;
  }
  
  if (MPURead(GYRO_Y_L, &dataLoc[2]) != SUCCESS){
    return MPU_READ_ERROR;
  }
  if (MPURead(GYRO_Y_H, &dataLoc[3]) != SUCCESS){
    return MPU_READ_ERROR;
  }
  
  if (MPURead(GYRO_Z_L, &dataLoc[4]) != SUCCESS){
    return MPU_READ_ERROR;
  }
  if (MPURead(GYRO_Z_H, &dataLoc[5]) != SUCCESS){
    return MPU_READ_ERROR;
  }
  return SUCCESS;
};
/*===========================================================
* getTemp()
* Description: Gets the raw temperature values
* dataLoc: the location where the data should be stored.
* should be at least 2 bytes in size
*/
int getTemp(byte * dataLoc) {
  if (MPURead(TEMP_L, &dataLoc[0]) != SUCCESS){
    return MPU_READ_ERROR;
  }
  if (MPURead(TEMP_H, &dataLoc[1]) != SUCCESS) {
    return MPU_READ_ERROR;
  }
  return SUCCESS;
};

/*===========================================================
* MPURead()
* Description: read data from the MPU
* addr: the address of the value to read
* numBytes: the number of bytes to read
* data: a pointer to the place to store data
*/
int MPURead(int addr, byte * data){
  int numBytes = 1;
  
  Wire.beginTransmission(deviceI2CAddress);
  if (Wire.write(addr) != 1){
    return MPU_ADDR_REQ_ERROR;
  }
  if (Wire.endTransmission(false) != SUCCESS){ //hold the I2C-bus
    return MPU_DETECTION_ERROR;
  }
  
  Wire.requestFrom(deviceI2CAddress,numBytes,true); //release bus after
  
  //get data
  int i = 0;
  while(Wire.available()){
    data[i] = Wire.read();
    i++;
  }
  if(i != numBytes){
    return MPU_READ_ERROR;
  }
  return SUCCESS;
};


/*=========================================================
* MPUWrite
* Description: Writes 1 byte of data to the specified address
* addr: the address to write to
* data: the location of the data to write
*/
int MPUWrite(int addr, byte * data){
  Wire.beginTransmission(deviceI2CAddress);
  if (Wire.write(addr) != 1){
    return MPU_ADDR_REQ_ERROR;
  }
  if(Wire.write(data,1) != 1){
    return MPU_WRITE_ERROR;
  }
  if (Wire.endTransmission(true) != SUCCESS){
    return MPU_DETECTION_ERROR;
  }
  return SUCCESS;
};

//converts a byte to an int, but makes the byte the upper half.
int byte2int(byte b){
  int i;
  if (b & B10000000 == B10000000){
    *((byte *)&i) = b;
    *(((byte *)&i) + 1) = B11111111;
  }
  return i;
}
