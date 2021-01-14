#include <Wire.h>

#define ROWS_COUNT 6
#define COLS_COUNT 3

#define TIME_DEBOUNCE 6

int CHARACTERS[ROWS_COUNT][COLS_COUNT] = 
  
{
  {0,1,2},
  {6,7,8},
  {12,13,14},
  {18,19,20},
  {24,25,26},
  {30,31,32},
};

int ROWS[ROWS_COUNT] = {2,3,4,5,6,7}, COLS[COLS_COUNT] = {10,9,8};

void MATRIX_BUTTON_PRESSED(int R, int C){
  Wire.beginTransmission(10); // transmit to device #9
  Wire.write(CHARACTERS[R][C]);
  Wire.endTransmission();
  //Serial.println(CHARACTERS[R][C]);
  
}


void setup(){
  
  for(int R = 0; R < ROWS_COUNT; R++){
    
    pinMode(ROWS[R],INPUT_PULLUP);
  }
  for(int C = 0; C < COLS_COUNT; C++){
    pinMode(COLS[C],OUTPUT);
    digitalWrite(COLS[C],1);
  }
  //Serial.begin(9600);
  Wire.begin();
  
  
}


void loop(){
  
  for(int C = 0; C < COLS_COUNT; C++){
    
    for(int R = 0; R < ROWS_COUNT; R++){
     
      digitalWrite(COLS[C],0);
      if(!(digitalRead(ROWS[R]))) MATRIX_BUTTON_PRESSED(R,C);
      digitalWrite(COLS[C],1);
      delay(TIME_DEBOUNCE);
    }
  	          
  }
  
}