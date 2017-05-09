//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Copyright (c) 2015-2016 Adafruit Industries
// Authors: Tony DiCola, Todd Treece
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.
//
#include "AdafruitIO_Data.h"
#include "AdafruitIO_Feed.h"

AdafruitIO_Data::AdafruitIO_Data()
{
  _lat = 0;
  _lon = 0;
  _ele = 0;
  next_data = 0;

  memset(_feed, 0, AIO_FEED_NAME_LENGTH);
  memset(_value, 0, AIO_DATA_LENGTH);
  memset(_csv, 0, AIO_CSV_LENGTH);
}

AdafruitIO_Data::AdafruitIO_Data(AdafruitIO_Feed *f)
{
  _lat = 0;
  _lon = 0;
  _ele = 0;
  next_data = 0;

  memset(_feed, 0, AIO_FEED_NAME_LENGTH);
  strcpy(_feed, f->name);
  memset(_value, 0, AIO_DATA_LENGTH);
  memset(_csv, 0, AIO_CSV_LENGTH);
}

AdafruitIO_Data::AdafruitIO_Data(AdafruitIO_Feed *f, char *csv)
{
  _lat = 0;
  _lon = 0;
  _ele = 0;
  next_data = 0;

  memset(_feed, 0, AIO_FEED_NAME_LENGTH);
  strcpy(_feed, f->name);
  memset(_value, 0, AIO_DATA_LENGTH);
  memset(_csv, 0, AIO_CSV_LENGTH);
  strcpy(_csv, csv);

  _parseCSV();
}

AdafruitIO_Data::AdafruitIO_Data(const char *f)
{
  _lat = 0;
  _lon = 0;
  _ele = 0;
  next_data = 0;

  memset(_feed, 0, AIO_FEED_NAME_LENGTH);
  strcpy(_feed, f);
  memset(_value, 0, AIO_DATA_LENGTH);
}

AdafruitIO_Data::AdafruitIO_Data(const char *f, char *csv)
{
  _lat = 0;
  _lon = 0;
  _ele = 0;
  next_data = 0;

  memset(_feed, 0, AIO_FEED_NAME_LENGTH);
  strcpy(_feed, f);
  memset(_value, 0, AIO_DATA_LENGTH);
  memset(_csv, 0, AIO_CSV_LENGTH);
  strcpy(_csv, csv);

  _parseCSV();
}

bool AdafruitIO_Data::setCSV(char *csv)
{
  memset(_csv, 0, AIO_CSV_LENGTH);
  strcpy(_csv, csv);
  return _parseCSV();
}

void AdafruitIO_Data::setLocation(double lat, double lon, double ele)
{
  // if lat, lon, ele == 0, don't set them
  if((abs(0-lat) < 0.000001) && (abs(0-lon) < 0.000001) && (abs(0-ele) < 0.000001))
    return;
  _lat = lat;
  _lon = lon;
  _ele = ele;
}

void AdafruitIO_Data::setValue(const char *value, double lat, double lon, double ele)
{
  strcpy(_value, value);
  setLocation(lat, lon, ele);
}

void AdafruitIO_Data::setValue(char *value, double lat, double lon, double ele)
{
  strcpy(_value, value);
  setLocation(lat, lon, ele);
}

void AdafruitIO_Data::setValue(bool value, double lat, double lon, double ele)
{
  if(value)
    strcpy(_value, "1");
  else
    strcpy(_value, "0");

  setLocation(lat, lon, ele);
}

void AdafruitIO_Data::setValue(String value, double lat, double lon, double ele)
{
  value.toCharArray(_value, value.length() + 1);
  setLocation(lat, lon, ele);
}

void AdafruitIO_Data::setValue(int value, double lat, double lon, double ele)
{
  memset(_value, 0, AIO_DATA_LENGTH);
  itoa(value, _value, 10);
  setLocation(lat, lon, ele);
}

void AdafruitIO_Data::setValue(unsigned int value, double lat, double lon, double ele)
{
  memset(_value, 0, AIO_DATA_LENGTH);
  utoa(value, _value, 10);
  setLocation(lat, lon, ele);
}

void AdafruitIO_Data::setValue(long value, double lat, double lon, double ele)
{
  memset(_value, 0, AIO_DATA_LENGTH);
  ltoa(value, _value, 10);
  setLocation(lat, lon, ele);
}

void AdafruitIO_Data::setValue(unsigned long value, double lat, double lon, double ele)
{
  memset(_value, 0, AIO_DATA_LENGTH);
  ultoa(value, _value, 10);
  setLocation(lat, lon, ele);
}

void AdafruitIO_Data::setValue(float value, double lat, double lon, double ele, int precision)
{
  memset(_value, 0, AIO_DATA_LENGTH);

  #if defined(ARDUINO_ARCH_AVR)
    // Use avrlibc dtostre function on AVR platforms.
    dtostre(value, _value, 10, 0);
  #elif defined(ESP8266)
    // ESP8266 Arduino only implements dtostrf and not dtostre.  Use dtostrf
    // but accept a hint as to how many decimals of precision are desired.
    dtostrf(value, 0, precision, _value);
  #else
    // Otherwise fall back to snprintf on other platforms.
    snprintf(_value, sizeof(_value)-1, "%f", value);
  #endif

  setLocation(lat, lon, ele);
}

