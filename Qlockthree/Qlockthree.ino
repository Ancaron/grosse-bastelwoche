/**
 * Clockthree.pde (.ino)
 * Die "Firmware" der Selbstbau-QLOCKTWO.
 *
 * @mc       Arduino/RBBB (ATMEGA328)
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  2.1.4
 * @created  1.11.2011
 * @updated  18.1.2013
 *
 * TO-DOs:
 * - ganzes Datum vom DCF77 in DS1307 schreiben; Ausgabe von 'Specials' an bestimmten
 *   Datumswerten (Geburtstag etc.) - fehlt noch. Das Problem ist die Ueberpruefung
 *   des DCF77-Signals. Soll das Datum auch stimmen werden viel mehr Telegramme
 *   verworfen und die Synczeit wird viel laenger. Ausserdem sollte man die Moeglichkeit
 *   habe, das Datum von Hand einstellen zu koennen.
 *
 * Versionshistorie:
 * V 1.1:   - DCF77 auf reine Zeit ohne Strings umgestellt.
 *          - Ganzes Datum wird in die DS1307 geschrieben (wieder verworfen).
 * V 1.2:   - Schnelles Schreiben der Shift-Register eingefuehrt.
 * V 1.3:   - Auf eigene DCF77-Bibliothek umgestellt (MyDCF77) und DCF77Helper verbessert.
 * V 1.4:   - Glimmen/Nachleuchten dank Tipp von Volker beseitigt (http://www.mikrocontroller.net/topic/209988).
 *          - Erneute Fehlerbereinigung in der DCF77-Bibliothek.
 * V 1.5:   - Die Helligkeit laesst sich ueber die Variable 'brightness' einstellen (Bereich 1-9) bzw.
 *            ueber den Compiler-Schalter 'ENABLE_LDR' die Regelung einschalten.
 * V 1.6:   - Fehler in der DCF77Helper-Bibliothek behoben.
 * V 1.7:   - SKIP_BLANK_LINES eingefuehrt, damit hellere LEDs (Danke an Johannes).
 * V 1.8:   - UPSIDE_DOWN eingefuehrt, damit man die Kabel beim Anoden-Multiplexer nicht kreuzen muss.
 * V 1.9:   - Diverse Verbesserungen und Fehlerbehebungen, die das Flackern drastisch reduzieren.
 * V 1.9.1: - Fehler behoben, der die Nutzung eines analogen Pins fuer den DCF77-Empfaenger verhindert hat.
 * V 1.9.2: - Timing-Parameter fuer die PWM ueber define anpassbar.
 *          - LDR-Grenzwerte automatisch anpassbar.
 *          - Schreibfehler in setHoures()->setHours() behoben.
 *          - Kompatibilitaet zu Arduino-IDE 1.0 hergestellt.
 * V 1.9.3: - Glimmen wieder behoben.
 * V 1.9.4: - Modus zum Einstellen der Helligkeit eingefuehrt.
 * V 2.0:   - Sprachrelevante Dinge ausgelagert, so kann man mehr Sprachen haben und einfach durch einkommentieren aktivieren.
 *          - setWords in setMinutes und setMinutes in setCorners umbenannt, weil es mehr Sinn ergibt.
 *          - setCorners in eigene Datei ausgelagert, weil viele Bastler sich vertun und in der Routine Aenderungen vornehmen muessen.
 *          - LDR in eigene Klasse ausgelagert und Werte geglaettet. Am Anfang werden 1000 Werte gelesen, damit er sich einpegelt.
 *          - Signal vom DCF77-Empfaenger geglaettet, damit nicht ein einzelner falscher Peak das Telegramm zerstoert. 
 *          - Status-LEDs koennen ueber DEFINEs ausgeschaltet werden.
 *          - DCF77- und SQW-LED blinken am Anfang drei Mal als 'Hello', damit man ohne Serial-Monitor sehen kann, ob der ATMEGA anlaeuft.
 *          - Serial-Output ist immer an, kleine Statusmeldung waehrend der Initialisierung, damit man beim Bespielen des ATMEGA ohne weitere 
 *            Elektronik sehen kann, ob das Programm drauf ist und laeuft.
 *          - Aenderung, die ein Stellen der Zeit nach dem DCF77-Signal auch im Modus 'BLANK' ermoeglicht - in diesem Modus ist der Empfang
 *            weniger gestoert, da die LED-Matrix abgeschaltet ist.
 *          - Zeitgesteuertes Abschalten des Displays eingefuehrt (Stromsparen in der Nacht/Schlafzimmer/besserer Empfang des DCF77-Empfaengers).
 *          - Speaker auf D13 eingefuehrt.
 *          - Alarm-Mode eingefuehrt.
 *          - Bayrische Sprachvariante (DE_BA): 'viertel nach Zehn', aber 'dreiviertel Elf'.
 * V 2.0.1: - DCF77-Tresholds angepasst.
 * V 2.0.2: - Strings in PROGMEM (flash) ausgelagert.
 * V 2.0.3: - SPEAKER_IS_BUZZER eingefuehrt, damit kann man sagen, ob man einen Lautsprecher oder Buzzer als Alarm verwendet.
 * V 2.0.4: - falsches BREAK dank Lars behoben.
 * V 2.0.5: - Franzoesisch hinzugefuegt, Woerter_??.h's anschaulicher gemacht. Weitere Sprachen angelegt, aber noch nicht die Logik implementiert (Hilfe?!).
 * V 2.0.6: - cleanWordsForAlarmSettingMode() eingefuehrt, damit das Stellen des Alarms sprachenunabhaengig ist.
 *          - Das DCF77-Signal kann per Compiler-Schalter invertiert werden.
 * V 2.0.7: - Neuer Modus: Umschaltung LDR auto/manuell dank Alexander.
 * V 2.0.8: - Genauigkeit verbessert, dank Peter (Interrupt auf FALLING). @Peter: Das Zurueckscheiben in die DS1307 passiert im Normalbetrieb ja nur beim Update
 *            ueber den DCF77-Empfaenger, daher habe ich es weggelassen.
 * V 2.0.9: - SplitSideDown rausgenommen, diesen seltenen Fehler braucht kein Mensch.
 * V 2.1:   - Neue Sprachen hinzugefuegt: Englisch und Italiensch. Spanisch ist angelegt, aber nicht implementiert, weil ich kein Wort Spanisch spreche.
 *            Man kann jetzt einfach relativ weit oben im Code ueber Compiler-Schalter festlegen, welche Sprache man haben moechte.
 * V 2.1.1: - Bitmaps in den PROGMEM ausgelagert. So kann man alle Buchstaben halten.
 * V 2.1.2: - Bug im Alaram-Modus behoben.
 * V 2.1.3: - Zusaetzlich zu den Ziffern auch Staben eingefuehrt, A/M-Modus darauf umgestellt (Vorbereitung auf Konfigurationsmoeglichkeit fuer alle Sprachen in einer Firmware)
 * V 2.1.4: - Optimierung hinsichtlich Speicherbedarf.
 * V 2.1.4.1: M. Knauer:
     - [CHANGE] Die meisten defines, die Anwender zwecks eigener Konfiguration selbst veraendern, wurden in den seperaten header "prj_settings.h" ausgelagert.
       Dies hat den Vorteil, dass viele Aenderungen in der Datei "Qlockthree.ino" (z.B. Menue Aenderungen, zusaetzliche Klassen/Module usw.) nicht die persoenlichen
       Anwender Konfigurationen (ehemals in "Qlockthree.ino") ueberschreiben.
     - [NEW] Neue Funktionalitaet hinzu, so dass Anwender-Einstellungen im Eeprom gespeichert werden und auch nach Abklemmen der Stromversorgung erhalten bleiben.
     - [BUGFIX] Obwohl lt. nicht definiertem define "ENABLE_LDR" ein LDR nicht vorhanden war, wurde ein Menue zur Verwendung des LDR angezeigt
       --> Wenn lt. Compilerschalter kein LDR vorhanden ist, wird das Menue zur Aktiverung des LDR nun nicht mehr angezeigt.
     - [BUGFIX][CHANGE]
         Voraussetzung: Lt. Compilerschalter ist ein LDR vorhanden:
         Fehler: Obwohl bei der LDR Einstellung "A" oder "M" (Automatisch oder manuell) die Einstellung "A" ausgewaehlt wurde, wird trotzdem die Einstellmoeglichkeit
                 zur Helligkeit (brightness) angezeigt. Es macht aber keinen Sinn bzw. ist fuer den Anwender nicht nachvollziehbar, wenn der Anwender Einstellungen
                 fuer Funktionen vornehmen kann, welche er deaktiviert hat.
 * V 2.1.4.2: M. Knauer:
     - [NEW] Umstellung auf LED Treiber WS2803.
 * V 2.1.4.3: M. Knauer:
     - [CHANGE] Die beiden Controllerausgaenge zur Ansteuerung der WS2803 Treiber wurden von den analogen Ausgaengen A0 u. A1 auf
	   die beiden digitalen Ausgaenge D10 und D11 geaendert (per Compilerschalter aenderbar).
 * V 2.1.4.4: M. Knauer:
     - [CHANGE] Umstellung der SW auf die Time.h Library. Die Library realisiert eine fortlaufende Uhrzeit inkl. Datum in Sekunden Aufloesung, welche auf der Arduino Plattform autark weiterlaufen kann. Somit kann die Wortuhr auch ohne RTC und ohne DCF Uhr weiterlaufen. Zumindest nach POR sollte die RTC oder DCF Uhr vorhanden sein. Ansonsten muss die Uhr haendisch gestellt werden.
     - [CHANGE] Verbesserung DCF Empfang: Umsetzung einer Strategie, damit das Beschreiben der WS2803 Treiber nicht immer den DCF Empfang stoert.
     - [CHANGE] Verschiebung weiterer persoenlicher Uhren-Einstellungen von Qlockthree.ino nach prj_settings.h
     - [CHANGE] Timings zum Sender der Daten an die WS2803 Treiber verkleinert.
     - [CHANGE] Verlegung der Sendereihenfolge der Buchstaben (send_order.h) vom RAM ins ROM.
     - [CHANGE] Berechnung des Ausgabe Inhaltes in eigene Funktion ausgelagert: void CalculateSceenBuffer(tmElements_t TimeOutput_tmElements)
     - [CHANGE] diverse kleinere Aenderungen
 * V 2.1.4.5: M. Knauer:
     - [CHANGE] Zu Programmstart werden seriell Infos wie Version, Stroeme usw. ausgegeben.
     - [CHANGE] Serielle Debug Infos entfernt
 * V 2.1.4.6: M. Knauer:
     - [CHANGE] - Umstellung, so dass die Eck-LEDs nicht mehr Teil der Matrix sind und die Matrix somit bis zu 16 Buchstaben Spalten enthalten kann.
     - [CHANGE] - Zwecks Umstellung auf die grosse 14*16 Buchstaben Wortuhr: Spalten und Zeilen defines (CNT_COLS und CNT_LINES) werden nun benutzt, um alle notwendigen Werte (z.B. Anzahl benoetigter WS2803 Treiber) zu berechnen.
     - [CHANGE] - Die Eck-LEDs werden nun auch in der Datei "send_order.h" angegeben.
     - [CHANGE] - Bei nicht gesetztem ENABLE_LDR wird immer die maximale Helligkeit eingestellt. Offene Aufgabe: Umstellen, so dass die eingestellte Helligkeit uebernommen wird!
*/

