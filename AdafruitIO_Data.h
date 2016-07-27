#ifndef ADAFRUITIO_DATA_H
#define ADAFRUITIO_DATA_H

#include "Arduino.h"

class AdafruitIO_Data {

  public:
    AdafruitIO_Data();
    AdafruitIO_Data(char *csv);

    void setCSV(char *csv);

    char* value();

    int toInt();
    unsigned int toUnsignedInt();

    double toDouble();
    float toFloat();

    long toLong();
    unsigned long toUnsignedLong();

    double lat();
    double lon();
    double ele();

  private:
    char *_csv;
    char *_value;
    double _lat;
    double _lon;
    double _ele;

};

#endif // ADAFRUITIO_DATA_H
