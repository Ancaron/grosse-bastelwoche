/**
 * DS1307.cpp
 * Klasse fuer den Zugriff auf die DS1307 Echtzeituhr.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.5
 * @created  1.3.2011
 * @updated  18.1.2013
 *
 * Versionshistorie:
 * V 1.1:  - dayOfMonth nach date umbenannt.
 * V 1.2:  - Kompatibilitaet zu Arduino-IDE 1.0 hergestellt.
 * V 1.3:  - getMinutesOfDay eingefuehrt.
 * V 1.4:  - getMinutesOf12HoursDay eingefuehrt.
 * V 1.5:  - Optimierung hinsichtlich Speicherbedarf.
 * V 1.5.1: M. Knauer:
     - [BUGFIX] Wenn beim Lesen der RTC Uhrzeit void DS1307::readTime() eine falsche Anzahl von Daten zurueck kommt, werden die gelesenen Daten verworfen.
 */
#include <Wire.h> // Wire library fuer I2C
#include "DS1307.h"

// #define DEBUG

/**
 * Initialisierung mit der Adresse der DS1307
 */
DS1307::DS1307(int address) {
  _address = address;
}

/**
 * Die Uhrzeit auslesen und in den Variablen ablegen
 */
void DS1307::readTime() {
#if defined(ARDUINO) && ARDUINO >= 100
  // Reset the register pointer
  Wire.beginTransmission(_address);
  Wire.write((uint8_t)0x00);
  Wire.endTransmission();
  
  if (7 == Wire.requestFrom(_address, 7)) {
    // A few of these need masks because certain bits are control bits
    _seconds = bcdToDec(Wire.read() & 0x7f);
    _minutes = bcdToDec(Wire.read());
    _hours = bcdToDec(Wire.read() & 0x3f); // Need to change this if 12 hour am/pm
    _dayOfWeek = bcdToDec(Wire.read());
    _date = bcdToDec(Wire.read());
    _month = bcdToDec(Wire.read());
    _year = bcdToDec(Wire.read());

#if defined(KNAUER_DEBUG)
Serial.print(F("Time ds1307 read: "));
Serial.print(_hours);
Serial.print(":");
Serial.print(_minutes);
Serial.print(":");
Serial.print(_seconds);
Serial.print(" ");
Serial.print(_date);
Serial.print(".");
Serial.print(_month);
Serial.print(".");
Serial.println(_year);
Serial.flush();
#endif
  }
#if defined(KNAUER_DEBUG)
else {
Serial.println(F("Time ds1307 FAILED "));
Serial.flush();
}
#endif
#else
  // Reset the register pointer
  Wire.beginTransmission(_address);
  Wire.send(0x00);
  Wire.endTransmission();
  
  if (7 == Wire.requestFrom(_address, 7)) {
    // A few of these need masks because certain bits are control bits
    _seconds = bcdToDec(Wire.receive() & 0x7f);
    _minutes = bcdToDec(Wire.receive());
    _hours = bcdToDec(Wire.receive() & 0x3f); // Need to change this if 12 hour am/pm
    _dayOfWeek = bcdToDec(Wire.receive());
    _date = bcdToDec(Wire.receive());
    _month = bcdToDec(Wire.receive());
    _year = bcdToDec(Wire.receive());
  }
#endif
}

/**
 * Die Uhrzeit aus den Variablen in die DS1307 schreiben
 */
void DS1307::writeTime() {
#if defined(ARDUINO) && ARDUINO >= 100
  Wire.beginTransmission(_address);
  Wire.write((uint8_t)0x00); // 0 to bit 7 starts the clock
  Wire.write(decToBcd(_seconds));
  Wire.write(decToBcd(_minutes));
  Wire.write(decToBcd(_hours)); // If you want 12 hour am/pm you need to set
  // bit 6 (also need to change readDateDs1307)
  Wire.write(decToBcd(_dayOfWeek));
  Wire.write(decToBcd(_date));
  Wire.write(decToBcd(_month));
  Wire.write(decToBcd(_year));
  Wire.write(0b00010000); // 1Hz Rechteck auf SQW fuer den Display-Update-Interrupt...
  Wire.endTransmission();
#else
  Wire.beginTransmission(_address);
  Wire.send(0x00); // 0 to bit 7 starts the clock
  Wire.send(decToBcd(_seconds));
  Wire.send(decToBcd(_minutes));
  Wire.send(decToBcd(_hours)); // If you want 12 hour am/pm you need to set
  // bit 6 (also need to change readDateDs1307)
  Wire.send(decToBcd(_dayOfWeek));
  Wire.send(decToBcd(_date));
  Wire.send(decToBcd(_month));
  Wire.send(decToBcd(_year));
  Wire.send(0b00010000); // 1Hz Rechteck auf SQW fuer den Display-Update-Interrupt...
  Wire.endTransmission();
#endif
}

/**
 * Konvertierung Dezimal zu "Binary Coded Decimal"
 */
byte DS1307::decToBcd(byte val) {
  return ((val / 10 * 16) + (val % 10));
}

/**
 * Konvertierung "Binary Coded Decimal" zu Dezimal
 */
byte DS1307::bcdToDec(byte val) {
  return ((val / 16 * 10) + (val % 16));
}

//
// Setter/Getter
//

void DS1307::setSeconds(byte seconds) {
  _seconds = seconds;
}

void DS1307::setMinutes(byte minutes) {
  _minutes = minutes;
}

void DS1307::incMinutes() {
  _minutes++;
  if(_minutes > 59) {
    _minutes = 0;
  }
}

void DS1307::setHours(byte hours) {
  _hours = hours;
}

void DS1307::incHours() {
  _hours++;
  if(_hours > 23) {
    _hours = 0;
  }
}

void DS1307::setDayOfWeek(byte dayOfWeek) {
  _dayOfWeek = dayOfWeek;
}

void DS1307::setDate(byte date) {
  _date = date;
}

void DS1307::setMonth(byte month) {
  _month = month;
}

void DS1307::setYear(byte year) {
  _year = year;
}

byte DS1307::getSeconds() {
  return _seconds;
}

byte DS1307::getMinutes() {
  return _minutes;
}

unsigned int DS1307::getMinutesOfDay() {
  return _minutes + 60 * _hours;
}

// Minuten des Tages ohne die Beruecksichtigung von 12/24 Stunden 
// (fuer den Wecker)...
unsigned int DS1307::getMinutesOf12HoursDay() {
  int h = _hours;
  while(h > 12) {
    h -= 12;
  }
  return _minutes + 60 * h;
}

byte DS1307::getHours() {
  return _hours;
}

byte DS1307::getDayOfWeek() {
  return _dayOfWeek;
}

byte DS1307::getDate() {
  return _date;
}

byte DS1307::getMonth() {
  return _month;
}

byte DS1307::getYear() {
  return _year;
}

