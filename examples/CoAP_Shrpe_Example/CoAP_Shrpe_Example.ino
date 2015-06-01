/**
 * Arduino Coap Example Application using the SHRPE library as transport:
 * https://github.com/Drotth/SHRPE-Arduino
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
#include <Shrpe.h>
#include <coap.h>
#include "examples/myGETSensor.h"
#include "examples/myPOSTSensor.h"
#include "ShrpeTransport.h"

Coap coap;
Shrpe shrpe;
ShrpeTransport transport(&shrpe);

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
  
  shrpe.begin();
  
  // init coap service, using the SHRPE transport 
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

