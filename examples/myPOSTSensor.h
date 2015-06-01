#include <coapSensor.h>

class myPOSTSensor : 
public CoapSensor 
{
public:
  int pin, status;
  myPOSTSensor(String name, int pin): 
  CoapSensor(name)
  {
    this->pin = pin;
    this->status = 0;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
  void get_value( uint8_t* output_data, size_t* output_data_len)
  {
    this->status = digitalRead(this->pin);
    *output_data_len = sprintf( (char*)output_data, "%d", this->status ); 
//    Serial.print("myPOSTSensor - get_value(): ");
//    Serial.println(this->status, HEX);
  }
  void set_value(uint8_t* input_data, size_t input_data_len, uint8_t* output_data, size_t* output_data_len)
  {
    this->set(*input_data-0x30);
    output_data[0] = 0x30 + status;
//    Serial.print("myPOSTSensor - set_value(): ");
//    Serial.println(output_data[0], HEX);
    *output_data_len = 1;
  }
  void set(uint8_t value)
  {
    this->status = value;
//    Serial.print("myPOSTSensor - set(): ");
//    Serial.println(value, HEX);
    digitalWrite(pin, status);
  }
};

