/**
 * SetHours_EN.h
 * Klasse fuer das Setzten der Stunden in Englisch.
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
#ifndef SETHOURS_EN_H
#define SETHOURS_EN_H

/**
 * Setzt die Stunden, je nach hours. 'glatt' bedeutet,
 * es ist genau diese Stunde und wir muessen 'OCLOCK' dazuschreiben.
 */
void setHours(byte hours, boolean glatt) {
  while (hours > 12) {
    hours -= 12;
  }

  if (glatt) {
    OCLOCK;
  }

  switch (hours) {
  case 0:
  case 12:
  case 24:
    H_TWELVE;
    break;
  case 1:
  case 13:
    H_ONE;
    break;
  case 2:
  case 14:
    H_TWO;
    break;
  case 3:
  case 15:
    H_THREE;
    break;
  case 4:
  case 16:
    H_FOUR;
    break;
  case 5:
  case 17:
    H_FIVE;
    break;
  case 6:
  case 18:
    H_SIX;
    break;
  case 7:
  case 19:
    H_SEVEN;
    break;
  case 8:
  case 20:
    H_EIGHT;
    break;
  case 9:
  case 21:
    H_NINE;
    break;
  case 10:
  case 22:
    H_TEN;
    break;
  case 11:
  case 23:
    H_ELEVEN;
    break;
  }
}

#endif
