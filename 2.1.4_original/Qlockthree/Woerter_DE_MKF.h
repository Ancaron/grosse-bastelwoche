/**
 * Woerter_DE_MKF.h
 * Definition der deutschen Woerter fuer die Zeitansage.
 * Hier in einer anderen Variante nach der Matix von Gerog M.
 * Sie entspricht dem Layout aus dem Mikrocontroller.net
 * Die Woerter sind Bitmasken fuer die Matrix.
 *
 *   01234567890
 * 0 ESKISTLFÜNF
 * 1 ZEHNZWANZIG
 * 2 DREIVIERTEL
 * 3 TGNACHVORJM
 * 4 HALBQZWÖLFP
 * 5 ZWEINSIEBEN
 * 6 KDREIRHFÜNF
 * 7 ELFNEUNVIER
 * 8 WACHTZEHNRS
 * 9 BSECHSFMUHR
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.0
 * @created  28.10.2012
 */
#ifndef WOERTER_DE_MKF_H
#define WOERTER_DE_MKF_H

/**
 * Definition der Woerter
 */
#define VOR          matrix[3] |= 0b0000001110000000
#define NACH         matrix[3] |= 0b0011110000000000
#define ESIST        matrix[0] |= 0b1101110000000000
#define UHR          matrix[9] |= 0b0000000011100000

#define FUENF        matrix[0] |= 0b0000000111100000
#define ZEHN         matrix[1] |= 0b1111000000000000
#define VIERTEL      matrix[2] |= 0b0000111111100000
#define ZWANZIG      matrix[1] |= 0b0000111111100000
#define HALB         matrix[4] |= 0b1111000000000000
#define DREIVIERTEL  matrix[2] |= 0b1111111111100000

#define H_EIN        matrix[5] |= 0b0011100000000000
#define H_EINS       matrix[5] |= 0b0011110000000000
#define H_ZWEI       matrix[5] |= 0b1111000000000000
#define H_DREI       matrix[6] |= 0b0111100000000000
#define H_VIER       matrix[7] |= 0b0000000111100000
#define H_FUENF      matrix[6] |= 0b0000000111100000
#define H_SECHS      matrix[9] |= 0b0111110000000000
#define H_SIEBEN     matrix[5] |= 0b0000011111100000
#define H_ACHT       matrix[8] |= 0b0111100000000000
#define H_NEUN       matrix[7] |= 0b0001111000000000
#define H_ZEHN       matrix[8] |= 0b0000011110000000
#define H_ELF        matrix[7] |= 0b1110000000000000
#define H_ZWOELF     matrix[4] |= 0b0000011111000000

#endif

