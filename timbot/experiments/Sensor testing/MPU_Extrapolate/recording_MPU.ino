
void extrapolate(int * a, int * v, int * s) {
//  if(abs(*a) < 1000){
//    *a = 0;
//  }
  *v += *a;
  *s += *v;
}

//prints recorded data to serial
void reportData(){
  Serial.print("A:\t");
  Serial.print(*mostRecentA,DEC);
  Serial.print("\tV:\t");
  Serial.print(*mostRecentV,DEC);
  Serial.print("\tS:\t");
  Serial.println(*mostRecentS,DEC);
}

//sets recorded data to 0
void clearData(){
  *mostRecentA = 0;
  *mostRecentV = 0;
  *mostRecentS = 0;
}




