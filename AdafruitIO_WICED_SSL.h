#ifndef ADAFRUITIO_WICED_SSL_H
#define ADAFRUITIO_WICED_SSL_H

#ifdef ARDUINO_STM32_FEATHER

#include <adafruit_feather.h>

class AdafruitIO_WICED_SSL : public AdafruitTCP {

  public:

    AdafruitIO_WICED_SSL() : AdafruitTCP() {}

    int connect(const char *host, uint16_t port)
    {
      return connectSSL(host, port);
    }

};

#endif // ARDUINO_STM32_FEATHER

#endif // ADAFRUITIO_WICED_H
