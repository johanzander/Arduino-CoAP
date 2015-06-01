#include <coapSensor.h>



class myGETSensor : 
public CoapSensor 
{
public:
  int pin, status;
  boolean digital;
  myGETSensor(String name, int pin, boolean digital): 
  CoapSensor(name)
  {
    this->pin = pin;
    this->status = 0;
    this->digital = digital;
    if(digital) 
    {
      pinMode(pin, INPUT);
    }
  }
  
  void get_value( uint8_t* output_data, size_t* output_data_len)
  {
//    Serial.print("myGETSensor - get_value(): ");
//    Serial.println(this->status, HEX);
    *output_data_len = sprintf( (char*)output_data, "%d", this->status ); 
  }
  
  void check(void)
  {
    static unsigned long timestamp = 0;
    if(millis() - timestamp > 300)
    {
      int newStatus;
      if(digital) 
      {
        newStatus = digitalRead(this->pin);
      }
      else
      {
        newStatus = analogRead(this->pin);  // read the value from the sensor
        newStatus = map(newStatus, 0, 1024, 0, 5000)/10;  
      }
      if(newStatus != this->status)
      {
        this->changed = true;
        this->status = newStatus;
//        Serial.print("Button state changed: ");
//        Serial.println(this->status);
      }
      timestamp = millis();
    }
  }
};

