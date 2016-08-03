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

    // CONNECTING
    AIO_IDLE                    = 0,
    AIO_NET_DISCONNECTED        = 1,
    AIO_DISCONNECTED            = 2,
    AIO_FINGERPRINT_UNKOWN      = 3,

    // FAILURE
    AIO_NET_CONNECT_FAILED      = 10,
    AIO_CONNECT_FAILED          = 11,
    AIO_FINGERPRINT_INVALID     = 12,
    AIO_AUTH_FAILED             = 13,

    // SUCCESS
    AIO_NET_CONNECTED           = 20,
    AIO_CONNECTED               = 21,
    AIO_CONNECTED_INSECURE      = 22,
    AIO_FINGERPRINT_UNSUPPORTED = 23,
    AIO_FINGERPRINT_VALID       = 24

} aio_status_t;

#endif /* ADAFRUITIO_DEFINITIONS_H_ */
