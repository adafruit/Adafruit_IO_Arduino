#ifndef ADAFRUITIO_DATA_H
#define ADAFRUITIO_DATA_H

#include "Arduino.h"

// forward decl
class AdafruitIO_Feed;

class AdafruitIO_Data {

  public:
    AdafruitIO_Data(AdafruitIO_Feed *f);
    AdafruitIO_Data(AdafruitIO_Feed *f, char *csv);

    bool setCSV(char *csv);

    char* value();

    bool toBool();
    bool isTrue();
    bool isFalse();

    int toInt();
    unsigned int toUnsignedInt();

    double toDouble();
    float toFloat();

    long toLong();
    unsigned long toUnsignedLong();

    double lat();
    double lon();
    double ele();

    AdafruitIO_Feed *feed;

  private:

    char *_csv,
         *_value;

    double _lat,
           _lon,
           _ele;

    bool _parseCSV();

};

#endif // ADAFRUITIO_DATA_H
