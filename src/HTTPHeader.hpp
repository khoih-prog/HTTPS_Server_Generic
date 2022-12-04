/****************************************************************************************************************************
  HTTPHeader.hpp

  For ESP32, and powerful-enough boards, such as ESP8266, Portenta_H7, RP2040W, Teensy 4.1, etc.

  HTTPS_Server_Generic is a library for HTTP/HTTPS server

  Based on and modified from esp32_https_server (https://github.com/fhessel/esp32_https_server)
  Built by Khoi Hoang https://github.com/khoih-prog/HTTPS_Server_Generic
  Licensed under MIT license

  Original author: Frank Hessel
 *****************************************************************************************************************************/

#ifndef SRC_HTTPHEADER_HPP_
#define SRC_HTTPHEADER_HPP_
#include <Arduino.h>

#include <string>

namespace httpsserver {

/**
 * \brief Represents a single name/value pair of an HTTP header
 */
class HTTPHeader {
public:
  HTTPHeader(const std::string &name, const std::string &value);
  virtual ~HTTPHeader();
  const std::string _name;
  const std::string _value;
  std::string print();
};

/**
 * \brief Normalizes case in header names
 * 
 * It converts the first letter and every letter after a non-alnum character
 * to uppercase. For example, "content-length" becomes "Content-Length" and
 * "HOST" becomes "Host".
 */
std::string normalizeHeaderName(std::string const &name);

} /* namespace httpsserver */

#endif /* SRC_HTTPHEADER_HPP_ */
