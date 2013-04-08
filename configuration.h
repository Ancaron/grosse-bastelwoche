/**
 * configuration.h
 * Diese Klasse dient zur Bereitstellung, Speicherung und Wiederherstellung von Einstellungen.
 *
 * @mc       Arduino/RBBB
 * @autor    Markus Knauer / knauer _AT_ gmx _DOT_ de
 * @version  1.1
 * @created  17.01.2013
 * @updated  20.01.2013
 *
 * Versionshistorie:
 * V 1.1:  - Erste Version.
 */
#ifndef CONFIG_H
#define CONFIG_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


#define GetConfig(handle)         (Config._config.cfg.handle)
#define SetConfig(handle, value)  Config._config.cfg.handle = value; Config._cfgChanged_bt = true


/* EEPROM Belegung:
  0x0000 - 0x0001: 2 Byte: Version der Konfiguration
  0x0002 - 0x001F: 30 Byte: Einstellungen, die der Anwender zur Laufzeit selbst einstellen kann
  0x0020 - tbd: : Daten, welche die SW selbstaendig speichert. Zur Erweiterung fuer diesen Bereich bitte an "knauer _AT_ gmx _DOT_ de" wenden.
*/
#define NVM_BASE_ADR_CONFIG  0x0000

/* Anmerkungen zur Versionsnummer "CFG_VERSION":
   Die Versionsnummer soll nur hochgezaehlt werden, wenn die EEPROM Belegung der aktuellen SW nicht mehr kompatibel zu den
   vorherigen Versionen ist und/ oder durch ein Sonderhandling in "CConfig::Init()" ensprechend drauf reagiert werden soll.

   Version 0x0000:
     Wenn das EEPROM uninitialisiert ist, dann werden die ersten 30 Byte (hier ist nicht die 2 Byte Versionsnummer enthalten!)
	 mit dem Defaultwert 0xFF vorinitialisert. Zusaetzlich werden die vorhandenen Config Bits/ Bytes auf einen individuellen
	 Defaultwert gesetzt.

   Version 0x0001 (noch nicht vergeben):
     ...
*/
#define CFG_VERSION  0x0000
typedef struct TConfigElements {
  unsigned int cfg_version: 16;
    
  /* Byte 0 */
  byte cfg_brightness_u8: 8;

  /* Byte 1 */
  byte cfg_ldr_auto_bt: 1; /* 0 = man, 1 = auto */
  byte cfg_free_1_1_bt: 1;
  byte cfg_free_1_2_bt: 1;
  byte cfg_free_1_3_bt: 1;
  byte cfg_free_1_4_bt: 1;
  byte cfg_free_1_5_bt: 1;
  byte cfg_free_1_6_bt: 1;
  byte cfg_free_1_7_bt: 1;

  /* Byte 2 */
  byte cfg_free_2_u8: 8;

  /* Byte 3 */
  byte cfg_free_3_u8: 8;

  /* Byte 4 */
  byte cfg_free_4_u8: 8;

  /* Byte 5 */
  byte cfg_free_5_u8: 8;

  /* Byte 6 */
  byte cfg_free_6_u8: 8;

  /* Byte 7 */
  byte cfg_free_7_u8: 8;

  /* Byte 8 */
  byte cfg_free_8_u8: 8;

  /* Byte 9 */
  byte cfg_free_9_u8: 8;

  /* Byte 10 */
  byte cfg_free_10_u8: 8;

  /* Byte 11 */
  byte cfg_free_11_u8: 8;

  /* Byte 12 */
  byte cfg_free_12_u8: 8;

  /* Byte 13 */
  byte cfg_free_13_u8: 8;

  /* Byte 14 */
  byte cfg_free_14_u8: 8;

  /* Byte 15 */
  byte cfg_free_15_u8: 8;

  /* Byte 16 */
  byte cfg_free_16_u8: 8;

  /* Byte 17 */
  byte cfg_free_17_u8: 8;

  /* Byte 18 */
  byte cfg_free_18_u8: 8;

  /* Byte 19 */
  byte cfg_free_19_u8: 8;

  /* Byte 20 */
  byte cfg_free_20_u8: 8;

  /* Byte 21 */
  byte cfg_free_21_u8: 8;

  /* Byte 22 */
  byte cfg_free_22_u8: 8;

  /* Byte 23 */
  byte cfg_free_23_u8: 8;

  /* Byte 24 */
  byte cfg_free_24_u8: 8;

  /* Byte 25 */
  byte cfg_free_25_u8: 8;

  /* Byte 26 */
  byte cfg_free_26_u8: 8;

  /* Byte 27 */
  byte cfg_free_27_u8: 8;

  /* Byte 28 */
  byte cfg_free_28_u8: 8;

  /* Byte 29 */
  byte cfg_free_29_u8: 8;
};
typedef union {
  TConfigElements cfg;  
  byte bytes[sizeof(TConfigElements)];
} TConfig;


class CConfig {
public:
  TConfig _config;
  boolean _cfgChanged_bt;

  void Init();
  void CyclicCall();
  void LoadCfg();
  void SaveCfg();

//private:
};

#endif
