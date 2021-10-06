#include <Arduino.h>
//modify these
int timeout = 20000;                          //time to fail in ms
int beepInterval = 1000;                      // buzzer interval(in ms)

bool t = false ;
bool gameState = false;


void setup() {

  pinMode(LED_BUILTIN, OUTPUT);               //set pins as output

  for(int i =2 ; i<=8 ; i++){
    pinMode(i, OUTPUT);    
  }

  digitalWrite(8,LOW);                        //make sure the buzzer isnt on 

  beepInterval = beepInterval/5;

}

void loop() {

  if(gameState == false){                      //init game

    t = false;
    
    digitalWrite(LED_BUILTIN, HIGH);

    for(int i=2; i <= 7 ; i++){               // turn on all LEDs
      digitalWrite(i , HIGH);
    }

    while(t == false){                        //hang program until a button is pressed
      for(int i = 2; i<=7; i++){
        if(analogRead(i)>500){
          t = true;
        }
      }
    }

    for(int i=2; i <= 7 ; i++){
      digitalWrite(i , LOW);                    // turn off all LEDs
    }

    gameState = true;

    digitalWrite(LED_BUILTIN, LOW);

  }

  if(gameState == true){

    int count = 0;
    int buzzOn = 0;

    int lightNum = random(2,8);                   //generate rand

    digitalWrite(lightNum,HIGH);

    while( analogRead(lightNum) < 500 ){          //hang program until light is pressed
      count +=1  ;


      if(0 == count % beepInterval){              // increment timer state if counter mod beepinterval =0
        if(buzzOn >3){
          digitalWrite(8,HIGH);
          buzzOn = 0;
        }
        else{
          digitalWrite(8,LOW);
          buzzOn ++;
        }
       
      }

      if(count > timeout){                        // if over timeout limit return to init
        gameState = false;
        break;
      }

      delay(1);  
      
    }

    digitalWrite(lightNum,LOW);
    digitalWrite(8,LOW);                          //make sure buzzer is off

  }
  
}
