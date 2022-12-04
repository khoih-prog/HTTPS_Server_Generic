/****************************************************************************************************************************
  WebsocketNode.hpp

  For ESP32, and powerful-enough boards, such as ESP8266, Portenta_H7, RP2040W, Teensy 4.1, etc.

  HTTPS_Server_Generic is a library for HTTP/HTTPS server

  Based on and modified from esp32_https_server (https://github.com/fhessel/esp32_https_server)
  Built by Khoi Hoang https://github.com/khoih-prog/HTTPS_Server_Generic
  Licensed under MIT license

  Original author: Frank Hessel
 *****************************************************************************************************************************/

#ifndef SRC_WEBSOCKETNODE_HPP_
#define SRC_WEBSOCKETNODE_HPP_

#include <string>

#include "HTTPNode.hpp"
#include "WebsocketHandler.hpp"

namespace httpsserver {

typedef WebsocketHandler* (WebsocketHandlerCreator)();

class WebsocketNode : public HTTPNode {
public:
  WebsocketNode(const std::string &path, const WebsocketHandlerCreator creatorFunction, const std::string &tag = "");
  virtual ~WebsocketNode();
  WebsocketHandler* newHandler();
  std::string getMethod() { return std::string("GET"); }
private:
  const WebsocketHandlerCreator * _creatorFunction;
};

} /* namespace httpsserver */

#endif /* SRC_WEBSOCKET_HPP_ */
