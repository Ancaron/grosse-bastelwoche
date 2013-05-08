/**
 * configuration.cpp
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
#include "prj_settings.h"
#include "configuration.h"

#include "LDR.h"

#if defined(ENABLE_EEPROM)
#include <eeprom.h>
#endif

// #define DEBUG_EEP


/**
 * Initialisierung:
 * Wenn ein Eeprom per Compilerschalter vorhanden ist, dann werden die letzten Daten aus dem Eeprom geladen.
 * Wenn im Eeprom keine gueltigen Daten vorhanden sind, werden Defaultwerte verwendet.
 * Wenn lt. Versionsangabe aus dem Eeprom die Daten entsprechend einer alten Version abgespeichert wurden, werden
 * die Eeprom Daten ggf. konvertiert oder neu initialisiert.
 *
 * Wenn per Compilerschalter kein Eeprom vorhanden ist, werden Defaultwerte verwendet.
 */
void CConfig::Init() {
  LoadCfg();
  
  /* Konfiguration fuer Version 0x0000 */
  if (
#if defined(ENABLE_EEPROM)
       (_config.cfg.cfg_version == 0xFFFF)
#else
       (true)
#endif
     ) {
    /* Konfiguration mit 0xFF vorinitialisieren */
    memset(&_config, 0xFF, sizeof(_config));

    /* Wenn
	     - Eeprom ist uninitialsiert (d.h. version == 0xFFFF) ODER
		 - das EEPROM ist per Compilerschalter nicht vorhanden
       dann	default Werte setzen:
	*/
    _config.cfg.cfg_version = 0x0000;
    _config.cfg.cfg_brightness_u8 = MAX_BRIGHTNESS;
    _config.cfg.cfg_ldr_auto_bt = true;

    _cfgChanged_bt = true;
  }

  #if !defined(ENABLE_LDR)
    /* Wenn es lt. Compilerschalter keinen LDR gibt, gibt es definitiv keinen Auto-Modus fuer die Helligkeit. */
	_config.cfg.cfg_ldr_auto_bt = false;
  
    _cfgChanged_bt = true;
  #endif


#if defined(Beispiel_fuer_neue_Konfiguration)
  /* Konfiguration fuer neue (aktuelle) Version CFG_VERSION */
  if (_config.cfg.cfg_version < CFG_VERSION) {
    /* Neue Defaultwerte festlegen */
    _config.cfg.Function_xy = false;
	...
  }
#endif

}

/**
 * Diese Funktion muss zyklisch aufgerufen werden. Es gibt keine feste Zeitbasis. Wenn die Funktion aufgerufen wird,
 * werden noch nicht gespeicherte Daten im Eeprom gespeichert.
 */
void CConfig::CyclicCall() {
  SaveCfg();
}

/**
 * Laedt alle Eeprom Daten neu.
 */
void CConfig::LoadCfg() {
#if defined(ENABLE_EEPROM)
  int i;
  
  for (i = 0; i < sizeof(_config); i++) {
    _config.bytes[i] = EEPROM.read(NVM_BASE_ADR_CONFIG + i);
#if defined(DEBUG_EEP)
	Serial.print("EEPROM Read: ");
	Serial.print(NVM_BASE_ADR_CONFIG + i);
	Serial.print("=");
	Serial.println(_config.bytes[i]);
    Serial.flush();
#endif
  }
#endif
}

/**
 * Wenn das Flag "_cfgChanged_bt" es anzeigt, werden geaenderte Daten ins Eeprom geschrieben. Zwecks Eeprom Schonung
 * werden nur geaenderte Daten geschrieben.
 */
void CConfig::SaveCfg() {
  int i;
  
  if (_cfgChanged_bt) {
#if defined(ENABLE_EEPROM)
    for (i = 0; i < sizeof(_config); i++) {
      /* Zur Schonung des Eeprom Daten nur schreiben, wenn sich etwas geaendert hat. */
      if (EEPROM.read(NVM_BASE_ADR_CONFIG + i) != _config.bytes[i]) {
	    EEPROM.write(NVM_BASE_ADR_CONFIG + i, _config.bytes[i]);
#if defined(DEBUG_EEP)
        Serial.print("EEPROM Write: ");
        Serial.print(NVM_BASE_ADR_CONFIG + i);
        Serial.print("=");
        Serial.println(_config.bytes[i]);
        Serial.flush();
#endif
	  }
    }
#endif
	
	_cfgChanged_bt = false;
  }
}
