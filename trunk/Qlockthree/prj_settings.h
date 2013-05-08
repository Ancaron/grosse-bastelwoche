/**
 * prj_settings.h
 * Compilereinstellungen, zur persoenlichen Firmware Konfiguration
 *
 * @mc       Arduino/RBBB
 * @autor    Markus Knauer / knauer _AT_ gmx _DOT_ de
 * @version  1.1
 * @created  18.01.2013
 * @updated  18.01.2013
 *
 * Versionshistorie:
 * V 1.1:  - Projekteinstellung aus "Qlockthree.ino" in diesen header ausgelagert.
  */
#ifndef PRJ_SETTINGS_H
#define PRJ_SETTINGS_H

/*
 * Den DEBUG-Schalter gibt es in allen Bibiliotheken. Wird er eingeschaltet, werden ueber den
 * 'Serial-Monitor' der Arduino-Umgebung Informationen ausgegeben. Die Geschwindigkeit im
 * Serial-Monitor muss mit der hier angegeben uebereinstimmen.
 * Default: ausgeschaltet
 */
// #define DEBUG
// Die Geschwindigkeit der seriellen Schnittstelle. Default: 57600
   #define SERIAL_SPEED 57600

/*
 * Welche Sprache wird gewuenscht?
 */
   #define DE_DE_HOCHDEUTSCH
// #define DE_SW_SCHWAEBISCH
// #define DE_BA_BAYRISCH
// #define CH_BERNERDUETSCH
// #define FR_FRANZOESISCH
// #define EN_ENGLISCH
// #define IT_ITALIENISCH

/*
 * Alarmfunktion einschalten?
 * Dazu muss ein Lautsprecher an D13 und GND und eine weitere 'Eck-LED' an die 5te Reihe.
 * Dann gibt es einen neuen Modus, direkt nach der normalen Zeitanzeige. Die neue LED
 * blinkt nach dem Moduswechsel und der Alarm ist eingeschaltet. Drueckt man jetzt M+ oder H+ stellt man
 * die Alarmzeit ein, angedeutet durch die blinkende Alarm-LED. Druckt man 10 Sekunden
 * keine Taste, hoert das Blinken auf und die normale Zeit wird wieder angezeigt.
 * Bei erreichen des Alarms piept der Lautpsrecher auf D13. Zum Ausschalten muss der
 * Modus-Taster gedrueckt werden.
 * Weiter unten kommen drei weitere DEFINEs:
 * - SPEAKER ist der Pin, an dem der Lautsprecher haengt.
 * - SPEAKER_FREQUENCY ist die Tonhoehe, wenn der Speaker ein Lautpsrecher ist.
 * - SPEAKER_IS_BUZZER: wenn einkommentiert wird davon ausgegangen, dass am Pin SPEAKER ein Buzzer haengt.
 * Default: ausgeschaltet
 */
// #define ENABLE_ALARM

/*
 * Die Status-LEDs koennen hier durch auskommentieren ausgeschaltet werden.
 * Default: eingeschaltet 
 */
#define ENABLE_DCF_LED
#define ENABLE_SQW_LED

/*
 * Wer einen LDR (an A3) installiert hat, kann diese Zeile auskommentieren und hat dann eine von
 * der Umgebungshelligkeit abhaengige Helligkeit.
 * Default: eingeschaltet
 */
// Knauer: ausgeschaltet
//  #define ENABLE_LDR

/*
 * Dieser Schalter erhoeht die Helligkeit, indem er nicht beleuchtete Zeilen ueberspringt. (Tipp
 * von Johannes)
 * Default: ausgeschaltet
 */
// Knauer: eingeschaltet
#define SKIP_BLANK_LINES

/*
 * Angabe, ob zur Speicherung von Einstellungen oder Daten das Eeprom verwendet wird. Da hoffentlich
 * jeder Arduino Controller ein Eeprom hat, spricht eigentlich nichts gegen die Verwendung des Eeproms.
 * Default: eingeschaltet, d.h. das EEPROM wird verwendet.
 */
#define ENABLE_EEPROM


#endif

