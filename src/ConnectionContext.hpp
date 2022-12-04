/****************************************************************************************************************************
  ConnectionContext.hpp

  For ESP32, and powerful-enough boards, such as ESP8266, Portenta_H7, RP2040W, Teensy 4.1, etc.

  HTTPS_Server_Generic is a library for HTTP/HTTPS server

  Based on and modified from esp32_https_server (https://github.com/fhessel/esp32_https_server)
  Built by Khoi Hoang https://github.com/khoih-prog/HTTPS_Server_Generic
  Licensed under MIT license

  Original author: Frank Hessel
 *****************************************************************************************************************************/

#ifndef SRC_CONNECTIONCONTEXT_HPP_
#define SRC_CONNECTIONCONTEXT_HPP_

#include <Arduino.h>
#include <IPAddress.h>

// Required for SSL
#if 0
#if defined(ESP32)
  //#include "openssl/ssl.h"
  #include "mbedtls/ssl.h"
#elif ( defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) )
  #include "mbedtls/ssl.h"
#endif
#endif

#undef read

namespace httpsserver {

class WebsocketHandler;

/**
 * \brief Internal class to handle the state of a connection
 */
class ConnectionContext {
public:
  ConnectionContext();
  virtual ~ConnectionContext();

  virtual void signalRequestError() = 0;
  virtual void signalClientClose() = 0;
  virtual size_t getCacheSize() = 0;

  virtual size_t readBuffer(byte* buffer, size_t length) = 0;
  virtual size_t pendingBufferSize() = 0;

  virtual size_t writeBuffer(byte* buffer, size_t length) = 0;

  virtual bool isSecure() = 0;
  virtual void setWebsocketHandler(WebsocketHandler *wsHandler);
  virtual IPAddress getClientIP() = 0;

  WebsocketHandler * _wsHandler;
};

} /* namespace httpsserver */

#endif /* SRC_CONNECTIONCONTEXT_HPP_ */