#include "prj_settings.h"
#include <Wire.h> // Wire library fuer I2C
#include <avr/pgmspace.h>
#include "configuration.h"
#include "DS1307.h"
#include "MyDCF77.h"
#include "Button.h"
#include "LDR.h"
#include "DCF77Helper.h"
#include "Time.h"

#if defined(ENABLE_EEPROM)
#include <EEPROM.h>
#endif


/**
 * SW Version
 */
#define SW_VERSION_STR  "Wortuhr WS2803 0.1+ (02.02.2014)"


/**
 * Konfiguration, die z.B. auch im Eeprom gespeichert wird.
 */
CConfig Config;

/* Position in screen buffer / matrix for special LEDs */
#define LED_CORNER_L_TOP     (CNT_LINES*CNT_COLS)     /* LED corner left top */
#define LED_CORNER_R_TOP     (CNT_LINES*CNT_COLS + 1) /* LED corner right top */
#define LED_CORNER_R_BOTTOM  (CNT_LINES*CNT_COLS + 2) /* LED corner right bottom */
#define LED_CORNER_L_BOTTOM  (CNT_LINES*CNT_COLS + 3) /* LED corner left bottom */
#define LED_NC               (CNT_LINES*CNT_COLS + 4) /* LED not connected */

// Tabelle im ROM ablegen
PROGMEM prog_uchar SEND_ORDER_TABLE[] = {
  #include "send_order.h"
};


/**
 * Die Real-Time-Clock
 */
DS1307 ds1307(0x68);
static boolean FetchDs1307Time = true;
static boolean RetryDs1307 = true;
// Hilfsvariable, da I2C und Interrupts nicht zusammenspielen
volatile static boolean ds1307Available = false;
volatile static unsigned long ds1307LastIrqTime_millis = 0;


/**
 * Die Funkuhr.
 */
#define dcf77Led      8
#define dcf77Signal   9
MyDCF77 dcf77(dcf77Signal);
DCF77Helper dcf77Helper;
/**
 * Das Rechtecksignal der RTC fuer den Interrupt
 */
#define rtcSQWLed     4
#define rtcSQWSignal  2

