/****************************************************************************************************************************
  WebsocketInputStreambuf.hpp

  For ESP32, and powerful-enough boards, such as ESP8266, Portenta_H7, RP2040W, Teensy 4.1, etc.

  HTTPS_Server_Generic is a library for HTTP/HTTPS server

  Based on and modified from esp32_https_server (https://github.com/fhessel/esp32_https_server)
  Built by Khoi Hoang https://github.com/khoih-prog/HTTPS_Server_Generic
  Licensed under MIT license

  Original author: Frank Hessel
 *****************************************************************************************************************************/

#ifndef SRC_WEBSOCKETINPUTSTREAMBUF_HPP_
#define SRC_WEBSOCKETINPUTSTREAMBUF_HPP_

#include <Arduino.h>
#include <lwip/def.h>

#include <string>
#undef min
#undef max
#include <iostream>
#include <streambuf>
#include <sstream>

#include <iostream>

#include "HTTPSServerConstants.hpp"
#include "ConnectionContext.hpp"

namespace httpsserver {

class WebsocketInputStreambuf : public std::streambuf {
public:
  WebsocketInputStreambuf(
    ConnectionContext *con,
    size_t dataLength,
    uint8_t *_ = nullptr,
    size_t bufferSize = 2048
  );
  virtual ~WebsocketInputStreambuf();

  int_type underflow();
  void discard();
  size_t getRecordSize();

private:
  char *_buffer;
  ConnectionContext *_con;
  size_t _dataLength;
  size_t _bufferSize;
  size_t _sizeRead;
  uint8_t *_pMask;

};

} // namespace

#endif
