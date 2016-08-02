#ifndef ADAFRUITIO_DEFINITIONS_H_
#define ADAFRUITIO_DEFINITIONS_H_

#define ADAFRUITIO_VERSION_MAJOR 1
#define ADAFRUITIO_VERSION_MINOR 0
#define ADAFRUITIO_VERSION_PATCH 0

// forward declaration
class AdafruitIO_Data;

typedef void (*AdafruitIODataCallbackType)(AdafruitIO_Data *data);

#define AIO_PING_INTERVAL 60000
#define AIO_THROTTLE_RECONNECT_INTERVAL 60000

#define AIO_ERROR_TOPIC "/errors"
#define AIO_THROTTLE_TOPIC "/throttle"

#define AIO_SSL_FINGERPRINT "26 96 1C 2A 51 07 FD 15 80 96 93 AE F7 32 CE B9 0D 01 55 C4"

typedef enum {
    AIO_IDLE                 = 0,
    AIO_NET_DISCONNECTED     = 1,
    AIO_NET_CONNECT_FAILED   = 2,
    AIO_NET_CONNECTED        = 3,
    AIO_DISCONNECTED         = 4,
    AIO_CONNECT_FAILED       = 5,
    AIO_CONNECTED            = 6,
    AIO_SSL_UNVERIFIED       = 7,
    AIO_SSL_VERIFIED         = 8
} aio_status_t;

#endif /* ADAFRUITIO_DEFINITIONS_H_ */
