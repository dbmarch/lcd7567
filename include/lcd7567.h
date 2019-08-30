#ifndef LCD7567_H__
#define LCD7567_H__
#include "spidev.h"

class Lcd7567 {
   SpiDev spi;

public:
   enum Bias { BIAS_SETTING_1_9, BIAS_SETTING_1_7};

   Lcd7567( std::string devPath);
   ~Lcd7567();

   int WriteData (uint8_t * buf, size_t nBytes);

   int Reset();
   int SetAllPixel (bool on);
   int SetPageAddress (const uint8_t &addr);
   int SetColumnAddress (const uint8_t &addr);
   int SegmentDirection (bool reverse );
   int InverseDisplay  (bool inverse);
   int BiasSelect( const Lcd7567::Bias &bias);
   int PowerSequence (bool on) ;
   int SetEV ( uint8_t &val);
   int SetRegulationRatio (uint8_t ratio);
   int SetComDirection(bool reverse);
};

#endif