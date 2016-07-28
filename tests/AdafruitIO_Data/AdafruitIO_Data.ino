#include "AdafruitIO_Data.h"

AdafruitIO_Data *data = new AdafruitIO_Data();

void setup()
{
  Serial.begin(115200);
  delay(100);

  Serial.println("---------- test start ----------");
  // should fail parsing bad CSV
  Serial.print("valid CSV passes: ");
  check(data->setCSV((char *)"12,18.000,-25.000,9"));

  Serial.print("invalid CSV fails: ");
  check(! data->setCSV((char *)"xxxxx"));

  data->setCSV((char *)"12.120,42.331427,-83.045754,233");

  Serial.print("char value matches: ");
  compareChar("12.120", data->value());

  Serial.print("int value matches: ");
  check(12 == data->toInt());

  Serial.print("double value matches: ");
  compareDouble(12.12, data->toDouble());

  Serial.print("lat matches: ");
  compareDouble(42.331427, data->lat());

  Serial.print("lon matches: ");
  compareDouble(-83.045754, data->lon());

  Serial.print("ele matches: ");
  compareDouble(233, data->ele());

  Serial.println("---------- test end ----------");

  Serial.println();

  Serial.print("value: ");
  Serial.println(data->value());

  Serial.print("toInt: ");
  Serial.println(data->toInt());

  Serial.print("toUnsignedInt: ");
  Serial.println(data->toUnsignedInt());

  Serial.print("toLong: ");
  Serial.println(data->toLong());

  Serial.print("toUnsignedLong: ");
  Serial.println(data->toUnsignedLong());

  Serial.print("toDouble: ");
  Serial.println(data->toDouble(),6);

  Serial.print("toFloat: ");
  Serial.println(data->toFloat(),6);

  Serial.print("lat: ");
  Serial.println(data->lat(),6);

  Serial.print("lon: ");
  Serial.println(data->lon(),6);

  Serial.print("ele: ");
  Serial.println(data->ele(),6);

}

void check(bool pass)
{
  if(pass) {
    Serial.println("✓");
  } else {
    Serial.println("✘");
  }
}

void compareDouble(double a, double b)
{
  check(abs(a-b) < 0.000001);
}

void compareChar(char *a, char *b)
{
  check(strcmp(a,b) == 0);
}

void loop(){}
