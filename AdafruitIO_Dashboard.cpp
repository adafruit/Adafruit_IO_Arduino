//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Copyright (c) 2015-2016 Adafruit Industries
// Authors: Tony DiCola, Todd Treece
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.
//
#include "AdafruitIO_Dashboard.h"
#include "AdafruitIO.h"

AdafruitIO_Dashboard::AdafruitIO_Dashboard(AdafruitIO *io, const char *n)
{
  _io = io;
  name = n;
}

AdafruitIO_Dashboard::~AdafruitIO_Dashboard(){}

bool AdafruitIO_Dashboard::exists()
{
  String url = "/api/v2/";
  url += _io->_username;
  url += "/dashboards/";
  url += name;

  _io->_http->startRequest(url.c_str(), HTTP_METHOD_GET);
  _io->_http->sendHeader("X-AIO-Key", _io->_key);
  _io->_http->endRequest();

  int status = _io->_http->responseStatusCode();
  _io->_http->responseBody(); // needs to be read even if not used

  return status == 200;
}

bool AdafruitIO_Dashboard::create()
{
  String url = "/api/v2/";
  url += _io->_username;
  url += "/dashboards";

  String body = "name=";
  body += name;

  _io->_http->startRequest(url.c_str(), HTTP_METHOD_POST);
  _io->_http->sendHeader(HTTP_HEADER_CONTENT_TYPE, "application/x-www-form-urlencoded");
  _io->_http->sendHeader(HTTP_HEADER_CONTENT_LENGTH, body.length());
  _io->_http->sendHeader("X-AIO-Key", _io->_key);
  _io->_http->endRequest();
  _io->_http->write((const byte*)body.c_str(), body.length());

  int status = _io->_http->responseStatusCode();
  _io->_http->responseBody(); // needs to be read even if not used

  return status == 201;
}

