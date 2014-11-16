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
 */

/*
 * Den DEBUG-Schalter gibt es in allen Bibiliotheken. Wird er eingeschaltet, werden ueber den
 * 'Serial-Monitor' der Arduino-Umgebung Informationen ausgegeben. Die Geschwindigkeit im
 * Serial-Monitor muss mit der hier angegeben uebereinstimmen.
 * Default: ausgeschaltet
 */
   #define DEBUG
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
 * Sollen die Eck-LEDs im oder gegen den Uhrzeigersinn laufen?
 * CW = CLOCK WISE = im Uhrzeigersinn
 * CCW = COUNTER CLOCK WISE = gegen den Uhrzeigersinn
 */
   #define SET_CORNERS_CW
// #define SET_CORNERS_CCW

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
   #define ENABLE_LDR

/*
 * Dieser Schalter erhoeht die Helligkeit, indem er nicht beleuchtete Zeilen ueberspringt. (Tipp
 * von Johannes)
 * Default: ausgeschaltet
 */
// #define SKIP_BLANK_LINES

/*
 * Dieser Schalter stellt die Anzeige auf den Kopf, falls man die Kabel beim Anoden-
 * multiplexer nicht kreuzen moechte oder es vergessen hat.
 * Default: ausgeschaltet
 */
// #define UPSIDE_DOWN

#include <Wire.h> // Wire library fuer I2C
#include <avr/pgmspace.h>
#include "DS1307.h"
#include "MyDCF77.h"
#include "ShiftRegister.h"
#include "Button.h"
#include "LDR.h"
#include "DCF77Helper.h"

/**
 * Die Real-Time-Clock
 */
DS1307 ds1307(0x68);
byte helperSeconds;
/**
 * Der serielle Ausgang zu den Multiplexern.
 * Data: 10
 * Clock: 12
 * Latch: 11
 */
#define outputEnablePin   3
ShiftRegister shiftRegister(10, 12, 11);
byte linesToWrite = 10;
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
 * LDR-Automatik oder manuelle Regelung der Helligkeit?
 */
boolean ldr_auto = true;

/**
 * Der Helligkeitssensor
 */
#ifdef ENABLE_LDR
  LDR ldr(A3);
#endif
/**
 * Die Helligkeit (default: MAX_BRIGHTNESS)
 */
int brightness = MAX_BRIGHTNESS;
/**
 * Die Helligkeit zum Anzeigen
 */
int brightnessToDisplay;
/**
 * Die Zeit, die mit LDR::MAX_BRIGHTNESS multipliziert auf 
 * eine Zeile aufgeteilt wird in Mikrosekunden.
 * (default = 50)
 */
#define PWM_DURATION 50
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
word matrix[16];

// Hilfsvariable, da I2C und Interrupts nicht zusammenspielen
volatile boolean needsUpdateFromRtc = true;

// Hilfsvariable, um das Display auf den Kopf zu stellen
#ifdef UPSIDE_DOWN
#define DISPLAY_SHIFT  9-
#else
#define DISPLAY_SHIFT  0+
#endif

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

/**
 * Hier wird die Datei includiert, die die Eck-Leds setzt.
 * So kann man sie leichter anpassen (wenn man sich beim
 * anloeten vertan hat) und hat bei Software-Updates weniger 
 * Probleme.
 */
#ifdef SET_CORNERS_CW
  #include "SetCorners.h"
#endif

#ifdef SET_CORNERS_CCW
  #include "SetCornersCCW.h"
#endif

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

  // Inhalt der Shift Register loeschen...
  clearMatrix();
  // Setze Output-Enable der Shift-Register auf LOW->enabled
  pinMode(outputEnablePin, OUTPUT);
  digitalWrite(outputEnablePin, LOW);

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
  if (ldr_auto) {
#ifdef ENABLE_LDR
    brightness = ldr.brightness();
#endif
  }

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
      case LDR_MODE:
        setCorners(0);
        clearScreenBuffer();
        if (ldr_auto) {
          for (byte i = 0; i < 6; i++) {
            matrix[2 + i] |= pgm_read_byte_near(&(staben['A'-'A'][i])) << 8;
          }
        } else {
          for (byte i = 0; i < 6; i++) {
            matrix[2 + i] |= pgm_read_byte_near(&(staben['M'-'A'][i])) << 8;
          }
        }
        break;
      case SCRAMBLE:
        scrambleScreenBuffer();
        break;
      case BLANK:
        clearScreenBuffer();
        break;
      case BRIGHTNESS:
        clearScreenBuffer();
        brightnessToDisplay = map(brightness, 1, MAX_BRIGHTNESS, 0, 9);
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
        }
        break;
      case LDR_MODE:
        ldr_auto = !ldr_auto;
