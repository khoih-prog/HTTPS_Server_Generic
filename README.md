# HTTPS_Server_Generic Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/HTTPS_Server_Generic.svg?)](https://www.ardu-badge.com/HTTPS_Server_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/HTTPS_Server_Generic.svg)](https://github.com/khoih-prog/HTTPS_Server_Generic/releases)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/HTTPS_Server_Generic.svg)](http://github.com/khoih-prog/HTTPS_Server_Generic/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>


---
---

## Table of contents

* [Table of contents](#table-of-contents)
* [Why do we need this HTTPS_Server_Generic library](#why-do-we-need-this-HTTPS_Server_Generic-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Get Started](#Get-Started)
  * [Create Server Instance](#Create-Server-Instance)
  * [Add Resources to the Server](#Add-Resources-to-the-Server)
  * [Start the Server](#Start-the-Server)
  * [Running the Server asynchronously](#Running-the-Server-asynchronously)
* [Advanced Configuration](#Advanced-Configuration)
  * [Saving Space by Reducing Functionality](#Saving-Space-by-Reducing-Functionality)
  * [Configure Logging](#Configure-Logging)
* [How to connect W5500, W6100 or ENC28J60 to ESP32_S2/S3/C3](#How-to-connect-W5500-W6100-or-ENC28J60-to-ESP32_S2S3C3)
* [HOWTO Example Usage](#HOWTO-Example-Usage)
* [Examples](#examples)
  * [For ESP32_WiFi](#For-ESP32_WiFi)
    * [ 1. Async-Server](examples/ESP32_WiFi/Async-Server)
    * [ 2. Authentication](examples/ESP32_WiFi/Authentication)
    * [ 3. HTML-Forms](examples/ESP32_WiFi/HTML-Forms)
    * [ 4. HTTPS-and-HTTP](examples/ESP32_WiFi/HTTPS-and-HTTP)
    * [ 5. Middleware](examples/ESP32_WiFi/Middleware)
    * [ 6. Parameters](examples/ESP32_WiFi/Parameters)
    * [ 7. Parameter-Validation](examples/ESP32_WiFi/Parameter-Validation)
    * [ 8. Put-Post-Echo](examples/ESP32_WiFi/Put-Post-Echo)
    * [ 9. REST-API](examples/ESP32_WiFi/REST-API)
    * [10. Self-Signed-Certificate](examples/ESP32_WiFi/Self-Signed-Certificate)
    * [11. Static-Page](examples/ESP32_WiFi/Static-Page)
    * [12. Websocket-Chat](examples/ESP32_WiFi/Websocket-Chat)
  * [For WT32_ETH01](#For-WT32_ETH01)
  * [For ESP32_W5500](#For-ESP32_W5500)
  * [For ESP32_W6100](#For-ESP32_W6100)
  * [For ESP32_ENC](#For-ESP32_ENC)
  * [For ESP32_SC_W5500](#For-ESP32_SC_W5500)
  * [For ESP32_SC_W6100](#For-ESP32_SC_W6100)
  * [For ESP32_SC_ENC](#For-ESP32_SC_ENC)
* [Example Async-Server](#Example-Async-Server) 
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. Async_Server on ESP32_DEV with ESP32_ENC28J60](#1-Async_Server-on-ESP32_DEV-with-ESP32_ENC28J60)
  * [2. Async_Server on ESP32_DEV with ESP32_W5500](#2-Async_Server-on-ESP32_DEV-with-ESP32_W5500)
  * [3. Async_Server on ESP32S3_DEV with ESP32_S3_ENC28J60](#3-Async_Server-on-ESP32S3_DEV-with-ESP32_S3_ENC28J60)
  * [4. Async_Server on ESP32S3_DEV with ESP32_S3_W5500](#4-Async_Server-on-ESP32S3_DEV-with-ESP32_S3_W5500)
  * [5. Async_Server on ESP32C3_DEV with ESP32_C3_W5500](#5-Async_Server-on-ESP32C3_DEV-with-ESP32_C3_W5500)
  * [6. Async_Server on ESP32_DEV with ESP32_W6100](#6-Async_Server-on-ESP32_DEV-with-ESP32_W6100)
  * [7. Async_Server on ESP32S3_DEV with ESP32_S3_W6100](#7-Async_Server-on-ESP32S3_DEV-with-ESP32_S3_W6100)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Why do we need this [HTTPS_Server_Generic library](https://github.com/khoih-prog/HTTPS_Server_Generic)


#### Features

This library is based on, modified from:

1. [Frank Hessel's **esp32_https_server**](https://github.com/fhessel/esp32_https_server)
2. [Khoi Hoang's **ESP32_HTTPS_Server**](https://github.com/khoih-prog/ESP32_HTTPS_Server)

to apply the **HTTPS Server** feature of the powerful [**esp32_https_server**](https://github.com/fhessel/esp32_https_server) into **other ESP32 boards, such as WT32_ETH01 (ESP32 + LwIP LAN8720), (ESP32 + LwIP W5500), (ESP32 + LwIP W6100) and (ESP32 + LwIP ENC28J60) Ethernet**.

In the future, this library will support `powerful-enough` boards using `LwIP WiFi/Ethernet`, such as `ESP8266, Portenta_H7, RP2040W, Teensy 4.1, etc.`

The library provides these following features:

- Providing support for `HTTP`, `HTTPS` or both at the same time
- Handling requests in callback functions that can be bound to URLs, like for example in `Express` or `Servlets`.
- Abstraction of handling the `HTTP` stuff and providing a simple `API` for it, eg. to access parameters, headers, HTTP Basic Auth etc.
- Using `middleware` functions as proxy to every request to perform central tasks like `authentication` or `logging`.
- Make use of the built-in encryption of the `ESP32-based` boards for `HTTPS`.
- Handle multiple clients in parallel (**max. 3-4 TLS clients due to memory limits**).
- Usage of `Connection: keep-alive` and SSL session reuse to reduce the overhead of SSL handshakes and speed up data transfer.

---

### Currently Supported Boards

#### 1. ESP32/S2/S3/C3 using WiFi

1. **ESP32 (ESP32-DEV, etc.)**

#### 2. ESP32 using LwIP ENC28J60, W5500, W6100 or LAN8720

1. **ESP32 (ESP32-DEV, etc.)**

#### 3. **WT32_ETH01** using ESP32-based boards and LAN8720 Ethernet

#### 4. ESP32S3 using LwIP W5500, W6100 or ENC28J60

1. **ESP32-S3 (ESP32S3_DEV, ESP32_S3_BOX, UM TINYS3, UM PROS3, UM FEATHERS3, etc.)**

#### 5. ESP32S2 using LwIP W5500, W6100 or ENC28J60

1. **ESP32-S2 (ESP32S2_DEV, ESP32-S2 Saola, AI-Thinker ESP-12K, etc.)**

#### 6. ESP32C3 using LwIP W5500, W6100 or ENC28J60

1. **ESP32-C3 (ESP32C3_DEV, etc.)**


--- 

#### ESP32S3_DEV

<p align="center">
    <img src="https://github.com/khoih-prog/HTTPS_Server_Generic/raw/main/Images/ESP32S3_DEV.png">
</p> 


#### ESP32S2_DEV

<p align="center">
    <img src="https://github.com/khoih-prog/HTTPS_Server_Generic/raw/main/Images/ESP32S2_DEV.png">
</p> 


#### ESP32C3_DEV

<p align="center">
    <img src="https://github.com/khoih-prog/HTTPS_Server_Generic/raw/main/Images/ESP32_C3_DevKitC_02.png">
</p> 


---

##### W6100

`FULL_DUPLEX, 100Mbps`

<p align="center">
    <img src="https://github.com/khoih-prog/HTTPS_Server_Generic/raw/main/Images/W6100.png">
</p>


---

##### W5500

`FULL_DUPLEX, 100Mbps`

<p align="center">
    <img src="https://github.com/khoih-prog/HTTPS_Server_Generic/raw/main/Images/W5500.png">
</p>

<p align="center">
    <img src="https://github.com/khoih-prog/HTTPS_Server_Generic/raw/main/Images/W5500_small.png">
</p> 

---

##### ENC28J60

`FULL_DUPLEX, 10Mbps`

<p align="center">
    <img src="https://github.com/khoih-prog/HTTPS_Server_Generic/raw/main/Images/ENC28J60.png">
</p>
 
 

---
---


## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`ESP32 Core 2.0.5+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards. ESP32 Latest Core [![Latest release](https://img.shields.io/github/release/espressif/arduino-esp32.svg)](https://github.com/espressif/arduino-esp32/releases/latest/)
 3. [`Functional-Vlpp library v1.0.2+`](https://github.com/khoih-prog/functional-vlpp) to use server's lambda function. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/Functional-Vlpp.svg?)](https://www.ardu-badge.com/Functional-Vlpp)
 4. [`ArduinoJson library v5.13.5-`](https://github.com/bblanchon/ArduinoJson) to use `REST-API` examples. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ArduinoJson.svg?)](https://www.ardu-badge.com/ArduinoJson)
 5. [`WebServer_WT32_ETH01 v1.5.1+`](https://github.com/khoih-prog/WebServer_WT32_ETH01) for ESP32-based WT32_ETH01 using **either ESP32 core v2.0.0+ or v1.0.6-**. [![GitHub release](https://img.shields.io/github/release/khoih-prog/WebServer_WT32_ETH01.svg)](https://github.com/khoih-prog/WebServer_WT32_ETH01/releases)
 6. [`WebServer_ESP32_ENC library v1.5.1+`](https://github.com/khoih-prog/WebServer_ESP32_ENC) if necessary to use ESP32 boards using `LwIP ENC28J60` Ethernet. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WebServer_ESP32_ENC.svg?)](https://www.ardu-badge.com/WebServer_ESP32_ENC)
 7. [`WebServer_ESP32_W5500 library v1.5.2+`](https://github.com/khoih-prog/WebServer_ESP32_W5500) if necessary to use ESP32 boards using `LwIP W5500` Ethernet. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WebServer_ESP32_W5500.svg?)](https://www.ardu-badge.com/WebServer_ESP32_W5500)
 8. [`WebServer_ESP32_SC_ENC library v1.2.0+`](https://github.com/khoih-prog/WebServer_ESP32_SC_ENC) if necessary to use `ESP32_S2/S3/C3` boards using `LwIP ENC28J60` Ethernet. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WebServer_ESP32_SC_ENC.svg?)](https://www.ardu-badge.com/WebServer_ESP32_SC_ENC)
 9. [`WebServer_ESP32_SC_W5500 library v1.2.1+`](https://github.com/khoih-prog/WebServer_ESP32_SC_W5500) if necessary to use `ESP32_S2/S3/C3` boards using `LwIP W5500` Ethernet. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WebServer_ESP32_SC_W5500.svg?)](https://www.ardu-badge.com/WebServer_ESP32_SC_W5500)
10. [`WebServer_ESP32_W6100 library v1.5.2+`](https://github.com/khoih-prog/WebServer_ESP32_W6100) if necessary to use ESP32 boards using `LwIP W6100` Ethernet. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WebServer_ESP32_W6100.svg?)](https://www.ardu-badge.com/WebServer_ESP32_W6100)
11. [`WebServer_ESP32_SC_W6100 library v1.2.1+`](https://github.com/khoih-prog/WebServer_ESP32_SC_W6100) if necessary to use `ESP32_S2/S3/C3` boards using `LwIP W6100` Ethernet. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WebServer_ESP32_SC_W6100.svg?)](https://www.ardu-badge.com/WebServer_ESP32_SC_W6100)
 


---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for `HTTPS_Server_Generic`, then select / install the latest version. You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/HTTPS_Server_Generic.svg?)](https://www.ardu-badge.com/HTTPS_Server_Generic) for more detailed instructions.

### Manual Install

1. Navigate to [HTTPS_Server_Generic](https://github.com/khoih-prog/HTTPS_Server_Generic) page.
2. Download the latest release `HTTPS_Server_Generic-main.zip`.
3. Extract the zip file to `HTTPS_Server_Generic-main` directory 
4. Copy the whole `HTTPS_Server_Generic-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**HTTPS_Server_Generic** library](https://registry.platformio.org/libraries/khoih-prog/HTTPS_Server_Generic) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/HTTPS_Server_Generic/installation). Search for **HTTPS_Server_Generic** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---
---

## Get Started

The following includes is required to setup the server.

```C++
#include <HTTPS_Server_Generic.h>

// The HTTPS Server comes in a separate namespace. For easier use, include it here.
using namespace httpsserver;
```

---

### Create Server Instance

You can create your server instance like shown below:

**For HTTP:**

```C++
HTTPServer myServer = HTTPServer();
```

**For HTTPS:**

```C++
// Create an SSL certificate object from the files included above
SSLCert cert = SSLCert(example_crt_DER, example_crt_DER_len,
                       example_key_DER, example_key_DER_len);

// Create an SSL-enabled server that uses the certificate
HTTPSServer secureServer = HTTPSServer(&cert);
```

By default, the server will listen on port `443`. If you want to change that (or some other options), you can have a look at the optional parameters of the [**HTTPServer**](https://khoih-prog.github.io/HTTPS_Server_Generic_docs/classhttpsserver_1_1HTTPServer.html) or [**HTTPSServer**](https://khoih-prog.github.io/HTTPS_Server_Generic_docs/classhttpsserver_1_1HTTPSServer.html) constructors.

The only difference between the HTTP and HTTPS version is the certificate which you have to configure. Keep in mind that each opened connection of the TLS-enabled `HTTPSServer` requires additional 40 to 50 kB of heap memory for the TLS connection itself. This has to be considered when increasing `maxConnections`.

---

### Add Resources to the Server

Every _route_ (or path) that should be accessible on the server has to be configured as a so-called `ResourceNode`. Such a node links a handler function to a specific route (like `/test`) and HTTP method (like `GET`). The handler function could look like this:

```C++
void handleRoot(HTTPRequest * req, HTTPResponse * res) 
{
	// We want to deliver an HTML page, so we set the content type
	res->setHeader("Content-Type", "text/html");
	// The response implements the Print interface, so you can use it just like
	// you would write to Serial etc.
	res->println("<!DOCTYPE html>");
	res->println("<html>");
	res->println("<head><title>Hello World!</title></head>");
	res->println("<body>");
	res->println("<h1>Hello World!</h1>");
	res->print("<p>... from your ESP32!</p>");
	res->println("</body>");
	res->println("</html>");
}
```

As you can see, the function gets references to the [**HTTPRequest**](https://khoih-prog.github.io/HTTPS_Server_Generic_docs/classhttpsserver_1_1HTTPRequest.html) and [**HTTPResponse**](https://khoih-prog.github.io/HTTPS_Server_Generic_docs/classhttpsserver_1_1HTTPResponse.html). You can use the request to read headers, parameters, authentication information etc. The response can be used to send data to the client, set headers or HTTP status codes.

Now we need to tell the server which URL should be served by this function. This can be done by creating a [**ResourceNode**](https://khoih-prog.github.io/HTTPS_Server_Generic_docs/classhttpsserver_1_1ResourceNode.html) (usually in your `setup()` function).

```C++
ResourceNode * nodeRoot = new ResourceNode("/", "GET", &handleRoot);
```

The first parameter defines the route. It should always start with a slash, and using just a slash like in this example means that the function will be called for requests to the server's root (like https://10.0.x.x/).

The second parameter is the HTTP method, `"GET"` in this case.

Finally, you pass a reference to the request handler function to link it to the route and method.

Now you just need to register the created [**ResourceNode**](https://khoih-prog.github.io/HTTPS_Server_Generic_docs/classhttpsserver_1_1ResourceNode.html) at your server:

```C++
myServer.registerNode(nodeRoot);
```

That's everything you need to do for a single web page on your server.

Note that you can define a single [**ResourceNode**](https://khoih-prog.github.io/HTTPS_Server_Generic_docs/classhttpsserver_1_1ResourceNode.html) via `HTTPServer::setDefaultNode()`, which will be called if no other node on the server matches. Method and route are ignored in this case. Most examples use this to define a 404-handler, which might be a good idea for most scenarios. In case no default node is specified, the server will return with a small error page if no matching route is found.

---

### Start the Server

A call to [**HTTPServer::start()**](https://khoih-prog.github.io/HTTPS_Server_Generic_docs/classhttpsserver_1_1HTTPServer.html#a1b1b6bce0b52348ca5b5664cf497e039) will start the server so that it is listening on the previously specified port:

```C++
myServer.start();
```

This code usually goes into your `setup()` function. You can use `HTTPServer::isRunning()` to check whether the server started successfully.

By default, you need to pass control to the server explicitly. This is done by calling the [**HTTPServer::loop()**](https://khoih-prog.github.io/HTTPS_Server_Generic_docs/classhttpsserver_1_1HTTPServer.html#af8f68f5ff6ad101827bcc52217249fe2) function, which you usually will put into your Arduino sketch's `loop()` function. Once called, the server will first check for incoming connection (up to the maximum connection count that has been defined in the constructor), and then handle every open connection if it has new data on the socket. So your request handler functions will be called during the call to `loop()`. Note that if one of your handler functions is blocking, it will block all other connections as well.

---

### Running the Server asynchronously

If you want to have the server running in the background (and not calling `loop()` by yourself every few milliseconds), you can make use of the ESP32's task feature and put the whole server in a separate task.

See the [**Async-Server** example](https://github.com/khoih-prog/HTTPS_Server_Generic/tree/main/examples/ESP32_WiFi/Async-Server) to see how this can be done.

---
---

## Advanced Configuration

This section covers some advanced configuration options that allow you, for example, to customize the build process, but which might require more advanced programming skills and a more sophisticated IDE that just the default Arduino IDE.

---

### Saving Space by Reducing Functionality

To save program space on the microcontroller, there are some parts of the library that can be disabled during compilation and will then not be a part of your program.

The following flags are currently available:

| Flag                      | Effect
| ------------------------- | ---------------------------
| HTTPS_DISABLE_SELFSIGNING | Removes the code for generating a self-signed certificate at runtime. You will need to provide certificate and private key data from another data source to use the `HTTPSServer`.

Setting these flags requires a build environment that gives you some control of the compiler, as libraries are usually compiled separately, so just doing a `#define HTTPS_SOMETHING` in your sketch will not work.

---

**Example: Configuration with PlatformIO**

To set these flags in PlatformIO, you can modify your `platformio.ini`. To disable for example the `self-signed-certificates` part of the library, the file could look like this:

```ini
[env:wroom]
platform = espressif32
board = esp32dev
framework = arduino
lib_deps = khoih-prog/HTTPS_Server_Generic@~1.5.0
build_flags =
  -DHTTPS_DISABLE_SELFSIGNING
```

Note the `-D` in front of the actual flag name, that passes this flag as a definition to the preprocessor. Multiple flags can be added one per line.

---

### Configure Logging

The server provides some internal logging, which is activated on level `INFO` by default. This will look like this on your serial console:

```
[HTTPS:I] New connection. SocketFID=49
[HTTPS:I] Request: GET / (FID=49)
[HTTPS:I] Connection closed. Socket FID=49
```

Logging output can also be controlled by using compiler flags. This requires an advanced development environment like explained in [Saving Space by Reducing Functionality](#saving-space-by-reducing-functionality).

There are two parameters that can be configured:

- `HTTPS_LOGLEVEL` defines the log level to use
- `HTTPS_LOGTIMESTAMP` adds a timestamp (based on uptime) to each log entry

| Value of `HTTPS_LOGLEVEL` | Error | Warning | Info | Debug |
| ------------------------- | ----- | ------- | ---- | ----- |
| 0                         |       |         |      |       |
| 1                         |   ✓   |         |      |       |
| 2                         |   ✓   |    ✓    |      |       |
| 3                         |   ✓   |    ✓    |  ✓   |       |
| 4                         |   ✓   |    ✓    |  ✓   |   ✓   |


**Example: Configuration with PlatformIO**

To set these flags in PlatformIO, you can modify your `platformio.ini`. The following entries set the minimum log level to warning and enable timestamps

```ini
[env:wroom]
platform = espressif32
board = esp32dev
framework = arduino
lib_deps = khoih-prog/HTTPS_Server_Generic@~1.5.0
build_flags =
  -DHTTPS_LOGLEVEL=2
  -DHTTPS_LOGTIMESTAMP
```


---
---

### How to connect W5500, W6100 or ENC28J60 to ESP32_S2/S3/C3

##### W6100

`FULL_DUPLEX, 100Mbps`

<p align="center">
    <img src="https://github.com/khoih-prog/HTTPS_Server_Generic/raw/main/Images/W6100.png">
</p>

---


#### W5500

`FULL_DUPLEX, 100Mbps`

<p align="center">
    <img src="https://github.com/khoih-prog/HTTPS_Server_Generic/raw/main/Images/W5500.png">
</p>

<p align="center">
    <img src="https://github.com/khoih-prog/HTTPS_Server_Generic/raw/main/Images/W5500_small.png">
</p> 
 
---


##### ENC28J60

`FULL_DUPLEX, 10Mbps`

<p align="center">
    <img src="https://github.com/khoih-prog/HTTPS_Server_Generic/raw/main/Images/ENC28J60.png">
</p>

---

#### ESP32S3_DEV

<p align="center">
    <img src="https://github.com/khoih-prog/HTTPS_Server_Generic/raw/main/Images/ESP32S3_DEV.png">
</p> 

You can change the `INT` pin to another one. Default is `GPIO4`

```cpp
// Must connect INT to GPIOxx or not working
#define INT_GPIO            4
```

---

|W5500, W6100 or ENC28J60|<--->|ESP32_S3|
|:-:|:-:|:-:|
|MOSI|<--->|GPIO11|
|MISO|<--->|GPIO13|
|SCK|<--->|GPIO12|
|CS/SS|<--->|GPIO10|
|INT|<--->|GPIO4|
|RST|<--->|RST|
|GND|<--->|GND|
|3.3V|<--->|3.3V|

---

#### ESP32S2_DEV


<p align="center">
    <img src="https://github.com/khoih-prog/HTTPS_Server_Generic/raw/main/Images/ESP32S2_DEV.png">
</p> 


You can change the `INT` pin to another one. Default is `GPIO4`

```cpp
// Must connect INT to GPIOxx or not working
#define INT_GPIO            4
```

|W5500, W6100 or ENC28J60|<--->|ESP32_S2|
|:-:|:-:|:-:|
|MOSI|<--->|GPIO35|
|MISO|<--->|GPIO37|
|SCK|<--->|GPIO36|
|CS/SS|<--->|GPIO34|
|INT|<--->|GPIO4|
|RST|<--->|RST|
|GND|<--->|GND|
|3.3V|<--->|3.3V|


---

#### ESP32C3_DEV

<p align="center">
    <img src="https://github.com/khoih-prog/HTTPS_Server_Generic/raw/main/Images/ESP32_C3_DevKitC_02.png">
</p> 


You can change the `INT` pin to another one. Default is `GPIO4`

```cpp
// Must connect INT to GPIOxx or not working
#define INT_GPIO            10
```

|W5500, W6100 or ENC28J60|<--->|ESP32_C3|
|:-:|:-:|:-:|
|MOSI|<--->|GPIO6|
|MISO|<--->|GPIO5|
|SCK|<--->|GPIO4|
|CS/SS|<--->|GPIO7|
|INT|<--->|GPIO10|
|RST|<--->|RST|
|GND|<--->|GND|
|3.3V|<--->|3.3V|


---
---

## HOWTO Example Usage

You will find several examples showing how you can use the library:

- [Static-Page](examples/ESP32_WiFi/Static-Page/Static-Page.ino): Short example showing how to serve some static resources with the server. You should start with this sketch and get familiar with it before having a look at the more complex examples.
- [Parameters](examples/ESP32_WiFi/Parameters/Parameters.ino): Shows how you can access request parameters (the part after the question mark in the URL) or parameters in dynamic URLs (like /led/1, /led/2, ...)
- [Put-Post-Echo](examples/ESP32_WiFi/Put-Post-Echo/Put-Post-Echo.ino): Implements a simple echo service for PUT and POST requests that returns the request body as response body. Also shows how to differentiate between multiple HTTP methods for the same URL.
- [HTTPS-and-HTTP](examples/ESP32_WiFi/HTTPS-and-HTTP/HTTPS-and-HTTP.ino): Shows how to serve resources via HTTP and HTTPS in parallel and how to check if the user is using a secure connection during request handling
- [Middleware](examples/ESP32_WiFi/Middleware/Middleware.ino): Shows how to use the middleware API for logging. Middleware functions are defined very similar to webservers like Express.
- [Authentication](examples/ESP32_WiFi/Authentication/Authentication.ino): Implements a chain of two middleware functions to handle authentication and authorization using HTTP Basic Auth.
- [Async-Server](examples/ESP32_WiFi/Async-Server/Async-Server.ino): Like the Static-Page example, but the server runs in a separate task on the ESP32, so you do not need to call the `loop()` function in your main sketch.
- [Websocket-Chat](examples/ESP32_WiFi/Websocket-Chat/Websocket-Chat.ino): Provides a browser-based chat built on top of websockets. **Note:** Websockets are still under development!
- [Parameter-Validation](examples/ESP32_WiFi/Parameter-Validation/Parameter-Validation.ino): Shows how you can integrate validator functions to do formal checks on parameters in your URL.
- [Self-Signed-Certificate](examples/ESP32_WiFi/Self-Signed-Certificate/Self-Signed-Certificate.ino): Shows how to generate a `self-signed certificate` on the fly on the ESP when the sketch starts. You do not need to run `create_cert.sh` to use this example.
- [REST-API](examples/ESP32_WiFi/REST-API/REST-API.ino): Uses [ArduinoJSON](https://arduinojson.org/) and [SPIFFS file upload](https://github.com/me-no-dev/arduino-esp32fs-plugin) to serve a small web interface that provides a REST API.

---
---

### Examples

#### For ESP32_WiFi

 1. [Async-Server](examples/ESP32_WiFi/Async-Server)
 2. [Authentication](examples/ESP32_WiFi/Authentication) 
 3. [HTML-Forms](examples/ESP32_WiFi/HTML-Forms)
 4. [HTTPS-and-HTTP](examples/ESP32_WiFi/HTTPS-and-HTTP)
 5. [Middleware](examples/ESP32_WiFi/Middleware)
 6. [Parameters](examples/ESP32_WiFi/Parameters)
 7. [Parameter-Validation](examples/ESP32_WiFi/Parameter-Validation)
 8. [Put-Post-Echo](examples/ESP32_WiFi/Put-Post-Echo)
 9. [REST-API](examples/ESP32_WiFi/REST-API)
10. [Self-Signed-Certificate](examples/ESP32_WiFi/Self-Signed-Certificate)
11. [Static-Page](examples/ESP32_WiFi/Static-Page)
12. [Websocket-Chat](examples/ESP32_WiFi/Websocket-Chat)

#### For WT32_ETH01

 1. [Async-Server](examples/WT32_ETH01/Async-Server)
 2. [Authentication](examples/WT32_ETH01/Authentication) 
 3. [HTML-Forms](examples/WT32_ETH01/HTML-Forms)
 4. [HTTPS-and-HTTP](examples/WT32_ETH01/HTTPS-and-HTTP)
 5. [Middleware](examples/WT32_ETH01/Middleware)
 6. [Parameters](examples/WT32_ETH01/Parameters)
 7. [Parameter-Validation](examples/WT32_ETH01/Parameter-Validation)
 8. [Put-Post-Echo](examples/WT32_ETH01/Put-Post-Echo)
 9. [REST-API](examples/WT32_ETH01/REST-API)
10. [Self-Signed-Certificate](examples/WT32_ETH01/Self-Signed-Certificate)
11. [Static-Page](examples/WT32_ETH01/Static-Page)
12. [Websocket-Chat](examples/WT32_ETH01/Websocket-Chat)

#### For ESP32_W5500

 1. [Async-Server](examples/ESP32_W5500/Async-Server)
 2. [Authentication](examples/ESP32_W5500/Authentication) 
 3. [HTML-Forms](examples/ESP32_W5500/HTML-Forms)
 4. [HTTPS-and-HTTP](examples/ESP32_W5500/HTTPS-and-HTTP)
 5. [Middleware](examples/ESP32_W5500/Middleware)
 6. [Parameters](examples/ESP32_W5500/Parameters)
 7. [Parameter-Validation](examples/ESP32_W5500/Parameter-Validation)
 8. [Put-Post-Echo](examples/ESP32_W5500/Put-Post-Echo)
 9. [REST-API](examples/ESP32_W5500/REST-API)
10. [Self-Signed-Certificate](examples/ESP32_W5500/Self-Signed-Certificate)
11. [Static-Page](examples/ESP32_W5500/Static-Page)
12. [Websocket-Chat](examples/ESP32_W5500/Websocket-Chat)

#### For ESP32_W6100

 1. [Async-Server](examples/ESP32_W6100/Async-Server)
 2. [Authentication](examples/ESP32_W6100/Authentication) 
 3. [HTML-Forms](examples/ESP32_W6100/HTML-Forms)
 4. [HTTPS-and-HTTP](examples/ESP32_W6100/HTTPS-and-HTTP)
 5. [Middleware](examples/ESP32_W6100/Middleware)
 6. [Parameters](examples/ESP32_W6100/Parameters)
 7. [Parameter-Validation](examples/ESP32_W6100/Parameter-Validation)
 8. [Put-Post-Echo](examples/ESP32_W6100/Put-Post-Echo)
 9. [REST-API](examples/ESP32_W6100/REST-API)
10. [Self-Signed-Certificate](examples/ESP32_W6100/Self-Signed-Certificate)
11. [Static-Page](examples/ESP32_W6100/Static-Page)
12. [Websocket-Chat](examples/ESP32_W6100/Websocket-Chat)


#### For ESP32_ENC

 1. [Async-Server](examples/ESP32_ENC/Async-Server)
 2. [Authentication](examples/ESP32_ENC/Authentication) 
 3. [HTML-Forms](examples/ESP32_ENC/HTML-Forms)
 4. [HTTPS-and-HTTP](examples/ESP32_ENC/HTTPS-and-HTTP)
 5. [Middleware](examples/ESP32_ENC/Middleware)
 6. [Parameters](examples/ESP32_ENC/Parameters)
 7. [Parameter-Validation](examples/ESP32_ENC/Parameter-Validation)
 8. [Put-Post-Echo](examples/ESP32_ENC/Put-Post-Echo)
 9. [REST-API](examples/ESP32_ENC/REST-API)
10. [Self-Signed-Certificate](examples/ESP32_ENC/Self-Signed-Certificate)
11. [Static-Page](examples/ESP32_ENC/Static-Page)
12. [Websocket-Chat](examples/ESP32_ENC/Websocket-Chat)

#### For ESP32_SC_W5500

 1. [Async-Server](examples/ESP32_SC_W5500/Async-Server)
 2. [Authentication](examples/ESP32_SC_W5500/Authentication) 
 3. [HTML-Forms](examples/ESP32_SC_W5500/HTML-Forms)
 4. [HTTPS-and-HTTP](examples/ESP32_SC_W5500/HTTPS-and-HTTP)
 5. [Middleware](examples/ESP32_SC_W5500/Middleware)
 6. [Parameters](examples/ESP32_SC_W5500/Parameters)
 7. [Parameter-Validation](examples/ESP32_SC_W5500/Parameter-Validation)
 8. [Put-Post-Echo](examples/ESP32_SC_W5500/Put-Post-Echo)
 9. [REST-API](examples/ESP32_SC_W5500/REST-API)
10. [Self-Signed-Certificate](examples/ESP32_SC_W5500/Self-Signed-Certificate)
11. [Static-Page](examples/ESP32_SC_W5500/Static-Page)
12. [Websocket-Chat](examples/ESP32_SC_W5500/Websocket-Chat)

#### For ESP32_SC_W6100

 1. [Async-Server](examples/ESP32_SC_W6100/Async-Server)
 2. [Authentication](examples/ESP32_SC_W6100/Authentication) 
 3. [HTML-Forms](examples/ESP32_SC_W6100/HTML-Forms)
 4. [HTTPS-and-HTTP](examples/ESP32_SC_W6100/HTTPS-and-HTTP)
 5. [Middleware](examples/ESP32_SC_W6100/Middleware)
 6. [Parameters](examples/ESP32_SC_W6100/Parameters)
 7. [Parameter-Validation](examples/ESP32_SC_W6100/Parameter-Validation)
 8. [Put-Post-Echo](examples/ESP32_SC_W6100/Put-Post-Echo)
 9. [REST-API](examples/ESP32_SC_W6100/REST-API)
10. [Self-Signed-Certificate](examples/ESP32_SC_W6100/Self-Signed-Certificate)
11. [Static-Page](examples/ESP32_SC_W6100/Static-Page)
12. [Websocket-Chat](examples/ESP32_SC_W6100/Websocket-Chat)

#### For ESP32_SC_ENC

 1. [Async-Server](examples/ESP32_SC_ENC/Async-Server)
 2. [Authentication](examples/ESP32_SC_ENC/Authentication) 
 3. [HTML-Forms](examples/ESP32_SC_ENC/HTML-Forms)
 4. [HTTPS-and-HTTP](examples/ESP32_SC_ENC/HTTPS-and-HTTP)
 5. [Middleware](examples/ESP32_SC_ENC/Middleware)
 6. [Parameters](examples/ESP32_SC_ENC/Parameters)
 7. [Parameter-Validation](examples/ESP32_SC_ENC/Parameter-Validation)
 8. [Put-Post-Echo](examples/ESP32_SC_ENC/Put-Post-Echo)
 9. [REST-API](examples/ESP32_SC_ENC/REST-API)
10. [Self-Signed-Certificate](examples/ESP32_SC_ENC/Self-Signed-Certificate)
11. [Static-Page](examples/ESP32_SC_ENC/Static-Page)
12. [Websocket-Chat](examples/ESP32_SC_ENC/Websocket-Chat)


---
---

### Example [Async-Server](examples/ESP32_W5500/Async-Server)

https://github.com/khoih-prog/HTTPS_Server_Generic/blob/804d9320ceba0ccf51ac1f4bfcf6263a89214495/examples/ESP32_W5500/Async-Server/Async-Server.ino#L19-L250

---
---

### Debug Terminal Output Samples

#### 1. Async_Server on ESP32_DEV with ESP32_ENC28J60

Following are debug terminal output when running example [Async-Server](examples/ESP32_ENC/Async-Server) on `ESP32_DEV with LwIP ENC28J60`, using ESP32 core `v2.0.0+`, to demonstrate the operation Async HTTPS WebServer serving multiple clients simultaneously


```cpp
Starting Async_Server on ESP32_DEV with ESP32_ENC28J60
WebServer_ESP32_ENC v1.5.1 for core v2.0.0+
HTTPS_Server_Generic v1.5.0

ETH Started
ETH Connected
ETH MAC: DE:AD:BE:EF:BE:14, IPv4: 192.168.2.232
FULL_DUPLEX, 10Mbps
HTTPS EthernetWebServer is @ IP : 192.168.2.232
To access, use https://192.168.2.232
Creating server task... 
loop()
Starting server...
Server ready.
[HTTPS:I] New connection. Socket FID=49
loop()
[HTTPS:I] New connection. Socket FID=50
[HTTPS:I] Request: GET / (FID=49)
loop()
loop()
[HTTPS:I] Request: GET / (FID=49)
loop()
...
```

---

#### 2. Async_Server on ESP32_DEV with ESP32_W5500

Following are debug terminal output when running example [Async-Server](examples/ESP32_W5500/Async-Server) on `ESP32_DEV with LwIP W5500`, using ESP32 core `v2.0.0+`, to demonstrate the operation Async HTTPS WebServer serving multiple clients simultaneously


```cpp
Starting Async_Server on ESP32_DEV with ESP32_W5500
WebServer_ESP32_W5500 v1.5.2 for core v2.0.0+
HTTPS_Server_Generic v1.5.0

ETH Started
ETH Connected
ETH MAC: DE:AD:BE:EF:BE:08, IPv4: 192.168.2.88
FULL_DUPLEX, 100Mbps
HTTPS EthernetWebServer is @ IP : 192.168.2.88
To access, use https://192.168.2.88
Creating server task... 
loop()
Starting server...
Server ready.
[HTTPS:I] New connection. Socket FID=49
[HTTPS:I] Request: GET / (FID=49)
loop()
[HTTPS:I] Request: GET / (FID=49)
loop()
[HTTPS:I] Request: GET / (FID=49)
loop()
.
```

#### 3. Async_Server on ESP32S3_DEV with ESP32_S3_ENC28J60

Following are debug terminal output when running example [Async-Server](examples/ESP32_SC_ENC/Async-Server) on `ESP32S3_DEV with LwIP ENC28J60`, using ESP32 core `v2.0.0+`, to demonstrate the operation Async HTTPS WebServer serving multiple clients simultaneously


```cpp
Starting Async_Server on ESP32S3_DEV with ESP32_S3_ENC28J60
WebServer_ESP32_SC_ENC v1.2.0 for core v2.0.0+
HTTPS_Server_Generic v1.5.0

ETH Started
ETH Connected
ETH MAC: DE:AD:BE:EF:FE:03, IPv4: 192.168.2.232
FULL_DUPLEX, 10Mbps
HTTPS EthernetWebServer is @ IP : 192.168.2.232
To access, use https://192.168.2.232
Creating server task... 
loop()
Starting server...
Server ready.
loop()
loop()
[HTTPS:I] New connection. Socket FID=49
loop()
[HTTPS:I] New connection. Socket FID=50
[HTTPS:I] Request: GET / (FID=49)
loop()
loop()
loop()
loop()
[HTTPS:I] Connection timeout. FID=50
[HTTPS:I] Connection closed. Socket FID=50
[HTTPS:I] Connection timeout. FID=49
[HTTPS:I] Connection closed. Socket FID=49
loop()
...
```

---

#### 4. Async_Server on ESP32S3_DEV with ESP32_S3_W5500

Following are debug terminal output when running example [Async-Server](examples/ESP32_SC_W5500/Async-Server) on `ESP32S3_DEV with LwIP W5500`, using ESP32 core `v2.0.0+`, to demonstrate the operation Async HTTPS WebServer serving multiple clients simultaneously


```cpp
Starting Async_Server on ESP32S3_DEV with ESP32_S3_W5500
WebServer_ESP32_SC_W5500 v1.2.1 for core v2.0.0+
HTTPS_Server_Generic v1.5.0

ETH Started
ETH Connected
ETH MAC: DE:AD:BE:EF:BE:14, IPv4: 192.168.2.89
FULL_DUPLEX, 100Mbps
HTTPS EthernetWebServer is @ IP : 192.168.2.89
To access, use https://192.168.2.89
Creating server task... 
loop()
Starting server...
Server ready.
loop()
loop()
loop()
loop()
loop()
loop()
[HTTPS:I] New connection. Socket FID=49
[HTTPS:I] Request: GET / (FID=49)
[HTTPS:I] Request: GET /favicon.ico (FID=49)
loop()
loop()
loop()
loop()
[HTTPS:I] Connection timeout. FID=49
[HTTPS:I] Connection closed. Socket FID=49
loop()
.
```

---

#### 5. Async_Server on ESP32C3_DEV with ESP32_C3_W5500

Following are debug terminal output when running example [Async-Server](examples/ESP32_SC_W5500/Async-Server) on `ESP32C3_DEV with LwIP W5500`, using ESP32 core `v2.0.0+`, to demonstrate the operation Async HTTPS WebServer serving multiple clients simultaneously


```
Starting Async_Server on ESP32C3_DEV with ESP32_C3_W5500
WebServer_ESP32_SC_W5500 v1.2.1 for core v2.0.0+
HTTPS_Server_Generic v1.5.0
Using built-in mac_eth = 7C:DF:A1:BC:BC:53

ETH Started
ETH Connected
ETH MAC: 7C:DF:A1:BC:BC:53, IPv4: 192.168.2.135
FULL_DUPLEX, 100Mbps
HTTPS EthernetWebServer is @ IP : 192.168.2.135
To access, use https://192.168.2.135
Creating server task... 
Starting server...
Server ready.
loop()
...
loop()
[HTTPS:I] New connection. Socket FID=49
[HTTPS:E] SSL_accept failed. Aborting handshake. FID=49
[HTTPS:I] Connection closed. Socket FID=49
loop()
[HTTPS:I] New connection. Socket FID=49
[HTTPS:E] SSL_accept failed. Aborting handshake. FID=49
[HTTPS:I] Connection closed. Socket FID=49
[HTTPS:I] New connection. Socket FID=49
[HTTPS:I] Request: GET / (FID=49)
[HTTPS:I] Request: GET /favicon.ico (FID=49)
loop()
...
```


---

#### 6. Async_Server on ESP32_DEV with ESP32_W6100

Following are debug terminal output when running example [Async-Server](examples/ESP32_W6100/Async-Server) on `ESP32_DEV with LwIP W6100`, using ESP32 core `v2.0.0+`, to demonstrate the operation Async HTTPS WebServer serving multiple clients simultaneously


```cpp
Starting Async_Server on ESP32_DEV with ESP32_W6100
WebServer_ESP32_W6100 v1.5.2 for core v2.0.0+
HTTPS_Server_Generic v1.5.0

ETH Started
ETH Connected
ETH MAC: 0C:B8:15:D8:01:D7, IPv4: 192.168.2.158
FULL_DUPLEX, 100Mbps
HTTPS EthernetWebServer is @ IP : 192.168.2.158
To access, use https://192.168.2.158
Creating server task... 
loop()
Starting server...
Server ready.
loop()
loop()
loop()
loop()
loop()
loop()
loop()
[HTTPS:I] New connection. Socket FID=49
[HTTPS:I] Request: GET / (FID=49)
[HTTPS:I] Request: GET /favicon.ico (FID=49)
loop()
loop()
loop()
loop()
[HTTPS:I] Connection timeout. FID=49
[HTTPS:I] Connection closed. Socket FID=49
loop()
loop()
...
```

---

#### 7. Async_Server on ESP32S3_DEV with ESP32_S3_W6100

Following are debug terminal output when running example [Async-Server](examples/ESP32_SC_W6100/Async-Server) on `ESP32S3_DEV with LwIP W6100`, using ESP32 core `v2.0.0+`, to demonstrate the operation Async HTTPS WebServer serving multiple clients simultaneously


```
Starting Async_Server on ESP32S3_DEV with ESP32_S3_W6100
WebServer_ESP32_SC_W6100 v1.2.1 for core v2.0.0+
HTTPS_Server_Generic v1.5.0

ETH Started
ETH Connected
ETH MAC: FE:ED:DE:AD:BE:EF, IPv4: 192.168.2.92
FULL_DUPLEX, 100Mbps
HTTPS EthernetWebServer is @ IP : 192.168.2.92
To access, use https://192.168.2.92

Creating server task... 
loop()
Starting server...
Server ready.
loop()
loop()
[HTTPS:I] New connection. Socket FID=49
loop()
[HTTPS:I] New connection. Socket FID=50
[HTTPS:I] Request: GET / (FID=49)
loop()
loop()
loop()
loop()
[HTTPS:I] Connection timeout. FID=50
[HTTPS:I] Connection closed. Socket FID=50
[HTTPS:I] Connection timeout. FID=49
[HTTPS:I] Connection closed. Socket FID=49
loop()
loop()
loop()
...
```

---
---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of Arduino IDE, the Arduino core or depending libraries.

Sometimes, the library will only work if you update the related core to the latest version because I'm always using the latest cores /libraries.

---

### Issues ###

Submit issues to: [HTTPS_Server_Generic issues](https://github.com/khoih-prog/HTTPS_Server_Generic/issues)

---
---

## TO DO

 1. Fix bug. Add enhancement
 2. For ESP32, using `ESP_TLS` for future ESP-IDF v5.0 instead of to-be-deprecated `OpenSSL`
 3. Using [ArduinoJson](https://github.com/bblanchon/ArduinoJson) `v6` instead of `v5.13.5-`
 4. Add support to more powerful-enough boards using LwIP WiFi/Ethernet, such as  :
   - `ESP8266` WiFi / Ethernet
   - `Portenta_H7` WiFi / Ethernet
   - `RP2040W` WiFi
   - `Teensy 4.1` QNEthernet
   - etc.

---

## DONE

 1. Initial port to `ESP32` boards using `LwIP` Ethernet, such as `WT32_ETH01`, `ESP32_W5500`, `ESP32_ENC`
 2. Add Table-of-Contents and Version String
 3. Use `allman astyle` and add `utils`
 4. Add support to `ESP32S3` using `LwIP W5500 or ENC28J60`
 4. Add support to `ESP32S2/C3` using `LwIP W5500 or ENC28J60`
 5. Add support to `ESP32` and `ESP32S2/S3/C3` boards using `LwIP W6100 Ethernet`
 
 
---
---


### Contributions and Thanks

1. Based on and modified from [Frank Hessel's esp32_https_server](https://github.com/fhessel/esp32_https_server). Many thanks to [Frank Hessel](https://github.com/fhessel) for the great [esp32_https_server](https://github.com/fhessel/esp32_https_server) library


<table>
  <tr>
    <td align="center"><a href="https://github.com/fhessel"><img src="https://github.com/fhessel.png" width="100px;" alt="fhessel"/><br /><sub><b>⭐️⭐️ Frank Hessel</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/HTTPS_Server_Generic/blob/main/LICENSE)

---

## Copyright

- Copyright (c) 2017- Frank Hessel

- Copyright (c) 2022- Khoi Hoang



