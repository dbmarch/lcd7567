#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "spidev.h"

// https://www.kernel.org/doc/Documentation/spi/spidev


/* 
*  SpiWrite
*/ 
SpiDev::SpiDev(std::string devPath)  :
   mode{SPI_MODE_3},
   bits{8},
   speed{1000000}
    {

      if ((fd = open(devPath.c_str(),O_RDWR)) < 0)
      {
         perror("SPI device not found");
      }
      else if (ioctl(fd, SPI_IOC_WR_MODE, &mode)<0)   {
         //  mode |= SPI_LOOP; mode |= SPI_CPHA; mode |= SPI_CPOL; mode |= SPI_LSB_FIRST; mode |= SPI_CS_HIGH; mode |= SPI_3WIRE; mode |= SPI_NO_CS; mode |= SPI_READY;

          perror("Error setting spi mode");
          }

      else if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits)<0)   
          {
          perror("Error setting bits");
          }
      else if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed)<0)  
          {
          perror("Error setting speed");
          }
 
    std::cout << devPath << " SPI mode: "<< static_cast<int>(mode) << std::endl;;

    }
  
 
/* 
*  SpiWrite
*/ 
int  SpiDev::Write(uint8_t * buf, int nBytes) {
    int status;
    struct spi_ioc_transfer xfer;

    uint64_t txBuf = reinterpret_cast<uint64_t>(buf);
    
    xfer.tx_buf = txBuf;
    xfer.len = nBytes; 
    xfer.cs_change = 1; 
    xfer.delay_usecs = 0, //delay in us
    xfer.speed_hz = speed, //speed
    xfer.bits_per_word = bits, // bites per word 8
 
    status = ioctl(fd, SPI_IOC_MESSAGE(1), xfer);
    if (status < 0)
        {
        perror("SPI_IOC_MESSAGE");
        }
     return status;
    }


SpiDev::~SpiDev () {
	int status_value = close(fd);
   if(status_value < 0) {
    	std::cout << "Error - Could not close SPI device" << std::endl;
   }

}
