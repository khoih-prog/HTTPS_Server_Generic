/****************************************************************************************************************************
  HTTPMultipartBodyParser.hpp

  For ESP32, and powerful-enough boards, such as ESP8266, Portenta_H7, RP2040W, Teensy 4.1, etc.

  HTTPS_Server_Generic is a library for HTTP/HTTPS server

  Based on and modified from esp32_https_server (https://github.com/fhessel/esp32_https_server)
  Built by Khoi Hoang https://github.com/khoih-prog/HTTPS_Server_Generic
  Licensed under MIT license

  Original author: Frank Hessel
 *****************************************************************************************************************************/

#ifndef SRC_HTTPMULTIPARTBODYPARSER_HPP_
#define SRC_HTTPMULTIPARTBODYPARSER_HPP_

#include <Arduino.h>
#include "HTTPBodyParser.hpp"

namespace httpsserver {

class HTTPMultipartBodyParser : public HTTPBodyParser {
public:
  HTTPMultipartBodyParser(HTTPRequest * req);
  ~HTTPMultipartBodyParser();
  virtual bool nextField();
  virtual std::string getFieldName();
  virtual std::string getFieldFilename();
  virtual std::string getFieldMimeType();
  virtual bool endOfField();
  virtual size_t read(byte* buffer, size_t bufferSize);
private:
  std::string readLine();
  void fillBuffer(size_t maxLen);
  void consumedBuffer(size_t consumed);
  bool skipCRLF();
  bool peekBoundary();
  void discardBody();
  bool endOfBody();
  char *peekBuffer;
  size_t peekBufferSize;

  std::string boundary;
  std::string lastBoundary;
  std::string fieldName;
  std::string fieldMimeType;
  std::string fieldFilename;
};

} // namespace httpserver

#endif
