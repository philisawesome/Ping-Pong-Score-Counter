#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

int score1=0;
int score2=0;
int b1State;
int b2State;
int lastP1;
int lastP2;
bool start = false; 
int count = 0;


unsigned long elapsed= 0;
unsigned long firstClick1= 0;
unsigned long firstClick2= 0;





const int interval = 2000;
const int delayClick = 500;
Adafruit_7segment display = Adafruit_7segment();

void setup() {
  Serial.begin(9600);
display.begin(0x70);

  pinMode(2,INPUT_PULLUP); //player 1
  pinMode(3, INPUT_PULLUP); //player 2
}

void loop() {
  display.setBrightness(9);
  display.drawColon(true);

  // always write both digits so a leftover tens digit can't stick (e.g. 10 -> 9 showing 19)
  display.writeDigitNum(0,score1/10);
  display.writeDigitNum(1,score1%10);

  display.writeDigitNum(3,score2/10);
  display.writeDigitNum(4,score2%10);
  display.writeDisplay();



  b1State= digitalRead(2);
  b2State= digitalRead(3);
  unsigned long curTime= millis();
  
    if (b1State== LOW and b1State != lastP1){
       if (!firstClick1){
      firstClick1 = millis();
    }
    else if(curTime- firstClick1 <=delayClick){
        if(score1 <=0){
        score1= 0;
        }else{
        score1--;

        Serial.print("player1: ");
        Serial.println(score1);
        }
        firstClick1 = 0;
        

    }
    else{
        firstClick1= 0;
    }
    }
    if( firstClick1 and curTime -firstClick1 > delayClick){

    if (b1State!= LOW){
      score1++;
      firstClick1= 0;

    Serial.print("player1: ");
    Serial.println(score1);
      
      }

    }

  
  
  


  if (b2State== LOW and b2State != lastP2){
       if (!firstClick2){
      firstClick2 = millis();
    }
    else if(curTime- firstClick2 <=delayClick){
        if(score2 <=0){
        score2= 0;
        }else{
        score2--;

        Serial.print("player2: ");
        Serial.println(score2);
        }
        firstClick2 = 0;
        

    }
    else{
        firstClick2= 0;
    }
    }
    if( firstClick2 and curTime -firstClick2 > delayClick){

    if (b2State!= LOW){
      score2++;

      firstClick2= 0;
    Serial.print("player2: ");
    Serial.println(score2);
      
      }

    }

  
  

  
  if (b1State==LOW and b2State==LOW and start == false){
    start= true;
    if (!elapsed){
      elapsed = millis();
    }
  }
  else if (b1State==LOW and b2State==LOW and start == true){
      if (curTime- elapsed >= interval){
        score1= 0; 
        score2=0;
        elapsed= 0;
        start = false;

        firstClick1 = 0;
        firstClick2 = 0;

      }
    }
  else if( b1State == HIGH or b2State == HIGH){
      start= false;
      elapsed= 0;

  }


  lastP1= b1State;
  lastP2=b2State;

}
