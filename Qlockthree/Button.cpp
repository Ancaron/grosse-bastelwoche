/**
 * Button.cpp
 * Kleine Klasse zum Entprellen der Tasten.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.2
 * @created  18.2.2011
 * @updated  18.1.2013
 *
 * Versionshistorie:
 * V 1.1:  - Kompatibilitaet zu Arduino-IDE 1.0 hergestellt.
 * V 1.2:  - Optimierung hinsichtlich Speicherbedarf.
 */
#include "Button.h"

// #define DEBUG

#define BUTTON_TRESHOLD 300

/**
 * Initialisierung mit dem Pin, an dem der Taster haengt
 */
Button::Button(byte pin) {
  _pin = pin;
  _lastPressTime = 0;
  pinMode(_pin, INPUT);
}

/**
 * Wurde der Taster gedrueckt?
 */
boolean Button::pressed() {
  boolean retVal = false;

  if (digitalRead(_pin) == HIGH) {
    if (_lastPressTime + BUTTON_TRESHOLD < millis()) {
      retVal = true;
      _lastPressTime = millis();
    }
  }

  return retVal;
}

