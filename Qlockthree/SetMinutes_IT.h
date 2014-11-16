/**
 * SetMinutes_IT.h
 * Klasse fuer das Setzten der Woerter fuer die Minuten. Hier: Italienisch.
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
#ifndef SETMINUTES_IT_H
#define SETMINUTES_IT_H

#include "SetHours_IT.h"

/**
 * Setzt die Variante "SONE LE" oder "E" je nach Stunde.
 */
void itOre(byte hours) {
  if(hours != 1) {
    SONOLE; 
  } else {
    H_E;
  }  
}

/**
 * Setzt die Wortminuten, je nach hours/minutes.
 */
void setMinutes(byte hours, byte minutes) {
  while (hours > 12) {
    hours -= 12;
  }

  switch (minutes / 5) {
  case 0:
    // glatte Stunde
    setHours(hours, true);
    itOre(hours);
    break;
  case 1:
    // 5 nach
    E;
    CINQUE;
    setHours(hours, false);
    itOre(hours);
    break;
  case 2:
    // 10 nach
    E;
    DIECI;
    setHours(hours, false);
    itOre(hours);
    break;
  case 3:
    // viertel nach
    E;
    UN;
    QUARTO;
    setHours(hours, false);
    itOre(hours);
    break;
  case 4:
    // 20 nach
    E;
    VENTI;
    setHours(hours, false);
    itOre(hours);
    break;
  case 5:
    // 5 vor halb
    E;
    VENTI;
    CINQUE;
    setHours(hours, false);
    itOre(hours);
    break;
  case 6:
    // halb
    E;
    MEZZA;
    setHours(hours, false);
    itOre(hours);
    break;
  case 7:
    // 5 nach halb
    MENO;
    VENTI;
    CINQUE;
    setHours(hours + 1, false);
    itOre(hours + 1);
    break;
  case 8:
    // 20 vor
    MENO;
    VENTI;
    setHours(hours + 1, false);
    itOre(hours + 1);
    break;
  case 9:
    // viertel vor
    MENO;
    UN;
    QUARTO;
    setHours(hours + 1, false);
    itOre(hours + 1);
    break;
  case 10:
    // 10 vor
    MENO;
    DIECI;
    setHours(hours + 1, false);
    itOre(hours + 1);
    break;
  case 11:
    // 5 vor
    MENO;
    CINQUE;
    setHours(hours + 1, false);
    itOre(hours + 1);
    break;
  }
}

/**
 * Loeschen von Woertern, waehrend der Alarm gestellt wird.
 */
void cleanWordsForAlarmSettingMode() {
  matrix[0] &= 0b0000100111111111; // SONO LE weg
  matrix[1] &= 0b0111111111111111; // E (L'UNA) weg
}

#endif
