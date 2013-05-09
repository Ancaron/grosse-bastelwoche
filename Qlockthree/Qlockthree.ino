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

#if defined(ENABLE_EEPROM)
#include <EEPROM.h>
#endif

/**
 * Konfiguration, die z.B. auch im Eeprom gespeichert wird.
 */
CConfig Config;

// Knauer: ToDo: ins ROM verschieben
const unsigned char SEND_ORDER_TABLE[] = {
  #include "send_order.h"
};
// Knauer, ToDo: if (mode == BLANK)  ---> Anzeige einmal loeschen (geschieht evtl. schon?), dann keine Ausgabe mehr an WS2803 Chips !!!  (oder evtl. nur noch x Mal, falls etwas bei der Uebertragung schief geht).


/*
  Allgemeine Wortuhr defines
*/
#define CNT_LINES 10
#define CNT_COLS  11
#define LED_PWM_MAX 0xFF
#define LED_CURRENT 0.020 /* max. 20 mA pro LED (d.h. bei voller Ansteuerung) */
#define MAX_CURRENT 1.5 /* Maximaler Strom fuer alle LEDs zusammen. Bei Stroemen darueber wird per PWM abgeregelt. */

/**
 * Die Real-Time-Clock
 */
DS1307 ds1307(0x68);
byte helperSeconds;

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
//#define WS2803_KNAUER_BELEGUNG
#define WS2803_ALLGEMEINE_BELEGUNG

#if defined(WS2803_KNAUER_BELEGUNG)
  #define WS2803_CKO  A0 /* Clock output an A0 */
  #define WS2803_SDO  A1 /* Serial data output an A1 */

  #define WS2803_CKO_Set_PinMode() /* bei analogem Output nicht einstellbar */
  #define WS2803_SDO_Set_PinMode() /* bei analogem Output nicht einstellbar */

  #define WS2803_CKO_Write_Low()   analogWrite(WS2803_CKO, 0x00)
  #define WS2803_CKO_Write_High()  analogWrite(WS2803_CKO, 0xFF)

  #define WS2803_SDO_Write_Low()   analogWrite(WS2803_SDO, 0x00)
  #define WS2803_SDO_Write_High()  analogWrite(WS2803_SDO, 0xFF)

#elif defined(WS2803_ALLGEMEINE_BELEGUNG)
  #define WS2803_CKO  10 /* Clock output an D10 */
  #define WS2803_SDO  11 /* Serial data output an D11 */

  #define WS2803_CKO_Set_PinMode()  pinMode(WS2803_CKO, OUTPUT)
  #define WS2803_SDO_Set_PinMode()  pinMode(WS2803_SDO, OUTPUT)

  #define WS2803_CKO_Write_Low()   digitalWrite(WS2803_CKO, LOW)
  #define WS2803_CKO_Write_High()  digitalWrite(WS2803_CKO, HIGH)

  #define WS2803_SDO_Write_Low()   digitalWrite(WS2803_SDO, LOW)
  #define WS2803_SDO_Write_High()  digitalWrite(WS2803_SDO, HIGH)
#endif


/**
 * Variablen fuer den Alarm.
 */
#ifdef ENABLE_ALARM
TimeStamp alarmTime(0, 7, 0, 0, 0, 0);
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
TimeStamp offTime(0, 0, 0, 0, 0, 0);
TimeStamp onTime(0, 0, 0, 0, 0, 0);
#else
// um 3 Uhr Display abschalten (Minuten, Stunden, -, -, -, -)
TimeStamp offTime(0, 3, 0, 0, 0, 0);
// um 4:30 Uhr Display wieder anschalten (Minuten, Stunden, -, -, -, -)
TimeStamp onTime(30, 4, 0, 0, 0, 0);
#endif

// Merker fuer den Modus vor der Abschaltung...
byte lastMode = mode;

// Ueber die Wire-Library festgelegt:
// Arduino analog input 4 = I2C SDA
// Arduino analog input 5 = I2C SCL

// Die Matrix, eine Art Bildschirmspeicher
word matrix[CNT_LINES];

// Hilfsvariable, da I2C und Interrupts nicht zusammenspielen
volatile boolean needsUpdateFromRtc = true;

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
#ifdef DEBUG
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
  ds1307.readTime();  
  ds1307.writeTime();
  helperSeconds = ds1307.getSeconds();
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
  
  /* Konfigurations Modul initialiseren */
  Config.Init();

  Serial.println(F("... done and ready to rock!"));
  Serial.flush();
}

/**
 * loop() wird endlos auf alle Ewigkeit vom Microcontroller durchlaufen
 */
