/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach whatever-the-hell we're using to pin A0.
 
 Modified from Public-Domain code.
 */

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

int average_amount = 15;

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = 0;
  for (int i = 0; i < average_amount; i++)
  {
    sensorValue += analogRead(A0);
    delay(10);
  }
  sensorValue /= average_amount;
  float sensor = (float)sensorValue/(1023);
  // print out the value you read:
  Serial.println(sensorValue, DEC);
  //delay(50);        // delay in between reads for stability
}