#ifdef DEBUG
        Serial.print(F("LDR is now "));
        Serial.println(ldr_auto);
        Serial.flush();
#endif      
        break;
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
        }
        break;
      case LDR_MODE:
        ldr_auto = !ldr_auto;
#ifdef DEBUG
        Serial.print(F("LDR is now "));
        Serial.println(ldr_auto);
        Serial.flush();
#endif      
        break;
    }
  }
  
  // Taste Moduswechsel gedrueckt?
  if (modeChangeButton.pressed()) {
    mode++;
    if(mode == MAX) {
      mode = 0;
    }
    needsUpdateFromRtc = true;

    // brauchen wir alle Zeilen?
    if((mode == NORMAL) || (mode == SECONDS)) {
      linesToWrite = 10;
    } else {
      linesToWrite = 16;
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
    
    // Displaytreiber ausschalten, wenn BLANK
    if(mode == BLANK) {
      digitalWrite(outputEnablePin, HIGH);
    } else {
      digitalWrite(outputEnablePin, LOW);
    }
    
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
      digitalWrite(outputEnablePin, HIGH);
    }
    if((mode == BLANK) && (onTime.getMinutesOfDay() == ds1307.getMinutesOfDay())) {
      mode = lastMode;
      digitalWrite(outputEnablePin, LOW);
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
  for (byte i = 0; i < 16; i++) {
    matrix[i] = random(65536);
  }
}

/**
 * Die Matrix loeschen (zum Strom sparen, DCF77-Empfang
 * verbessern etc.)
 */
void clearScreenBuffer() {
  for (byte i = 0; i < 16; i++) {
    matrix[i] = 0;
  }
}

/**
 * Die Matrix komplett einschalten (zum Testen der LEDs)
 */
void setAllScreenBuffer() {
  for (byte i = 0; i < 16; i++) {
    matrix[i] = 65535;
  }
}

/**
 * Die Matrix ausgeben
 */
void writeScreenBufferToMatrix() {
  word row = 1;  

  // Jetzt die Daten...
  // wir brauchen keine 16, 10 wuerden reichen... dann gehen aber nicht 
  // mehr alle Modi! Also via Variable, die im Modus-Wechsel geaendert wird...
  for (byte k = 0; k < linesToWrite; k++) { 
#ifdef SKIP_BLANK_LINES
    if(matrix[DISPLAY_SHIFT k] != 0) {
#endif
      // Zeile einschalten...
      shiftRegister.prepareShiftregisterWrite();
      shiftRegister.shiftOut(~matrix[DISPLAY_SHIFT k]);
      shiftRegister.shiftOut(row);
      shiftRegister.finishShiftregisterWrite();    

      // hier kann man versuchen, das Taktverhaeltnis zu aendern (Anzeit)...
      // delayMicroseconds mit Werten <= 3 macht Probleme...
      if(brightness != 0) {
        delayMicroseconds(brightness*PWM_DURATION);
      }

      // Zeile ausschalten (einfach ganze Matrix gegenlaeufig schalten)...
      shiftRegister.prepareShiftregisterWrite();
      shiftRegister.shiftOut(65535);
      shiftRegister.shiftOut(0);
      shiftRegister.finishShiftregisterWrite();    
  
      // hier kann man versuchen, das Taktverhaeltnis zu aendern (Auszeit)...
      // delayMicroseconds mit Werten <= 3 macht Probleme...
      if(brightness != MAX_BRIGHTNESS) {
        delayMicroseconds((MAX_BRIGHTNESS-brightness)*PWM_DURATION);
      }

#ifdef SKIP_BLANK_LINES
    }
#endif
    
    row = row << 1;
  }
}

/**
 * Die Matrix (Shift-Register) loeschen...
 */
void clearMatrix() {
  word row = 1;  

  for (byte k = 0; k < 16; k++) { 
    shiftRegister.prepareShiftregisterWrite();
    shiftRegister.shiftOut(65535);
    shiftRegister.shiftOut(row);
    shiftRegister.finishShiftregisterWrite();        
    row = row << 1;
  }
}
