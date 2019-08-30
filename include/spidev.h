#ifndef __SPIDEV_H__
#define __SPIDEV_H__

#include <string>


class SpiDev {
   int fd;
   uint8_t mode;
   uint8_t bits; 
   uint8_t lsb;  // 0 = MSB first , 1 = lsb first
   uint32_t speed;

public:
   SpiDev (std::string devPath);
   ~SpiDev();

   int Write(uint8_t * buf, int nbytes);
};


#endif