/**
 * Der Lautsprecher
 */
#define SPEAKER  13
#define SPEAKER_FREQUENCY 200000
// #define SPEAKER_IS_BUZZER 

/*
  LED Driver WS2803 von Worldsemi
*/
#define WS2803_DELAY       0     /* with a 16 MHz Arduino no delay is needed */
#define WS2803_RESET_TIME  650   /* perhaps this time can be set to 600 (?) */

#define WS2803_CKO  10 /* Clock output an D10 */
#define WS2803_SDO  11 /* Serial data output an D11 */
#define WS2803_CKO_Set_PinMode()  pinMode(WS2803_CKO, OUTPUT)
#define WS2803_SDO_Set_PinMode()  pinMode(WS2803_SDO, OUTPUT)
#define WS2803_CKO_Write_Low()   digitalWrite(WS2803_CKO, LOW)
#define WS2803_CKO_Write_High()  digitalWrite(WS2803_CKO, HIGH)
#define WS2803_SDO_Write_Low()   digitalWrite(WS2803_SDO, LOW)
#define WS2803_SDO_Write_High()  digitalWrite(WS2803_SDO, HIGH)


/**
 * Variablen fuer den Alarm.
 */
#ifdef ENABLE_ALARM
tmElements_t alarmTime_tmElements = {0, 0, 7, 0, 1, 1, 0}; // Second, Minute, Hour, Wday: day of week, sunday is day 1, Day, Month, Year: offset from 1970
boolean isBeeping;
byte showAlarmTimeTimer;
boolean toneIsOn;
#endif

/**
 * Der Helligkeitssensor
 */
#ifdef ENABLE_LDR
  LDR ldr(A3);
#endif
/**
 * Die Helligkeit
 */
int brightness;
/**
 * Die Helligkeit zum Anzeigen
 */
int brightnessToDisplay;

/**
 * Die Tasten
 */
Button minutesPlusButton(5);
Button hoursPlusButton(6);
Button modeChangeButton(7);
/**
 * Die Modi
 */
#ifndef ENABLE_ALARM
  #define NORMAL     0
  #define SECONDS    1
  #define LDR_MODE   2
  #define BRIGHTNESS 3
  #define SCRAMBLE   4
  #define BLANK      5
  #define ALL        6
  #define MAX        7
  byte mode = NORMAL;
#else
  #define NORMAL     0
  #define ALARM      1
  #define SECONDS    2
  #define LDR_MODE   3
  #define BRIGHTNESS 4
  #define SCRAMBLE   5
  #define BLANK      6
  #define ALL        7
  #define MAX        8
  byte mode = NORMAL;
#endif

/**
 * Hier definiert man die Ab- und Anschaltzeiten fuer das Display. Die Abschaltung des
 * Displays verbessert den Empfang des DCF77-Empfaengers. Und hilft, falls die Uhr im 
 * Schlafzimmer haengt.
 * Sind alle Werte auf 0 wird das Display nie abgeschaltet. Nach einer Minute kann man das 
 * Display manuell wieder ein- / ausschalten.
 * Achtung! Wenn sich die Uhr nachmittags abschaltet ist sie in der falschen Tageshaelfte!
 */
#ifdef ENABLE_ALARM 
// als Wecker Display nicht abschalten...
tmElements_t offTime_tmElements = {0, 0, 0, 0, 1, 1, 0}; // Sekunden werden ignoriert. Second, Minute, Hour, Wday: day of week, sunday is day 1, Day, Month, Year: offset from 1970
tmElements_t onTime_tmElements  = {0, 0, 0, 0, 1, 1, 0}; // Sekunden werden ignoriert. Second, Minute, Hour, Wday: day of week, sunday is day 1, Day, Month, Year: offset from 1970
#else
// um 3 Uhr Display abschalten
tmElements_t offTime_tmElements = {0, 0, 3, 0, 1, 1, 0}; // Sekunden werden ignoriert. Second, Minute, Hour, Wday: day of week, sunday is day 1, Day, Month, Year: offset from 1970
// um 4:30 Uhr Display wieder anschalten
tmElements_t onTime_tmElements  = {0, 30, 4, 0, 1, 1, 0}; // Sekunden werden ignoriert. Second, Minute, Hour, Wday: day of week, sunday is day 1, Day, Month, Year: offset from 1970
#endif

// Merker fuer den Modus vor der Abschaltung...
byte lastMode = mode;

// Ueber die Wire-Library festgelegt:
// Arduino analog input 4 = I2C SDA
// Arduino analog input 5 = I2C SCL

// Wenn auf true gesetzt, erfolgt eine schnellstmoegliche Ausgabe des Bildschirminhaltes.
// Dies kann ggf. das DCF Empfangssignal stoeren!
boolean fastDisplayRefresh_bt;

// Die Matrix, der Bildschirmspeicher
word matrix[CNT_LINES];

// In folgendem Byte werden die Eck-LEDs gesetzt. Es handelt sich nicht um eine Matrix, aber es ist eine Erweiterung der Matrix und laesst sich mit diesem Namen so besser finden.
unsigned char matrix_corners;

/**
 * Hier werden die Grafiken fuer die Zahlen der
 * Sekundenanzeige und die Staben includiert.
 */
#include "Zahlen.h"
#include "Staben.h"

/**
 * Hier werden die sprachabhaengigen Dateien includiert.
 * Die Sprache kann weiter oben mit Compiler-Schaltern geaendert werden.
 */
#ifdef DE_DE_HOCHDEUTSCH 
  #include "Woerter_DE.h"
// Die Variante DE_MKF entspricht der Vorlage vom Mikrocontroller-Forum.
// #include "Woerter_DE_MKF.h"
   #include "SetMinutes_DE_DE.h"
   #include "SetHours_DE.h"
#endif

#ifdef DE_SW_SCHWAEBISCH 
  #include "Woerter_DE.h"
// Die Variante DE_MKF entspricht der Vorlage vom Mikrocontroller-Forum.
// #include "Woerter_DE_MKF.h"
   #include "SetMinutes_DE_SW.h"
   #include "SetHours_DE.h"
#endif

#ifdef DE_BA_BAYRISCH 
  #include "Woerter_DE.h"
// Die Variante DE_MKF entspricht der Vorlage vom Mikrocontroller-Forum.
// #include "Woerter_DE_MKF.h"
   #include "SetMinutes_DE_BA.h"
   #include "SetHours_DE.h"
#endif

#ifdef CH_BERNERDUETSCH
  #include "Woerter_CH.h"
  #include "SetMinutes_CH.h"
  #include "SetHours_CH.h"
#endif

#ifdef FR_FRANZOESISCH
  #include "Woerter_FR.h"
  #include "SetMinutes_FR.h"
  #include "SetHours_FR.h"
#endif

