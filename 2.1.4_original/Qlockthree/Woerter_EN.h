/**
 * Woerter_EN.h
 * Definition der englischen Woerter fuer die Zeitansage.
 * Die Woerter sind Bitmasken fuer die Matrix.
 *
 *   01234567890 
 * 0 ITLISASTIME
 * 1 ACQUARTERDC
 * 2 TWENTYFIFEX
 * 3 HALFBTENFTO
 * 4 PASTERUNINE
 * 5 ONESIXTHREE
 * 6 FOURFIVETWO
 * 7 EIGHTELEVEN
 * 8 SEVENTWELVE
 * 9 TENSEOCLOCK
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.0
 * @created  17.12.2012
 */
#ifndef WOERTER_EN_H
#define WOERTER_EN_H

/**
 * Definition der Woerter. 
 */
 
#define ITIS     matrix[0] |= 0b1101100000000000
#define TIME     matrix[0] |= 0b0000000111100000
#define A        matrix[1] |= 0b1000000000000000
#define OCLOCK   matrix[9] |= 0b0000011111100000

#define QUATER   matrix[1] |= 0b0011111110000000
#define TWENTY   matrix[2] |= 0b1111110000000000
#define FIVE     matrix[2] |= 0b0000001111000000
#define HALF     matrix[3] |= 0b1111000000000000
#define TEN      matrix[3] |= 0b0000011100000000
#define TO       matrix[3] |= 0b0000000001100000
#define PAST     matrix[4] |= 0b1111000000000000

#define H_NINE   matrix[4] |= 0b0000000111100000
#define H_ONE    matrix[5] |= 0b1110000000000000
#define H_SIX    matrix[5] |= 0b0001110000000000
#define H_THREE  matrix[5] |= 0b0000001111100000
#define H_FOUR   matrix[6] |= 0b1111000000000000
#define H_FIVE   matrix[6] |= 0b0000111100000000
#define H_TWO    matrix[6] |= 0b0000000011100000
#define H_EIGHT  matrix[7] |= 0b1111100000000000
#define H_ELEVEN matrix[7] |= 0b0000011111100000
#define H_SEVEN  matrix[8] |= 0b1111100000000000
#define H_TWELVE matrix[8] |= 0b0000011111100000
#define H_TEN    matrix[9] |= 0b1110000000000000

#endif

