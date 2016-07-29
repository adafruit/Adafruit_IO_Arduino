#include "AdafruitIO_Data.h"

AdafruitIO_Data::AdafruitIO_Data(AdafruitIO_Feed *f)
{
  feed = f;
  _csv = 0;
  _value = 0;
  _lat = 0;
  _lon = 0;
  _ele = 0;
}

AdafruitIO_Data::AdafruitIO_Data(AdafruitIO_Feed *f, char *csv)
{
  feed = f;
  _csv = csv;
  _value = 0;
  _lat = 0;
  _lon = 0;
  _ele = 0;

  _parseCSV();
}

bool AdafruitIO_Data::setCSV(char *csv)
{
  _csv = csv;
  return _parseCSV();
}

char* AdafruitIO_Data::value()
{
  return _value;
}

bool AdafruitIO_Data::toBool()
{

  if(_value[0] == '1' || _value[0] == 't' || _value[0] == 'T')
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
  char* endptr;
  return (int)strtol(_value, &endptr, 10);
}

unsigned int AdafruitIO_Data::toUnsignedInt()
{
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
  char* endptr;
  return (float)strtod(_value, &endptr);
}

double AdafruitIO_Data::toDouble()
{
  char* endptr;
  return strtod(_value, &endptr);
}

long AdafruitIO_Data::toLong()
{
  char* endptr;
  return strtol(_value, &endptr, 10);
}

unsigned long AdafruitIO_Data::toUnsignedLong()
{
  char* endptr;
  #ifdef ESP8266
      // For some reason strtoul is not defined on the ESP8266 platform right now.
      // Just use a strtol function and hope for the best.
      return (unsigned long)strtol(_value, &endptr, 10);
  #else
      return strtoul(_value, &endptr, 10);
  #endif
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

bool AdafruitIO_Data::_parseCSV()
{
  // parse value from csv
  _value = strtok(_csv, ",");
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
