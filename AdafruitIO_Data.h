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

    void setValue(char *value, double lat=0, double lon=0, double ele=0);
    void setValue(bool value, double lat=0, double lon=0, double ele=0);
    void setValue(String value, double lat=0, double lon=0, double ele=0);
    void setValue(int value, double lat=0, double lon=0, double ele=0);
    void setValue(unsigned int value, double lat=0, double lon=0, double ele=0);
    void setValue(long value, double lat=0, double lon=0, double ele=0);
    void setValue(unsigned long value, double lat=0, double lon=0, double ele=0);
    void setValue(float value, double lat=0, double lon=0, double ele=0, int precision=6);
    void setValue(double value, double lat=0, double lon=0, double ele=0, int precision=6);

    char* value();
    char* toChar();
    String toString();

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
