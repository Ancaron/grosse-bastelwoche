/**
 * Woerter_CH.h
 * Definition der schweizerischen Woerter fuer die Zeitansage.
 * Die Woerter sind Bitmasken fuer die Matrix.
 * 
 *   01234567890
 * 0 ESKISCHAFÜF
 * 1 VIERTUBFZÄÄ
 * 2 ZWÄNZGXVORI
 * 3 ABOHAUBITOM
 * 4 EISZWÖISDRÜ
 * 5 VIERIVFÜFIK
 * 6 SÄCHSISIBNI
 * 7 ACHTIMNÜNIG
 * 8 ZÄNILBJEUFI
 * 9 ZWÖUFINAUHR
 *
 * @mc       Arduino/RBBB
 * @autor    Thomas Schuler / thomas.schuler _AT_ vtg _DOT_ admin _DOT_ ch
 * @version  1.0
 * @created  18.3.2012
 */
#ifndef WOERTER_CH_H
#define WOERTER_CH_H

/**
 * Definition der Woerter
 */
#define VOR          matrix[2] |= 0b0000000111000000
#define AB           matrix[3] |= 0b1100000000000000
#define ESISCH       matrix[0] |= 0b1101111000000000

#define FUEF         matrix[0] |= 0b0000000011100000
#define ZAEAE        matrix[1] |= 0b0000000011100000
#define VIERTU       matrix[1] |= 0b1111110000000000
#define ZWAENZG      matrix[2] |= 0b1111110000000000
#define HAUBI        matrix[3] |= 0b0001111100000000

#define H_EIS        matrix[4] |= 0b1110000000000000
#define H_ZWOEI      matrix[4] |= 0b0001111000000000
#define H_DRUE       matrix[4] |= 0b0000000011100000
#define H_VIER       matrix[5] |= 0b1111100000000000
#define H_FUEFI      matrix[5] |= 0b0000001111000000
#define H_SAECHSI    matrix[6] |= 0b1111110000000000
#define H_SIEBNI     matrix[6] |= 0b0000001111100000
#define H_ACHTI      matrix[7] |= 0b1111100000000000
#define H_NUENI      matrix[7] |= 0b0000001111000000
#define H_ZAENI      matrix[8] |= 0b1111000000000000
#define H_EUFI       matrix[8] |= 0b0000000111100000
#define H_ZWOEUFI    matrix[9] |= 0b1111110000000000

#endif

