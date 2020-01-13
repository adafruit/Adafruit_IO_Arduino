/*!
 * @file AdafruitIO.cpp
 *
 * @mainpage Adafruit IO Arduino Client Library
 *
 * @section intro_sec Introduction
 *
 * This is the documentation for the Adafruit IO Arduino library. This library
 * provides a simple device independent interface for interacting with Adafruit
 * IO using Arduino. It allows you to switch between WiFi (ESP8266, ESP32,
 * AirLift, WINC1500, & WICED), Cellular (32u4 FONA), and Ethernet (Ethernet
 * FeatherWing)
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * @section dependencies Dependencies
 *
 * This library depends on <a
 * href="https://github.com/arduino-libraries/ArduinoHttpClient">
 * ArduinoHTTPClient</a> and <a
 * href="https://github.com/adafruit/Adafruit_MQTT_Library"> Adafruit MQTT
 * Library</a> being present on your system. Please make sure you have installed
 * the latest version before using this library.
 *
 * @section author Author
 *
 * Written by Tony DiCola, Todd Treece for Adafruit Industries
 *
 * @section license License
 *
 * BSD license, all text here must be included in any redistribution.
 *
 */
#include "AdafruitIO.h"

/**************************************************************************/
/*!
    @brief    Instantiate the AIO object.
    @param    user
              A pointer to a constant AIO user name.
    @param    key
              A pointer to a constant key for the user name.
*/
/**************************************************************************/
AdafruitIO::AdafruitIO(const char *user, const char *key) {
  _mqtt = 0;
  _http = 0;
  _username = user;
  _key = key;
  _err_topic = 0;
  _throttle_topic = 0;
  _err_sub = 0;
  _throttle_sub = 0;
  _packetread_timeout = 100;
  _user_agent = 0;

  _init();
}

/**************************************************************************/
/*!
    @brief    Initialize the AIO object.
*/
/**************************************************************************/
void AdafruitIO::_init() {

  // we have never pinged, so set last ping to now
  _last_ping = millis();

  // dynamically allocate memory for err topic
  _err_topic = (char *)malloc(
      sizeof(char) * (strlen(_username) + strlen(AIO_ERROR_TOPIC) + 1));

  if (_err_topic) {

    // build error topic
    strcpy(_err_topic, _username);
    strcat(_err_topic, AIO_ERROR_TOPIC);

  } else {

    // malloc failed
    _err_topic = 0;
  }

  // dynamically allocate memory for throttle topic
  _throttle_topic = (char *)malloc(
      sizeof(char) * (strlen(_username) + strlen(AIO_THROTTLE_TOPIC) + 1));

  if (_throttle_topic) {

    // build throttle topic
    strcpy(_throttle_topic, _username);
    strcat(_throttle_topic, AIO_THROTTLE_TOPIC);

  } else {

    // malloc failed
    _throttle_topic = 0;
  }
}

/**************************************************************************/
/*!
    @brief    Destructor to end the AIO object.
*/
/**************************************************************************/
AdafruitIO::~AdafruitIO() {
  if (_err_topic)
    free(_err_topic);

  if (_throttle_topic)
    free(_throttle_topic);

  if (_err_sub)
    delete _err_sub;

  if (_throttle_sub)
    delete _throttle_sub;
}

/**************************************************************************/
/*!
    @brief    Prints errors
    @param    err
              An error string to print.
    @param    len
              The length of the error string.
*/
/**************************************************************************/
void errorCallback(char *err, uint16_t len) {
  AIO_ERROR_PRINTLN();
  AIO_ERROR_PRINT("ERROR: ");
  AIO_ERROR_PRINTLN(err);
  AIO_ERROR_PRINTLN();
}

/**************************************************************************/
/*!
    @brief    Connects to AIO, setting up using parameters set when the
              class is instantiated.
*/
/**************************************************************************/
void AdafruitIO::connect() {

  AIO_DEBUG_PRINTLN("AdafruitIO::connect()");

  _last_mqtt_connect = 0; // need to start over fresh
  _status = AIO_IDLE;
  _last_ping = 0;

  if (_err_sub) {
    // setup error sub
    _err_sub = new Adafruit_MQTT_Subscribe(_mqtt, _err_topic);
    _mqtt->subscribe(_err_sub);
    _err_sub->setCallback(errorCallback);
  }

  if (_throttle_sub) {
    // setup throttle sub
    _throttle_sub = new Adafruit_MQTT_Subscribe(_mqtt, _throttle_topic);
    _mqtt->subscribe(_throttle_sub);
    _throttle_sub->setCallback(errorCallback);
  }

  _connect();
}

