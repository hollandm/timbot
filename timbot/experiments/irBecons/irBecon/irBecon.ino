void setup()
{
 Serial.begin(9600); 
}

void loop()
{
 int west = analogRead(A0);
 int north = analogRead(A3);
 int south = analogRead(A1);
 int east = analogRead(A2);
 
 Serial.println(String(north) + ", " + String(south) + ", " + String(east) + ", " + String(west));
 
 delay(4000);
}