void loop() {
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

  //
  // needsUpdateFromRtc wird via Interrupt gesetzt ueber fallende 
  // Flanke des SQW-Signals von der RTC
  //
  if (needsUpdateFromRtc) {
    needsUpdateFromRtc = false;
    // die Zeit verursacht ein kurzes Flackern. Wir muessen
    // sie aber nicht immer lesen, im Modus 'normal' alle 60 Sekunden,
    // im Modus 'seconds' alle Sekunde, sonst garnicht.
    helperSeconds++;
    if(helperSeconds == 60) {
      helperSeconds = 0;
    }
    
    //
    // Zeit einlesen...
    //
    switch(mode) {
      case NORMAL:
#ifdef ENABLE_ALARM
      case ALARM:
        if(isBeeping) {
          ds1307.readTime();
        }
#endif      
        if(helperSeconds == 0) {
          ds1307.readTime();
          helperSeconds = ds1307.getSeconds();
        }
        break;
      case SECONDS:
      case BLANK:
        ds1307.readTime();
        helperSeconds = ds1307.getSeconds();
        break;
      // andere Modi egal...
    }

    //
    // Bildschirmpuffer beschreiben...
    //
    switch (mode) {
      case NORMAL:
        clearScreenBuffer();
        setMinutes(ds1307.getHours(), ds1307.getMinutes());
        setCorners(ds1307.getMinutes());
        break;
#ifdef ENABLE_ALARM
      case ALARM:
        clearScreenBuffer();
        if(showAlarmTimeTimer == 0) {
          setMinutes(ds1307.getHours(), ds1307.getMinutes());
          setCorners(ds1307.getMinutes());
          matrix[4] |= 0b0000000000011111; // Alarm-LED
        } else {        
          setMinutes(alarmTime.getHours(), alarmTime.getMinutes());
          setCorners(alarmTime.getMinutes());
          cleanWordsForAlarmSettingMode(); // ES IST weg
          if(showAlarmTimeTimer % 2 == 0) {
            matrix[4] |= 0b0000000000011111; // Alarm-LED
          }
          showAlarmTimeTimer--;
        }
      break;
#endif      
      case SECONDS:
        clearScreenBuffer();
        for (byte i = 0; i < 7; i++) {
          matrix[1 + i] |= pgm_read_byte_near(&(ziffern[ds1307.getSeconds()/10][i])) << 11;
          matrix[1 + i] |= pgm_read_byte_near(&(ziffern[ds1307.getSeconds()%10][i])) << 5;
        }
        break;
#if defined(ENABLE_LDR)
      case LDR_MODE:
        setCorners(0);
        clearScreenBuffer(); // Knauer, ToDo: Was genau macht (1 Zeile vorher) setCorners und was clearScreenBuffer? Passt das so (in dieser Reihenfolge)?
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
        clearScreenBuffer();
		writeScreenBufferToMatrix(); // Knauer, ToDo: Wird dies staendig aufgerufen? Dann begrenzen !!!
        break;
      case BRIGHTNESS:
        clearScreenBuffer();
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
    needsUpdateFromRtc = true;
    switch(mode) {
      case NORMAL:
        ds1307.incMinutes();
        ds1307.setSeconds(0);
        ds1307.writeTime();
        ds1307.readTime();
        helperSeconds = 0;  
#ifdef DEBUG
        Serial.print(F("M is now "));
        Serial.println(ds1307.getMinutes());
        Serial.flush();
#endif      
        break;
#ifdef ENABLE_ALARM
      case ALARM:
        alarmTime.incMinutes();
        showAlarmTimeTimer = 10;
#ifdef DEBUG
        Serial.print(F("A is now "));
        Serial.println(alarmTime.asString());
        Serial.flush();
#endif      
      break;
#endif      
      case BRIGHTNESS:
        if(brightness < MAX_BRIGHTNESS) {
          brightness++;
          SetConfig(cfg_brightness_u8, brightness);
        }
      break;
#if defined(ENABLE_LDR)
      case LDR_MODE:
        SetConfig(cfg_ldr_auto_bt, !GetConfig(cfg_ldr_auto_bt));
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
    needsUpdateFromRtc = true;
    switch(mode) {
      case NORMAL:
        ds1307.incHours();
        ds1307.setSeconds(0);
        ds1307.writeTime();
        ds1307.readTime();
        helperSeconds = 0;
#ifdef DEBUG
        Serial.print(F("H is now "));
        Serial.println(ds1307.getHours());
        Serial.flush();
#endif      
      break;
#ifdef ENABLE_ALARM
      case ALARM:
        alarmTime.incHours();
        showAlarmTimeTimer = 10;
#ifdef DEBUG
        Serial.print(F("A is now "));
        Serial.println(alarmTime.asString());
        Serial.flush();
#endif      
      break;
#endif      
      case BRIGHTNESS:
        if(brightness > 2) {
          brightness--;
          SetConfig(cfg_brightness_u8, brightness);
        }
        break;
#if defined(ENABLE_LDR)
      case LDR_MODE:
        SetConfig(cfg_ldr_auto_bt, !GetConfig(cfg_ldr_auto_bt));
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
    needsUpdateFromRtc = true;

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
  if((offTime.getMinutesOfDay() != 0) && (onTime.getMinutesOfDay() != 0)) {
    if((mode != BLANK) && (offTime.getMinutesOfDay() == ds1307.getMinutesOfDay())) {
      mode = BLANK;
    }
    if((mode == BLANK) && (onTime.getMinutesOfDay() == ds1307.getMinutesOfDay())) {
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
    if(alarmTime.getMinutesOf12HoursDay() == ds1307.getMinutesOf12HoursDay()) {
      isBeeping = true;
    }
  }
  if(isBeeping) {
    if(ds1307.getSeconds() % 2 == 0) {
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
   * Die Matrix auf die LEDs multiplexen
   *
   */
  if(mode != BLANK) {
    writeScreenBufferToMatrix();
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
  
    ds1307.readTime();
    dcf77Helper.addSample(dcf77, ds1307);
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
      ds1307.setYear(dcf77.getYear());

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
  needsUpdateFromRtc = true;
}

/**
 * Ein Zufallsmuster erzeugen (zum Testen der LEDs)
 */
void scrambleScreenBuffer() {
  for (byte i = 0; i < CNT_LINES; i++) {
    matrix[i] = random(65536);
  }
}

/**
 * Die Matrix loeschen (zum Strom sparen, DCF77-Empfang
 * verbessern etc.)
 */
void clearScreenBuffer() {
  memset(matrix, 0x00, sizeof(matrix));
}

/**
 * Die Matrix komplett einschalten (zum Testen der LEDs)
 */
void setAllScreenBuffer() {
  memset(matrix, 0xFF, sizeof(matrix));
}

/**
 * Die Matrix ausgeben
 */
void writeScreenBufferToMatrix() {
	unsigned char WS2803_buf[7*18]; /* 7 LED Treiber, pro Treiber 18 PWM Werte:  7*18 = 126 */

	unsigned char buffer_pos;
	unsigned char matrix_pos;
	unsigned char zeile;
	unsigned char spalte;
	unsigned char PwmVal;
	unsigned char output_data;

	float CurrentSum;
	float CurrentPwmFactor;


	CurrentSum = 0;
	

	/* Die ersten 12 Byte erstmal leer machen. */
	for (buffer_pos = 0; buffer_pos < 12; buffer_pos++) { /* 12 Byte */
		WS2803_buf[buffer_pos] = 0x00;
	}

	/* Die 4 Eck-LEDs fuellen */
	for (buffer_pos = 0; buffer_pos < 4; buffer_pos++) { /* 4 Byte */
		PwmVal = (((matrix[0] >> buffer_pos) & 0b0000000000000010) > 0) * LED_PWM_MAX;
		WS2803_buf[12 + buffer_pos] = PwmVal;
		
		CurrentSum += ( ((float)PwmVal) * (LED_CURRENT / 255.0) );
	}

	/* Fuer alle Buchstaben: WS2803_buf[16..125] fuellen und CurrentSum berechnen */
	for (buffer_pos = 0; buffer_pos < CNT_LINES * CNT_COLS; buffer_pos++) { /* 10*11 = 110 Byte */
		matrix_pos = SEND_ORDER_TABLE[buffer_pos];
		zeile = (matrix_pos / CNT_COLS);
		spalte = matrix_pos % 11;
		
		PwmVal = (((matrix[zeile] >> (10 - spalte)) & 0b0000000000100000) > 0) * LED_PWM_MAX;
		WS2803_buf[16 + buffer_pos] = PwmVal;

		CurrentSum += ( ((float)PwmVal) * (LED_CURRENT / 255.0) );
	}

	/* Faktor berechnen, um ggf. den Strom per PWM zu begrenzen. */
	if (CurrentSum > MAX_CURRENT) {
		CurrentPwmFactor = MAX_CURRENT / CurrentSum;
	}
	else {
		CurrentPwmFactor = 1.0;
	}

    for (buffer_pos = 0; buffer_pos < sizeof(WS2803_buf); buffer_pos++) {
        /* 1 Byte senden, d.h. 1 PWM Wert senden */
		output_data = WS2803_buf[buffer_pos] * CurrentPwmFactor;
        for (unsigned char bit = 0x80; bit; bit >>= 1) {
          if (output_data & bit)
            WS2803_SDO_Write_High();
          else
            WS2803_SDO_Write_Low();

          delayMicroseconds(1);
          WS2803_CKO_Write_High(); // Clock high
          delayMicroseconds(1);
          WS2803_CKO_Write_Low();  // Clock low
        }
    }


    // Neues Bild rausgeben
    delayMicroseconds(1);
    WS2803_CKO_Write_Low(); // Clock low
    delayMicroseconds(1);
    WS2803_SDO_Write_Low();
    delayMicroseconds(650); // CKI fuer laenger als 600 us LOW --> Reset, Daten uebernehmen
}
