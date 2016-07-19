#include "AdafruitIO_ESP8266.h"
AdafruitIO_ESP8266::AdafruitIO_ESP8266(const char *ssid, const char *pass):AdafruitIO()
{
  _ssid = ssid;
  _pass = pass;
  _client = new WiFiClientSecure;
  _mqtt = new Adafruit_MQTT_Client(_client, _host, _port);
}

AdafruitIO_ESP8266::AdafruitIO_ESP8266(const __FlashStringHelper *ssid, const __FlashStringHelper *pass):AdafruitIO()
{
  _ssid = (const char*)ssid;
  _pass = (const char*)pass;
  _client = new WiFiClientSecure;
  _mqtt = new Adafruit_MQTT_Client(_client, _host, _port);
}

void AdafruitIO_ESP8266::_connect()
{

  delay(100);
  WiFi.begin(_ssid, _pass);
  delay(100);
  _status = AIO_NET_DISCONNECTED;

}

aio_status_t AdafruitIO_ESP8266::status()
{

  aio_status_t net_status = networkStatus();

  // if we aren't connected, return network status
  if(net_status != AIO_NET_CONNECTED) {
    _status = net_status;
    return _status;
  }

  // check mqtt status and return
  _status = mqttStatus();
  return _status;

}

aio_status_t AdafruitIO_ESP8266::networkStatus()
{

  switch(WiFi.status()) {
    case WL_CONNECTED:
      return AIO_NET_CONNECTED;
    case WL_CONNECT_FAILED:
      return AIO_NET_CONNECT_FAILED;
    case WL_IDLE_STATUS:
      return AIO_IDLE;
    default:
      return AIO_NET_DISCONNECTED;
  }

}

aio_status_t AdafruitIO_ESP8266::mqttStatus()
{

  // if the connection failed,
  // return so we don't hammer IO
  if(_status == AIO_CONNECT_FAILED)
    return _status;

  if(_mqtt->connected())
    return AIO_CONNECTED;

  switch(_mqtt->connect(_username, _key)) {
    case 0:
      return AIO_CONNECTED;
    case 1:   // invalid mqtt protocol
    case 2:   // client id rejected
    case 4:   // malformed user/pass
    case 5:   // unauthorized
    case 7:   // banned
    case -1:  // general failure
      return AIO_CONNECT_FAILED;
    case 3: // mqtt service unavailable
    case 6: // throttled
      delay(60000); // wait 60 seconds
      return AIO_DISCONNECTED;
    default:
      return AIO_DISCONNECTED;
  }

}