/**************************************************************************/
/*!
    @brief    Disconnects from WiFi.
*/
/**************************************************************************/
void AdafruitIO::wifi_disconnect() {

  AIO_DEBUG_PRINTLN("AdafruitIO::wifi_disconnect()");

  _disconnect();
}

/**************************************************************************/
/*!
    @brief    Create a new AIO feed.
    @param    name
              The AIO name of the feed.
    @return   A pointer to the feed.
*/
/**************************************************************************/
AdafruitIO_Feed *AdafruitIO::feed(const char *name) {
  return new AdafruitIO_Feed(this, name);
}

/**************************************************************************/
/*!
    @brief    Create a new AIO feed.
    @param    name
              The AIO name of the feed.
    @param    owner
              The AIO name of the user that owns the feed, if not the current
   user.
    @return   A pointer to the feed.
*/
/**************************************************************************/
AdafruitIO_Feed *AdafruitIO::feed(const char *name, const char *owner) {
  return new AdafruitIO_Feed(this, name, owner);
}

/**************************************************************************/
/*!
    @brief    Create a new AIO time.
    @param    format
              A format specifier.
    @return   A pointer to the time.
*/
/**************************************************************************/
AdafruitIO_Time *AdafruitIO::time(aio_time_format_t format) {
  return new AdafruitIO_Time(this, format);
}

/**************************************************************************/
/*!
    @brief    Create a new AIO group.
    @param    name
              The AIO name of the group.
    @return   A pointer to the group.
*/
/**************************************************************************/
AdafruitIO_Group *AdafruitIO::group(const char *name) {
  return new AdafruitIO_Group(this, name);
}

/**************************************************************************/
/*!
    @brief    Create a new AIO dashboard.
    @param    name
              The AIO name of the dashboard.
    @return   A pointer to the dashboard.
*/
/**************************************************************************/
AdafruitIO_Dashboard *AdafruitIO::dashboard(const char *name) {
  return new AdafruitIO_Dashboard(this, name);
}

/**************************************************************************/
/*!
    @brief    Provide status explanation strings.
    @param    _status
              The AIO status value
    @return   A pointer to the status string.
*/
/**************************************************************************/
const __FlashStringHelper *AdafruitIO::statusText() {
  switch (_status) {

  // CONNECTING
  case AIO_IDLE:
    return F("Idle. Waiting for connect to be called...");
  case AIO_NET_DISCONNECTED:
    return F("Network disconnected.");
  case AIO_DISCONNECTED:
    return F("Disconnected from Adafruit IO.");

  // FAILURE
  case AIO_NET_CONNECT_FAILED:
    return F("Network connection failed.");
  case AIO_CONNECT_FAILED:
    return F("Adafruit IO connection failed.");
  case AIO_FINGERPRINT_INVALID:
    return F("Adafruit IO SSL fingerprint verification failed.");
  case AIO_AUTH_FAILED:
    return F("Adafruit IO authentication failed.");

  // SUCCESS
  case AIO_NET_CONNECTED:
    return F("Network connected.");
  case AIO_CONNECTED:
    return F("Adafruit IO connected.");
  case AIO_CONNECTED_INSECURE:
    return F("Adafruit IO connected. **THIS CONNECTION IS INSECURE** SSL/TLS "
             "not supported for this platform.");
  case AIO_FINGERPRINT_UNSUPPORTED:
    return F("Adafruit IO connected over SSL/TLS. Fingerprint verification "
             "unsupported.");
  case AIO_FINGERPRINT_VALID:
    return F("Adafruit IO connected over SSL/TLS. Fingerprint valid.");

  default:
    return F("Unknown status code");
  }
}

/**************************************************************************/
/*!
    @brief    Must be called frequently to keep AIO connections alive. When
              called with no arguments run() will try to repair MQTT and WiFi
              connections before returning. To avoid potentially long timeout
              delays, sketches can use the busywait_ms and fail_fast arguments
              to return an imperfect status quickly. The calling sketch will
              then need to respond appropriately to that status.
    @param    busywait_ms
              The packet read timeout, optional.
    @param    fail_fast
              Set true to skip retries and return with status immediately,
   optional.
    @return   AIO status value
*/
/**************************************************************************/
aio_status_t AdafruitIO::run(uint16_t busywait_ms, bool fail_fast) {
  uint32_t timeStart = millis();
  if (status() < AIO_NET_CONNECTED) { // If we aren't network connected...
    if (fail_fast)
      return status(); // return status and fail quickly
    else {             // or try to reconnect from the start
      AIO_ERROR_PRINT("run() connection failed -- retrying");
      unsigned long started = millis();
      connect();
      // wait for a full AIO connection then carry on
      while (status() < AIO_CONNECTED) {
        // or return an error if the reconnection times out
        if (millis() - started > AIO_NET_CONNECTION_TIMEOUT)
          return status();
        delay(500);
      }
    }
  }

  // loop until we have a connection
  // mqttStatus() will try to reconnect before returning
  while (mqttStatus(fail_fast) != AIO_CONNECTED &&
         millis() - timeStart < AIO_MQTT_CONNECTION_TIMEOUT) {
  }
  if (mqttStatus(fail_fast) != AIO_CONNECTED)
    return status();

  if (busywait_ms > 0)
    _packetread_timeout = busywait_ms;

  _mqtt->processPackets(_packetread_timeout);

  // ping to keep connection alive if needed
  if (millis() > (_last_ping + AIO_PING_INTERVAL)) {
    _mqtt->ping();
    _last_ping = millis();
  }
  return status();
}