#ifdef EN_ENGLISCH
  #include "Woerter_EN.h"
  #include "SetMinutes_EN.h"
  #include "SetHours_EN.h"
#endif

#ifdef IT_ITALIENISCH
  #include "Woerter_IT.h"
  #include "SetMinutes_IT.h"
  #include "SetHours_IT.h"
#endif  


/* Header fuer Eck LEDs includieren */
#include "SetCorners.h"


/**
 * Initialisierung. setup() wird einmal zu Beginn aufgerufen, wenn der
 * Arduino Strom bekommt.
 */
void setup() {
  Serial.begin(SERIAL_SPEED);
  Serial.println(F("Qlockthree is initializing..."));

  Serial.println(F(SW_VERSION_STR));
  
  Serial.print(F("Send order version: "));
  Serial.println(F(SEND_ORDER_VERSION_STR));

  Serial.print(F("Current limitation all LEDs: "));
  Serial.print(MAX_CURRENT, 4);
  Serial.println(F(" A"));
  
  Serial.print(F("Current limitation one LED: "));
  Serial.println(LED_CURRENT, 4);
#ifdef DEBUG
  Serial.println();
  Serial.println(F("... and starting in debug-mode..."));
#endif
  Serial.flush();

  // starte Wire-Library als I2C-Bus Master
  Wire.begin();

  // DCF77-Pins konfigurieren
  pinMode(dcf77Signal, INPUT);
  digitalWrite(dcf77Signal, HIGH);
  pinMode(dcf77Led, OUTPUT);
  digitalWrite(dcf77Led, LOW);

  // DS1307-Pins konfigurieren
  pinMode(rtcSQWSignal, INPUT);
  digitalWrite(rtcSQWSignal, HIGH);
  pinMode(rtcSQWLed, OUTPUT);
  digitalWrite(rtcSQWLed, LOW);
  
  // Alarm?
#ifdef ENABLE_ALARM
  pinMode(SPEAKER, OUTPUT);
#endif

  // DCF77-LED drei Mal als 'Hello' blinken lassen
  // und Speaker piepsen kassen, falls ENABLE_ALARM eingeschaltetr ist.
  for(byte i=0; i<3; i++) {
    digitalWrite(dcf77Led, HIGH);
#ifdef ENABLE_ALARM
    #ifdef SPEAKER_IS_BUZZER
      digitalWrite(SPEAKER, HIGH);
    #else
      tone(SPEAKER, SPEAKER_FREQUENCY);
    #endif
#endif 
    delay(100);
    digitalWrite(dcf77Led, LOW);
#ifdef ENABLE_ALARM
    #ifdef SPEAKER_IS_BUZZER
      digitalWrite(SPEAKER, LOW);
    #else
      noTone(SPEAKER);
    #endif
#endif
    delay(100);    
  }

  // Matrix loeschen
  clearScreenBuffer();

  // 1 Hz-SQW-Signal einschalten
  ds1307.readTime();  // Knauer: ToDo: Wiederholstrategie einbauen, so dass bei erster fehlerhafter ds1307 Initialisierung immer wieder versucht wird, ds1307 zu initialisieren und das 1 Hz Signal einzuschalten
  ds1307.writeTime();

#ifdef DEBUG
  Serial.print(F("Time: "));
  Serial.print(ds1307.getHours());
  Serial.print(":");
  Serial.print(ds1307.getMinutes());
  Serial.print(":");
  Serial.println(ds1307.getSeconds());
  Serial.flush();
#endif

  // Den Interrupt konfigurieren,
  // nicht mehr CHANGE, das sind 2 pro Sekunde,
  // RISING ist einer pro Sekunde, das reicht.
  // Auf FALLING geandert, das signalisiert
  // den Sekundenwechsel, Danke an Peter.
  attachInterrupt(0, updateFromRtc, FALLING);

  // Werte vom LDR einlesen, da die ersten nichts taugen...
#ifdef ENABLE_LDR
  for(int i=0; i<1000; i++) {
    ldr.value();
  }  
#endif

#ifdef ENABLE_ALARM
  // Alarm-Sachen
  isBeeping = false;
  showAlarmTimeTimer = 0;
  toneIsOn = false;
#endif

  // Init LED Driver WS2803
  WS2803_CKO_Set_PinMode();   // sets the pin as output
  WS2803_SDO_Set_PinMode();   // sets the pin as output
  WS2803_CKO_Write_Low();
  WS2803_SDO_Write_Low();
  delayMicroseconds(650); // CKI fuer laenger als 600 us LOW --> Reset

  // rtcSQWLed-LED drei Mal als 'Hello' blinken lassen
  // und Speaker piepsen kassen, falls ENABLE_ALARM eingeschaltetr ist.
  for(byte i=0; i<3; i++) {
    digitalWrite(rtcSQWLed, HIGH);
#ifdef ENABLE_ALARM
    #ifdef SPEAKER_IS_BUZZER
      digitalWrite(SPEAKER, HIGH);
    #else
      tone(SPEAKER, SPEAKER_FREQUENCY);
    #endif
#endif 
    delay(100);
    digitalWrite(rtcSQWLed, LOW);
#ifdef ENABLE_ALARM
    #ifdef SPEAKER_IS_BUZZER
      digitalWrite(SPEAKER, LOW);
    #else
      noTone(SPEAKER);
    #endif
#endif
    delay(100);    
  }

  /* Konfigurations Modul initialisieren */
  Config.Init();

	/* Timermodul initialisieren, falls die RTC nicht funktioniert */
	setSyncProvider(0);  // set function to call when sync required. Here: no function
	setTime(ds1307.getHours(), ds1307.getMinutes(), ds1307.getSeconds(), ds1307.getDate(), ds1307.getMonth(), ds1307.getYear() /* liefert z.B. 13 fuer 2013*/); /* hours, minutes, seconds, days, months, years (z.B. als 13 fuer 2013) */


  Serial.println(F("... done and ready to rock!"));
  Serial.flush();
}

/**
 * loop() wird endlos auf alle Ewigkeit vom Microcontroller durchlaufen
 */
