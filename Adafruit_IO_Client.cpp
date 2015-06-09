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
#include "Adafruit_IO_Client.h"

bool Adafruit_IO_Client::send(const char* feed, const char* value, 
                              const char* key, bool quoted) {
    // Make HTTP POST to send feed data as JSON object.

    // First make sure a connection to the service is available.
    if (!connected()) {
        DEBUG_PRINTLN(F("Failed to connect to service!"));
        return false;
    }

    // Compute size of request.
    uint16_t len = 10 + strlen(value);
    if (quoted) {
        len += 2;
    }

    // Send HTTP POST and headers.
    _client.print(F("POST /api/feeds/"));
    _client.print(feed);
    _client.print(F("/data/send HTTP/1.1\r\n"));
    sendHeaders(key);
    _client.print(F("Content-Type: application/json\r\n"));
    _client.print(F("Content-Length: "));
    _client.print(len, DEC);
    _client.print(F("\r\n\r\n"));

    // Send HTTP POST data.
    _client.print(F("{\"value\":"));
    if (quoted) {
        _client.print('"');
        _client.print(value);
        _client.print('"');
    }
    else {
        _client.print(value);
    }
    _client.print('}');

    // Now wait to read response (up to the client's configured stream timeout).
    // First read the HTTP/1.1 response.
    char recvbuffer[IO_RECV_LENGTH] = {0};
    if ((_client.readBytesUntil(' ', recvbuffer, sizeof(recvbuffer)) != 8) ||
        (strcmp_P(recvbuffer, PSTR("HTTP/1.1")) != 0)) {
        DEBUG_PRINTLN(F("Failed to find expected HTTP/1.1 response!"));
        _client.stop();
        return false;
    }
    // Now read the status code and expect a 200-level response.
    memset(recvbuffer, 0, sizeof(recvbuffer));
    if ((_client.readBytesUntil(' ', recvbuffer, sizeof(recvbuffer)-1) != 3) ||
        (recvbuffer[0] != '2')) {
        DEBUG_PRINT(F("HTTP POST failed with error code: "));
        DEBUG_PRINTLN(recvbuffer);
        _client.stop();
        return false;
    }

    // Ignore parsing the response data for now.  Close connection and return
    // success.
    _client.stop();
    return true;
}

FeedData Adafruit_IO_Client::receive(const char* feed, const char* key) {
    // Make HTTP GET request to read latest feed item and then parse response
    // into FeedData object.

    // First make sure a connection to the service is available.
    if (!connected()) {
        DEBUG_PRINTLN(F("Failed to connect to service!"));
        return FeedData();
    }

    // Send HTTP GET and headers.
    _client.print(F("GET /api/feeds/"));
    _client.print(feed);
    _client.print(F("/data/last.txt HTTP/1.1\r\n"));
    sendHeaders(key);
    _client.print(F("Accept: text/plain\r\n\r\n"));

    // Parse HTTP GET response.
    // First read the HTTP/1.1 response.
    char recvbuffer[IO_RECV_LENGTH] = {0};
    if ((_client.readBytesUntil(' ', recvbuffer, sizeof(recvbuffer)) != 8) ||
        (strcmp_P(recvbuffer, PSTR("HTTP/1.1")) != 0)) {
        DEBUG_PRINTLN(F("Failed to find expected HTTP/1.1 response!"));
        _client.stop();
        return FeedData();
    }
    // Now read the status code and expect a 200-level response.
    memset(recvbuffer, 0, sizeof(recvbuffer));
    if ((_client.readBytesUntil(' ', recvbuffer, sizeof(recvbuffer)-1) != 3) ||
        (recvbuffer[0] != '2')) {
        DEBUG_PRINT(F("HTTP GET failed with error code: "));
        DEBUG_PRINTLN(recvbuffer);
        _client.stop();
        return FeedData();
    }
    // Read the rest of the line.
    if (!_client.find("\r\n")) {
        DEBUG_PRINT(F("Unexpected HTTP GET response!"));
        _client.stop();
        return FeedData();
    }
    // Now parse all the header lines and look for an explicit content length.
    // If no content length is found then assume a chunked transfer encoding.
    uint16_t len = 0;
    while (true) {
        char c = _client.peek();
        // Check for \r\n blank line to signify end of headers.
        if (c == '\r') {
            if (!_client.find("\r\n")) {
                // Something unexpected, fail.
                DEBUG_PRINT(F("Expected blank line after headers!"));
                _client.stop();
                return FeedData();
            }
            // Else found the end of the headers so stop parsing them.
            break;
        }
        // Parse a header name.
        char recvbuffer[IO_RECV_LENGTH] = {0};
        if (!_client.readBytesUntil(':', recvbuffer, sizeof(recvbuffer)-1)) {
            DEBUG_PRINT(F("Expected header name!"));
            _client.stop();
            return FeedData();
        }
        // Check for content-length header and read its value, otherwise just
        // swallow the header value.
        if (strcmp_P(recvbuffer, PSTR("Content-Length")) == 0) {
            len = (uint16_t)_client.parseInt();
        }
        if (!_client.find("\r\n")) {
            DEBUG_PRINT(F("Failed to find end of header line!"));
            _client.stop();
            return FeedData();
        }
    }
    // If we didn't see a content-length header then assume a chunked transfer
    // encoding and read the length as the first line.
    if (len == 0) {
        len = (uint16_t)_client.parseInt();
        if (!_client.find("\r\n")) {
            DEBUG_PRINT(F("Failed to find end of chunk size line!"));
            _client.stop();
            return FeedData();
        }
    }

    // Let FeedData parse out the result.
    return FeedData(_client, len);
}

bool Adafruit_IO_Client::connected() {
    // Create connection to AIO service.  Return true if successful and connection
    // is open, or false if something failed.

    // If connection is already open close it to start fresh.
    if (_client.connected()) {
        _client.stop();
    }

    // Create connection.
    return _client.connect(_serviceHost, _servicePort) != 0;
}

void Adafruit_IO_Client::sendHeaders(const char* key) {
    // Send standard HTTP headers used by AIO REST requests.
    _client.print(F("Connection: close\r\n"));
    _client.print(F("User-Agent: Adafruit_IO_Client\r\n"));
    _client.print(F("Host: "));
    _client.print(_serviceHost);
    _client.print(':');
    _client.print(_servicePort, DEC);
    _client.print(F("\r\n"));
    _client.print(F("X-AIO-Key: "));
    _client.print(key);
    _client.print(F("\r\n"));
}
