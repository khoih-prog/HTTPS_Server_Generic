/**
   Example for the ESP32_SC_ENC HTTP(S) Webserver

   IMPORTANT NOTE:
   To run this script, you need to
    1) Make sure to have certificate data available. You will find a
       shell script (create_cert.sh) and instructions to do so in the library folder
       under extras/

   This script will install an HTTPS Server on your ESP32_SC_ENC with the following
   functionalities:
    - Shows you a page with some LEDs and allow you to turn them on or off
      Parameters for the URLs are checked, so that you cannot address non-existing objects
    - 404 for everything else
   If you want to see the LEDs, connect them to GPIOs 33 (red), 25 (yellow), 26 (green)
   and 27 (blue).
*/

// Include certificate data (see note above)
#include "cert.h"
#include "private_key.h"

//////////////////////////////////////////////////

// For ESP32_SC_ENC
#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       3

//////////////////////////////////////////////////////////

// For ESP32-S3
// Optional values to override default settings
//#define ETH_SPI_HOST        SPI2_HOST
//#define SPI_CLOCK_MHZ       8

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
//#define SPI_CLOCK_MHZ       8

// Must connect INT to GPIOxx or not working
//#define INT_GPIO            10

//#define MISO_GPIO           5
//#define MOSI_GPIO           6
//#define SCK_GPIO            4
//#define CS_GPIO             7

//////////////////////////////////////////////////////////

#include <WebServer_ESP32_SC_ENC.h>

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

// We use strings
#include <string>

#include <HTTPS_Server_Generic.h>

// The HTTPS Server comes in a separate namespace. For easier use, include it here.
using namespace httpsserver;

// Create an SSL certificate object from the files included above
SSLCert cert = SSLCert(
                 example_crt_DER, example_crt_DER_len,
                 example_key_DER, example_key_DER_len
               );

// Create an SSL-enabled server that uses the certificate
// The contstructor takes some more parameters, but we go for default values here.
HTTPSServer secureServer = HTTPSServer(&cert);

// A class that defines an LED
class LED
{
  public:
    /** Name for the LED */
    const std::string _name;
    /** Pin that it's connected to */
    const uint8_t _pin;
    /** Current state */
    bool _on;
    /** Constructor */
    LED(const std::string name, uint8_t pin): _name(name), _pin(pin)
    {
      _on = false;
      pinMode(pin, OUTPUT);
    }

    /** Method to turn the led on or of */
    void setOn(bool on)
    {
      digitalWrite(_pin, on ? HIGH : LOW);
      _on = on;
    }
};

// We create some LEDs:
#define LEDCOUNT 4
LED myLEDs[LEDCOUNT] =
{
  LED("Red LED",    33),
  LED("Yellow LED", 25),
  LED("Green LED",  26),
  LED("Blue LED",   27)
};

// Root node, will show the LEDs that are available
void handleRoot(HTTPRequest * req, HTTPResponse * res)
{
  // We will deliver an HTML page
  res->setHeader("Content-Type", "text/html");

  // Write the response page
  res->println("<!DOCTYPE html>");
  res->println("<html><head><style>");
  res->println("* {font-family: sans-serif; font-size:12px}");
  res->println("form.on {background: #ffffcc;color:black;}");
  res->println("form.off {background: #404040;color:white;}");
  res->println("</style><title>Parameter Validation Example</title></head>");
  res->println("<body>");

  // Iterate over the LEDs.
  for (int id = 0; id < LEDCOUNT; id++)
  {
    LED * led = &myLEDs[id];

    res->print(
      "<form "
      "style=\"border:1px solid black;padding:10px;width:300px;margin:10px;float:left\" "
      "method=\"post\" "
      "class=\"");
    res->print(led->_on ? "on" : "off");
    res->print(
      "\" "
      "action=\"/led/"
    );

    res->print(id);
    res->print("/");
    res->print(led->_on ? 0 : 1);
    res->print(
      "\">"
      "<p style=\"text-align:center;font-size:16px;\">"
    );
    res->printStd(led->_name);
    res->print("</p><button type=\"submit\">Turn ");
    res->print(led->_on ? "off" : "on");
    res->print("</button></form>");
  }

  res->print(
    "<form method=\"post\" action=\"/led/foobar/1\" style=\"clear:both\">"
    "<p>To see that the validator functions are working as expected, you can e.g. call <button type=\"submit\">POST /led/foobar/1</button>.</p>"
    "</form>"
    "</body>"
    "</html>"
  );
}

// Node to switch an LED on or off
// This is the handler for our post callback. We can work with the parameters without further
// validation, as the server assures this function only gets called if the validation succeeded.
void handleSwitch(HTTPRequest * req, HTTPResponse * res)
{
  // POST, so drain the input, if any
  req->discardRequestBody();

  // Get access to the parameters
  ResourceParameters * params = req->getParams();

  // Get the LED that is requested.
  // Note that we can call stoi safely without further validation, as we
  // defined that is has to be an unsigned integer and must not be >LEDCOUNT-1
  LED * led = &myLEDs[std::stoi(params->getPathParameter(0))];

  // Set the state of the LED. The value of the parameter can only be "0" or "1" here,
  // otherwise the server would not have called the handler.
  led->setOn(params->getPathParameter(1) != "0");

  // Redirect the user to the main page
  res->setStatusCode(303);
  // This should make the browser do a GET /
  res->setStatusText("See Other");
  res->setHeader("Location", "/");
  res->println("Redirecting...");
}

