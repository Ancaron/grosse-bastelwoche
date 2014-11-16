/**
 * SetMinutes_FR.h
 * Klasse fuer das Setzten der Woerter fuer die Minuten. Hier: Franzoesisch.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.2
 * @created  14.12.2012
 * @update   18.1.2013
 *
 * Versionshistorie:
 * V 1.1:  - cleanWordsForAlarmSettingMode() eingefuehrt, damit das Stellen des Alarms sprachenunabhaengug ist.
 * V 1.2:  - Optimierung hinsichtlich Speicherbedarf.
 */
#ifndef SETMINUTES_FR_H
#define SETMINUTES_FR_H

#include "SetHours_FR.h"

void frHeures(byte hours) {
  if((hours == 1) || (hours == 13)) {
    HEURE;
  } else if((hours == 0) || (hours == 12) || (hours == 24)) {
    // MIDI / MINUIT ohne HEURES
  } else {
    HEURES;
  }
}

/**
 * Setzt die Wortminuten, je nach hours/minutes.
 */
void setMinutes(byte hours, byte minutes) {
  ILEST;

  switch (minutes / 5) {
  case 0:
    // glatte Stunde
    setHours(hours, true);
    frHeures(hours);
    break;
  case 1:
    // 5 nach
    setHours(hours, false);
    frHeures(hours);
    CINQ;    
    break;
  case 2:
    // 10 nach
    setHours(hours, false);
    frHeures(hours);
    DIX;
    break;
  case 3:
    // viertel nach
    setHours(hours, false);
    frHeures(hours);
    ET;
    QUART;
    break;
  case 4:
    // 20 nach
    setHours(hours, false);
    frHeures(hours);
    VINGT;
    break;
  case 5:
    // 5 vor halb
    setHours(hours, false);
    frHeures(hours);
    VINGT;
    TRAIT;
    CINQ;
    break;
  case 6:
    // halb
    setHours(hours, false);
    frHeures(hours);
    ET;
    DEMI;
    break;
  case 7:
    // 5 nach halb
    setHours(hours + 1, false);
    frHeures(hours + 1);
    MOINS;
    VINGT;
    TRAIT;
    CINQ;
    break;
  case 8:
    // 20 vor
    setHours(hours + 1, false);
    frHeures(hours + 1);
    MOINS;
    VINGT;
    break;
  case 9:
    // viertel vor
    setHours(hours + 1, false);
    frHeures(hours + 1);
    MOINS;
    LE;
    QUART;
    break;
  case 10:
    // 10 vor
    setHours(hours + 1, false);
    frHeures(hours + 1);
    MOINS;
    DIX;
    break;
  case 11:
    // 5 vor
    setHours(hours + 1, false);
    frHeures(hours + 1);
    MOINS;
    CINQ;
    break;
  }
}

/**
 * Loeschen von Woertern, waehrend der Alarm gestellt wird.
 */
void cleanWordsForAlarmSettingMode() {
  matrix[0] &= 0b0010001111111111; // IL EST weg
}

#endif