void loop() {
	time_t TimeNowTemp_1970;
	tmElements_t TimeNowTemp_tmElements; // elements of date and time
	tmElements_t TimeTemp_tmElements;
	unsigned int minutes1;

	TimeNowTemp_1970 = now();                            // Zeit fuer diesen loop-Durchlauf sichern
	breakTime(TimeNowTemp_1970, TimeNowTemp_tmElements); // Zeit fuer diesen loop-Durchlauf sichern

  //
  // Dimmung.
  //
#if defined(ENABLE_LDR)
  if (GetConfig(cfg_ldr_auto_bt)) {
    brightness = ldr.brightness();
  }
  else {
    brightness = GetConfig(cfg_brightness_u8);
  }
#else
    brightness = GetConfig(cfg_brightness_u8);
#endif


	// Zu jeder 55. Sekunde RTC auslesen.
	if ((ds1307Available) && ((TimeNowTemp_tmElements.Second+4) % 59) == 0) {
		if (FetchDs1307Time) {
			FetchDs1307Time = false;

			ds1307.readTime();
			setTime(ds1307.getHours(), ds1307.getMinutes(), ds1307.getSeconds(), ds1307.getDate(), ds1307.getMonth(), ds1307.getYear() /* liefert z.B. 13 fuer 2013*/); /* hours, minutes, seconds, days, months, years (z.B. als 13 fuer 2013) */
		}
	}
	else {
		FetchDs1307Time = true;
	}
	
	// Alle 2 Sekunden ggf. ein Retry fuer ds1307 durchfuehren
	if ((TimeNowTemp_tmElements.Second % 2) == 0) {
		if (RetryDs1307) {
			RetryDs1307 = false;
		
			if ((millis() - ds1307LastIrqTime_millis) > 1500) {
				ds1307Available = false;
			}
		
			if (!ds1307Available) {
#ifdef willi // ToDo: Checken: Bei neuem Retry Systemzeit in ds1307 schreiben?
  				ds1307.setSeconds(TimeNowTemp_tmElements.Second);
				ds1307.setMinutes(TimeNowTemp_tmElements.Minute);
				ds1307.setHours(TimeNowTemp_tmElements.Hour);
				ds1307.setDayOfWeek(TimeNowTemp_tmElements.Wday); // Knauer ToDo: Konvertieren?
				ds1307.setDate(TimeNowTemp_tmElements.Day);
				ds1307.setMonth(TimeNowTemp_tmElements.Month);
				ds1307.setYear(tmYearToY2k(TimeNowTemp_tmElements.Year)); // Convert from offset to 1970 to offset to year 2000, example: 43 to 13  (1970+43 = 2013 to 13)
#endif

				ds1307.readTime();
				ds1307.writeTime();
			}
		}
	}
	else {
		RetryDs1307 = true;
	}


  /*
   *
   * Tasten abfragen
   *
   */
  // Taste Minuten++ (brighness++) gedrueckt?
  if (minutesPlusButton.pressed()) {
#ifdef DEBUG
    Serial.println(F("\nMinutes plus pressed..."));
    Serial.flush();    
#endif      
    switch(mode) {
      case NORMAL:
		if (TimeNowTemp_tmElements.Minute < 59)
			TimeNowTemp_tmElements.Minute++;
		else
			TimeNowTemp_tmElements.Minute = 0;
		TimeNowTemp_tmElements.Second = 0;

		ds1307.setSeconds(TimeNowTemp_tmElements.Second);
		ds1307.setMinutes(TimeNowTemp_tmElements.Minute);
		ds1307.setHours(TimeNowTemp_tmElements.Hour);
		ds1307.setDayOfWeek(TimeNowTemp_tmElements.Wday); // Knauer ToDo: Konvertieren?
		ds1307.setDate(TimeNowTemp_tmElements.Day);
		ds1307.setMonth(TimeNowTemp_tmElements.Month);
		ds1307.setYear(tmYearToY2k(TimeNowTemp_tmElements.Year)); // Convert from offset to 1970 to offset to year 2000, example: 43 to 13  (1970+43 = 2013 to 13)

        ds1307.writeTime();
        ds1307.readTime();
        
        // interne Uhr auf ds1307 Uhr setzen
        setTime(ds1307.getHours(), ds1307.getMinutes(), ds1307.getSeconds(), ds1307.getDate(), ds1307.getMonth(), ds1307.getYear() /* liefert z.B. 13 fuer 2013*/); /* hours, minutes, seconds, days, months, years (z.B. als 13 fuer 2013) */
#ifdef DEBUG
        Serial.print(F("M is now "));
        Serial.println(ds1307.getMinutes());
        Serial.flush();
#endif      
        break;
#ifdef ENABLE_ALARM
      case ALARM:
        alarmTime_tmElements.incMinutes();
        showAlarmTimeTimer = 10;
		
		fastDisplayRefresh_bt = true; /* sofortige Ausgabe veranlassen */
#ifdef DEBUG
        Serial.print(F("A is now "));
        Serial.println(alarmTime_tmElements.asString());
        Serial.flush();
#endif      
      break;
#endif      
      case BRIGHTNESS:
        if(brightness < MAX_BRIGHTNESS) {
          brightness++;
          SetConfig(cfg_brightness_u8, brightness);
		  
		  fastDisplayRefresh_bt = true; /* sofortige Ausgabe veranlassen */
        }
      break;
#if defined(ENABLE_LDR)
      case LDR_MODE:
        SetConfig(cfg_ldr_auto_bt, !GetConfig(cfg_ldr_auto_bt));
		
		fastDisplayRefresh_bt = true; /* sofortige Ausgabe veranlassen */
#ifdef DEBUG
        Serial.print(F("LDR is now "));
        Serial.println(GetConfig(cfg_ldr_auto_bt));
        Serial.flush();
#endif      
        break;
#endif
    }
  }
  
  // Taste Stunden++ (brightness--) gedrueckt?
  if (hoursPlusButton.pressed()) {
#ifdef DEBUG
    Serial.println(F("\nHours plus pressed..."));
    Serial.flush();
#endif      
    switch(mode) {
      case NORMAL:
		if (TimeNowTemp_tmElements.Hour < 23)
			TimeNowTemp_tmElements.Hour++;
		else
			TimeNowTemp_tmElements.Hour = 0;
		TimeNowTemp_tmElements.Second = 0;

		ds1307.setSeconds(TimeNowTemp_tmElements.Second);
		ds1307.setMinutes(TimeNowTemp_tmElements.Minute);
		ds1307.setHours(TimeNowTemp_tmElements.Hour);
		ds1307.setDayOfWeek(TimeNowTemp_tmElements.Wday); // Knauer ToDo: Konvertieren?
		ds1307.setDate(TimeNowTemp_tmElements.Day);
		ds1307.setMonth(TimeNowTemp_tmElements.Month);
		ds1307.setYear(tmYearToY2k(TimeNowTemp_tmElements.Year)); // Convert from offset to 1970 to offset to year 2000, example: 43 to 13  (1970+43 = 2013 to 13)

        ds1307.writeTime();
        ds1307.readTime();

        // interne Uhr auf ds1307 Uhr setzen
        setTime(ds1307.getHours(), ds1307.getMinutes(), ds1307.getSeconds(), ds1307.getDate(), ds1307.getMonth(), ds1307.getYear() /* liefert z.B. 13 fuer 2013*/); /* hours, minutes, seconds, days, months, years (z.B. als 13 fuer 2013) */
#ifdef DEBUG
        Serial.print(F("H is now "));
        Serial.println(ds1307.getHours());
        Serial.flush();
#endif      
      break;
#ifdef ENABLE_ALARM
      case ALARM:
        alarmTime_tmElements.incHours();
        showAlarmTimeTimer = 10;
		
		fastDisplayRefresh_bt = true; /* sofortige Ausgabe veranlassen */
#ifdef DEBUG
        Serial.print(F("A is now "));
        Serial.println(alarmTime_tmElements.asString());
        Serial.flush();
#endif      
      break;
#endif      
      case BRIGHTNESS:
        if(brightness > 2) {
          brightness--;
          SetConfig(cfg_brightness_u8, brightness);
		  
		  fastDisplayRefresh_bt = true; /* sofortige Ausgabe veranlassen */
        }
        break;
#if defined(ENABLE_LDR)
      case LDR_MODE:
        SetConfig(cfg_ldr_auto_bt, !GetConfig(cfg_ldr_auto_bt));
		
		fastDisplayRefresh_bt = true; /* sofortige Ausgabe veranlassen */
#ifdef DEBUG
        Serial.print(F("LDR is now "));
        Serial.println(GetConfig(cfg_ldr_auto_bt));
        Serial.flush();
#endif      
        break;
#endif
    }
  }
  
  // Taste Moduswechsel gedrueckt?
  if (modeChangeButton.pressed()) {
    mode++;

#if !defined(ENABLE_LDR)
    /* Wenn es per Compilerschalter keinen LDR gibt, darf der Mode zum Wechsel zwischen LDR Auto mode und deaktiviertem LDR nicht angezeigt werden. */	
	if (mode == LDR_MODE) {
	  mode++;
	}
#endif
	if (mode == BRIGHTNESS) {
	  /* Im LDR Auto mode kann man die Display Helligkeit nicht einstellen, da die Helligkeit vom LDR geregelt wird. Also im LDR Auto mode die Einstellung zur Helligkeit ueberspringen. */
	  if (GetConfig(cfg_ldr_auto_bt)) {
	    mode++;
	  }
	}
	
    if(mode == MAX) {
      mode = 0;
    }

#ifdef ENABLE_ALARM
    if(mode == ALARM) {
      showAlarmTimeTimer = 10;
    } else {
      isBeeping = false;
      if(toneIsOn) {
#ifdef SPEAKER_IS_BUZZER
        digitalWrite(SPEAKER, LOW);
#else
        noTone(SPEAKER);
#endif      
        toneIsOn = false;
      }
    }
#endif

#ifdef DEBUG
    Serial.print(F("\nChange mode pressed, mode is now "));
    Serial.print(mode);
    Serial.println(F("..."));
    Serial.flush();
#endif      
    
    // Merker, damit wir nach einer automatischen Abschaltung
    // zum richtigen Mode zurueckkommen.
    lastMode = mode;
  }

  /*
   *
   * Display zeitgesteuert abschalten?
   *
   */
  if((makeTime(offTime_tmElements) != 0) && (makeTime(onTime_tmElements) != 0)) {
	minutes1 = TimeNowTemp_tmElements.Minute + 60 * TimeNowTemp_tmElements.Hour;

    if((mode != BLANK) && ((offTime_tmElements.Minute + 60 * offTime_tmElements.Hour) == minutes1)) { // nur auf Minuten seit Mitternacht ueberpruefen
      mode = BLANK;
    }
    if((mode == BLANK) && ((onTime_tmElements.Minute + 60 * onTime_tmElements.Hour) == minutes1)) { // nur auf Minuten seit Mitternacht ueberpruefen
      mode = lastMode;
    }
  }

#ifdef ENABLE_ALARM  
  /*
   *
   * Alarm?
   *
   */
  if((mode == ALARM) && (showAlarmTimeTimer == 0) && !isBeeping) {
    if(alarmTime_tmElements.getMinutesOf12HoursDay() == ds1307.getMinutesOf12HoursDay()) { // Knauer ToDo: ds1307 entfernen, sondern stattdessen auf die interne Uhr schauen. Ausserdem auf 24 Stunden Format umstellen!
      isBeeping = true;
    }
  }
  if(isBeeping) {
    if(TimeNowTemp_tmElements.Second % 2 == 0) {
#ifdef SPEAKER_IS_BUZZER
      digitalWrite(SPEAKER, HIGH);
#else
      tone(SPEAKER, SPEAKER_FREQUENCY);
#endif
      toneIsOn = true;
    } else {
#ifdef SPEAKER_IS_BUZZER
      digitalWrite(SPEAKER, LOW);
#else
      noTone(SPEAKER);
#endif      
      toneIsOn = false;
    }
  }
#endif

  /*
   *
   * Die Matrix auf die LEDs ausgeben
   *
   */
	/* Da eine Bildausgabe den DCF Empfang stoert:
	   Jede Sekunde das Bild neu ausgeben. Nach 61 s die Ausgabe zusaetzlich um 100 ms nach hinten verschieben.
	   Durch den 100 ms Offest ist sichergestellt, dass die Uebertragung zur Bildausgabe im unguenstigsten Fall nicht
	   immer den DCF Empfang stoert. DCF Signale kommen jede Sekunde und dauern jeweils maximal 200 ms. Eine
	   komplette Bildausgabe per serieller Schnittstelle dauert ca. 25 ms.
	*/
	static unsigned long time_next_output_millis;
	static int time_seconds; /* Zaehlt die Sekunden, um alle 61 Sekunden den Ausgabe-Offest um 100 ms zu verschieben. Laeuft asysnchron zu den realen Sekunden. */
	static boolean running_up = true;
	static time_t TimeLastOutput_1970 = 0;
	
	unsigned long time_now_millis;

	time_now_millis = millis();

	/* Wenn ein sofortiger Refresh angefordert wird oder die naechste Ausgabe um mehr als 1500 ms von
	   der aktuellen Uhrzeit abweicht, dann Variablen so initialisieren, dass das Bild sofort ausgegeben
	   wird. Eine Abweichung um mehr als 1500 ms tritt z.B. auf, wenn die Zeit millis() einen Ueberlauf
	   hatte.
	*/

	if (
		(fastDisplayRefresh_bt) ||
		( (TimeLastOutput_1970 <  TimeNowTemp_1970) && ((TimeNowTemp_1970 - TimeLastOutput_1970) >= 3) ) ||
		( (TimeLastOutput_1970 >= TimeNowTemp_1970) && ((TimeLastOutput_1970 - TimeNowTemp_1970) >= 1) )
	) {
		// (Re-)Init
		fastDisplayRefresh_bt = false;
		time_seconds = 0;
		time_next_output_millis = time_now_millis;

		TimeLastOutput_1970 = TimeNowTemp_1970 - 1;
		running_up = true;
	}



	if ((TimeNowTemp_1970 - TimeLastOutput_1970) >= 2) {
		/* Abstand ist groesser als 1 Sekunde, deshalb nun runterzaehlen */;
		running_up = false;
	}
	if ((TimeNowTemp_1970 - TimeLastOutput_1970) <= 0) {
		/* Abstand ist kleiner als 1 Sekunde, deshalb nun hochzaehlen */;
		running_up = true;
	}


	/* Nach Ablauf der Zielzeit das Bild neu ausgeben und die naechste Zielzeit berechnen. */
	if (time_now_millis >= time_next_output_millis) {
		TimeLastOutput_1970++;
		breakTime(TimeLastOutput_1970, TimeTemp_tmElements);  // break time_t into elements

		// ScreenBuffer berechnen
		CalculateSceenBuffer(TimeTemp_tmElements);
		
		// ScreenBuffer ausgeben
		writeScreenBufferToMatrix();

		time_next_output_millis += 1000; /* naechste Ausgabe nach 1 s */
		time_seconds++;
		
		// alle 61 s Offest um 100 ms veraendern
		if (time_seconds > 60) {
			time_seconds = 0;
			if (running_up)
				time_next_output_millis += 100; /* 1 Minute ist rum, deshalb um 100 ms verschieben. */
			else
				time_next_output_millis -= 100; /* 1 Minute ist rum, deshalb um 100 ms verschieben. */
		}
	}

  /*
   *
   * Status-LEDs ausgeben
   *
   */
#ifdef ENABLE_DCF_LED
  digitalWrite(dcf77Led, dcf77.signal());
#endif
#ifdef ENABLE_SQW_LED
  digitalWrite(rtcSQWLed, digitalRead(rtcSQWSignal));
#endif

  /*
   *
   * DCF77-Empfaenger abfragen
   *
   */
  if(dcf77.poll()) {
#ifdef DEBUG
    Serial.print(F("Captured: "));
    Serial.println(dcf77.asString());
    Serial.flush();
#endif
  
	TimeTemp_tmElements.Second = 0;
	TimeTemp_tmElements.Minute = dcf77.getMinutes();
	TimeTemp_tmElements.Hour = dcf77.getHours();
	TimeTemp_tmElements.Day = dcf77.getDate();
	TimeTemp_tmElements.Month = dcf77.getMonth();
	TimeTemp_tmElements.Year = y2kYearToTm(dcf77.getYear()); // convert offset from 2000 to offset from 1970
	
    dcf77Helper.addSample(makeTime(TimeTemp_tmElements), now());
    // stimmen die Abstaende im Array?
    if(dcf77Helper.samplesOk()) {
      ds1307.setSeconds(0);
      ds1307.setMinutes(dcf77.getMinutes());
      ds1307.setHours(dcf77.getHours());
      // wir setzen auch das Datum, dann kann man, wenn man moechte,
      // auf das Datum eingehen (spezielle Nachrichten an speziellen
      // Tagen). Allerdings ist das Datum bisher ungeprueft!
      ds1307.setDate(dcf77.getDate());
      ds1307.setDayOfWeek(dcf77.getDayOfWeek());
      ds1307.setMonth(dcf77.getMonth());
      ds1307.setYear(dcf77.getYear()); // ds1307 und dcf77 nutzen z.B. 13 fuer 2013

	  setTime(ds1307.getHours(), ds1307.getMinutes(), ds1307.getSeconds(), ds1307.getDate(), ds1307.getMonth(), ds1307.getYear() /* liefert z.B. 13 fuer 2013*/); /* hours, minutes, seconds, days, months, years (z.B. als 13 fuer 2013) */

      ds1307.writeTime();
#ifdef DEBUG
      Serial.println(F("DCF77-Time written to DS1307."));
      Serial.flush();
#endif    
    }
    else {
#ifdef DEBUG
      Serial.println(F("DCF77-Time trashed because wrong distances between timestamps."));
      Serial.flush();
#endif    
    }
  }
  
  Config.CyclicCall();
}

