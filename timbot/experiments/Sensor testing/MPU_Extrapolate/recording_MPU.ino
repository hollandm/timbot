int beginRecording () {
  if (recording){
    return ALREADY_RECORDING;
  }
  recording = true;
  return SUCCESS;
}

void endRecording() {
  recording = false;
}

void extrapolate(int * a, int * v, int * s) {
    *v += *a;
    *s += *v;
}

void reportData(){
  Serial.print("A: ");
  Serial.print(*mostRecentA,DEC);
  Serial.print(" V: ");
  Serial.print(*mostRecentV,DEC);
  Serial.print(" S: ");
  Serial.println(*mostRecentS,DEC);
}
