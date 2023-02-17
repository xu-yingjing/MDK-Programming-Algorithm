#include "FlashOS.h"

struct FlashDevice const FlashDevice  =  {
    FLASH_DRV_VERS,             // Driver Version, do not modify!
    "APM32E103_SPI_W25Q128",    // Device Name
    EXTSPI,                     // Device Type
    0xF0000000,                 // Device Start Address
    0x01000000,                 // Device Size in Bytes (16MB)
    0x1000,                     // Programming Page Size
    0,                          // Reserved, must be 0
    0xFF,                       // Initial Content of Erased Memory
    3000,                       // Program Page Timeout 3000 mSec
    3000,                       // Erase Sector Timeout 3000 mSec

// Specify Size and Address of Sectors
    0x1000, 0x00000000,         // Sector Size 4kB (1 Sectors)
    SECTOR_END
};
