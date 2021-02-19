#include <Wire.h>

// the setup routine runs once when you press reset:
void setup()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Wire.begin();
}

// the loop routine runs over and over again forever:
void loop()
{
  // read the input on analog pin 0:

  // print out the value you read:
  Serial.println("Hello YE BOY");
  delay(1000); // delay in between reads for stability

  Wire.beginTransmission(0x14);
  Wire.write(123);
  Wire.endTransmission();
}