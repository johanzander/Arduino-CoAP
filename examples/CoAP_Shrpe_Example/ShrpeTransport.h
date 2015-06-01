
#include <coapTransport.h>
#include <Shrpe.h>


class ShrpeTransport : public CoapTransport
{
public:
    ShrpeTransport(Shrpe *transport):
    CoapTransport()
    {
        transport_ = transport;
    }
    
    int write(unsigned char *buf, size_t buflen)
    {
        //        transport_->beginPacket(udp_->remoteIP(), udp_->remotePort());
        while(buflen--)
            transport_->write(*buf++);
        //        transport_->endPacket();
    }
    
    int parsePacket()
    {
        //      return transport_->parsePacket();
    }
    
    int read(unsigned char *buf, size_t buflen)
    {
        //        return transport_->read(buf, buflen);
    }
    
private:
    Shrpe *transport_;
};
