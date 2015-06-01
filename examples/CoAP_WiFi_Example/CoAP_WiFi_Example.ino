/**
* Arduino Coap Example Application using the standard WiFi library.
*
* This Example creates a CoAP server with 2 resources.
* 'button' : A resource that contains an integer and the GET method is only available.
*            A GET request returns the value of the value_get variable.
The resource is OBSERVEable.
* 'led'    : A resource that contains an integer and the GET-POST methods are available.
*            A GET request returns the value of the value_post variable.
*            A POST request sets the value of value_post to the sent integer.
* All resources are of TEXT_PLAIN content type.
*/

#include <SPI.h>
#include <WiFi.h>
#include <coap.h>
#include "examples/myGETSensor.h"
#include "examples/myPOSTSensor.h"
#include "WiFiTransport.h"

// WiFi stuff
char ssid[] = "*********";    //  your network SSID (name)
char pass[] = "*********";    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;

#define PORT 5683

Coap coap;
WiFiClient client(255);
WiFiUDP udp;
WiFiTransport transport(&udp);

//myGETSensor aSensor = myGETSensor("light" , A0, false);
myPOSTSensor bSensor = myPOSTSensor("led" , 3);
myGETSensor cSensor = myGETSensor("button" , 8, true);

//Runs only once
void setup()
{
int i;
Serial.begin(9600);
while (!Serial)
{
; // wait for serial port to connect. Needed for Leonardo only
}

// attempt to connect to Wifi network:
while (status != WL_CONNECTED) {
Serial.print("Attempting to connect to SSID: ");
Serial.println(ssid);
// Connect to WPA/WPA2 network. Change this line if using open or WEP network:
status = WiFi.begin(ssid, pass);

// wait 5 seconds for connection:
delay(5000);
}
Serial.println("Connected to wifi");
printWifiStatus();
udp.begin(PORT);

// init coap service
coap.init( &transport );

//add the resourse resGET
//  coap.add_resource(&aSensor);
coap.add_resource(&bSensor);
coap.add_resource(&cSensor);
}

void loop()
{
//run the handler on each loop to respond to incoming requests
coap.handler();
}

void printWifiStatus() {
// print the SSID of the network you're attached to:
Serial.print("SSID: ");
Serial.println(WiFi.SSID());

// print your WiFi shield's IP address:
IPAddress ip = WiFi.localIP();
Serial.print("IP Address: ");
Serial.println(ip);

// print the received signal strength:
long rssi = WiFi.RSSI();
Serial.print("signal strength (RSSI):");
Serial.print(rssi);
Serial.println(" dBm");
}
