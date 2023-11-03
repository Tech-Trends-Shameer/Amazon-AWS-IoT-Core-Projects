#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "***********"                         //Thing Name
 
const char WIFI_SSID[] = "***********";               //WiFi Username
const char WIFI_PASSWORD[] = "***********";           //WiFi Password
const char AWS_IOT_ENDPOINT[] = "***********";       //End Point Name
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
 
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
 
-----END CERTIFICATE-----
 
 
)KEY";
 
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
 
-----END RSA PRIVATE KEY-----
 
)KEY";
