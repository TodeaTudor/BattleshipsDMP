#include <Wire.h>
char turn = '1';
bool p2Turn = false;
int countHits = 0;
int LedMatrix[6][6] =
  {  
    {1,1,1,1,1,1},
    {1,1,1,1,1,1},
    {1,1,1,1,1,1},
    {1,1,1,1,1,1},
    {1,1,1,1,1,1},
    {1,1,1,1,1,1}
  };

int BattleshipPositions[6][6] = 
  {  
    {0,0,0,0,0,0},
    {0,0,0,0,1,1},
    {1,1,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,1},
    {0,0,0,0,0,1}
  };

int ledRows[6]={1,3,4,5,6,7};
int ledCols[6]={13,12,11,10,9,8};

void setup() {
 
 
  Wire.begin(10);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(9600);
  for (int i = 2; i < 14; i++){
    pinMode(i,OUTPUT);
  	digitalWrite(i,LOW);
  }
  pinMode(2, INPUT);
  EIMSK |= (1 << INT0);
  EICRA |= (1 << ISC01); 
  sei(); 
}

ISR(INT0_vect)
{
  countHits = 0;
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
    	BattleshipPositions[i][j] = 0;
      	LedMatrix[i][j] = 1;
    }
  }
}

void receiveEvent(int bytes) {
  int x = Wire.read();
  if (x == '0' + 2) {
  	 p2Turn = true;
     turn = '2';
   }
  if ((p2Turn == true) && (x <= 35)) {
  	int row = x / 6;
    int col = x % 6;
    if (BattleshipPositions[row][col] == 1) {
      LedMatrix[row][col] = 0;  
      countHits++;
      if (countHits > 5) {
      	tone(A0, 2400, 125);
        tone(A0, 2400, 125);
        tone(A0, 2400, 125);
        tone(A0, 2400, 125);
        tone(A0, 2400, 125);
      }else {
        
      	tone(A0, 1500, 125);
      }
    }else {
      tone(A0, 73, 125);
    }
    
    turn = '1';
    p2Turn = false;
    	
  }
  Serial.println(x);
}

void requestEvent() {
  Wire.write(turn);
  
}
void loop() {
  for(int c = 0; c < 6; c++){
    digitalWrite(ledCols[c],HIGH);
    for(int r = 0; r < 6; r++){
      digitalWrite(ledRows[r],1000*LedMatrix[r][c]);
    }
    for (int r = 0; r < 6; r++){
      digitalWrite(ledRows[r], HIGH);
     delay(1);
    }
   digitalWrite(ledCols[c],LOW);
  }
}