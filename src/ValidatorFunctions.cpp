/****************************************************************************************************************************
  ValidatorFunctions.cpp

  For ESP32, and powerful-enough boards, such as ESP8266, Portenta_H7, RP2040W, Teensy 4.1, etc.

  HTTPS_Server_Generic is a library for HTTP/HTTPS server

  Based on and modified from esp32_https_server (https://github.com/fhessel/esp32_https_server)
  Built by Khoi Hoang https://github.com/khoih-prog/HTTPS_Server_Generic
  Licensed under MIT license

  Original author: Frank Hessel
 *****************************************************************************************************************************/

#include "ValidatorFunctions.hpp"

namespace httpsserver
{
bool validateNotEmpty(std::string s)
{
  return s != "";
}

bool validateUnsignedInteger(std::string s)
{
  for (size_t x = 0; x < s.size(); x++)
  {
    if (s[x] < '0' || s[x] > '9')
      return false;
  }

  return true;
}
}
