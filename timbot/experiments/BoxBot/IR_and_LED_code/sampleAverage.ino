void sample(struct dataStore data, int sampleAmount, int pin){
  for (int i = 0; i < sampleAmount; i++) {
    // read the value(s) from the sensor:
    data.value = analogRead(pin);
    data.sum += data.value;
  }
  //average them
  data.avg = data.sum/sampleAmount;
}

