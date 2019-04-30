/************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME   "your_username"
#define IO_KEY        "your_key"

/******************************* WIFI **************************************/

// the AdafruitIO_WiFi client will work with the following boards:
//   - HUZZAH ESP8266 Breakout -> https://www.adafruit.com/products/2471
//   - Feather HUZZAH ESP8266 -> https://www.adafruit.com/products/2821
//   - Feather HUZZAH ESP32 -> https://www.adafruit.com/product/3405
//   - Feather M0 WiFi -> https://www.adafruit.com/products/3010
//   - Feather WICED -> https://www.adafruit.com/products/3056
//   - Adafruit PyPortal -> https://www.adafruit.com/product/4116
//   - Adafruit Metro M4 Express AirLift Lite -> https://www.adafruit.com/product/4000
//   - Adafruit AirLift Breakout -> https://www.adafruit.com/product/4201

#define WIFI_SSID   "your_ssid"
#define WIFI_PASS   "your_pass"

// uncomment the following line if you are using airlift,
// #define USE_AIRLIFT

// uncomment the following line if you are using winc1500,
// #define USE_WINC1500

// comment out the following two lines if you are using fona or ethernet
#include "AdafruitIO_WiFi.h"

// if you are using ESP32, MKR1000, ESP8266 or WICED, use the following line
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// uncomment the following line if you are using airlift,
// AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS, SPIWIFI_SS, SPIWIFI_ACK, ESP32_RESETN, ESP32_GPIO0);

// uncomment the following line if you are using winc1500,
// AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS, WINC_CS, WINC_IRQ, WINC_RST, WINC_EN);

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