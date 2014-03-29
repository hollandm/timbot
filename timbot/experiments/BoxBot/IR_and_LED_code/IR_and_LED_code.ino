
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
  int value;
  int run[RUN_SIZE];
  int insertIndex;
  long sum;
  int avg;
  double dist;
};

struct dataStore front;
struct dataStore back;
struct dataStore right;
struct dataStore left;

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

  front.insertIndex = 0;
  back.insertIndex = 0;
  right.insertIndex = 0;
  left.insertIndex = 0;
}

void loop() {
  zero(&front);
  zero(&back);
  zero(&right);
  zero(&left);
  
  //sample(front, SAMPLE_SIZE, SENSOR_PIN_F);
  running(&front, RUN_SIZE, SENSOR_PIN_F);
  running(&back, RUN_SIZE, SENSOR_PIN_B);
  running(&right, RUN_SIZE, SENSOR_PIN_R);
  running(&left, RUN_SIZE, SENSOR_PIN_L);
  
  convertToDist(&front);
  convertToDist(&back);
  convertToDist(&right);
  convertToDist(&left);

  if (loopCount %100 == 0) {
    //print the data
    Serial.print("Front val dist(cm):\t");
    Serial.print(front.avg);
    Serial.print("\t");
    Serial.print(front.dist);
    Serial.print("\tBack:\t");
    Serial.print(back.avg);
    Serial.print("\t");
    Serial.print(back.dist);
    Serial.print("\tRight:\t");
    Serial.print(right.avg);
    Serial.print("\t");
    Serial.print(right.dist);
    Serial.print("\tLeft\t");
    Serial.print(left.avg);
    Serial.print("\t");
    Serial.print(left.dist);
    Serial.println();
  }

  //directional LEDS
  if (front.avg < back.avg) {
    digitalWrite(LED_F, HIGH);
    digitalWrite(LED_B, LOW);
  }
  else {
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_F, LOW);
  }

  if (right.avg < left.avg) {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_L, LOW);
  }
  else {
    digitalWrite(LED_L, HIGH);
    digitalWrite(LED_R, LOW);
  }

  //center check
  if (centered() == 1) {
    digitalWrite(LED_C, HIGH);
  }
  else{
    digitalWrite(LED_C, LOW);
  }
  loopCount++;
}



