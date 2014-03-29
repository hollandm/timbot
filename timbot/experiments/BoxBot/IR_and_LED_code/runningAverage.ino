void running(struct dataStore * data, int runAmount, int pin){
  //read data value
  (*data).value = analogRead(pin);
  
  //add to array in place of the oldest sample
  (*data).run[(*data).insertIndex] = (*data).value;
  
  //point the indexer at the oldest sample
  if ((*data).insertIndex < runAmount){
    (*data).insertIndex++;
  }
  else {
    (*data).insertIndex = 0;
  }
  
  //take the most recent sum
  (*data).sum = sumArray((*data).run, runAmount);
  //take the most recent average
  (*data).avg = (*data).sum/runAmount;
}

//sums all elements in an array
long sumArray(int input[], int arrSize) {
  long sum = 0;
  for(int i = 0; i < arrSize; i++){
    sum += input[i];
  }
  return sum;
}
