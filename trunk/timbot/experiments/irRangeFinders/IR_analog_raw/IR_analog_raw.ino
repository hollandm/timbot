/*
* This program averages a number of samples together, designed to
* read from an IR sensor.
*/

#define SAMPLE_AMOUNT 500

int sensorPin = A0;
int sensorValue = 0;

void setup() {
  Serial.begin(9600);
};

void loop() {
  long sensorAverage = 0;
  long sampleSum = 0;
  for (int i = 0; i < SAMPLE_AMOUNT; i++) {
    // read the value(s) from the sensor:
    // won't need this technically, but it might be useful later.
    sensorValue = analogRead(sensorPin); 
    sampleSum += sensorValue;
    sensorAverage = sampleSum/SAMPLE_AMOUNT;
  };
  Serial.write(sensorAverage);
};
