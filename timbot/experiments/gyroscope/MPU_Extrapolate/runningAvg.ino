//sums all elements in an array
long sumArray(int * input){
  long sum = 0;
  for(int i = 0; i < SAMPLE_AMOUNT; i++){
    sum += *(input + i);
  }
  return sum;
}

//shifts all the elements in an array up one
//inserts first into the input[0] position
void shiftArray(int * input,int first, int size){
  for(int i = size-1; i > 0; i--){
    //move each datum to a HIGHER position in the array
    *(input + i) = *(input + i - 1);
  }
  *input = first;
}
