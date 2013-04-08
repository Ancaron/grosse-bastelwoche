/**
 * SetHours_IT.h
 * Klasse fuer das Setzten der Stunden auf Italienisch.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.1
 * @created  12.1.2013
 * @update   18.1.2013
 *
 * Versionshistorie:
 * V 1.1:  - Optimierung hinsichtlich Speicherbedarf.
 */
#ifndef SETHOURS_IT_H
#define SETHOURS_IT_H

/**
 * Setzt die Stunden, je nach hours. 'glatt' bedeutet,
 * es ist genau diese Stunde.
 */
void setHours(byte hours, boolean glatt) {
  while (hours > 12) {
    hours -= 12;
  }

  switch (hours) {
  case 0:
  case 12:
  case 24:
    H_DODICI;
    break;
  case 1:
  case 13:
    H_LUNA;
    break;
  case 2:
  case 14:
    H_DUE;
    break;
  case 3:
  case 15:
    H_TRE;
    break;
  case 4:
  case 16:
    H_QUATTRO;
    break;
  case 5:
  case 17:
    H_CINQUE;
    break;
  case 6:
  case 18:
    H_SEI;
    break;
  case 7:
  case 19:
    H_SETTE;
    break;
  case 8:
  case 20:
    H_OTTO;
    break;
  case 9:
  case 21:
    H_NOVE;
    break;
  case 10:
  case 22:
    H_DIECI;
    break;
  case 11:
  case 23:
    H_UNDICI;
    break;
  }
}

#endif
