/**
 * Woerter_IT.h
 * Definition der italienischen Woerter fuer die Zeitansage.
 * Die Woerter sind Bitmasken fuer die Matrix.
 *
 *   01234567890 
 * 0 SONORLEBORE
 * 1 ERLUNASDUEZ
 * 2 TREOTTONOVE
 * 3 DIECIUNDICI
 * 4 DODICISETTE
 * 5 QUATTROCSEI
 * 6 CINQUESMENO
 * 7 ECUNOQUARTO
 * 8 VENTICINQUE
 * 9 DIECIEMEZZA
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.0
 * @created  17.12.2012
 */
#ifndef WOERTER_IT_H
#define WOERTER_IT_H

/**
 * Definition der Woerter.
 */
#define SONOLE    matrix[0] |= 0b1111011000000000
#define LE        matrix[0] |= 0b0000011000000000
#define ORE       matrix[0] |= 0b0000000011100000
#define H_E       matrix[1] |= 0b1000000000000000

#define H_LUNA    matrix[1] |= 0b0011110000000000
#define H_DUE     matrix[1] |= 0b0000000111000000
#define H_TRE     matrix[2] |= 0b1110000000000000
#define H_OTTO    matrix[2] |= 0b0001111000000000
#define H_NOVE    matrix[2] |= 0b0000000111100000
#define H_DIECI   matrix[3] |= 0b1111100000000000
#define H_UNDICI  matrix[3] |= 0b0000011111100000
#define H_DODICI  matrix[4] |= 0b1111110000000000
#define H_SETTE   matrix[4] |= 0b0000001111100000
#define H_QUATTRO matrix[5] |= 0b1111111000000000
#define H_SEI     matrix[5] |= 0b0000000011100000
#define H_CINQUE  matrix[6] |= 0b1111110000000000

#define MENO      matrix[6] |= 0b0000000111100000
#define E         matrix[7] |= 0b1000000000000000
#define UN        matrix[7] |= 0b0011000000000000
#define QUARTO    matrix[7] |= 0b0000011111100000
#define VENTI     matrix[8] |= 0b1111100000000000
#define CINQUE    matrix[8] |= 0b0000011111100000
#define DIECI     matrix[9] |= 0b1111100000000000
#define MEZZA     matrix[9] |= 0b0000001111100000

#endif

