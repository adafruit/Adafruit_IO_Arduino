#include "AdafruitIO_WINC1500.h"

Adafruit_WINC1500 WiFi(WINC_CS, WINC_IRQ, WINC_RST);

AdafruitIO_WINC1500::AdafruitIO_WINC1500(const char *ssid, const char *pass):AdafruitIO()
{
  _ssid = ssid;
  _pass = pass;
  _client = new Adafruit_WINC1500SSLClient;
  _mqtt = new Adafruit_MQTT_Client(_client, _host, _port);
}

AdafruitIO_WINC1500::AdafruitIO_WINC1500(const __FlashStringHelper *ssid, const __FlashStringHelper *pass):AdafruitIO()
{
  _ssid = (const char*)ssid;
  _pass = (const char*)pass;
  _client = new Adafruit_WINC1500SSLClient;
  _mqtt = new Adafruit_MQTT_Client(_client, _host, _port);
}

void AdafruitIO_WINC1500::_connect()
{

  pinMode(WINC_EN, OUTPUT);
  digitalWrite(WINC_EN, HIGH);
  delay(100);

  // no shield? bail
  if(WiFi.status() == WL_NO_SHIELD)
    return;

  WiFi.begin(_ssid, _pass);
  _status = AIO_NET_DISCONNECTED;

}

aio_status_t AdafruitIO_WINC1500::networkStatus()
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
