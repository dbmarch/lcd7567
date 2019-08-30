#include <iostream>
#include <unistd.h>

#include "lcd7567.h"


const uint8_t CMD_DISPLAY              { 0xAE };
const uint8_t CMD_START_LINE           { 0x40 };
const uint8_t CMD_SET_PAGE             { 0xB0 };
const uint8_t CMD_SET_COLUMN_ADDR_MSB  { 0x10 };
const uint8_t CMD_SET_COLUMN_ADDR_LSB  { 0x00 };
const uint8_t WRITE_DATA               { 0x80 };
const uint8_t CMD_SEG_DIRECTION_REVERSE{ 0xA1 };
const uint8_t CMD_SEG_DIRECTION_NORMAL { 0xA0 };
const uint8_t CMD_INVERSE_DISPLAY_ON   { 0xA7 };
const uint8_t CMD_INVERSE_DISPLAY_OFF  { 0xA6 };
const uint8_t CMD_ALL_PIXEL_ON         { 0xA5 };
const uint8_t CMD_ALL_PIXEL_OFF        { 0xA4 };
const uint8_t CMD_BIAS_SELECT          { 0xA2 };
const uint8_t CMD_RESET                { 0xE2 };
const uint8_t CMD_POWER_SEQUENCE       { 0x24 };
const uint8_t CMD_SET_EV               { 0x81 };
const uint8_t CMD_SET_RR               { 0x20 };
const uint8_t CMD_COM_DIRECTION_REVERSE{ 0xC1 };
const uint8_t CMD_COM_DIRECTION_NORMAL { 0xC0 };

Lcd7567::Lcd7567( std::string devPath) : spi (devPath)  {
}

Lcd7567::~Lcd7567( ){ 
}


int Lcd7567::Reset () {
   std::cout << "Reset LCD" << std::endl;
   uint8_t buf[] {CMD_RESET };
   return spi.Write (buf, sizeof(buf));
}


int Lcd7567::SetAllPixel (bool on) {
   uint8_t buf[] { on  ? CMD_ALL_PIXEL_ON : CMD_ALL_PIXEL_OFF };
   return spi.Write (buf, sizeof(buf));
}

int Lcd7567::SetPageAddress (const uint8_t &addr) {
   const uint8_t val = CMD_SET_PAGE | (addr & 0x0F);
   uint8_t buf[] { val };
   return spi.Write (buf, sizeof(buf));   
}

int Lcd7567::SetColumnAddress (const uint8_t &addr) {
   const uint8_t msb = CMD_SET_COLUMN_ADDR_MSB| (addr & 0xF0);
   const uint8_t lsb = CMD_SET_COLUMN_ADDR_LSB| (addr & 0x0F);

   uint8_t buf[] { msb, lsb };
   return spi.Write (buf, sizeof(buf));   
}

int Lcd7567::SegmentDirection  (bool reverse) {
   uint8_t buf[] { reverse  ? CMD_SEG_DIRECTION_REVERSE : CMD_SEG_DIRECTION_NORMAL };
   return spi.Write (buf, sizeof(buf));
}


int Lcd7567::InverseDisplay  (bool inverse) {
   uint8_t buf[] { inverse  ? CMD_INVERSE_DISPLAY_ON : CMD_INVERSE_DISPLAY_OFF };
   return spi.Write (buf, sizeof(buf));
}

int Lcd7567::BiasSelect( const Lcd7567::Bias &bias) {
   uint8_t buf[] { CMD_BIAS_SELECT};
   *buf |= (bias == Lcd7567::BIAS_SETTING_1_9) ? 0 : 1;
   return spi.Write (buf, sizeof(buf));
}

int Lcd7567::PowerSequence (bool on) {
   int rval{};
   uint8_t buf[] { CMD_POWER_SEQUENCE | 0x04};
   if ( (rval = spi.Write (buf, sizeof(buf))) < 0) {
      return rval;
   }
   usleep(50000UL); // 50 msec
   *buf |= 0x02;
   if ( (rval = spi.Write (buf, sizeof(buf))) < 0) {
      return rval;
   }
   usleep(2000UL); // 2 msec

   *buf |= 0x01;
   if ( ( rval = spi.Write (buf, sizeof(buf)))< 0) {
      return rval;
   }
   usleep(2000UL); // 2 msec

   return (rval);
}


int Lcd7567::SetEV ( uint8_t &ev) {
   const uint8_t val  = ev & 0x3F;
   uint8_t buf[] { CMD_SET_EV, val };
   return spi.Write (buf, sizeof(buf));
}


int Lcd7567::SetRegulationRatio (uint8_t ratio) {
   const uint8_t val  = CMD_SET_RR | (ratio & 0x07);
   uint8_t buf[] { val };
   return spi.Write (buf, sizeof(buf));
}

int Lcd7567::SetComDirection (bool reverse) {
   uint8_t buf[] { reverse  ? CMD_COM_DIRECTION_REVERSE : CMD_COM_DIRECTION_NORMAL };
   return spi.Write (buf, sizeof(buf));
}

int Lcd7567::WriteData (uint8_t * buf, size_t nBytes) {
   std::cout << "WRITE DATA - NOT IMPLEMENTED " << std::endl;
   return false;
}
