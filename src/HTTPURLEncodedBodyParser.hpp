/****************************************************************************************************************************
  HTTPURLEncodedBodyParser.hpp

  For ESP32, and powerful-enough boards, such as ESP8266, Portenta_H7, RP2040W, Teensy 4.1, etc.

  HTTPS_Server_Generic is a library for HTTP/HTTPS server

  Based on and modified from esp32_https_server (https://github.com/fhessel/esp32_https_server)
  Built by Khoi Hoang https://github.com/khoih-prog/HTTPS_Server_Generic
  Licensed under MIT license

  Original author: Frank Hessel
 *****************************************************************************************************************************/

#ifndef SRC_HTTPURLENCODEDBODYPARSER_HPP_
#define SRC_HTTPURLENCODEDBODYPARSER_HPP_

#include <Arduino.h>
#include "HTTPBodyParser.hpp"

namespace httpsserver {

class HTTPURLEncodedBodyParser : public HTTPBodyParser {
public:
  // From HTTPBodyParser
  HTTPURLEncodedBodyParser(HTTPRequest * req);
  ~HTTPURLEncodedBodyParser();
  virtual bool nextField();
  virtual std::string getFieldName();
  virtual std::string getFieldFilename();
  virtual std::string getFieldMimeType();
  virtual bool endOfField();
  virtual size_t read(byte* buffer, size_t bufferSize);
protected:
  char *bodyBuffer;
  char *bodyPtr;
  size_t bodyLength;
  std::string fieldName;
  std::string fieldBuffer;
  const char *fieldPtr;
  size_t fieldRemainingLength;
};

} // namespace httpserver

#endif
