/****************************************************************************************************************************
  HTTPRequest.hpp

  For ESP32, and powerful-enough boards, such as ESP8266, Portenta_H7, RP2040W, Teensy 4.1, etc.

  HTTPS_Server_Generic is a library for HTTP/HTTPS server

  Based on and modified from esp32_https_server (https://github.com/fhessel/esp32_https_server)
  Built by Khoi Hoang https://github.com/khoih-prog/HTTPS_Server_Generic
  Licensed under MIT license

  Original author: Frank Hessel
 *****************************************************************************************************************************/

#ifndef SRC_HTTPREQUEST_HPP_
#define SRC_HTTPREQUEST_HPP_

#include <Arduino.h>
#include <IPAddress.h>
#include <string>


#if defined(ESP32)
  #include <mbedtls/base64.h>
#elif defined(ESP8266)
  #include "utility/base64.h"
#elif ( defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) )
  #warning Using PORTENTA_H7 in HTTPRequest.hpp
  #include "utility/base64.h"
#endif

#include "ConnectionContext.hpp"
#include "HTTPNode.hpp"
#include "HTTPHeader.hpp"
#include "HTTPHeaders.hpp"
#include "ResourceParameters.hpp"
#include "util.hpp"

namespace httpsserver {

/**
 * \brief Represents the request stream for an HTTP request
 */
class HTTPRequest {
public:
  HTTPRequest(ConnectionContext * con, HTTPHeaders * headers, HTTPNode * resolvedNode, std::string method, ResourceParameters * params, std::string requestString);
  virtual ~HTTPRequest();

  std::string getHeader(std::string const &name);
  void setHeader(std::string const &name, std::string const &value);
  HTTPNode * getResolvedNode();
  std::string getRequestString();
  std::string getMethod();
  std::string getTag();
  IPAddress getClientIP();

  size_t readChars(char * buffer, size_t length);
  size_t readBytes(byte * buffer, size_t length);
  size_t getContentLength();
  bool   requestComplete();
  void   discardRequestBody();
  ResourceParameters * getParams();
  HTTPHeaders *getHTTPHeaders();
  std::string getBasicAuthUser();
  std::string getBasicAuthPassword();
  bool   isSecure();
  void setWebsocketHandler(WebsocketHandler *wsHandler);

private:
  std::string decodeBasicAuthToken();

  ConnectionContext * _con;

  HTTPHeaders * _headers;

  HTTPNode * _resolvedNode;

  std::string _method;

  ResourceParameters * _params;

  std::string _requestString;

  bool _contentLengthSet;
  size_t _remainingContent;
};

} /* namespace httpsserver */

#endif /* SRC_HTTPREQUEST_HPP_ */
