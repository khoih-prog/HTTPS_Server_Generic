/****************************************************************************************************************************
  ResourceNode.cpp

  For ESP32, and powerful-enough boards, such as ESP8266, Portenta_H7, RP2040W, Teensy 4.1, etc.

  HTTPS_Server_Generic is a library for HTTP/HTTPS server

  Based on and modified from esp32_https_server (https://github.com/fhessel/esp32_https_server)
  Built by Khoi Hoang https://github.com/khoih-prog/HTTPS_Server_Generic
  Licensed under MIT license

  Original author: Frank Hessel
 *****************************************************************************************************************************/

#include "ResourceNode.hpp"

namespace httpsserver
{

ResourceNode::ResourceNode(const std::string &path, const std::string &method, const HTTPSCallbackFunction * callback,
                           const std::string &tag):
  HTTPNode(path, HANDLER_CALLBACK, tag),
  _method(method),
  _callback(callback)
{

}

ResourceNode::~ResourceNode()
{

}

} /* namespace httpsserver */
