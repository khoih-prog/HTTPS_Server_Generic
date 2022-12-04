/****************************************************************************************************************************
  ResolvedResource.hpp

  For ESP32, and powerful-enough boards, such as ESP8266, Portenta_H7, RP2040W, Teensy 4.1, etc.

  HTTPS_Server_Generic is a library for HTTP/HTTPS server

  Based on and modified from esp32_https_server (https://github.com/fhessel/esp32_https_server)
  Built by Khoi Hoang https://github.com/khoih-prog/HTTPS_Server_Generic
  Licensed under MIT license

  Original author: Frank Hessel
 *****************************************************************************************************************************/

#ifndef SRC_RESOLVEDRESOURCE_HPP_
#define SRC_RESOLVEDRESOURCE_HPP_

#include "ResourceNode.hpp"
#include "ResourceParameters.hpp"

namespace httpsserver {

/**
 * \brief This class represents a resolved resource, meaning the result of mapping a string URL to an HTTPNode
 */
class ResolvedResource {
public:
  ResolvedResource();
  ~ResolvedResource();

  void setMatchingNode(HTTPNode * node);
  HTTPNode * getMatchingNode();
  bool didMatch();
  ResourceParameters * getParams();
  void setParams(ResourceParameters * params);

private:
  HTTPNode * _matchingNode;
  ResourceParameters * _params;
};

} /* namespace httpsserver */

#endif /* SRC_RESOLVEDRESOURCE_HPP_ */
