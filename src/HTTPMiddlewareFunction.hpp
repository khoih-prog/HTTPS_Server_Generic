/****************************************************************************************************************************
  HTTPMiddlewareFunction.hpp

  For ESP32, and powerful-enough boards, such as ESP8266, Portenta_H7, RP2040W, Teensy 4.1, etc.

  HTTPS_Server_Generic is a library for HTTP/HTTPS server

  Based on and modified from esp32_https_server (https://github.com/fhessel/esp32_https_server)
  Built by Khoi Hoang https://github.com/khoih-prog/HTTPS_Server_Generic
  Licensed under MIT license

  Original author: Frank Hessel
 *****************************************************************************************************************************/

#ifndef SRC_HTTPMIDDLEWAREFUNCTION_HPP_
#define SRC_HTTPMIDDLEWAREFUNCTION_HPP_

#include <functional-vlpp.h>

#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"
#include "HTTPSCallbackFunction.hpp"

namespace httpsserver {
  class HTTPRequest;
  /**
   * \brief A middleware function that can be registered at the server.
   *
   * It will be called before an incoming request is passed to any HTTPSCallbackFunction and may perform
   * operations like redirects or authentication.
   *
   * It receives the request and response object as well as a function pointer ("next") to pass on processing.
   * This allows chaining those functions. If next() is not called, the HTTPSCallbackFunction that
   * would match the request url will not be invoked. This might become handy if you want to intercept request
   * handling in case of missing authentication. Don't forget to call next in case you want to access your
   * resources, though.
   */
  typedef void (HTTPSMiddlewareFunction)(HTTPRequest * req, HTTPResponse * res, std::function<void()> next);
}
 #endif /* SRC_HTTPMIDDLEWAREFUNCTION_HPP_ */
