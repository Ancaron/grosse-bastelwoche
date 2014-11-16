/**
 * SetHours_FR.h
 * Klasse fuer das Setzten der Stunden in Franzoesisch.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.1
 * @created  14.12.2012
 * @update   18.1.2013
 *
 * Versionshistorie:
 * V 1.1:  - Optimierung hinsichtlich Speicherbedarf.
 */
#ifndef SETHOURS_FR_H
#define SETHOURS_FR_H

/**
 * Setzt die Stunden, je nach hours. 'glatt' bedeutet,
 * es ist genau diese Stunde und wir muessen 'UHR'
 * dazuschreiben und EIN statt EINS, falls es 1 ist.
 * (Zumindest im Deutschen)
 */
void setHours(byte hours, boolean glatt) {
  switch (hours) {
  case 0:
  case 24:
    H_MINUIT;
    break;
  case 12:
    H_MIDI;
    break;
  case 1:
  case 13:
    H_UNE;
    break;
  case 2:
  case 14:
    H_DEUX;
    break;
  case 3:
  case 15:
    H_TROIS;
    break;
  case 4:
  case 16:
    H_QUATRE;
    break;
  case 5:
  case 17:
    H_CINQ;
    break;
  case 6:
  case 18:
    H_SIX;
    break;
  case 7:
  case 19:
    H_SEPT;
    break;
  case 8:
  case 20:
    H_HUIT;
    break;
  case 9:
  case 21:
    H_NEUF;
    break;
  case 10:
  case 22:
    H_DIX;
    break;
  case 11:
  case 23:
    H_ONZE;
    break;
  }
}

#endif
