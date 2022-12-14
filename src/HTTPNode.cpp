/****************************************************************************************************************************
  HTTPNode.cpp

  For ESP32, and powerful-enough boards, such as ESP8266, Portenta_H7, RP2040W, Teensy 4.1, etc.

  HTTPS_Server_Generic is a library for HTTP/HTTPS server

  Based on and modified from esp32_https_server (https://github.com/fhessel/esp32_https_server)
  Built by Khoi Hoang https://github.com/khoih-prog/HTTPS_Server_Generic
  Licensed under MIT license

  Original author: Frank Hessel
 *****************************************************************************************************************************/

#include "HTTPNode.hpp"
#include "HTTPSServerConstants.hpp"

namespace httpsserver
{

HTTPNode::HTTPNode(std::string const &path, const HTTPNodeType nodeType, std::string const &tag):
  _path(path),
  _tag(tag),
  _nodeType(nodeType)
{

  // Count the parameters and store the indices
  size_t idx = 0;

  while ((idx = path.find("/*", idx)) != std::string::npos)
  {
    // Skip the "/*"
    idx += 2;

    // Assure that we have either /* at the URL's end or /*/ somewhere in between
    if (idx == path.size() || path[idx] == '/')
    {
      _pathParamIdx.push_back(idx - 1);
    }
  };
}

HTTPNode::~HTTPNode()
{
  // Delete validator references
  for (std::vector<HTTPValidator*>::iterator validator = _validators.begin(); validator != _validators.end();
       ++validator)
  {
    delete *validator;
  }
}

bool HTTPNode::hasPathParameter()
{
  return !_pathParamIdx.empty();
}

ssize_t HTTPNode::getParamIdx(size_t idx)
{
  if (idx < _pathParamIdx.size())
  {
    return _pathParamIdx[idx];
  }
  else
  {
    return -1;
  }
}

size_t HTTPNode::getPathParamCount()
{
  return _pathParamIdx.size();
}

void HTTPNode::addPathParamValidator(size_t paramIdx, const HTTPValidationFunction * validator)
{
  _validators.push_back(new HTTPValidator(paramIdx, validator));

}

std::vector<HTTPValidator*> * HTTPNode::getValidators()
{
  return &_validators;
}
}
