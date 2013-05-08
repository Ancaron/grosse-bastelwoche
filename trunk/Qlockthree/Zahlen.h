/**
 * Zahlen.h
 * Definition der Zahlen fuer die Sekundenanzeige der QLOCKTWO.
 * Die Zahlen sind wie die Woerter Bitmasken fuer die Matrix.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.3
 * @created  18.2.2011
 * @updated  18.1.2013
 *
 * Versionshistorie:
 * V 1.1:  - A/M fuer die Umschaltung zwischen LDR auto/manuell hinzugefuegt (Danke an Alexander).
 * V 1.2:  - Bitmaps in den PROGMEM ausgelagert.
 * V 1.3:  - Staben von V 1.1 in eigene Datei ausgelagert.
 * V 1.4.1: M. Knauer:
     - [CHANGE] Ziffer '0': Schraegstrich in der Null entfernt, da der Strich die ohnehin schon schlechte
       Lesbarkeit noch mehr verschlechtert. Aus dem Kontext heraus besteht keine Verwechslungsgefahr
       mit 'O'.
     - [CHANGE] Ziffer '1': Lesbarkeit verbessert.
 */
#ifndef ZAHLEN_H
#define ZAHLEN_H

#include <avr/pgmspace.h>

/* Nachfolgend erfolgt die Definition von folgenden Zeichen:
  0
  1
  2
  3
  4
  5
  6
  7
  8
  9
  =
  A
  B
  C
  D
  E
  F
*/

// Knauer: Die Zeichen '0' und '1' angepasst.
// Knauer: Die Zeichen '=' und 'A' bis 'F' hinzu.
PROGMEM prog_uchar ziffern[][7] = {
  /* '0' */
  {
    0b00001110,
    0b00010001,
    0b00010001,
    0b00010001,
    0b00010001,
    0b00010001,
    0b00001110
  }
  /* '1' */
  , {
    0b00000010,
    0b00000110,
    0b00001010,
    0b00000010,
    0b00000010,
    0b00000010,
    0b00000111
  }
  /* '2' */
  , {
    0b00001110,
    0b00010001,
    0b00000001,
    0b00000010,
    0b00000100,
    0b00001000,
    0b00011111
  }
  /* '3' */
  , {
    0b00011111,
    0b00000010,
    0b00000100,
    0b00000010,
    0b00000001,
    0b00010001,
    0b00001110
  }
  /* '4' */
  , {
    0b00000010,
    0b00000110,
    0b00001010,
    0b00010010,
    0b00011111,
    0b00000010,
    0b00000010
  }
  /* '5' */
  , {
    0b00011111,
    0b00010000,
    0b00011110,
    0b00000001,
    0b00000001,
    0b00010001,
    0b00001110
  }
  /* '6' */
  , {
    0b00000110,
    0b00001000,
    0b00010000,
    0b00011110,
    0b00010001,
    0b00010001,
    0b00001110
  }
  /* '7' */
  , {
    0b00011111,
    0b00000001,
    0b00000010,
    0b00000100,
    0b00001000,
    0b00001000,
    0b00001000
  }
  /* '8' */
  , {
    0b00001110,
    0b00010001,
    0b00010001,
    0b00001110,
    0b00010001,
    0b00010001,
    0b00001110
  }
  /* '9' */
  , {
    0b00001110,
    0b00010001,
    0b00010001,
    0b00001111,
    0b00000001,
    0b00000010,
    0b00001100
  }
  /* '=' */
  , {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00111110,
    0b00111110,
    0b00000000,
    0b00000000,
  }
  /* 'A' */
  , {
    0b00000100,
    0b00001010,
    0b00010001,
    0b00011111,
    0b00010001,
    0b00010001,
    0b00010001,
  }
  /* 'B' */
  , {
    0b00011100,
    0b00010011,
    0b00011100,
    0b00010000,
    0b00011100,
    0b00010011,
    0b00011100,
  }
  /* 'C' */
  , {
    0b00000011,
    0b00001100,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00001100,
    0b00000011,
  }
  /* 'D' */
  , {
    0b00011000,
    0b00010100,
    0b00010010,
    0b00010010,
    0b00010010,
    0b00010100,
    0b00011000,
  }
  /* 'E' */
  , {
    0b00011111,
    0b00010000,
    0b00010000,
    0b00011110,
    0b00010000,
    0b00010000,
    0b00011111,
  }
  /* 'F' */
  , {
    0b00011111,
    0b00010000,
    0b00010000,
    0b00011110,
    0b00010000,
    0b00010000,
    0b00010000,
  }
};

#endif

