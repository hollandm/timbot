/*
* This program averages a number of samples together, designed to
 * read from several IR sensors.
 */

#define SAMPLE_AMOUNT 250

int sensorPinF = A0;
int sensorPinB = A1;
int sensorPinR = A2;
int sensorPinL = A3;

typedef struct dataStore{
  int D0;
  int D1;
  int D2;
  int D3;

  long sum0;
  long sum1;
  long sum2;
  long sum3;

  int avg0;
  int avg1;
  int avg2;
  int avg3;
};

void setup() {
  Serial.begin(9600);
  pinMode(sensorPinF,INPUT);
  pinMode(sensorPinB,INPUT);
  pinMode(sensorPinR,INPUT);
  pinMode(sensorPinL,INPUT);

};

void loop() {
  struct dataStore data;
  data.sum0 = 0;
  data.sum1 = 0;
  data.sum2 = 0;
  data.sum3 = 0;
  long sensorAverage = 0;
  long sampleSum = 0;
  for (int i = 0; i < SAMPLE_AMOUNT; i++) {


    // read the value(s) from the sensor:
    data.D0 = analogRead(sensorPinF);
    data.D1 = analogRead(sensorPinB);
    data.D2 = analogRead(sensorPinR);
    data.D3 = analogRead(sensorPinL);
    data.sum0 += data.D0;
    data.sum1 += data.D1;
    data.sum2 += data.D2;
    data.sum3 += data.D3;
  };

  data.avg0 = data.sum0/SAMPLE_AMOUNT;
  data.avg1 = data.sum1/SAMPLE_AMOUNT;
  data.avg2 = data.sum2/SAMPLE_AMOUNT;
  data.avg3 = data.sum3/SAMPLE_AMOUNT;

  Serial.print(data.avg0);
  Serial.print("\t");
  Serial.print(data.avg1);
  Serial.print("\t");
  Serial.print(data.avg2);
  Serial.print("\t");
  Serial.print(data.avg3);
  Serial.println();

};





