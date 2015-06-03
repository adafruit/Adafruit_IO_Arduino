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
#ifndef ADAFRUIT_IO_FONA_H
#define ADAFRUIT_IO_FONA_H

#include "Adafruit_IO_Arduino.h"

// FONA-specific implementation of the AIO service.  Note that this is a
// header-only class to work around the fact that Arduino compiles all cpp files
// inside a library (which would require all platforms to reference all other
// potential platforms).
class Adafruit_IO_FONA: public AIOService {
public:
    Adafruit_IO_FONA(Adafruit_FONA& fona, const char* defaultKey,
                     const char* serviceUrl = "http://io.adafruit.com"):
        _fona(fona),
        _defaultKey(defaultKey),
        _serviceUrl(serviceUrl)
    {}

    Adafruit_IO_Feed getFeed(const char* name, const char* key = NULL) {
        return Adafruit_IO_Feed(name, key == NULL ? _defaultKey : key, this);
    }

    bool begin() {
        // Make sure GPRS is turned on.
        _fona.enableGPRS(true);    
    }

    virtual bool send(const char* feed, const char* value, const char* key, 
                      bool quoted) {
        // Make HTTP POST to send feed data as JSON object.

        // Make sure GPRS is connected.
        if (_fona.GPRSstate() != 1) {
            DEBUG_PRINTLN(F("GPRS is not enabled!"));
            return false;
        }

        // Setup FONA for HTTP POST.
        _fona.HTTP_term();  // Stop any pending request.
        bool r = _fona.HTTP_init();
        r &= _fona.HTTP_para(F("CID"), 1);
        _fona.HTTP_para_start(F("URL"));
        _fona.print(_serviceUrl);
        _fona.print(F("/api/feeds/"));
        _fona.print(feed);
        _fona.print(F("/data/send?X-AIO-Key="));
        _fona.print(key);
        r &= _fona.HTTP_para_end();
        r &= _fona.HTTP_para(F("CONTENT"), F("application/json"));
        if (!r) {
            DEBUG_PRINTLN(F("HTTP POST parameters failed!"));
            return false;
        }

        // Send HTTP POST data.
        if (quoted) {
            // Handle if the value should be surrounded in quotes.
            if (!_fona.HTTP_data(12+strlen(value), 10000)) {
                DEBUG_PRINTLN(F("HTTP POST data failed!"));
                return false;
            }
            _fona.print(F("{\"value\":\""));
            _fona.print(value);
            _fona.print(F("\"}"));
        }
        else {
            // Handle if the value should not be in quotes.
            if (!_fona.HTTP_data(10+strlen(value), 10000)) {
                DEBUG_PRINTLN(F("HTTP POST data failed!"));
                return false;
            }
            _fona.print(F("{\"value\":"));
            _fona.print(value);
            _fona.print(F("}"));
        }

        // Verify OK response.
        if (!_fona.expectReply(F("OK"))) {
            DEBUG_PRINTLN(F("HTTP POST data response failed!"));
            return false;
        }

        // Send HTTP POST request.
        uint16_t status;
        uint16_t datalen;
        if (!_fona.HTTP_action(FONA_HTTP_POST, &status, &datalen)) {
            DEBUG_PRINTLN(F("HTTP POST failed!"));
            return false;
        }

        // Verify response succeeded (is a 200-level response).
        if (status < 200 || status >= 300) {
            DEBUG_PRINT(F("HTTP POST status failure: "));
            DEBUG_PRINTLN(status);
            return false;
        }

        // Ignore parsing the response data for now.
        return true;
    }

    virtual FeedData receive(const char* feed, const char* key) {
        // Make HTTP GET request to read latest feed item and then parse response
        // into FeedData object.

        // Make sure GPRS is connected.
        if (_fona.GPRSstate() != 1) {
            DEBUG_PRINTLN(F("GPRS is not enabled!"));
            return false;
        }

        // Setup FONA for HTTP POST.
        _fona.HTTP_term();  // Stop any pending request.
        bool r = _fona.HTTP_init();
        r &= _fona.HTTP_para(F("CID"), 1);
        _fona.HTTP_para_start(F("URL"));
        _fona.print(_serviceUrl);
        _fona.print(F("/api/feeds/"));
        _fona.print(feed);
        _fona.print(F("/data/last.txt?X-AIO-Key="));
        _fona.print(key);
        r &= _fona.HTTP_para_end();
        if (!r) {
            DEBUG_PRINTLN(F("HTTP parameters failed!"));
            return false;
        }

        // Send HTTP GET request.
        uint16_t status;
        uint16_t datalen;
        if (!_fona.HTTP_action(FONA_HTTP_GET, &status, &datalen)) {
            DEBUG_PRINTLN(F("HTTP GET failed!"));
            return false;
        }

        // Verify response succeeded (is a 200-level response).
        if (status < 200 || status >= 300) {
            DEBUG_PRINT(F("HTTP GET status failure: "));
            DEBUG_PRINTLN(status);
            return false;
        }

        // Read HTTP response data
        if (!_fona.HTTP_readall(&datalen)) {
            DEBUG_PRINTLN(F("HTTP GET read failed!"));
            return false;
        }
        return FeedData(_fona, datalen);
    }

private:
    Adafruit_FONA& _fona;
    const char* _defaultKey;
    const char* _serviceUrl;
};

#endif