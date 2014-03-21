
#define SAMPLE_AMOUNT 100
#define RUN_SIZE 50

//LED pins, C is for the center.
#define LED_F 2
#define LED_B 3
#define LED_R 4
#define LED_L 5
#define LED_C 6

//IR Rangefinder pins
#define SENSOR_PIN_F A0
#define SENSOR_PIN_B A1
#define SENSOR_PIN_R A2
#define SENSOR_PIN_L A3

#define SQUARE(x) (x)*(x)
#define CUBE(x) (x)*(x)*(x)

//a struct designed to hold our various points of data
struct dataStore{
  int D0;
  int D1;
  int D2;
  int D3;

  int insertIndex;
  int run0[RUN_SIZE];
  int run1[RUN_SIZE];
  int run2[RUN_SIZE];
  int run3[RUN_SIZE];

  long sum0;
  long sum1;
  long sum2;
  long sum3;

  int avg0;
  int avg1;
  int avg2;
  int avg3;
};

struct dataStore data;
int loopCount = 0;
//setup: init serial, init pins.
void setup() {
  Serial.begin(9600);
  //led pins
  pinMode(LED_F, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_L, OUTPUT);
  pinMode(LED_C, OUTPUT);
  //sensor pins
  pinMode(SENSOR_PIN_F, INPUT);
  pinMode(SENSOR_PIN_B, INPUT);
  pinMode(SENSOR_PIN_R, INPUT);
  pinMode(SENSOR_PIN_L, INPUT);

  data.insertIndex = 0;
}

void loop() {
  zero(data);
  //sample(SAMPLE_SIZE);
  running(RUN_SIZE);

  if (loopCount %100 == 0) {
    //print the data
    Serial.print(data.avg0);
    Serial.print("\t");
    Serial.print(data.avg1);
    Serial.print("\t");
    Serial.print(data.avg2);
    Serial.print("\t");
    Serial.print(data.avg3);
    Serial.println();
  }

  //directional LEDS
  if (data.avg0 < data.avg1) {
    digitalWrite(LED_F, HIGH);
    digitalWrite(LED_B, LOW);
  }
  else {
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_F, LOW);
  }

  if (data.avg2 < data.avg3) {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_L, LOW);
  }
  else {
    digitalWrite(LED_L, HIGH);
    digitalWrite(LED_R, LOW);
  }

  //center check
  if (centered(data)) {
    digitalWrite(LED_C, HIGH);
  }
  else{
    digitalWrite(LED_C, LOW);
  }
  loopCount++;
}