// Validation function for the LED ID and state
// This function is the validator for the second parameter of the POST /led route.
// It accepts only the strings "0" (off) and "1" (on)
bool validateLEDState(std::string s)
{
  return s == "0" || s == "1";
}

// This function is a validator for the first parameter of the POST /led route.
// We did check before that the parameter is an integer, now we check its range.
bool validateLEDID(std::string s)
{
  uint32_t id = std::stoul(s);

  return id < LEDCOUNT;
}

// Default handler for resources that do not exist
// For details to this function, see the Static-Page example
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

  Serial.print("\nStarting Parameter_Validation on " + String(ARDUINO_BOARD));
  Serial.println(" with " + String(SHIELD_TYPE));
  Serial.println(WEBSERVER_ESP32_SC_ENC_VERSION);
  Serial.println(HTTPS_SERVER_GENERIC_VERSION);

  ///////////////////////////////////

  // To be called before ETH.begin()
  ESP32_ENC_onEvent();

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;

  //bool begin(int MISO_GPIO, int MOSI_GPIO, int SCLK_GPIO, int CS_GPIO, int INT_GPIO, int SPI_CLOCK_MHZ,
  //           int SPI_HOST, uint8_t *ENC28J60_Mac = ENC28J60_Default_Mac);
  //ETH.begin( MISO_GPIO, MOSI_GPIO, SCK_GPIO, CS_GPIO, INT_GPIO, SPI_CLOCK_MHZ, ETH_SPI_HOST );
  ETH.begin( MISO_GPIO, MOSI_GPIO, SCK_GPIO, CS_GPIO, INT_GPIO, SPI_CLOCK_MHZ, ETH_SPI_HOST, mac[index] );

  // Static IP, leave without this line to get IP via DHCP
  //bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = 0, IPAddress dns2 = 0);
  ETH.config(myIP, myGW, mySN, myDNS);

  ESP32_ENC_waitForConnect();

  ///////////////////////////////////

  Serial.print(F("HTTPS EthernetWebServer is @ IP : "));
  Serial.println(ETH.localIP());

  Serial.print(F("To access, use https://"));
  Serial.println(ETH.localIP());

  ///////////////////////////////////////////////

  // We create a node for the main page of the server, available via get
  ResourceNode * nodeRoot     = new ResourceNode("/", "GET", &handleRoot);

  // This node will turn an LED on or of. It has two parameters:
  // 1) The ID of the LED (0..LEDCOUNT)
  // 2) The new state (0..1)
  // For more information on path parameters in general, see the Parameters example.
  ResourceNode * nodeSwitch = new ResourceNode("/led/*/*", "POST", &handleSwitch);

  // We want to use parameter validation. The ResourceNode class provides the method
  // addPathParamValidator() for that. This method takes two parameters:
  // 1) The index of the parameter that you want to validate, so for the first wildcard
  //    in the route pattern that has been specified above, it's 0, and for the second
  //    parameter it's 1.
  // 2) A function pointer that takes an std::string as parameter and returns a bool.
  //    That bool should be true if the parameter is considered valid.
  // All those functions are called in the order in that they have been added. So if
  // you want check if a parameter is an integer and then do some calculation with it,
  // make sure to add the integer-check first and the other function later.
  //
  // If any of the functions returns false, the URL is considered to be invalid completely.
  // In this case, the server will return with a static 400 Bad Request response.
  //
  // For convenience, the ValidatorFunctions.hpp include file already provides some useful
  // and common checks (integer, non-empty, ...). Have a look at it before you start
  // implementing your own checks to save time!

  // First we will take care of the LED ID. This ID should be...
  // ... an unsigned integer ...
  nodeSwitch->addPathParamValidator(0, &validateUnsignedInteger);
  // ... and within the range of known IDs.
  // We can treat the parameter safely as integer in this validator, as all validators
  // are executed in order and validateUnsignedInteger has been run before.
  nodeSwitch->addPathParamValidator(0, &validateLEDID);

  // The second parameter should either be 0 or 1. We use our custom validateLEDState() validator for this:
  nodeSwitch->addPathParamValidator(1, &validateLEDState);

  // Not found node
  ResourceNode * node404 = new ResourceNode("", "GET", &handle404);

  // Add the root node to the server
  secureServer.registerNode(nodeRoot);
  // And the switch node
  secureServer.registerNode(nodeSwitch);

  // Add the 404 not found node to the server.
  // The path is ignored for the default node.
  secureServer.setDefaultNode(node404);

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
