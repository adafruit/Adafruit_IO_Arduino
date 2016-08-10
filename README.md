# Adafruit IO Arduino Library [![Build Status](https://travis-ci.org/adafruit/Adafruit_IO_Arduino.svg?branch=master)](https://travis-ci.org/adafruit/Adafruit_IO_Arduino)

This library provides a simple device independent interface for interacting with [Adafruit IO](https://io.adafruit.com) using Arduino.
It allows you to switch beween WiFi (ESP8266, M0 WINC1500, & WICED), Cellular (32u4 FONA), and Ethernet (Ethernet FeatherWing)
with only a two line change in your sketch.

## Dependencies

This library requires the latest version of the [Arduino IDE](https://www.arduino.cc/en/Main/Software) (tested with v1.6.10).

### Adafruit Feather HUZZAH ESP8266 & Adafruit HUZZAH ESP8266 Breakout

* Latest version of the [ESP8266 Arduino Core](https://github.com/esp8266/Arduino#installing-with-boards-manager)
* Latest version of the [Adafruit MQTT Library](https://github.com/adafruit/Adafruit_MQTT_Library)

### Adafruit Feather M0 WiFi with ATWINC1500

* Latest version of the [Arduino SAMD Arduino Core](https://github.com/arduino/ArduinoCore-samd)
* Latest version of the [Adafruit SAMD Arduino Core](https://github.com/adafruit/ArduinoCore-samd)
* Latest version of the [Adafruit MQTT Library](https://github.com/adafruit/Adafruit_MQTT_Library)

You will also need to add the SSL certificate for `io.adafruit.com` using the [guide on the Adafruit Learning System.](https://learn.adafruit.com/adafruit-feather-m0-wifi-atwinc1500/updating-ssl-certificates)

### Adafruit WICED Feather WiFi

* Latest version of the [Adafruit WICED Arduino Core](https://github.com/adafruit/Adafruit_WICED_Arduino)
* Latest version of the [Adafruit MQTT Library](https://github.com/adafruit/Adafruit_MQTT_Library)

### Adafruit Feather 32u4 FONA

* Latest version of the [Adafruit AVR Arduino Core](https://github.com/adafruit/Adafruit_Arduino_Boards)
* Latest version of the [Adafruit MQTT Library](https://github.com/adafruit/Adafruit_MQTT_Library)
* Latest version of the [Adafruit FONA Library](https://github.com/adafruit/Adafruit_FONA)

### Adafruit Ethernet FeatherWing

The Ethernet FeatherWing will also require a 32u4, M0, or ESP8266 based Feather. Any Arduino cores
required by the host Feather board will also be required.

* Latest version of the [Adafruit Ethernet2 Library](https://github.com/adafruit/Ethernet2)
* Latest version of the [Adafruit MQTT Library](https://github.com/adafruit/Adafruit_MQTT_Library)

## Usage

The included examples sketches will walk you through all of the features of the library.
They can be used on all platforms, but they default to WiFi. To change between platforms,
you will need to change two lines of code in the example. It is recommended that you start with
one of the Adafruit WiFi feathers before moving on to Cellular or Ethernet.

The examples below demonstrate how to switch between platforms.

### WiFi (ESP8266, M0 WINC1500, WICED)

```ino
#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, "your_wifi_ssid", "your_wifi_pass");
```

### Cellular (32u4 FONA)

```ino
#include "AdafruitIO_FONA.h"
AdafruitIO_FONA io(IO_USERNAME, IO_KEY);
```

If you need to set APN info, you can do so by adding a call to `io.setAPN()` after `io.connect()` in the `setup()` function.

```ino
void setup() {

  // start the serial connection
  Serial.begin(115200);

  // connect to io.adafruit.com
  io.connect();

  io.setAPN(F("your_apn"), F("your_apn_user"), F("your_apn_pass"));

}
```

### Ethernet (Ethernet FeatherWing)

```ino
#include "AdafruitIO_Ethernet.h"
AdafruitIO_Ethernet io(IO_USERNAME, IO_KEY);
```

## Compatibility

Last test with `v2.0.0` on 08/10/2016.

Example            | ESP8266      | M0 WINC1500  | WICED       | FONA 32u4   | Ethernet*  |
------------------ | :----------: | :----------: | :---------: | :---------: | :--------: |
00_publish         |      ✓       |      ✓       |      ✓      |      ✓      |      ✓     |
01_subscribe       |      ✓       |      ✓       |      ✓      |      ✓      |      ✓     |
02_pubsub          |      ✓       |      ✓       |      ✓      |      ✓      |      ✓     |
03_multiple_feeds  |      ✓       |      ✓       |      ✓      |      ✓      |      ✓     |
04_location        |      ✓       |      ✓       |      ✓      |      ✓      |      ✓     |
05_type_conversion |      ✓       |      ✓       |      ✓      |      ✓      |      ✓     |

*Ethernet FeatherWing tested with Feather M0 Basic Proto

## License
Copyright (c) 2016 [Adafruit Industries](https://adafruit.com). Licensed under the [MIT license](/LICENSE?raw=true).

[Adafruit](https://adafruit.com) invests time and resources providing this open source code.
Please support Adafruit and open-source hardware by purchasing products from [Adafruit](https://adafruit.com).
