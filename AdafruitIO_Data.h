#ifndef ADAFRUITIO_DATA_H
#define ADAFRUITIO_DATA_H

#include "Arduino.h"

class AdafruitIO_Data {

  public:
    AdafruitIO_Data();
    AdafruitIO_Data(char *csv);

    bool setCSV(char *csv);

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
    char *_csv,
         *_value;

    double _lat,
           _lon,
           _ele;

    bool _parseCSV();

};

#endif // ADAFRUITIO_DATA_H
