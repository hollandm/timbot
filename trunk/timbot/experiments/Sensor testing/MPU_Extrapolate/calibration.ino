//sums up an array of size SAMPLE_AMOUNT
//using pointers.
//also moves the whole array down one.
int runningAverage(int * input){
  int sum=0;
  for(int i = 0; i < SAMPLE_AMOUNT; i++){
    sum += *(input + i);
  }
  for(int i = SAMPLE_AMOUNT-1; i > 0; i--){
    //move each datum to a HIGHER position in the array
    *(input + i) = *(input + i - 1);
  }
  return (sum/SAMPLE_AMOUNT);
}

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


