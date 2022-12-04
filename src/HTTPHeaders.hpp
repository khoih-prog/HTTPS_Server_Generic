/****************************************************************************************************************************
  HTTPHeaders.hpp

  For ESP32, and powerful-enough boards, such as ESP8266, Portenta_H7, RP2040W, Teensy 4.1, etc.

  HTTPS_Server_Generic is a library for HTTP/HTTPS server

  Based on and modified from esp32_https_server (https://github.com/fhessel/esp32_https_server)
  Built by Khoi Hoang https://github.com/khoih-prog/HTTPS_Server_Generic
  Licensed under MIT license

  Original author: Frank Hessel
 *****************************************************************************************************************************/

#ifndef SRC_HTTPHEADERS_HPP_
#define SRC_HTTPHEADERS_HPP_

#include <string>
// Arduino declares it's own min max, incompatible with the stl...
#undef min
#undef max
#include <vector>

#include "HTTPSServerConstants.hpp"
#include "HTTPHeader.hpp"

namespace httpsserver {

/**
 * \brief Groups and manages a set of HTTPHeader instances
 */
class HTTPHeaders {
public:
  HTTPHeaders();
  virtual ~HTTPHeaders();

  HTTPHeader * get(std::string const &name);
  std::string getValue(std::string const &name);
  void set(HTTPHeader * header);

  std::vector<HTTPHeader *> * getAll();

  void clearAll();

private:
  std::vector<HTTPHeader*> * _headers;
};

} /* namespace httpsserver */

#endif /* SRC_HTTPHEADERS_HPP_ */
