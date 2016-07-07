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
#ifndef ADAFRUIT_IO_ARDUINO_H
#define ADAFRUIT_IO_ARDUINO_H

#include "Arduino.h"

// Control how big the buffer is for storing a data instance's value.
// Keep at least a value of ~41 to store large numeric and float values.
#define FEEDDATA_LENGTH 41

// How large the received data buffer is in bytes.  This is used for reading
// the response of HTTP requests like header names and response codes.
#define IO_RECV_LENGTH 33

// Uncomment/comment to enable & disable debug output.
//#define ADAFRUIT_IO_DEBUG

// Macros for debug output (only enabled when debug mode is enabled.)
#ifdef ADAFRUIT_IO_DEBUG
    #define DEBUG_PRINT(...) { Serial.print(__VA_ARGS__); }
    #define DEBUG_PRINTLN(...) { Serial.println(__VA_ARGS__); }
#else
    #define DEBUG_PRINT(...) {}
    #define DEBUG_PRINTLN(...) {}
#endif


// Adafruit IO feed data instance.  Exposes functions to read the value of the
// feed as different types.
class FeedData {
public:
    FeedData();
    FeedData(const FeedData& copy);
    FeedData(const char* value);
    FeedData(Stream& stream, uint16_t length, uint32_t timeoutMS = 5000);

    // Functions to support checking if this data instance was able to be read
    // from the AIO service.
    bool isValid() { return _value != NULL; }

    // Allow implicit conversion to a C string.
    operator char*() { return _value; }

    // Explicit conversion functions that convert to the specified value.  Each
    // will return true if the conversion succeeded and false if it could not
    // be converted.
    bool intValue(int* value);
    bool uintValue(unsigned int* value);
    bool longValue(long* value);
    bool ulongValue(unsigned long* value);
    bool floatValue(float* value);
    bool doubleValue(double* value);

private:
    char _value[FEEDDATA_LENGTH];
};


// Interface for an AIO service that defines functions to send and receive data
// to the AIO REST API.  Concrete implementations for FONA, CC3000, and ESP8266
// are what users will actually use.
class AIOService {
public:
    virtual ~AIOService() {}
    virtual bool send(const char* feed, const char* value, const char* key,
                      bool quoted) = 0;
    virtual FeedData receive(const char* feed, const char* key) = 0;
};


// Main IO feed class that uses an AIO service reference to send and receive
// data with IO.
class Adafruit_IO_Feed {
public:
    Adafruit_IO_Feed(const char* name, const char* key, AIOService* adapter):
        _name(name), _key(key), _adapter(adapter)
    {}

    bool send(const char* value) {
        return _adapter->send(_name, value, _key, true);
    }
    bool send(int value);
    bool send(unsigned int value);
    bool send(long value);
    bool send(unsigned long value);
    bool send(float value, int precision=6);
    bool send(double value, int precision=6);

    FeedData receive() {
        return _adapter->receive(_name, _key);
    }

private:
    const char* _name;
    const char* _key;
    AIOService* _adapter;
};


#endif
