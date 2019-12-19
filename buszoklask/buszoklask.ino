#define sensorPin 2
#include "DigiKeyboard.h"
#define KEY_PAGEDOWN 0x4E
#define KEY_PAGEUP 0x4B
int lastSoundValue;
int soundValue;
long lastNoiseTime = 0;
long currentNoiseTime = 0;
long lastSlideChange = 0;
int rStatus = LOW;

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(1, OUTPUT);
     
  DigiKeyboard.update();
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(1500);
  
}

void loop() {
  DigiKeyboard.update();
  soundValue = !digitalRead(sensorPin);
  currentNoiseTime = millis();
  digitalWrite(1, rStatus);
  if (soundValue == 1) { // if there is currently a noise
    if ((currentNoiseTime > lastNoiseTime + 200) && (lastSoundValue== 0)&&(rStatus == LOW)){rStatus = HIGH;DigiKeyboard.sendKeyStroke(KEY_PAGEDOWN); }
      
      digitalWrite(1, rStatus);
    if (
     (currentNoiseTime > lastNoiseTime + 200) && // to debounce a sound occurring in more than a loop cycle as a single noise
      (lastSoundValue == 0) &&  // if it was silent before
     (currentNoiseTime < lastNoiseTime + 800) && // if current clap is less than 0.8 seconds after the first clap
      (currentNoiseTime > lastSlideChange + 1000)&&// to avoid taking a third clap as part of a pattern
      (rStatus == HIGH)
    ) {

      

      
      DigiKeyboard.sendKeyStroke(KEY_PAGEUP);
      DigiKeyboard.sendKeyStroke(KEY_PAGEUP);
      
      
      lastSlideChange = currentNoiseTime;
      rStatus = LOW;
      digitalWrite(1, rStatus);
      //DigiKeyboard.delay(1000);
     }
     
     lastNoiseTime = currentNoiseTime;
  }
else if((rStatus == HIGH)&& (currentNoiseTime > lastNoiseTime+800)&&(currentNoiseTime > lastSlideChange + 1000)){
      
      
      //lastSlideChange = currentNoiseTime;
      rStatus = LOW;
      digitalWrite(1, rStatus);
      //DigiKeyboard.delay(1000);      
      
      }

      
  lastSoundValue = soundValue;
}
