
#include <coapTransport.h>
#include <WiFiUdp.h>


class WiFiTransport : public CoapTransport
{
public:
    WiFiTransport(WiFiUDP *udp):
    CoapTransport()
    {
      udp_ = udp;
    }
    
    int write(unsigned char *buf, size_t buflen)
    {
//        debug_msg((uint8_t*)buf, buflen);
        udp_->beginPacket(udp_->remoteIP(), udp_->remotePort());
        while(buflen--)
            udp_->write(*buf++);
        udp_->endPacket();
    }

    int parsePacket()
    {
      int res = udp_->parsePacket();
      if (res > 0 ) 
      {
        Serial.println("WiFiTransport::parsePacket()");
      }
        return res;
    }
    
    int read(unsigned char *buf, size_t buflen)
    {
        return udp_->read(buf, buflen);
    }

private:
    WiFiUDP *udp_;
};

