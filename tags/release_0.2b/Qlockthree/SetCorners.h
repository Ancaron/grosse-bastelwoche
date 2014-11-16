/**
 * SetCorners.h
 * Klasse fuer das Setzten der Eck-Leds. Da man sich haeufig beim Verkabeln
 * vertut und dann die Software anpassen muss, sind die Eck-Leds hier ausgelagert.
 * Dann hat man es bei Software-Updates einfacher.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.1
 * @created  18.3.2012
 * @update   18.1.2013
 *
 * Versionshistorie:
 * V 1.1:  - Optimierung hinsichtlich Speicherbedarf.
 * V 1.1.2: M.Knauer: - Umstellung, so dass die Eck-LEDs nicht mehr Teil der Matrix sind und die Matrix somit bis zu 16 Buchstaben Spalten enthalten kann.
 */
#ifndef SETCORNERS_H
#define SETCORNERS_H

/**
 * Setzt die vier Punkte in den Ecken, je nach minutes % 5 (Rest).
 * Hat man sich in der Verkabelung vertan, muss man die Reihenfolge 
 * der Zahlen in den eckigen Klammern tauschen (aber es bleibt bei
 * den Zahlen 0-3, die die Reihe der Matrix angeben, an die man die
 * Anoden angeloetet hat).
 */
void setCorners(byte minutes) {
  switch (minutes % 5) {
  case 0:
    matrix_corners = 0b00000000;
    break;
  case 1:
    matrix_corners = 0b00000001;
    break;
  case 2:
    matrix_corners = 0b00000011;
    break;
  case 3:
    matrix_corners = 0b00000111;
    break;
  case 4:
    matrix_corners = 0b00001111;
    break;
  }
}

#endif
