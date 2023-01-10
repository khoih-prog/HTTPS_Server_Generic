/**
   Example for the ESP32_SC_W6100 HTTP(S) Webserver

   IMPORTANT NOTE:

   This script will install an HTTPS Server on your ESP32 with the following
   functionalities:
    - Show simple page on web server root
    - 404 for everything else

   In contrast to the other examples, the certificate and the private key will be
   generated on the ESP32_SC_W6100, so you do not need to provide them here.
   (this means no need to run create_cert.sh)
*/

//////////////////////////////////////////////////

// For ESP32_SC_W6100
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

#include <WebServer_ESP32_SC_W6100.h>

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

SSLCert * cert;
HTTPSServer * secureServer;

// Handler functions for the various URLs on the server

void handleRoot(HTTPRequest * req, HTTPResponse * res)
{
  // Status code is 200 OK by default.
  // We want to deliver a simple HTML page, so we send a corresponding content type:
  res->setHeader("Content-Type", "text/html");

  // The response implements the Print interface, so you can use it just like
  // you would write to Serial etc.
  res->println("<!DOCTYPE html>");
  res->println("<html>");
  res->println("<head><title>Hello World!</title></head>");
  res->println("<body>");
  res->println("<h1>Hello World!</h1>");
  res->print("<p>Your server is running for ");
  // A bit of dynamic data: Show the uptime
  res->print((int)(millis() / 1000), DEC);
  res->println(" seconds.</p>");
  res->println("</body>");
  res->println("</html>");
}

void handle404(HTTPRequest * req, HTTPResponse * res)
{
  // Discard request body, if we received any
  // We do this, as this is the default node and may also server POST/PUT requests
  req->discardRequestBody();

  // Set the response status
  res->setStatusCode(404);
  res->setStatusText("Not Found");

  // Set content type of the response
  res->setHeader("Content-Type", "text/html");

  // Write a tiny HTTP page
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

  Serial.print("\nStarting Self-Signed-Certificate on " + String(ARDUINO_BOARD));
  Serial.println(" with " + String(SHIELD_TYPE));
  Serial.println(WEBSERVER_ESP32_SC_W6100_VERSION);
  Serial.println(HTTPS_SERVER_GENERIC_VERSION);

  ///////////////////////////////////

  Serial.println("Creating a new self-signed certificate.");
  Serial.println("This may take up to a minute, so be patient ;-)");

  // First, we create an empty certificate:
  cert = new SSLCert();

  // Now, we use the function createSelfSignedCert to create private key and certificate.
  // The function takes the following parameters:
  // - Key size: 1024 or 2048 bit should be fine here, 4096 on the ESP might be "paranoid mode"
  //   (in generel: shorter key = faster but less secure)
  // - Distinguished name: The name of the host as used in certificates.
  //   If you want to run your own DNS, the part after CN (Common Name) should match the DNS
  //   entry pointing to your ESP32_SC_W6100. You can try to insert an IP there, but that's not really good style.
  // - Dates for certificate validity (optional, default is 2022-2032, both included)
  //   Format is YYYYMMDDhhmmss
  int createCertResult = createSelfSignedCert(
                           *cert,
                           KEYSIZE_2048,
                           "CN=myesp32.local,O=FancyCompany,C=CA",
                           "20220101000000",
                           "20330101000000"
                         );

  // Now check if creating that worked
  if (createCertResult != 0)
  {
    Serial.printf("Creating certificate failed. Error Code = 0x%02X, check SSLCert.hpp for details", createCertResult);

    while (true)
      delay(500);
  }

  Serial.println("Creating the certificate was successful");

  // If you're working on a serious project, this would be a good place to initialize some form of non-volatile storage
  // and to put the certificate and the key there. This has the advantage that the certificate stays the same after a reboot
  // so your client still trusts your server, additionally you increase the speed-up of your application.
  // Some browsers like Firefox might even reject the second run for the same issuer name (the distinguished name defined above).
  //
  // Storing:
  //   For the key:
  //     cert->getPKLength() will return the length of the private key in byte
  //     cert->getPKData() will return the actual private key (in DER-format, if that matters to you)
  //   For the certificate:
  //     cert->getCertLength() and ->getCertData() do the same for the actual certificate data.
  // Restoring:
  //   When your applications boots, check your non-volatile storage for an existing certificate, and if you find one
  //   use the parameterized SSLCert constructor to re-create the certificate and pass it to the HTTPSServer.
  //
  // A short reminder on key security: If you're working on something professional, be aware that the storage of the ESP32 is
  // not encrypted in any way. This means that if you just write it to the flash storage, it is easy to extract it if someone
  // gets a hand on your hardware. You should decide if that's a relevant risk for you and apply countermeasures like flash
  // encryption if necessary

  // We can now use the new certificate to setup our server as usual.
  secureServer = new HTTPSServer(cert);

  ///////////////////////////////////

  // To be called before ETH.begin()
  ESP32_W6100_onEvent();

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  //bool begin(int MISO_GPIO, int MOSI_GPIO, int SCLK_GPIO, int CS_GPIO, int INT_GPIO, int SPI_CLOCK_MHZ,
  //           int SPI_HOST, uint8_t *W6100_Mac = W6100_Default_Mac);
  ETH.begin( MISO_GPIO, MOSI_GPIO, SCK_GPIO, CS_GPIO, INT_GPIO, SPI_CLOCK_MHZ, ETH_SPI_HOST );
  //ETH.begin( MISO_GPIO, MOSI_GPIO, SCK_GPIO, CS_GPIO, INT_GPIO, SPI_CLOCK_MHZ, ETH_SPI_HOST, mac[millis() % NUMBER_OF_MAC] );

  // Static IP, leave without this line to get IP via DHCP
  //bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = 0, IPAddress dns2 = 0);
  //ETH.config(myIP, myGW, mySN, myDNS);

  ESP32_W6100_waitForConnect();

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
  secureServer->registerNode(nodeRoot);
  // Add the 404 not found node to the server.
  secureServer->setDefaultNode(node404);

  Serial.println("Starting server...");
  secureServer->start();

  if (secureServer->isRunning())
  {
    Serial.println("Server ready.");
  }
}

void loop()
{
  // This call will let the server do its work
  secureServer->loop();

  // Other code would go here...
  delay(1);
}
