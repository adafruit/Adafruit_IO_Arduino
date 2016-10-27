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

const char* AdafruitIO_Block::type()
{
  return _visual_type;
}

bool AdafruitIO_Block::save()
{
  HttpClient *http = _dashboard->io()->_http;

  String url = "/api/v2/";
  url += _dashboard->user();
  url += "/dashboards/";
  url += _dashboard->name;
  url += "/blocks";

  String user = _dashboard->user();
  user.replace("_", "-");

  String block_feeds = "[{\"group_id\": \"";
  block_feeds += user;
  block_feeds += "\",\"feed_id\":\"";
  block_feeds += _feed->name;
  block_feeds += "\"}]";

  String body = "{\"visual_type\":\"";
  body += type();
  body += "\",\"properties\":";
  body += properties();
  body += "\,\"size_x\":\"";
  body += width;
  body += "\",\"size_y\":\"";
  body += height;
  body += "\",\"block_feeds\":";
  body += block_feeds;
  body += "}";

  http->startRequest(url.c_str(), HTTP_METHOD_POST);
  http->sendHeader(HTTP_HEADER_CONTENT_TYPE, "application/json");
  http->sendHeader(HTTP_HEADER_CONTENT_LENGTH, body.length());
  http->sendHeader("X-AIO-Key", _dashboard->io()->_key);
  http->endRequest();
  http->write((const byte*)body.c_str(), body.length());

  int status = http->responseStatusCode();
  http->responseBody(); // needs to be read even if not used

  return status == 200;
}
