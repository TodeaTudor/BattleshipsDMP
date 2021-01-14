#include "Wire.h"
char prevReadCharFromP1;
char prevReadCharFromP2;
void setup() {
 
  Wire.begin();  
  Serial.begin(9600);
}

void loop()
{
  Wire.requestFrom(9, 1);
  char readCharFromP1 = Wire.read();
  Wire.requestFrom(10, 1);
  char readCharFromP2 = Wire.read();
  if (readCharFromP1 != readCharFromP2) {
    if (readCharFromP1 == '2' && readCharFromP2 == '1') {
      if (prevReadCharFromP1 == '1') {
      	Wire.beginTransmission(10);
  	 	Wire.write('2');
  	 	Wire.endTransmission();
      }
      if (prevReadCharFromP2 == '2') {
      	Wire.beginTransmission(9);
  	 	Wire.write('1');
  	 	Wire.endTransmission();
      }
      
    }
  }
  prevReadCharFromP1 = readCharFromP1;
  prevReadCharFromP2 = readCharFromP2;
 delay(100);
}