/****************************************************************************************************************************
  HTTPValidator.cpp

  For ESP32, and powerful-enough boards, such as ESP8266, Portenta_H7, RP2040W, Teensy 4.1, etc.

  HTTPS_Server_Generic is a library for HTTP/HTTPS server

  Based on and modified from esp32_https_server (https://github.com/fhessel/esp32_https_server)
  Built by Khoi Hoang https://github.com/khoih-prog/HTTPS_Server_Generic
  Licensed under MIT license

  Original author: Frank Hessel
 *****************************************************************************************************************************/

#include "HTTPValidator.hpp"

namespace httpsserver
{

HTTPValidator::HTTPValidator(const uint8_t idx, const HTTPValidationFunction * validatorFunction):
  _idx(idx),
  _validatorFunction(validatorFunction)
{

}

HTTPValidator::~HTTPValidator()
{

}

} /* namespace httpsserver */
