
#include <MPR121.h>
#include <Wire.h>
#include <Keyboard.h>

#define NUM_STRIPS 1
#define PERIOD 500

//Input where the sensors is connected to
#define switchElectrode01 6 // E6 on the board
#define switchElectrode02 8 // E8 on the board
#define switchElectrode03 10 // E10 on the board

int buttonState01 = LOW;
int timerState01 = false;
unsigned long time01 = 0;

int buttonState02 = LOW;
int timerState02 = false;;
unsigned long time02 = 0;

int buttonState03 = LOW;
int timerState03 = false;
unsigned long time03 = 0;

void setup() {
  Serial.begin(9600);
  Keyboard.begin();

  MPR121.begin(0x5C);
  MPR121.setInterruptPin(4);   // pin 4 is the MPR121 interrupt on the Bare Touch Board
  
  MPR121.setTouchThreshold(11);     // this is the threshold at which the board senses a touch
                                    // higher values are less sensitive, lower values are more sensitive
                                    // for proximity operation, you could try a value of 6  
                                                              
  MPR121.setReleaseThreshold(2);   // this is the threshold at which the board senses a release 
                                   // higher values are less sensitive, lower values are more sensitive
                                    // for proximity operation, you could try a value of 3
                                    // this must ALWAYS be lower than the touch threshold
                                    
  MPR121.updateTouchData(); // initial data update


}

void loop() {
  //https://forum.arduino.cc/index.php?topic=114964.0
  if(buttonState01 == HIGH){
    if(millis()-time01 > PERIOD){
       Serial.println("1 OFF");
       buttonState01 = LOW;
    }
  }

  if(buttonState02 == HIGH){
    if(millis()-time02 > PERIOD){
       Serial.println("2 OFF");
       buttonState02 = LOW;
    }
  }

  if(buttonState03 == HIGH){
    if(millis()-time03 > PERIOD){
       Serial.println("3 OFF");
       buttonState03 = LOW;
    }
  }

  if(MPR121.touchStatusChanged()){
    MPR121.updateTouchData();
    if(MPR121.isNewTouch(switchElectrode01) && buttonState01 == LOW){
         buttonState01 = HIGH;
         Keyboard.press('q');
         delay(100);
         Keyboard.releaseAll();
         time01 = millis(); //Active delay to prevent repeat in button touch :)
         Serial.println("1 ON"); 
    }
    if(MPR121.isNewTouch(switchElectrode02) && buttonState02 == LOW){
         buttonState02 = HIGH;
         Keyboard.press('w');
         delay(100);
         Keyboard.releaseAll();
         time02 = millis(); //Active delay to prevent repeat in button touch :)
         Serial.println("2 ON");
    
    }
    if(MPR121.isNewTouch(switchElectrode03) && buttonState03 == LOW){
         buttonState03 = HIGH;
         Keyboard.press('r');
         Keyboard.releaseAll();
         time03 = millis(); //Activate delay to prevent repeat in button touch :)
         Serial.println("3 ON");
    }
    
  }
}
