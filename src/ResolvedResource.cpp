/****************************************************************************************************************************
  ResolvedResource.cpp

  For ESP32, and powerful-enough boards, such as ESP8266, Portenta_H7, RP2040W, Teensy 4.1, etc.

  HTTPS_Server_Generic is a library for HTTP/HTTPS server

  Based on and modified from esp32_https_server (https://github.com/fhessel/esp32_https_server)
  Built by Khoi Hoang https://github.com/khoih-prog/HTTPS_Server_Generic
  Licensed under MIT license

  Original author: Frank Hessel
 *****************************************************************************************************************************/

#include "ResolvedResource.hpp"

namespace httpsserver
{

ResolvedResource::ResolvedResource()
{
  _matchingNode = NULL;
  _params = NULL;
}

ResolvedResource::~ResolvedResource()
{
  // Delete only params, nodes are reused/server-internal
  if (_params != NULL)
  {
    delete _params;
  }
}

bool ResolvedResource::didMatch()
{
  return _matchingNode != NULL;
}

HTTPNode * ResolvedResource::getMatchingNode()
{
  return _matchingNode;
}

void ResolvedResource::setMatchingNode(HTTPNode * node)
{
  _matchingNode = node;
}

ResourceParameters * ResolvedResource::getParams()
{
  return _params;
}

void ResolvedResource::setParams(ResourceParameters * params)
{
  if (_params != NULL && _params != params)
  {
    delete _params;
  }

  _params = params;
}

} /* namespace httpsserver */
