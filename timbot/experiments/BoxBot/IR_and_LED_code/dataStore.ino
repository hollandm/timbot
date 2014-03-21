//function zero: sets all fields in the provided struct to 0.
void zero(struct dataStore d) {
  d.D0 = 0;
  d.D1 = 0;
  d.D2 = 0;
  d.D3 = 0;
  
  d.sum0 = 0;
  d.sum1 = 0;
  d.sum2 = 0;
  d.sum3 = 0;
  
  d.avg0 = 0;
  d.avg1 = 0;
  d.avg2 = 0;
  d.avg3 = 0;
}

//cm = 0.0544x^3 - 0.6527x^2 - 7.8283^x + 108.18
float toCentimeters(int value) {
  return 0.0544*CUBE(value) - 0.6527*SQUARE(value) - 7.8283*value + 108.18;
}
