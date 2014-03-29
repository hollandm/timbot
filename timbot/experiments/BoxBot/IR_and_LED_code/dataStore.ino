//function zero: sets all fields in the provided struct to 0.
void zero(struct dataStore * d) {
  (*d).value = 0;  
  (*d).sum = 0;
  (*d).avg = 0;
  (*d).dist = 0;
}

int centered() {
  int centerBuffer = 50;
  if (abs(front.avg - back.avg) < centerBuffer && abs(right.avg - left.avg) < centerBuffer){
    return 1;
  }
  else {
    return 0;
  }
}

//cm = 0.0544x^3 - 0.6527x^2 - 7.8283^x + 108.18
double toCentimeters(int value) {
  return 0.0544*CUBE(value) - 0.6527*SQUARE(value) - 7.8283*value + 108.18;
}

void convertToDist(struct dataStore * data) {
  (*data).dist = toCentimeters((*data).avg);
}
