/**
 * SetMinutes_EN.h
 * Klasse fuer das Setzten der Woerter fuer die Minuten. Hier: Englisch.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.1
 * @created  12.1.2013
 * @updated  18.1.2013
 *
 * Versionshistorie:
 * V 1.1:  - Optimierung hinsichtlich Speicherbedarf.
 */
#ifndef SETMINUTES_EN_H
#define SETMINUTES_EN_H

#include "SetHours_EN.h"

/**
 * Setzt die Wortminuten, je nach hours/minutes.
 */
void setMinutes(byte hours, byte minutes) {
  while (hours > 12) {
    hours -= 12;
  }

  ITIS;

  switch (minutes / 5) {
  case 0:
    // glatte Stunde
    setHours(hours, true);
    break;
  case 1:
    // 5 nach
    FIVE;
    PAST;
    setHours(hours, false);
    break;
  case 2:
    // 10 nach
    TEN;
    PAST;
    setHours(hours, false);
    break;
  case 3:
    // viertel nach
    A;
    QUATER;
    PAST;
    setHours(hours, false);
    break;
  case 4:
    // 20 nach
    TWENTY;
    PAST;
    setHours(hours, false);
    break;
  case 5:
    // 5 vor halb
    TWENTY;
    FIVE;
    PAST;
    setHours(hours, false);
    break;
  case 6:
    // halb
    HALF;
    PAST;
    setHours(hours, false);
    break;
  case 7:
    // 5 nach halb
    TWENTY;
    FIVE;
    TO;
    setHours(hours + 1, false);
    break;
  case 8:
    // 20 vor
    TWENTY;
    TO;
    setHours(hours + 1, false);
    break;
  case 9:
    // viertel vor
    A;
    QUATER;
    TO;
    setHours(hours + 1, false);
    break;
  case 10:
    // 10 vor
    TEN;
    TO;
    setHours(hours + 1, false);
    break;
  case 11:
    // 5 vor
    FIVE;
    TO;
    setHours(hours + 1, false);
    break;
  }
}

/**
 * Loeschen von Woertern, waehrend der Alarm gestellt wird.
 */
void cleanWordsForAlarmSettingMode() {
  matrix[0] &= 0b0010011111111111; // IT IS weg
}

#endif
