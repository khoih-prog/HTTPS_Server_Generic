/****************************************************************************************************************************
  ValidatorFunctions.hpp

  For ESP32, and powerful-enough boards, such as ESP8266, Portenta_H7, RP2040W, Teensy 4.1, etc.

  HTTPS_Server_Generic is a library for HTTP/HTTPS server

  Based on and modified from esp32_https_server (https://github.com/fhessel/esp32_https_server)
  Built by Khoi Hoang https://github.com/khoih-prog/HTTPS_Server_Generic
  Licensed under MIT license

  Original author: Frank Hessel
 *****************************************************************************************************************************/

#ifndef SRC_VALIDATORFUNCTIONS_HPP_
#define SRC_VALIDATORFUNCTIONS_HPP_

#include <Arduino.h>
#include <string>
#undef max
#undef min

#include <functional-vlpp.h>

#include <memory>
#include "HTTPValidator.hpp"
#include "util.hpp"

/**
 * This file contains some validator functions that can be used to validate URL parameters.
 * 
 * They covor common cases like checking for integer, non-empty, ..., so the user of this library
 * does not need to write them on his own.
 */

namespace httpsserver {

  /**
   * \brief **Built-in validator function**: Checks that a string is not empty.
   */
  bool validateNotEmpty(std::string s);

  /**
   * \brief **Built-in validator function**: Checks that a value is a positive int
   * 
   * Checks that the value is a positive integer (combine it with newValidateUnsignedIntegerMax if
   * you have constraints regarding the size of that number)
   */
  bool validateUnsignedInteger(std::string s);

}

#endif
