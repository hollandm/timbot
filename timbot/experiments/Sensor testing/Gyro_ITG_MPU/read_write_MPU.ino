int MPUread(int addr, int numBytes, byte * data){
  int n;
  
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
}

int MPUwrite(int wake, int numBytes, byte * d){
  
}