/**
 * Aenderung der Anzeige als Funktion fuer den Interrupt, der ueber das SQW-Signal 
 * der Real-Time-Clock gesetzt wird. Da die Wire-Bibliothek benutzt wird, kann man
 * den Interrupt nicht direkt benutzen, sondern muss eine Hilfsvariable setzen, die
 * dann in loop() ausgewertet wird.
 */
void updateFromRtc() {
  ds1307Available = true;
  ds1307LastIrqTime_millis = millis();
}

/**
 * Ein Zufallsmuster erzeugen (zum Testen der LEDs)
 */
void scrambleScreenBuffer() {
  for (byte i = 0; i < CNT_LINES; i++) {
    matrix[i] = random(65536);
  }

  matrix_corners = random(256);
}

/**
 * Die Matrix loeschen (zum Strom sparen, DCF77-Empfang
 * verbessern etc.)
 */
void clearScreenBuffer() {
  memset(matrix, 0x00, sizeof(matrix));
  matrix_corners = 0x00;
}

/**
 * Die Matrix komplett einschalten (zum Testen der LEDs)
 */
void setAllScreenBuffer() {
  memset(matrix, 0xFF, sizeof(matrix));
  matrix_corners = 0xFF;
}


void CalculateSceenBuffer(tmElements_t TimeOutput_tmElements) {
    //
    // Bildschirmpuffer beschreiben...
    //
    clearScreenBuffer();
    switch (mode) {
      case NORMAL:
        setMinutes(TimeOutput_tmElements.Hour, TimeOutput_tmElements.Minute); // Schreibe in den Bildschirmbuffer die Uhrzeit
        setCorners(TimeOutput_tmElements.Minute);                   // Schreibe in den Bildschirmbuffer die Minuten
        break;
#ifdef ENABLE_ALARM
      case ALARM:
        if(showAlarmTimeTimer == 0) {
			setMinutes(TimeOutput_tmElements.Hour, TimeOutput_tmElements.Minute); // Schreibe in den Bildschirmbuffer die Uhrzeit
			setCorners(TimeOutput_tmElements.Minute);                   // Schreibe in den Bildschirmbuffer die Minuten
			matrix_corners = 0b00001111; // Alarm-LED
        } else {        
          setMinutes(alarmTime_tmElements.getHours(), alarmTime_tmElements.getMinutes());
          setCorners(alarmTime_tmElements.getMinutes());
          cleanWordsForAlarmSettingMode(); // ES IST weg
          if(showAlarmTimeTimer % 2 == 0) {
            matrix_corners = 0b00001111; // Alarm-LED
          }
          showAlarmTimeTimer--;
        }
      break;
#endif      
      case SECONDS:
        for (byte i = 0; i < 7; i++) {
          matrix[1 + i] |= pgm_read_byte_near(&(ziffern[TimeOutput_tmElements.Second / 10][i])) << 11; // ToDo: 11 nicht hart verwenden
          matrix[1 + i] |= pgm_read_byte_near(&(ziffern[TimeOutput_tmElements.Second % 10][i])) << 5;   // ToDo: 5 nicht hart verwenden
        }
        break;
#if defined(ENABLE_LDR)
      case LDR_MODE:
        if (GetConfig(cfg_ldr_auto_bt)) {
          for (byte i = 0; i < 6; i++) { // ToDo: Zahl 6 nicht hart verwenden, da potenzieller Fehler
            matrix[2 + i] |= pgm_read_byte_near(&(staben['A'-'A'][i])) << 8;
          }
        } else {
          for (byte i = 0; i < 6; i++) { // ToDo: Zahl 6 nicht hart verwenden, da potenzieller Fehler
            matrix[2 + i] |= pgm_read_byte_near(&(staben['M'-'A'][i])) << 8;
          }
        }
        break;
#endif
      case SCRAMBLE:
        scrambleScreenBuffer();
        break;
      case BLANK:
        break;
      case BRIGHTNESS:
        brightnessToDisplay = map(brightness, 1, MAX_BRIGHTNESS, 1, 9); // knauer: alt: ... map(brightness, 1, MAX_BRIGHTNESS, 0, 9)
        for(byte x=0; x<brightnessToDisplay; x++) {
          for(byte y=0; y<=x; y++) {
            matrix[9-y] |= 1 << (14-x);
          }
        }
      break;
      case ALL:
        setAllScreenBuffer();
        break;
    }
}