/**************************************************************************/
/*!
    @brief    Status check.
    @return   An AIO status value. Lower values represent poorer connection
              status.
*/
/**************************************************************************/
aio_status_t AdafruitIO::status() {
  aio_status_t net_status = networkStatus();

  // if we aren't connected, return network status
  if (net_status != AIO_NET_CONNECTED) {
    _status = net_status;
    return _status;
  }

  // check mqtt status and return
  _status = mqttStatus();
  return _status;
}

/**************************************************************************/
/*!
    @brief    Identify the board.
    @return   A board ID
*/
/**************************************************************************/
char *AdafruitIO::boardID() { return AdafruitIO_Board::id(); }

/**************************************************************************/
/*!
    @brief    Identify the board type.
    @return   A board type
*/
/**************************************************************************/
const char *AdafruitIO::boardType() { return AdafruitIO_Board::type(); }

/**************************************************************************/
/*!
    @brief    Identify the software version.
    @return   A pointer to a version number string.
*/
/**************************************************************************/
char *AdafruitIO::version() {
  sprintf(_version, "%d.%d.%d", ADAFRUITIO_VERSION_MAJOR,
          ADAFRUITIO_VERSION_MINOR, ADAFRUITIO_VERSION_PATCH);
  return _version;
}

/**************************************************************************/
/*!
    @brief    Identify the user agent.
    @return   A pointer to a user agent string.
*/
/**************************************************************************/
char *AdafruitIO::userAgent() {
  if (!_user_agent) {
    _user_agent =
        (char *)malloc(sizeof(char) * (strlen(version()) + strlen(boardType()) +
                                       strlen(connectionType()) + 24));
    strcpy(_user_agent, "AdafruitIO-Arduino/");
    strcat(_user_agent, version());
    strcat(_user_agent, " (");
    strcat(_user_agent, boardType());
    strcat(_user_agent, "-");
    strcat(_user_agent, connectionType());
    strcat(_user_agent, ")");
  }
  return _user_agent;
}

/**************************************************************************/
/*!
    @brief    Checks connection status with Adafruit IO's MQTT broker.
    @param    fail_fast
              Set true to skip retries and return with status immediately.
    @return   True if connected, otherwise False.
*/
/**************************************************************************/
aio_status_t AdafruitIO::mqttStatus(bool fail_fast) {
  // if the connection failed,
  // return so we don't hammer IO
  if (_status == AIO_CONNECT_FAILED) {
    AIO_ERROR_PRINT("mqttStatus() failed to connect");
    AIO_ERROR_PRINTLN(_mqtt->connectErrorString(_status));
    return _status;
  }

  if (_mqtt->connected())
    return AIO_CONNECTED;

  // prevent fast reconnect attempts, except for the first time through
  if (_last_mqtt_connect == 0 ||
      millis() - _last_mqtt_connect > AIO_THROTTLE_RECONNECT_INTERVAL) {
    _last_mqtt_connect = millis();
    switch (_mqtt->connect(_username, _key)) {
    case 0:
      return AIO_CONNECTED;
    case 1: // invalid mqtt protocol
    case 2: // client id rejected
    case 4: // malformed user/pass
    case 5: // unauthorized
      return AIO_CONNECT_FAILED;
    case 3: // mqtt service unavailable
    case 6: // throttled
    case 7: // banned -> all MQTT bans are temporary, so eventual retry is
            // permitted
      // delay to prevent fast reconnects and fast returns (backward
      // compatibility)
      if (!fail_fast)
        delay(AIO_THROTTLE_RECONNECT_INTERVAL);
      return AIO_DISCONNECTED;
    default:
      return AIO_DISCONNECTED;
    }
  }
  return AIO_DISCONNECTED;
}