void AdafruitIO_Data::setValue(double value, double lat, double lon, double ele, int precision)
{
  memset(_value, 0, AIO_DATA_LENGTH);

  #if defined(ARDUINO_ARCH_AVR)
    // Use avrlibc dtostre function on AVR platforms.
    dtostre(value, _value, 10, 0);
  #elif defined(ESP8266)
    // ESP8266 Arduino only implements dtostrf and not dtostre.  Use dtostrf
    // but accept a hint as to how many decimals of precision are desired.
    dtostrf(value, 0, precision, _value);
  #else
    // Otherwise fall back to snprintf on other platforms.
    snprintf(_value, sizeof(_value)-1, "%f", value);
  #endif

  setLocation(lat, lon, ele);
}

char* AdafruitIO_Data::feedName()
{
  if(! _feed)
    return (char*)"";

  return _feed;
}

char* AdafruitIO_Data::value()
{
  return toChar();
}

char* AdafruitIO_Data::toChar()
{
  return _value;
}

String AdafruitIO_Data::toString()
{
  if(! _value)
    return String();

  return String(_value);
}

bool AdafruitIO_Data::toBool()
{
  if(! _value)
    return false;

  if(strcmp(_value, "1") == 0 || _value[0] == 't' || _value[0] == 'T')
    return true;
  else
    return false;
}

bool AdafruitIO_Data::isTrue()
{
  return toBool();
}

bool AdafruitIO_Data::isFalse()
{
  return !toBool();
}

int AdafruitIO_Data::toInt()
{
  if(! _value)
    return 0;

  char* endptr;
  return (int)strtol(_value, &endptr, 10);
}

int AdafruitIO_Data::toPinLevel()
{
  if(isTrue())
    return HIGH;
  else
    return LOW;
}

unsigned int AdafruitIO_Data::toUnsignedInt()
{
  if(! _value)
    return 0;

  char* endptr;
  #ifdef ESP8266
    // For some reason strtoul is not defined on the ESP8266 platform right now.
    // Just use a strtol function and hope for the best.
    return (unsigned int)strtol(_value, &endptr, 10);
  #else
    return (unsigned int)strtoul(_value, &endptr, 10);
  #endif
}

float AdafruitIO_Data::toFloat()
{
  if(! _value)
    return 0;

  char* endptr;
  return (float)strtod(_value, &endptr);
}

double AdafruitIO_Data::toDouble()
{
  if(! _value)
    return 0;

  char* endptr;
  return strtod(_value, &endptr);
}

long AdafruitIO_Data::toLong()
{
  if(! _value)
    return 0;

  char* endptr;
  return strtol(_value, &endptr, 10);
}

unsigned long AdafruitIO_Data::toUnsignedLong()
{
  if(! _value)
    return 0;

  char* endptr;
  #ifdef ESP8266
      // For some reason strtoul is not defined on the ESP8266 platform right now.
      // Just use a strtol function and hope for the best.
      return (unsigned long)strtol(_value, &endptr, 10);
  #else
      return strtoul(_value, &endptr, 10);
  #endif
}

int AdafruitIO_Data::toRed()
{
  if(! _value)
    return 0;

  char r[] = "0x";
  strncat(r, toChar() + 1, 2);

  return (int)strtol(r, NULL, 0);
}

int AdafruitIO_Data::toGreen()
{
  if(! _value)
    return 0;

  char g[] = "0x";
  strncat(g, toChar() + 3, 2);

  return (int)strtol(g, NULL, 0);
}

int AdafruitIO_Data::toBlue()
{
  if(! _value)
    return 0;

  char b[] = "0x";
  strncat(b, toChar() + 5, 2);

  return (int)strtol(b, NULL, 0);
}

long AdafruitIO_Data::toNeoPixel()
{
  if(! _value)
    return 0;

  char rgb_string[9] = "0x";
  strncat(rgb_string, toChar() + 1, 6);

  return strtol(rgb_string, NULL, 0);
}

char* AdafruitIO_Data::toCSV()
{
  if(! _value)
    return _csv;

  memset(_csv, 0, AIO_CSV_LENGTH);

  strcpy(_csv, _value);
  strcat(_csv, ",");
  strcat(_csv, charFromDouble(_lat));
  strcat(_csv, ",");
  strcat(_csv, charFromDouble(_lon));
  strcat(_csv, ",");
  strcat(_csv, charFromDouble(_ele, 2));

  return _csv;
}

double AdafruitIO_Data::lat()
{
  return _lat;
}

double AdafruitIO_Data::lon()
{
  return _lon;
}

double AdafruitIO_Data::ele()
{
  return _ele;
}

static char _double_buffer[20];

char* AdafruitIO_Data::charFromDouble(double d, int precision)
{
  memset(_double_buffer, 0, sizeof(_double_buffer));

  #if defined(ARDUINO_ARCH_AVR)
    // Use avrlibc dtostre function on AVR platforms.
    dtostre(d, _double_buffer, 10, 0);
  #elif defined(ESP8266)
    // ESP8266 Arduino only implements dtostrf and not dtostre.  Use dtostrf
    // but accept a hint as to how many decimals of precision are desired.
    dtostrf(d, 0, precision, _double_buffer);
  #else
    // Otherwise fall back to snprintf on other platforms.
    snprintf(_double_buffer, sizeof(_double_buffer)-1, "%f", d);
  #endif

  return _double_buffer;
}

bool AdafruitIO_Data::_parseCSV()
{
  // parse value from csv
  strcpy(_value, strtok(_csv, ","));
  if (! _value) return false;

  // parse lat from csv and convert to float
  char *lat = strtok(NULL, ",");
  if (! lat) return false;

  _lat = atof(lat);

  // parse lon from csv and convert to float
  char *lon = strtok(NULL, ",");
  if (! lon) return false;

  _lon = atof(lon);

  // parse ele from csv and convert to float
  char *ele = strtok(NULL, ",");
  if (! ele) return false;

  _ele = atof(ele);

  return true;
}
