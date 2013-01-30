 /* Keep track of gyro angle over time
 * Connect Gyro to Analog Pin 0
 *
 * Sketch by eric barch / ericbarch.com
 * v. 0.1 - simple serial output
 *
 */

int gyroPin = 0;               //Gyro is connected to analog pin 0
float gyroVoltage = 0;         //Gyro is supposed to run at 3.3V
float arduinoVoltage = 5;      //Arduino voltage is 5
float gyroZeroVoltage = 1.16;  //Gyro is zeroed at 1.23V
float gyroSensitivityCW = 0.002244448137;  //  Our gyro is supposed to be 10mV/deg/sec clockwise
float gyroSensitivityCC = 0.002463151468;  //   Our gyro is supposed to be 10mV/deg/sec counterclockwise
float rotationThreshold = 4;   //Minimum deg/sec to keep track of - helps with gyro drifting
float maxrotationThreshold = 100;   //Minimum deg/sec to keep track of - helps with gyro drifting
float minrotationThreshold = -100;   //Minimum deg/sec to keep track of - helps with gyro drifting
int multiplier = 0 ;            //Used with currentAngle to keep it between 0 - 360 degrees
float gyroTime = 0;              //Track time from the first recorded data point of test run

float currentAngle = 0;          //Keep track of our current angle


void setup() {
  Serial.begin (9600);
}

void loop() {
  //This line grabs the gyro voltage (3.3 V)
  gyroVoltage = (analogRead(1) * arduinoVoltage/1023);
  
  
  
        //DEBUG
 // Serial.println(gyroVoltage);
  
  //This line converts the 0-1023 signal to 0-3.3V
  float gyroRate = (analogRead(gyroPin) * gyroVoltage) / (3.3/5*1023);
  
    //DEBUG
  //Serial.println(analogRead(gyroPin));
  //Serial.println(gyroVoltage);
  //Serial.println(gyroRate);

  //This line finds the voltage offset from sitting still
  gyroRate -= gyroZeroVoltage;
  
      //DEBUG
  //Serial.println(gyroRate);

  //These lines divide the voltage we found by the gyro's sensitivity
  //
  
  if (gyroRate >= 0 ) {
    gyroRate /= gyroSensitivityCW;
  }
  else if (gyroRate < 0 ) {
        gyroRate /= gyroSensitivityCC;
  }
  
    //Serial.println(gyroRate);

  //Ignore the gyro if our angular velocity does not meet our threshold
  if (gyroRate >= rotationThreshold && gyroRate <= maxrotationThreshold 
     || gyroRate <= -rotationThreshold && gyroRate >= minrotationThreshold) {
        //&& logical AND || 
    //This line divides the value by 100 since we are running in a 10ms loop (1000ms/10ms)
    gyroRate /= 100;
    //Debug for running in a 100ms loop (Leave the above code)
    gyroRate *= 10;
    
          //DEBUG
  //Serial.println(gyroRate);
    
    //back to normal code
    currentAngle += gyroRate;
      }
  
      //DEBUG
 // Serial.println(gyroRate);
      

  //Keep our angle between 0-359 degrees
  if (currentAngle < 0){
    multiplier = currentAngle / -360 ;
    currentAngle += 360 * multiplier ;
  }
  else if (currentAngle > 359) {
    multiplier = currentAngle / 360 ;
    currentAngle -= 360 * multiplier ;
  }

  gyroTime += 0.1;      //Time for loop added. = (delay time)/1000 = 100/1000 =0.1s  
  
  //Serial.print(gyroTime);
  //Serial.print(",");
 // Serial.print(analogRead(gyroPin));
  //Serial.print(",");
 // Serial.print(gyroVoltage);
 // Serial.print(",");
  Serial.println(currentAngle);


  delay(100);
} 
