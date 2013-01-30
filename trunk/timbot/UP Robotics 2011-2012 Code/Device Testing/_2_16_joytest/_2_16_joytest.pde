int spd = -1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(10, OUTPUT);

}

void loop() {
  // put your maincode here, to run repeatedly:
  if(Serial.available())
  {
     spd = Serial.read();
  } 
  
  
  
  
  float pulseSpd = (float)(spd - 100)/100;
  
  if (spd == -1)
  {
     pulseSpd = 0; 
  }
  
  
  driveRight(pulseSpd);
  
  //driveRight(0.5);
  
}



void driveRight(float spd)
{
  float aspeed = spd;
  if ( spd > 1)
  {
    aspeed = 1;
  }
  else if ( spd < -1)
  {
    aspeed = -1;
  }
  
  int ms = (int)((( aspeed * 0.3 ) + 1.5) * 1000 );
  drivePulse(10, ms);
}

void drivePulse(int pin, int ms) 
{
	digitalWrite(pin, HIGH);
	delayMicroseconds(ms);
        digitalWrite(pin, LOW);
}

