/****************************************************************************************************************************
  ResourceNode.hpp

  For ESP32, and powerful-enough boards, such as ESP8266, Portenta_H7, RP2040W, Teensy 4.1, etc.

  HTTPS_Server_Generic is a library for HTTP/HTTPS server

  Based on and modified from esp32_https_server (https://github.com/fhessel/esp32_https_server)
  Built by Khoi Hoang https://github.com/khoih-prog/HTTPS_Server_Generic
  Licensed under MIT license

  Original author: Frank Hessel
 *****************************************************************************************************************************/

#ifndef SRC_RESOURCENODE_HPP_
#define SRC_RESOURCENODE_HPP_

#include <string>

#include "HTTPNode.hpp"
#include "HTTPSCallbackFunction.hpp"

namespace httpsserver {

/**
 * \brief This HTTPNode represents a route that maps to a regular HTTP request for a resource (static or dynamic)
 *
 * It therefore contrasts to the WebsocketNode, which handles requests for Websockets.
 */
class ResourceNode : public HTTPNode {
public:
  ResourceNode(const std::string &path, const std::string &method, const HTTPSCallbackFunction * callback, const std::string &tag = "");
  virtual ~ResourceNode();

  const std::string _method;
  const HTTPSCallbackFunction * _callback;
  std::string getMethod() { return _method; }
};

} /* namespace httpsserver */

#endif /* SRC_RESOURCENODE_HPP_ */
