# Adafruit IO Arduino Library

Arduino library to access the Adafruit IO REST API on platforms like the FONA,
CC3000, and ESP8266.  This is a good library for simple send and receive access
to Adafruit IO feeds.  Unlike MQTT the REST API does not require a connection to
be kept alive so it's good for things to periodically need to connect and 
send/receive values.  For example a sensor device that sends sensor measurements
to AIO and then enters deep power-saving sleep for a period is perfect to use
with this library.

Currently FONA is the only supported platform, however support for the CC3000
and ESP8266 is planned and coming soon.
