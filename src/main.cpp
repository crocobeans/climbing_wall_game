#include <Arduino.h>
//modify these
int timeout = 3500; //time to fail in ms / 5.7
//int beepInterval = 1000; // buzzer interval(in ms)

bool t = false ;
bool gameState = false;


void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  for(int i =2 ; i<=8 ; i++){
    pinMode(i, OUTPUT);    
  }

  digitalWrite(8,LOW);


}

void loop() {
  if(gameState == false){

    t = false;
    
    digitalWrite(LED_BUILTIN, HIGH);

    for(int i=2; i <= 7 ; i++){
      digitalWrite(i , HIGH);
    }

    while(t == false){
      for(int i = 2; i<=7; i++){
        if(analogRead(i)>500){
          t = true;
        }
      }
    }

    for(int i=2; i <= 7 ; i++){
      digitalWrite(i , LOW);
    }

    gameState = true;

    digitalWrite(LED_BUILTIN, LOW);

  }

  if(gameState == true){

    int count = 0;
//    bool buzzOn = false;

    int lightNum = random(2,8);

    digitalWrite(lightNum,HIGH);

    while( analogRead(lightNum) < 500 ){
      count +=1  ;
//      if(0 == count % beepInterval){
//        if(buzzOn == true){
//          digitalWrite(8,LOW);
//          buzzOn = false;
//        }
//        else{
//          digitalWrite(8,HIGH);
//          buzzOn = true;
//        }
        
//      }
      
      if(count > timeout){
        gameState = false;
        break;
      }

      digitalWrite(8,LOW);

    }

    digitalWrite(lightNum,LOW);
  }
  
}
