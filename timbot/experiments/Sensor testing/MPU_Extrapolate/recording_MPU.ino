
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

void clearData(){
  *mostRecentA = 0;
  *mostRecentV = 0;
  *mostRecentS = 0;
}
