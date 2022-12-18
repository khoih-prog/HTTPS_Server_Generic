/****************************************************************************************************************************
  HTTPS_Server_Generic.h

  For ESP32, and powerful-enough boards, such as ESP8266, Portenta_H7, RP2040W, Teensy 4.1, etc.

  HTTPS_Server_Generic is a library for HTTP/HTTPS server

  Based on and modified from esp32_https_server (https://github.com/fhessel/esp32_https_server)
  Built by Khoi Hoang https://github.com/khoih-prog/HTTPS_Server_Generic
  Licensed under MIT license

  Original author: Frank Hessel

  Version: 1.3.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.2.0   K Hoang      03/12/2022 Initial porting for ESP32, WT32_ETH01, ESP32_W5500 and ESP32_ENC
  1.3.0   K Hoang      17/12/2022 Add support to ESP32S3 using LwIP W5500 and ENC28J60
 *****************************************************************************************************************************/

#ifndef HTTPS_SERVER_GENERIC_H_
#define HTTPS_SERVER_GENERIC_H_

#include <Arduino.h>
#include <IPAddress.h>

// For the middleware
#include <functional-vlpp.h>

#define USING_ESP_TLS       false   //true

// Required for SSL
#if defined(ESP32)
  #if USING_ESP_TLS
    #error ESP_TLS not ready yet
    #include "mbedtls/ssl.h"
    #include <mbedtls/sha1.h>
  #else
    #include "openssl/ssl.h"
  #endif

  #include <sha/sha_parallel_engine.h>
#elif defined(ESP8266)
  #error Not ready yet
  //#include "mbedtls/ssl.h"
  //#include <mbedtls/sha1.h>
  //#include <sha/sha_parallel_engine.h>
#elif ( defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) )
  #error  Using PORTENTA_H7 not ready yet
  //#include "mbedtls/ssl.h"
  //#include <mbedtls/sha1.h>
#else
  #error Not support board
#endif

////////////////////////////////////////

#define HTTPS_SERVER_GENERIC_VERSION            "HTTPS_Server_Generic v1.3.0"

#define HTTPS_SERVER_GENERIC_VERSION_MAJOR      1
#define HTTPS_SERVER_GENERIC_VERSION_MINOR      3
#define HTTPS_SERVER_GENERIC_VERSION_PATCH      0

#define HTTPS_SERVER_GENERIC_VERSION_INT        1003000

////////////////////////////////////////

#include <HTTPSServer.hpp>
#include <HTTPServer.hpp>
#include <SSLCert.hpp>
#include <HTTPRequest.hpp>
#include <HTTPResponse.hpp>

#include <HTTPBodyParser.hpp>
#include <HTTPMultipartBodyParser.hpp>
#include <HTTPURLEncodedBodyParser.hpp>
#include <ValidatorFunctions.hpp>

#include <WebsocketHandler.hpp>

#include <util.hpp>

#endif /* HTTPS_SERVER_GENERIC_H_ */
