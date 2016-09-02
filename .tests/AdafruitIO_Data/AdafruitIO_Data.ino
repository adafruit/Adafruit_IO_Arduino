#include <ArduinoTap.h>
#include "AdafruitIO_Data.h"

AdafruitIO_Data *data = new AdafruitIO_Data();

void setup()
{
  Serial.begin(115200);
  while(! Serial);
}

void loop() {

  delay(5000);

  plan(8);

  char bad_csv[] = "xxxxx";
  char good_csv[] = "12.120,42.331427,-83.045754,233";

  nok(
    data->setCSV(bad_csv),
    "invalid CSV doesn't parse"
  );

  ok(
    data->setCSV(good_csv),
    "valid CSV parses"
  );

  ok(
    compareChar("12.120", data->value()),
    "char value match"
  );

  ok(
    (12 == data->toInt()),
    "int value match"
  );

  ok(
    compareDouble(12.12, data->toDouble()),
    "double value match"
  );

  ok(
    compareDouble(42.331427, data->lat()),
    "lat match"
  );

  ok(
    compareDouble(-83.045754, data->lon()),
    "lon match"
  );

  ok(
    compareDouble(233, data->ele()),
    "ele match"
  );

  done_testing();

}


bool compareDouble(double a, double b)
{
#ifdef __AVR__
  return abs(a-b) < 0.00001;
#else
  return abs(a-b) < 0.000001;
#endif
}

bool compareChar(char *a, char *b)
{
  return strcmp(a,b) == 0;
}

