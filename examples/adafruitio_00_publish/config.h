/************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME    "your_username"
#define IO_KEY         "your_key"

/******************************* WIFI **************************************/

// the AdafruitIO_WiFi client will work with the following boards:
//   - HUZZAH ESP8266 Breakout -> https://www.adafruit.com/products/2471
//   - Feather HUZZAH ESP8266 -> https://www.adafruit.com/products/2821
//   - Feather HUZZAH ESP32 -> https://www.adafruit.com/product/3405
//   - Feather M0 WiFi -> https://www.adafruit.com/products/3010
//   - Feather WICED -> https://www.adafruit.com/products/3056

#define WIFI_SSID       "your_ssid"
#define WIFI_PASS       "your_pass"

// comment out the following two lines if you are using fona or ethernet
#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);


/******************************* WIFI WPA2 Enterprise***********************/

// the AdafruitIO_WiFi_Enterprise client will work with the following boards:
//   - HUZZAH ESP8266 Breakout -> https://www.adafruit.com/products/2471
//   - Feather HUZZAH ESP8266 -> https://www.adafruit.com/products/2821
//   - Feather HUZZAH ESP32 -> https://www.adafruit.com/product/3405
// currently only username/password authentication is supported.

// uncomment the below lines for WPA2 Enterprise
// and comment out the AdafruitIO_WiFi client in the WIFI section

// It is unclear whether CA certificate validation is functional for either board. I was unable to get it to work.

#include "AdafruitIO_WiFi_Enterprise.h"
#define WIFI_ENT_SSID  "eduroam"
#define WIFI_ENT_IDENT "user"
#define WIFI_ENT_PASS  "password"
// I was unable to get CA certificate validation to work. Passing NULL disables it.
#define WIFI_CACERT NULL

AdafruitIO_WiFi_Enterprise io(IO_USERNAME, IO_KEY, WIFI_ENT_SSID, WIFI_ENT_IDENT, WIFI_ENT_PASS, WIFI_CACERT);

/******************************* FONA **************************************/
// the AdafruitIO_FONA client will work with the following boards:
//   - Feather 32u4 FONA -> https://www.adafruit.com/product/3027

// uncomment the following two lines for 32u4 FONA,
// and comment out the AdafruitIO_WiFi client in the WIFI section
// #include "AdafruitIO_FONA.h"
// AdafruitIO_FONA io(IO_USERNAME, IO_KEY);


/**************************** ETHERNET ************************************/

// the AdafruitIO_Ethernet client will work with the following boards:
//   - Ethernet FeatherWing -> https://www.adafruit.com/products/3201

// uncomment the following two lines for ethernet,
// and comment out the AdafruitIO_WiFi client in the WIFI section
// #include "AdafruitIO_Ethernet.h"
// AdafruitIO_Ethernet io(IO_USERNAME, IO_KEY);
