/**
 * SetHours_CH.h
 * Klasse fuer das Setzten der Stunden in Schweizerisch.
 *
 * @mc       Arduino/RBBB
 * @autor    Thomas Schuler / thomas.schuler _AT_ vtg _DOT_ admin _DOT_ ch
 * @version  1.1
 * @created  18.3.2012
 * @update   18.1.2013
 *
 * Versionshistorie:
 * V 1.1:  - Optimierung hinsichtlich Speicherbedarf.
 */
#ifndef SETHOURS_CH_H
#define SETHOURS_CH_H

/**
 * Setzt die Stunden, je nach hours. 'glatt' bedeutet,
 * es ist genau diese Stunde und wir muessen 'UHR'
 * dazuschreiben und EIN statt EINS, falls es 1 ist.
 * (Zumindest im Deutschen)
 */
void setHoures(byte hours, boolean glatt) {
  while (hours > 12) {
    hours -= 12;
  }

  switch (hours) {
  case 0:
  case 12:
  case 24:
    H_ZWOEUFI;
    break;
  case 1:
  case 13:
    H_EIS;
    break;
  case 2:
  case 14:
    H_ZWOEI;
    break;
  case 3:
  case 15:
    H_DRUE;
    break;
  case 4:
  case 16:
    H_VIER;
    break;
  case 5:
  case 17:
    H_FUEFI;
    break;
  case 6:
  case 18:
    H_SAECHSI;
    break;
  case 7:
  case 19:
    H_SIEBNI;
    break;
  case 8:
  case 20:
    H_ACHTI;
    break;
  case 9:
  case 21:
    H_NUENI;
    break;
  case 10:
  case 22:
    H_ZAENI;
    break;
  case 11:
  case 23:
    H_EUFI;
    break;
  }
}

#endif

