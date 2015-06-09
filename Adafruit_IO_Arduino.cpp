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
#include "Adafruit_IO_Arduino.h"

FeedData::FeedData() {
    // Feed data is invalid without a value so write all zeros.
    memset(_value, 0, sizeof(_value));
}

FeedData::FeedData(const FeedData& copy) {
    // Copy the value from the provided FeedData object.
    memset(_value, 0, sizeof(_value));
    strncpy(_value, copy._value, sizeof(_value)-1);
}

FeedData::FeedData(const char* value) {
    // Copy the provided string value as the feed data value.
    memset(_value, 0, sizeof(_value));
    strncpy(_value, value, FEEDDATA_LENGTH-1);
}

FeedData::FeedData(Stream& stream, uint16_t length, uint32_t timeoutMS) {
    // Load the data value from the provided stream.  Will read a value up to
    // length characters in size.  If the data can't be read for some reason,
    // like the timeout exceeding, then the FeedData will be left in an invalid
    // state.
    memset(_value, 0, sizeof(_value));
    if (length > FEEDDATA_LENGTH-1) {
        // Not enough space to store the value.
        DEBUG_PRINTLN(F("Not enough space to store feed data!"));
        return;
    }
    stream.setTimeout(timeoutMS);
    if (stream.readBytes(_value, length) != length) {
        // Didn't find enough data, set the value as invalid.
        DEBUG_PRINTLN(F("Failed to find expected data!"));
        memset(_value, 0, sizeof(_value));
    }
}

bool FeedData::intValue(int* value) {
    // Attempt to convert the value to an integer.  Returns true if it succeeds,
    // and false if it fails for some reason.
    char* endptr;
    *value = (int)strtol(_value, &endptr, 10);
    return (*_value != 0 && *endptr == 0);
}

bool FeedData::uintValue(unsigned int* value) {
    // Attempt to convert the value to an unsigned integer.  Returns true if it
    // succeeds, and false if it fails for some reason.
    char* endptr;
    #ifdef ESP8266
        // For some reason strtoul is not defined on the ESP8266 platform right now.
        // Just use a strtol function and hope for the best.
        *value = (unsigned int)strtol(_value, &endptr, 10);
    #else
        *value = (unsigned int)strtoul(_value, &endptr, 10);
    #endif
    return (*_value != 0 && *endptr == 0);
}

bool FeedData::longValue(long* value) {
    // Attempt to convert the value to a long.  Returns true if it
    // succeeds, and false if it fails for some reason.
    char* endptr;
    *value = strtol(_value, &endptr, 10);
    return (*_value != 0 && *endptr == 0);
}

bool FeedData::ulongValue(unsigned long* value) {
    // Attempt to convert the value to an unsigned long.  Returns true if it
    // succeeds, and false if it fails for some reason.
    char* endptr;
    #ifdef ESP8266
        // For some reason strtoul is not defined on the ESP8266 platform right now.
        // Just use a strtol function and hope for the best.
        *value = (unsigned long)strtol(_value, &endptr, 10);
    #else
        *value = strtoul(_value, &endptr, 10);
    #endif
    return (*_value != 0 && *endptr == 0);  
}

bool FeedData::floatValue(float* value) {
    // Attempt to convert the value to a float.  Returns true if it succeeds,
    // and false if it fails for some reason.
    char* endptr;
    *value = (float)strtod(_value, &endptr);
    return (*_value != 0 && *endptr == 0);
}

bool FeedData::doubleValue(double* value) {
    // Attempt to convert the value to a double.  Returns true if it succeeds,
    // and false if it fails for some reason.
    char* endptr;
    *value = strtod(_value, &endptr);
    return (*_value != 0 && *endptr == 0);
}

// Buffer to store values converted from numbers to strings before sending to IO.
static char _converted[FEEDDATA_LENGTH];

bool Adafruit_IO_Feed::send(int value) {
    // Convert int to string, then send the value (being careful not to quote it).
    memset(_converted, 0, sizeof(_converted));
    itoa(value, _converted, 10);
    return _adapter->send(_name, _converted, _key, false);
}

bool Adafruit_IO_Feed::send(unsigned int value) {
    // Convert uint to string, then send the value (being careful not to quote it).
    memset(_converted, 0, sizeof(_converted));
    utoa(value, _converted, 10);
    return _adapter->send(_name, _converted, _key, false);
}

bool Adafruit_IO_Feed::send(long value) {
    // Convert long to string, then send the value (being careful not to quote it).
    memset(_converted, 0, sizeof(_converted));
    ltoa(value, _converted, 10);
    return _adapter->send(_name, _converted, _key, false);
}

bool Adafruit_IO_Feed::send(unsigned long value) {
    // Convert ulong to string, then send the value (being careful not to quote it).
    memset(_converted, 0, sizeof(_converted));
    ultoa(value, _converted, 10);
    return _adapter->send(_name, _converted, _key, false);
}

bool Adafruit_IO_Feed::send(float value) {
    // Convert float to string using scientific notation, then send the value 
    // (being careful not to quote it).
    memset(_converted, 0, sizeof(_converted));
    #if defined(ARDUINO_ARCH_AVR)
        // Use avrlibc dtostre function on AVR platforms.
        dtostre(value, _converted, 10, 0);
    #else
        // Otherwise fall back to snprintf on other platforms.
        snprintf(_converted, sizeof(_converted)-1, "%f", value);
    #endif
    return _adapter->send(_name, _converted, _key, false);
}

bool Adafruit_IO_Feed::send(double value) {
    // Convert double to string using scientific notation, then send the value 
    // (being careful not to quote it).
    memset(_converted, 0, sizeof(_converted));
    #if defined(ARDUINO_ARCH_AVR)
        // Use avrlibc dtostre function on AVR platforms.
        dtostre(value, _converted, 10, 0);
    #else
        // Otherwise fall back to snprintf on other platforms.
        snprintf(_converted, sizeof(_converted)-1, "%f", value);
    #endif
    return _adapter->send(_name, _converted, _key, false);
}
