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
 * V 1.2:
     - [CHANGE] Verschiebung weiterer persoenlicher Uhren-Einstellungen von Qlockthree.ino nach prj_settings.h
 * V 1.3:
     - Nachtrag der Aenderungshistory
 * V 1.4:
     - [CHANGE] Erweiterung, so dass eine kleine Wortuhr (10*11+4=114 LEDs) und eine grosse Wortuhr (14*16+4=228 LEDs) moeglich ist.
     - [CHANGE] Defaultwert fuer maximalen LED Strom aller LEDs zusammen von 1.0 auf 0.8 geaendert. Ein z.B. 1 A Stromnetzteil muss auch noch den Rest der Elektronik (Arduino Board usw.) versorgen.
 * V 1.5:
     - [NEW] Zwecks schnellerem Start der Uhr nach Reset kann das "Hello" Blinken per  Compilerschaltert START_WITH_HELLO ausgeschaltet werden.
     - [CHANGE] defines zur Angabe einer kleinen oder grossen Wortuhr umbenannt.

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
 * Welche Wortuhr, 10*11 LEDs oder 14*16 LEDs? Es muss genau eines der defines gesetzt sein.
 */
#define WORDCLOCK_SMALL   /* 10*11 + 4 = 114 LEDs */
/* #define WORDCLOCK_BIG */     /* 14*16 + 4 = 228 LEDs */


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
 * Zwecks schnellerem Start der Uhr nach Reset kann der "Hello-Start" (Blinken zweier LEDs) ausgeschaltet werden
 * (Default: "Hello" ist eingeschaltet).
*/
#define START_WITH_HELLO

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
#define ENABLE_LDR

/*
 * Angabe, ob zur Speicherung von Einstellungen oder Daten das Eeprom verwendet wird. Da hoffentlich
 * jeder Arduino Controller ein Eeprom hat, spricht eigentlich nichts gegen die Verwendung des Eeproms.
 * Default: eingeschaltet, d.h. das EEPROM wird verwendet.
 */
#define ENABLE_EEPROM

/*
  Strombegrenzung der LEDs per PWM
*/
#define LED_CURRENT 0.020 /* max. 20 mA pro LED (d.h. bei voller Ansteuerung) */
#define MAX_CURRENT 0.8   /* Maximaler Strom fuer alle LEDs zusammen. Bei Stroemen darueber wird per PWM abgeregelt. */
/* LED_PWM_MAX gibt den maximal einstellbaren Wert an. LED_PWM_MAX entspricht 100% Helligkeit.
*/
#define LED_PWM_MAX  255

/* Angaben fuer die automatische Lichthelligkeit per LDR */
/* ToDo: Ausfuehrliche Erklaerung */
/* AD-Wandler:
   Eingelesener Wert liegt im Bereich [0..1023]
      0: Maximale Helligkeit erkannt
   1023: Minimale Dunkelheit erkannt
*/
#define LDR_BRIGHTNESS_VAL_MIN  500   /* [0..1023] */
#define LDR_MIN_PWM             80.0  /* [0..255] bzw. [0..LED_PWM_MAX] */

/*
  Allgemeine Wortuhr defines
*/
#if defined(WORDCLOCK_SMALL)
	#define CNT_LINES 10
	#define CNT_COLS  11
#endif
#if defined(WORDCLOCK_BIG)
	#define CNT_LINES 14
	#define CNT_COLS  16
#endif

// Minimale und maximale Ausmasse der Uhr, Zeilen duerfen vom User nicht veraendert werden!
#if CNT_LINES > CNT_COLS
  #define CNT_CHARS_MAX  CNT_LINES
  #define CNT_CHARS_MIN  CNT_COLS
#else
  #define CNT_CHARS_MAX  CNT_COLS
  #define CNT_CHARS_MIN  CNT_LINES
#endif



#endif

