#include <iostream>
#include <unistd.h>
#include <string>
#include "lcd7567.h"

int main() {
   Lcd7567 lcd ("/dev/spidev0.0");
   
   std::cout << "LCD7567 Test Application" << std::endl;

   lcd.Reset();
   return 0;
}