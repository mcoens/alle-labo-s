#include <Wire.h>
# define TMP102_ADDRESS 72


void setup() {
  Wire.begin();
  Serial.begin(9600);
  setConf();
}

void loop() {
  Serial.println(getTemp());
  delay(200);
}

float getTemp () {
  Wire.beginTransmission(TMP102_ADDRESS);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(TMP102_ADDRESS , 2);
  Wire.endTransmission();
  
  byte MSB = Wire.read();
  byte LSB = Wire.read();
  int msbInt = MSB;
  int lsbInt = LSB;
  
  int waarde = (msbInt << 4) | (lsbInt >> 4);
  return (float) (waarde * 0.0625);
}

void setConf() {
  Wire.beginTransmission(TMP102_ADDRESS);
  Wire.write(0x01);
  Wire.write(B01100100);
  Wire.endTransmission();
  
  Wire.beginTransmission(TMP102_ADDRESS);
  Wire.write(0x02);
  Wire.write(25);
  Wire.write(0);
  Wire.endTransmission();

  Wire.beginTransmission(TMP102_ADDRESS);
  Wire.write(0x03);
  Wire.write(28);
  Wire.write(0);
  Wire.endTransmission();  
}
