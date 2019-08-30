#ifndef LCD7567_H__
#define LCD7567_H__
#include "spidev.h"

class Lcd7567 {

   SpiDev spi;

public:
   Lcd7567( std::string devPath);
   ~Lcd7567();

   bool Reset();
};

#endif