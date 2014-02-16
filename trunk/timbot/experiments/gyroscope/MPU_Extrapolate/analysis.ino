//compares the elements in the array
int analyze(int * arry){
  if(mode == STOPPING && abs(arry[0]) < 500){
    return STOPPED;
  }
  else if(mode == STOPPED && abs(arry[0]) > 1000){
    return STARTING;
  }
  //if we've just peaked
  else if(mode == STARTING && abs(arry[0]) < 500){
    return GOING;
  }
  else if(mode == GOING && abs(arry[0]) > 1000){
    return STOPPING;
  }
  return UNCHANGED;
}
