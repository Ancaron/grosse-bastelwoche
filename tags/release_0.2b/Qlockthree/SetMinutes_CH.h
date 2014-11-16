/**
 * SetMinutes_CH.h
 * Klasse fuer das Setzten der Woerter fuer die Minuten. Hier: Schweizerisch.
 *
 * @mc       Arduino/RBBB
 * @autor    Thomas Schuler / thomas.schuler _AT_ vtg _DOT_ admin _DOT_ ch
 * @version  1.2
 * @created  18.3.2012
 * @update   18.1.2013
 *
 * Versionshistorie:
 * V 1.1:   - cleanWordsForAlarmSettingMode() eingefuehrt, damit das Stellen des Alarms sprachenunabhaengug ist.
 * V 1.2:  - Optimierung hinsichtlich Speicherbedarf.
 */
#ifndef SETMINUTES_CH_H
#define SETMINUTES_CH_H

#include "SetHours_CH.h"

/**
 * Setzt die Wortminuten, je nach hours/minutes.
 */
void setMinutes(byte hours, byte minutes) {
  while (hours > 12) {
    hours -= 12;
  }

  ESISCH;

  switch (minutes / 5) {
  case 0:
    // glatte Stunde
    setHoures(hours, true);
    break;
  case 1:
    // 5 ab
    FUEF;
    AB;
    setHoures(hours, false);
    break;
  case 2:
    // 10 ab
    ZAEAE;
    AB;
    setHoures(hours, false);
    break;
  case 3:
    // viertel ab
    VIERTU;
    AB;
    setHoures(hours, false);
    break;
  case 4:
    // 20 ab
    ZWAENZG;
    AB;
    setHoures(hours, false);
    break;
  case 5:
    // 5 vor halb
    FUEF;
    VOR;
    HAUBI;
    setHoures(hours + 1, false);
    break;
  case 6:
    // halb
    HAUBI;
    setHoures(hours + 1, false);
    break;
  case 7:
    // 5 ab halb
    FUEF;
    AB;
    HAUBI;
    setHoures(hours + 1, false);
    break;
  case 8:
    // 20 vor
    ZWAENZG;
    VOR;
    setHoures(hours + 1, false);
    break;
  case 9:
    // viertel vor
    VIERTU;
    VOR;
    setHoures(hours + 1, false);
    break;
  case 10:
    // 10 vor
    ZAEAE;
    VOR;
    setHoures(hours + 1, false);
    break;
  case 11:
    // 5 vor
    FUEF;
    VOR;
    setHoures(hours + 1, false);
    break;
  }
}

/**
 * Loeschen von Woertern, waehrend der Alarm gestellt wird.
 */
void cleanWordsForAlarmSettingMode() {
  matrix[0] &= 0b0010000111111111; // ES ISCH weg
}

#endif

