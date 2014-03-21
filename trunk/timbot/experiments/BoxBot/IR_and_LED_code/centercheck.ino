int centered(struct dataStore data) {
  int centerBuffer = 50;
  if (abs(data.avg0 - data.avg1) < centerBuffer && abs(data.avg1 - data.avg2) < centerBuffer){
    return 1;
  }
  else {
    return 0;
  }
}
