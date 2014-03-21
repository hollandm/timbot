void sample(int sampleAmount){
  for (int i = 0; i < sampleAmount; i++) {
    // read the value(s) from the sensor:
    data.D0 = analogRead(SENSOR_PIN_F);
    data.D1 = analogRead(SENSOR_PIN_B);
    data.D2 = analogRead(SENSOR_PIN_R);
    data.D3 = analogRead(SENSOR_PIN_L);
    
    data.sum0 += data.D0;
    data.sum1 += data.D1;
    data.sum2 += data.D2;
    data.sum3 += data.D3;
  }

  data.avg0 = data.sum0/sampleAmount;
  data.avg1 = data.sum1/sampleAmount;
  data.avg2 = data.sum2/sampleAmount;
  data.avg3 = data.sum3/sampleAmount;
}

