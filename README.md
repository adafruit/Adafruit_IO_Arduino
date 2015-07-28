# Adafruit IO Arduino Library [![Build Status](https://travis-ci.org/adafruit/Adafruit_IO_Arduino.svg?branch=master)](https://travis-ci.org/adafruit/Adafruit_IO_Arduino)

Arduino library to access the Adafruit IO REST API on platforms like the FONA,
CC3000, and ESP8266.  This is a good library for simple send and receive access
to Adafruit IO feeds.  Unlike MQTT the REST API does not require a connection to
be kept alive so it's good for things to periodically need to connect and 
send/receive values.  For example a sensor device that sends sensor measurements
to AIO and then enters deep power-saving sleep for a period is perfect to use
with this library.

An alternative is the [Adafruit MQTT library](https://github.com/adafruit/Adafruit_MQTT_Library) 
which uses the MQTT protocol to talk to Adafruit IO.  This is good for devices
that are always on and need to keep a connection alive to to be quickly notified
of changes.

Currently this library supports the send API to send a value to a feed and the
receive/last API to get the latest value from a feed.

The supported platforms are the Adafruit CC3000, FONA, and ESP8266 Arduino.
