/*
* This program averages a number of samples together, designed to
* read from an IR sensor.
*/

//the amount of times to sample per loop
#define SAMPLE_AMOUNT 500

int sensorPinL = A0;
int sensorPinR = A1;
int sensorValueL = 0;
int sensorValueR = 0;

void setup() {
  Serial.begin(9600);
};

void loop() {
  long sensorAverageL = 0;
  long sensorAverageR = 0;
  long sampleSumL = 0;
  long sampleSumR = 0;
  for (int i = 0; i < SAMPLE_AMOUNT; i++) {
    // read the value(s) from the sensor:
    // won't need this technically, but it might be useful later.
    sensorValueL = analogRead(sensorPinL); 
    sensorValueR = analogRead(sensorPinR); 
    sampleSumL += sensorValueL;
    sampleSumR += sensorValueR;
    sensorAverageL = sampleSumL/SAMPLE_AMOUNT;
    sensorAverageR = sampleSumR/SAMPLE_AMOUNT;
  };
  
  Serial.println(max(sensorAverageL,sensorAverageR));
  delay(50);
};
