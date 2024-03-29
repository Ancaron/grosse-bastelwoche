/**
 * DCF77Helper.h
 * Klasse um die Qualitaet der DCF77-Samples zu verbessern. Dazu wird der Minutenabstand
 * zwischen den empfangenen DCF77-Samples mit Hilfe der DS1307 Echtzeituhr verglichen.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.6
 * @created  19.3.2011
 * @updated  18.1.2013
 *
 * Versionshistorie:
 * V 1.1  - Fehler in der Initialisierung behoben.
 * V 1.2  - Umstellung auf TimeStamps und Verbesserung des Plausibilitaetstests.
 * V 1.3  - Fehler im samplesOk() behoben.
 * V 1.4  - Kompatibilitaet zu Arduino-IDE 1.0 hergestellt.
 * V 1.5  - Strings in PROGMEM ausgelagert.
 * V 1.6  - Optimierung hinsichtlich Speicherbedarf.
 * V 1.6.1: M. Knauer:
     - [CHANGE] Umstellung der SW auf die Time.h Library.
 */
#ifndef DCF77HELPER_H
#define DCF77HELPER_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "Time.h"

// Wieviele Samples muessen stimmen, damit das DCF77-Telegramm als gueltig zaehlt?
#define DCF77HELPER_MAX_SAMPLES 3

class DCF77Helper {
public:
  DCF77Helper();

  void addSample(time_t time_dcf77, time_t time_ds1307);
  boolean samplesOk();

private:
  byte _cursor;
  time_t _zeitstempelDcf77[DCF77HELPER_MAX_SAMPLES]; // Offset in s zum 01.01.1970
  time_t _zeitstempelRtc[DCF77HELPER_MAX_SAMPLES];   // Offset in s zum 01.01.1970
};

#endif

