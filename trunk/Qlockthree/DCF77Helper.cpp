/**
 * DCF77Helper.cpp
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
#include "DCF77Helper.h"

// #define DEBUG

/**
 * Initialisierung und das Array 'falsch' vorbelegen
 */
DCF77Helper::DCF77Helper() {
  _cursor = 0;
  for(byte i=0; i<DCF77HELPER_MAX_SAMPLES; i++) {
    _zeitstempelDcf77[i] = 400 * i * SECS_PER_DAY; // Faktor 400 fuehrt zu verschieden Jahren
    _zeitstempelRtc[i]   = 900 * i * SECS_PER_DAY; // Faktor 900 fuehrt zu verschieden Jahren, auch zwischen Dcf77 und Rtc
  }
}

/**
 * Einen neuen Sample hinzufuegen
 */
void DCF77Helper::addSample(time_t time_dcf77, time_t time_ds1307) {
#ifdef DEBUG
  Serial.print(F("Adding sample from dcf77: "));
#endif
  _zeitstempelDcf77[_cursor] = time_dcf77;
#ifdef DEBUG
  Serial.println(_zeitstempelDcf77[_cursor].asString());
  Serial.print(F("Adding sample from ds1307: "));
#endif
  _zeitstempelRtc[_cursor] = time_ds1307;
#ifdef DEBUG
  Serial.println(_zeitstempelRtc[_cursor].asString());
  Serial.flush();
#endif
  _cursor++;
  if(_cursor >= DCF77HELPER_MAX_SAMPLES) {
    _cursor = 0;
  }
#if defined(KNAUER_DEBUG)
Serial.print(F("addSample: DCF: "));
Serial.print(time_dcf77);
Serial.print(", Interne Uhr");
Serial.println(time_ds1307);
Serial.flush();
#endif
}

/**
 * Die Samples vergleichen
 */
boolean DCF77Helper::samplesOk() {
  boolean ret = true;

  for(byte i=0; i<DCF77HELPER_MAX_SAMPLES-1; i++) {
    // Teste den Minutenabstand zwischen den Zeitstempeln...
	
	if (( (_zeitstempelDcf77[i] / 60) - (_zeitstempelDcf77[i+1] / 60)) != ( (_zeitstempelRtc[i] / 60) - (_zeitstempelRtc[i+1] / 60) )) { // Pruefung von Datum Uhrzeit
#ifdef DEBUG
      Serial.print(F("Diff #"));
      Serial.print(i);
      Serial.print(F(" distance is wrong ("));
      Serial.print((_zeitstempelDcf77[i] / 60) - (_zeitstempelDcf77[i+1] / 60));
      Serial.print(F("!="));
      Serial.print((_zeitstempelRtc[i] / 60) - (_zeitstempelRtc[i+1] / 60));
      Serial.println(F(")."));
      Serial.flush();
#endif    
      ret = false;
    } 
    else {
#ifdef DEBUG
      Serial.print(F("Diff #"));
      Serial.print(i);
      Serial.print(F(" distance is ok ("));
      Serial.print((_zeitstempelDcf77[i] / 60) - (_zeitstempelDcf77[i+1] / 60));
      Serial.print(F("=="));
      Serial.print((_zeitstempelRtc[i] / 60) - (_zeitstempelRtc[i+1] / 60));
      Serial.println(F(")."));
      Serial.flush();
#endif    
    }
  }   

  return ret;
}

