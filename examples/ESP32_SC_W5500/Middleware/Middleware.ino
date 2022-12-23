/**
   Example for the ESP32_SC_W5500 HTTP(S) Webserver

   IMPORTANT NOTE:
   To run this script, your need to
    1) Make sure to have certificate data available. You will find a
       shell script (create_cert.sh) and instructions to do so in the library folder
       under extras/

   This script will install an HTTPS Server on your ESP32_SC_W5500 with the following
   functionalities:
    - Show simple page on web server root
    - Run a middleware that logs every request
    - 404 for everything else
*/

// Include certificate data (see note above)
#include "cert.h"
#include "private_key.h"

//////////////////////////////////////////////////

// For ESP32_SC_W5500
#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       3

//////////////////////////////////////////////////////////

// For ESP32-S3
// Optional values to override default settings
// Don't change unless you know what you're doing
//#define ETH_SPI_HOST        SPI3_HOST
//#define SPI_CLOCK_MHZ       25

// Must connect INT to GPIOxx or not working
//#define INT_GPIO            4

//#define MISO_GPIO           13
//#define MOSI_GPIO           11
//#define SCK_GPIO            12
//#define CS_GPIO             10

// For ESP32_C3
// Optional values to override default settings
// Don't change unless you know what you're doing
//#define ETH_SPI_HOST        SPI2_HOST
//#define SPI_CLOCK_MHZ       25

// Must connect INT to GPIOxx or not working
//#define INT_GPIO            10

//#define MISO_GPIO           5
//#define MOSI_GPIO           6
//#define SCK_GPIO            4
//#define CS_GPIO             7

//////////////////////////////////////////////////////////

#include <WebServer_ESP32_SC_W5500.h>

//////////////////////////////////////////////////

// Enter a MAC address and IP address for your controller below.
#define NUMBER_OF_MAC      20

byte mac[][NUMBER_OF_MAC] =
{
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x02 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x03 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x04 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x05 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x06 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x07 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x08 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x09 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0A },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0B },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0C },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0D },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0E },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0F },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x10 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x11 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x12 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x13 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x14 },
};

// Select the IP address according to your local network
IPAddress myIP(192, 168, 2, 232);
IPAddress myGW(192, 168, 2, 1);
IPAddress mySN(255, 255, 255, 0);

// Google DNS Server IP
IPAddress myDNS(8, 8, 8, 8);

//////////////////////////////////////////////////

#include <HTTPS_Server_Generic.h>

// The HTTPS Server comes in a separate namespace. For easier use, include it here.
using namespace httpsserver;

// Create an SSL certificate object from the files included above
SSLCert cert = SSLCert(
                 example_crt_DER, example_crt_DER_len,
                 example_key_DER, example_key_DER_len
               );

// Create an SSL-enabled server that uses the certificate
// The constructor takes some more parameters, but we go for default values here.
HTTPSServer secureServer = HTTPSServer(&cert);

// Declare a middleware function.
// Parameters:
// req: Request data, can be used to access URL, HTTP Method, Headers, ...
// res: Response data, can be used to access HTTP Status, Headers, ...
// next: This function is used to pass control down the chain. If you have done your work
//       with the request object, you may decide if you want to process the request.
//       If you do so, you call the next() function, and the next middleware function (if
//       there is any) or the actual requestHandler will be called.
//       If you want to skip the request, you do not call next, and set for example status
//       code 403 on the response to show that the user is not allowed to access a specific
//       resource.
//       The Authentication examples provides more details on this.
// We want to log the following information for every request:
// - Response Status
// - Request Method
// - Request String (URL + Parameters)
void middlewareLogging(HTTPRequest * req, HTTPResponse * res, std::function<void()> next)
{
  // We want to print the response status, so we need to call next() first.
  next();
  // After the call, the status is (hopefully) set by the handler function, so we can
  // access it for logging.
  Serial.printf("middlewareLogging(): %3d\t%s\t\t%s\n",
                // Status code (like: 200)
                res->getStatusCode(),
                // Method used for the request (like: GET)
                req->getMethod().c_str(),
                // Request string (like /index.html)
                req->getRequestString().c_str());
}

