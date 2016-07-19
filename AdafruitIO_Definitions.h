#ifndef ADAFRUITIO_DEFINITIONS_H_
#define ADAFRUITIO_DEFINITIONS_H_

#define AIO_PING_INTERVAL 60000

typedef enum {
    AIO_IDLE                 = 0,
    AIO_NET_DISCONNECTED     = 1,
    AIO_NET_CONNECT_FAILED   = 2,
    AIO_NET_CONNECTED        = 3,
    AIO_DISCONNECTED         = 4,
    AIO_CONNECT_FAILED       = 5,
    AIO_CONNECTED            = 6
} aio_status_t;

#endif /* ADAFRUITIO_DEFINITIONS_H_ */
