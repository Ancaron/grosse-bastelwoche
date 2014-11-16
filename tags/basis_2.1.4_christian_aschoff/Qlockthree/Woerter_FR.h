/**
 * Woerter_FR.h
 * Definition der franzoesischen Woerter fuer die Zeitansage.
 * Die Woerter sind Bitmasken fuer die Matrix.
 *
 *   01234567890
 * 0 ILNESTODEUX
 * 1 QUATRETROIS
 * 2 NEUFUNESEPT
 * 3 HUITSIXCINQ
 * 4 MIDIXMINUIT
 * 5 ONZERHEURES
 * 6 MOINSOLEDIX
 * 7 ETRQUARTPMD
 * 8 VINGT-CINQU
 * 9 ETSDEMIEPAM
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.0
 * @created  12.12.2012
 */
#ifndef WOERTER_FR_H
#define WOERTER_FR_H

/**
 * Definition der Woerter
 */
// Trait = Bindestrich (-)
#define TRAIT        matrix[8] |= 0b0000010000000000
#define ET           matrix[7] |= 0b1100000000000000
#define LE           matrix[6] |= 0b0000001100000000
#define MOINS        matrix[6] |= 0b1111100000000000
#define ILEST        matrix[0] |= 0b1101110000000000
#define HEURE        matrix[5] |= 0b0000011111000000
#define HEURES       matrix[5] |= 0b0000011111100000

#define CINQ         matrix[8] |= 0b0000001111000000
#define DIX          matrix[6] |= 0b0000000011100000
#define QUART        matrix[7] |= 0b0001111100000000
#define VINGT        matrix[8] |= 0b1111100000000000
#define DEMI         matrix[9] |= 0b0001111000000000

#define H_UNE        matrix[2] |= 0b0000111000000000
#define H_DEUX       matrix[0] |= 0b0000000111100000
#define H_TROIS      matrix[1] |= 0b0000001111100000
#define H_QUATRE     matrix[1] |= 0b1111110000000000
#define H_CINQ       matrix[3] |= 0b0000000111100000
#define H_SIX        matrix[3] |= 0b0000111000000000
#define H_SEPT       matrix[2] |= 0b0000000111100000
#define H_HUIT       matrix[3] |= 0b1111000000000000
#define H_NEUF       matrix[2] |= 0b1111000000000000
#define H_DIX        matrix[4] |= 0b0011100000000000
#define H_ONZE       matrix[5] |= 0b1111000000000000
#define H_MIDI       matrix[4] |= 0b1111000000000000
#define H_MINUIT     matrix[4] |= 0b0000011111100000

#endif

