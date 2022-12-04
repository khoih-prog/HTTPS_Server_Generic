/****************************************************************************************************************************
  HTTPSCallbackFunction.hpp

  For ESP32, and powerful-enough boards, such as ESP8266, Portenta_H7, RP2040W, Teensy 4.1, etc.

  HTTPS_Server_Generic is a library for HTTP/HTTPS server

  Based on and modified from esp32_https_server (https://github.com/fhessel/esp32_https_server)
  Built by Khoi Hoang https://github.com/khoih-prog/HTTPS_Server_Generic
  Licensed under MIT license

  Original author: Frank Hessel
 *****************************************************************************************************************************/

#ifndef SRC_HTTPSCALLBACKFUNCTION_HPP_
#define SRC_HTTPSCALLBACKFUNCTION_HPP_

#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"

namespace httpsserver {
  /**
   * \brief A callback function that will be called by the server to handle a request
   */
  typedef void (HTTPSCallbackFunction)(HTTPRequest * req, HTTPResponse * res); 
}

#endif /* SRC_HTTPSCALLBACKFUNCTION_HPP_ */
