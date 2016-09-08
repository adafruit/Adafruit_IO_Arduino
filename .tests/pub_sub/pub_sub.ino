#include <ArduinoTap.h>
#include "config.h"

/************************ Example Starts Here *******************************/

AdafruitIO_Feed *pubsub = io.feed("pubsub");
char time[] = __TIME__;

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  delay(3000);

  plan(2);

  io.connect();
  pubsub->onMessage(handleMessage);

  while(io.status() < AIO_CONNECTED) {
    delay(500);
  }

  ok(io.status() > AIO_CONNECTED, "connected to IO");
  ok(pubsub->save(time), "sent message");

}

void loop() {
  io.run();
}

void handleMessage(AdafruitIO_Data *data) {
  ok(compareChar(time, data->value()), "message received");
  done_testing();
}


bool compareChar(char *a, char *b)
{
  return strcmp(a,b) == 0;
}

