#define SAMPLE_AMOUNT 50

int sensorPin = A0;
int sensorValue = 0;

void setup() {
  Serial.begin(9600);
};

void loop() {
  int sensorAverage = 0;
  int sampleSum = 0;
  for (int i = 0; i < SAMPLE_AMOUNT; i++) {
    // read the value(s) from the sensor:
    // won't need this technically, but it might be useful later.
    sensorValue = analogRead(sensorPin); 
    sampleSum += sensorValue;
    sensorAverage = sampleSum/SAMPLE_AMOUNT;
  };
  Serial.println(sensorAverage);
  delay(50);
};
