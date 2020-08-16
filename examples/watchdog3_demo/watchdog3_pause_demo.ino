/*
 * watchdog3_demo modified to show pause() and resume() functions
 * on button press, WDT3 gets properly disabled, releasing button WDT3 starts again
 * uncommenting disable2 will cause Teensy reset after releasing the button
 */
#include "Watchdog_t4.h"
WDT_T4<WDT3> wdt;

bool  disable = false;
bool  disable2 = false;
#define BUTTON          3     /*  button is connected on this pin */


void myCallback() {
  Serial.println("YOU DIDNT FEED THE DOG, 255 CYCLES TILL RESET...");
}

void setup() {
  Serial.begin(1);
  delay(600);
  pinMode(BUTTON,  INPUT_PULLUP);
  pinMode(LED_BUILTIN,  OUTPUT);
  Serial.println("Begin......");

  WDT_timings_t config;
  config.window = 45; /* in ms, 32ms to 522.232s, must be smaller than timeout */
  config.timeout = 60; /* in ms, 32ms to 522.232s */
  config.callback = myCallback;
  wdt.begin(config);
}

void loop() {
  static uint32_t feed = millis();

  /* set to below 45 to demonstrate windowMode effect for feeding the dog too fast */
  /* set to 50 to demonstrate proper processing */
  /* set to 70 to demonstrate an actual non-feeding reset */

  if ( millis() - feed > 50 ) {
    
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   /*  just to show our program is running */
    
    feed = millis();
    if  (digitalReadFast(BUTTON))  {
      if  (disable)  {
        disable = false;
        wdt.resume();
        Serial.println(F("WDT3 RESUMED"));
      }
      if  (!disable2)  {
        wdt.feed();
      }
    } else  {
      if  (!disable) {
        disable = true;
//        disable2 = true;        /*  uncomment to demonstrate reset after resuming */
        wdt.pause();
        Serial.println(F("WDT3 DISABLED"));
      }

    }
  }
}
