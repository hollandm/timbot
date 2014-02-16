/*
* The function looks for a device. it stops at the first device it finds.
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