/**
 * Die Matrix ausgeben
 */
void writeScreenBufferToMatrix() {
	unsigned char WS2803_buf[((((CNT_LINES*CNT_COLS + 4) - 1) / 18) + 1) * 18]; /* z.B.: 7 LED Treiber, pro Treiber 18 PWM Werte:  7*18 = 126 */

	unsigned char buffer_pos;
	unsigned char matrix_pos;
	unsigned char zeile;
	unsigned char spalte;
	unsigned char PwmVal;
	unsigned char output_data;

	float CurrentSum;
	float CurrentSum_TEMP;
	float CurrentPwmFactor;
	
	int AnalogLdrVal;
	#define PWM_LDR_STEIGUNGS_FAKTOR  ((LED_PWM_MAX - LDR_MIN_PWM) / (1023.0 - LDR_BRIGHTNESS_VAL_MIN))


	CurrentSum = 0;


	/* WS2803_buf[0..125] fuellen: Gewuenschte PWM Werte fuer alle Treiber Ausgaenge ermitteln. Falls maximaler Strom ueberschritten wird, wird per PWM heruntergeregelt. */
	for (buffer_pos = 0; buffer_pos < sizeof(WS2803_buf); buffer_pos++) { /* 7 Treiber * 18 Ausgaenge = 126 Byte */
		matrix_pos = pgm_read_byte_near(&SEND_ORDER_TABLE[buffer_pos]);
		
		/* Buchstaben ausgeben */
		if (matrix_pos < (CNT_LINES*CNT_COLS)) {
			zeile  = (matrix_pos / CNT_COLS);
			spalte = (matrix_pos % CNT_COLS);
		
			PwmVal = (((matrix[zeile] >> (15 - spalte)) & 0x0001) > 0) * LED_PWM_MAX; /* linkeste Spalte wird ganz nach rechts geshiftet usw. */
		}
		else {
			/* Corner LED ausgeben */
			if (matrix_pos <= LED_CORNER_L_BOTTOM) {
				PwmVal = (((matrix_corners >> (matrix_pos - LED_CORNER_L_TOP)) & 0b00000001) > 0) * LED_PWM_MAX;
			}
			else {
				/* Ausgang ist nicht belegt oder ungueltig: PWM Wert 0 senden */
				PwmVal = 0x00;
			}
		}
		
		/* Berechneten PWM Wert in den Buffer schreiben */
		WS2803_buf[buffer_pos] = PwmVal;
		
		/* Strom fuer diese LED hinzuaddieren */
		CurrentSum += ( ((float)PwmVal) * (LED_CURRENT / 255.0) );
		/* 255.0 gibt den maximal einstellbaren Wert an. 255.0 entspricht 100% an.
		LED_PWM_MAX hingegen begrenzt den maximal gewuenschten Einstellwert. LED_PWM_MAX muss <= 255.0 sein.
		*/
	}

	/* LDR Wert verarbeiten */
#if defined(ENABLE_LDR)
	AnalogLdrVal = ldr.value(); /* ldr.value() zwischenspeichern, da bei jedem Aufruf unterschiedliche Werte zurueckkommen koennen. */
#else
	/* ToDo: Momentan wird bei nicht gesetztem ENABLE_LDR immer die maximale Helligkeit eingestellt. Umstellen, so dass die eingestellte Helligkeit uebernommen wird! */
	AnalogLdrVal = 0;
#endif
	if (AnalogLdrVal > LDR_BRIGHTNESS_VAL_MIN) {
		/* Bei Dunkelheit per PWM runterdimmen. */
		CurrentPwmFactor = (LED_PWM_MAX - ((AnalogLdrVal - LDR_BRIGHTNESS_VAL_MIN) * PWM_LDR_STEIGUNGS_FAKTOR)) / LED_PWM_MAX;
	}
	else {
		/* Es ist nicht dunkel genug, damit per PWM runtergedimmt werden muss. */
		CurrentPwmFactor = 1.0;
	}

	/* Faktor berechnen, um ggf. den Strom per PWM zu begrenzen. */
	CurrentSum_TEMP = CurrentSum*CurrentPwmFactor;
	if (CurrentSum_TEMP > MAX_CURRENT) {
		CurrentPwmFactor = MAX_CURRENT / CurrentSum_TEMP;
	}

    for (buffer_pos = 0; buffer_pos < sizeof(WS2803_buf); buffer_pos++) {
        /* 1 Byte senden, d.h. 1 PWM Wert senden */
		output_data = WS2803_buf[buffer_pos] * CurrentPwmFactor;
        for (unsigned char bit = 0x80; bit; bit >>= 1) {
          if (output_data & bit)
            WS2803_SDO_Write_High();
          else
            WS2803_SDO_Write_Low();

#if WS2803_DELAY != 0
          delayMicroseconds(WS2803_DELAY);
#endif
          WS2803_CKO_Write_High(); // Clock high
#if WS2803_DELAY != 0
          delayMicroseconds(WS2803_DELAY);
#endif
          WS2803_CKO_Write_Low();  // Clock low
        }
    }


    // Neues Bild ausgeben
#if WS2803_DELAY != 0
    delayMicroseconds(WS2803_DELAY);
#endif
    WS2803_CKO_Write_Low(); // Clock low
#if WS2803_DELAY != 0
    delayMicroseconds(WS2803_DELAY);
#endif
    WS2803_SDO_Write_Low();
    delayMicroseconds(WS2803_RESET_TIME); // CKI fuer laenger als 600 us LOW --> Reset, Daten uebernehmen
}
