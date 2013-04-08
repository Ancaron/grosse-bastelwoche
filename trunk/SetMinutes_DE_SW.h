/**
 * SetMinutes_DE_SW.h
 * Klasse fuer das Setzten der Woerter fuer die Minuten. Hier: Deutsch/Schwaebisch,
 * also mit "viertel Elf" oder "dreiviertel Zehn".
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.2
 * @created  18.3.2012
 * @update   18.1.2013
 *
 * Versionshistorie:
 * V 1.1:  - cleanWordsForAlarmSettingMode() eingefuehrt, damit das Stellen des Alarms sprachenunabhaengug ist.
 * V 1.1:  - Optimierung hinsichtlich Speicherbedarf.
 */
#ifndef SETMINUTES_DE_SW_H
#define SETMINUTES_DE_SW_H

#include "SetHours_DE.h"

/**
 * Setzt die Wortminuten, je nach hours/minutes.
 */
void setMinutes(byte hours, byte minutes) {
  while (hours > 12) {
    hours -= 12;
  }

  ESIST;

  switch (minutes / 5) {
  case 0:
    // glatte Stunde
    setHours(hours, true);
    break;
  case 1:
    // 5 nach
    FUENF;
    NACH;
    setHours(hours, false);
    break;
  case 2:
    // 10 nach
    ZEHN;
    NACH;
    setHours(hours, false);
    break;
  case 3:
    // viertel
    VIERTEL;
    setHours(hours + 1, false);
    break;
  case 4:
    // 20 nach
    ZWANZIG;
    NACH;
    setHours(hours, false);
    break;
  case 5:
    // 5 vor halb
    FUENF;
    VOR;
    HALB;
    setHours(hours + 1, false);
    break;
  case 6:
    // halb
    HALB;
    setHours(hours + 1, false);
    break;
  case 7:
    // 5 nach halb
    FUENF;
    NACH;
    HALB;
    setHours(hours + 1, false);
    break;
  case 8:
    // 20 vor
    ZWANZIG;
    VOR;
    setHours(hours + 1, false);
    break;
  case 9:
    // dreiviertel
    DREIVIERTEL;
    setHours(hours + 1, false);
    break;
  case 10:
    // 10 vor
    ZEHN;
    VOR;
    setHours(hours + 1, false);
    break;
  case 11:
    // 5 vor
    FUENF;
    VOR;
    setHours(hours + 1, false);
    break;
  }
}

/**
 * Loeschen von Woertern, waehrend der Alarm gestellt wird.
 */
void cleanWordsForAlarmSettingMode() {
  matrix[0] &= 0b0010001111111111; // ES IST weg
}

#endif
