#include <iostream>

#include "lcd7567.h"

Lcd7567::Lcd7567( std::string devPath) : spi (devPath)  {
}

Lcd7567::~Lcd7567( ){ 
}


bool Lcd7567::Reset () {
   std::cout << "Reset LCD" << std::endl;
   return false;
}