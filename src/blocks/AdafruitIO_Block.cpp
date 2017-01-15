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
#include "AdafruitIO_Block.h"
#include "AdafruitIO.h"
#include "AdafruitIO_Dashboard.h"

AdafruitIO_Block::AdafruitIO_Block(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f)
{
  _dashboard = d;
  _feed = f;
}

AdafruitIO_Block::~AdafruitIO_Block(){}

String AdafruitIO_Block::properties()
{
  String props = "{}";
  return props;
}

String AdafruitIO_Block::dimensions()
{
  String dim = "\",\"size_x\":\"";
  dim += _width();
  dim += "\",\"size_y\":\"";
  dim += _height();

  if(_row() > 0) {
    dim += "\",\"row\":\"";
    dim += _row();
  }

  if(_column() > 0) {
    dim += "\",\"column\":\"";
    dim += _column();
  }

  return dim;
}

const char* AdafruitIO_Block::type()
{
  return _visual_type;
}

bool AdafruitIO_Block::save()
{
#if defined(ARDUINO_AVR_YUN)
  BridgeHttpClient *http = _dashboard->io()->_http;
#else
  HttpClient *http = _dashboard->io()->_http;
#endif // defined(ARDUINO_AVR_YUN)

  String url = "/api/v2/";
  url += _dashboard->user();
  url += "/dashboards/";
  url += _dashboard->name;
  url += "/blocks";

  String block_feeds = "[{\"feed_id\":\"";
  block_feeds += _feed->name;
  block_feeds += "\"}]";

  String body = "{\"visual_type\":\"";
  body += type();
  body += dimensions();
  body += "\",\"properties\":";
  body += properties();
  body += ",\"block_feeds\":";
  body += block_feeds;
  body += "}";

#if defined(ARDUINO_AVR_YUN)
  String aiokey = "X-AIO-Key: ";
  aiokey += _dashboard->io()->_key;

  String req = "https://";
  req += _dashboard->io()->_host;
  req += url;

  http->startRequest();
  http->addHeader("Content-Type: application/json");
  http->addHeader(aiokey.c_str());
  http->enableInsecure();
  // Content-Length is implicit
  http->post(req.c_str(), body.c_str());

  int status = http->getResponseCode();
#else
  http->startRequest(url.c_str(), HTTP_METHOD_POST);
  http->sendHeader(HTTP_HEADER_CONTENT_TYPE, "application/json");
  http->sendHeader(HTTP_HEADER_CONTENT_LENGTH, body.length());
  http->sendHeader("X-AIO-Key", _dashboard->io()->_key);
  http->endRequest();
  http->write((const byte*)body.c_str(), body.length());

  int status = http->responseStatusCode();
  http->responseBody(); // needs to be read even if not used
#endif // defined(ARDUINO_AVR_YUN)

  return status == 200;
}
