// The MIT License (MIT)
//
// Copyright (c) 2015 Adafruit Industries
// Author: Tony DiCola
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#ifndef ADAFRUIT_IO_CLIENT_H
#define ADAFRUIT_IO_CLIENT_H

#include "Client.h"
#include "Adafruit_IO_Arduino.h"


// Arduino Client class implementation of AIO REST service.  Good for using with
// hardware like the ESP8266 or Ethernet shield.
class Adafruit_IO_Client: public AIOService {
public:
    Adafruit_IO_Client(Client& client, const char* defaultKey,
                       const char* serviceHost = "io.adafruit.com",
                       uint16_t servicePort = 80):
        _client(client),
        _defaultKey(defaultKey),
        _serviceHost(serviceHost),
        _servicePort(servicePort)
    {}

    Adafruit_IO_Feed getFeed(const char* name, const char* key = NULL) {
        return Adafruit_IO_Feed(name, key == NULL ? _defaultKey : key, this);
    }

    bool begin() {}  // Nothing to do, no initialization required.

    virtual bool send(const char* feed, const char* value, const char* key, 
                      bool quoted);

    virtual FeedData receive(const char* feed, const char* key);

private:
    Client& _client;
    const char* _defaultKey;
    const char* _serviceHost;
    uint16_t _servicePort;

    bool connected();
    void sendHeaders(const char* key);
};

#endif