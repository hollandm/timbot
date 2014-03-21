void running(int runAmount){
  //read data values
  data.D0 = analogRead(SENSOR_PIN_F);
  data.D1 = analogRead(SENSOR_PIN_B);
  data.D2 = analogRead(SENSOR_PIN_R);
  data.D3 = analogRead(SENSOR_PIN_L);
  
  //add to array in place of the oldest sample
  arrayInsert(data.run0, data.D0, data.insertIndex);
  arrayInsert(data.run1, data.D1, data.insertIndex);
  arrayInsert(data.run2, data.D2, data.insertIndex);
  arrayInsert(data.run3, data.D3, data.insertIndex);
  //point the indexer at the oldest sample
  if (data.insertIndex < runAmount){
    data.insertIndex++;
  }
  else {
    data.insertIndex = 0;
  }
  
  //take the most recent sums
  data.sum0 = sumArray(data.run0, runAmount);
  data.sum1 = sumArray(data.run1, runAmount);
  data.sum2 = sumArray(data.run2, runAmount);
  data.sum3 = sumArray(data.run3, runAmount);
  
  //take the most recent averages
  data.avg0 = data.sum0/runAmount;
  data.avg1 = data.sum1/runAmount;
  data.avg2 = data.sum2/runAmount;
  data.avg3 = data.sum3/runAmount;
}

//sums all elements in an array
long sumArray(int input[], int runAmount) {
  long sum = 0;
  for(int i = 0; i < runAmount; i++){
    sum += input[i];
  }
  return sum;
}

//inserts a specified value into an array
void arrayInsert(int input[], int value, int index) {
  input[index] = value;
}