// For details on the implementation of the handler functions, refer to the Static-Page example.
void handleRoot(HTTPRequest * req, HTTPResponse * res)
{
  res->setHeader("Content-Type", "text/html");
  res->println("<!DOCTYPE html>");
  res->println("<html>");
  res->println("<head><title>Hello World!</title></head>");
  res->println("<body>");
  res->println("<h1>Hello World!</h1>");
  res->print("<p>Your server is running for ");
  res->print((int)(millis() / 1000), DEC);
  res->println(" seconds.</p>");
  res->println("</body>");
  res->println("</html>");
}

void handle404(HTTPRequest * req, HTTPResponse * res)
{
  req->discardRequestBody();
  res->setStatusCode(404);
  res->setStatusText("Not Found");
  res->setHeader("Content-Type", "text/html");
  res->println("<!DOCTYPE html>");
  res->println("<html>");
  res->println("<head><title>Not Found</title></head>");
  res->println("<body><h1>404 Not Found</h1><p>The requested resource was not found on this server.</p></body>");
  res->println("</html>");
}

void setup()
{
  // For logging
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  delay(500);

  ///////////////////////////////////////////////

  Serial.print("\nStarting Middleware on " + String(ARDUINO_BOARD));
  Serial.println(" with " + String(SHIELD_TYPE));
  Serial.println(WEBSERVER_ESP32_SC_W5500_VERSION);
  Serial.println(HTTPS_SERVER_GENERIC_VERSION);

  ///////////////////////////////////

  // To be called before ETH.begin()
  ESP32_W5500_onEvent();

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;

  //bool begin(int MISO_GPIO, int MOSI_GPIO, int SCLK_GPIO, int CS_GPIO, int INT_GPIO, int SPI_CLOCK_MHZ,
  //           int SPI_HOST, uint8_t *W5500_Mac = W5500_Default_Mac);
  //ETH.begin( MISO_GPIO, MOSI_GPIO, SCK_GPIO, CS_GPIO, INT_GPIO, SPI_CLOCK_MHZ, ETH_SPI_HOST );
  ETH.begin( MISO_GPIO, MOSI_GPIO, SCK_GPIO, CS_GPIO, INT_GPIO, SPI_CLOCK_MHZ, ETH_SPI_HOST, mac[index] );

  // Static IP, leave without this line to get IP via DHCP
  //bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = 0, IPAddress dns2 = 0);
  //ETH.config(myIP, myGW, mySN, myDNS);

  ESP32_W5500_waitForConnect();

  ///////////////////////////////////

  Serial.print(F("HTTPS EthernetWebServer is @ IP : "));
  Serial.println(ETH.localIP());

  Serial.print(F("To access, use https://"));
  Serial.println(ETH.localIP());

  ///////////////////////////////////////////////

  // For every resource available on the server, we need to create a ResourceNode
  // The ResourceNode links URL and HTTP method to a handler function
  ResourceNode * nodeRoot    = new ResourceNode("/", "GET", &handleRoot);
  ResourceNode * node404     = new ResourceNode("", "GET", &handle404);

  // Add the root node to the server
  secureServer.registerNode(nodeRoot);

  // Add the 404 not found node to the server.
  // The path is ignored for the default node.
  secureServer.setDefaultNode(node404);

  // Add the middleware. The function will be called globally for every request
  // Note: The functions are called in the order they are added to the server.
  // Also, if you want a middleware to handle only specific requests, you can check
  // the URL within the middleware function.
  secureServer.addMiddleware(&middlewareLogging);

  Serial.println("Starting server...");
  secureServer.start();

  if (secureServer.isRunning())
  {
    Serial.println("Server ready.");
  }
}

void loop()
{
  // This call will let the server do its work
  secureServer.loop();

  // Other code would go here...
  delay(1);
}
