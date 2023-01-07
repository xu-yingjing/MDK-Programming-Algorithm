#include "FlashOS.h"
#include "apm32f4xx.h"
#include "bsp_norflash.h"

#define FlashDeviceStartAddressOffset 0xF0000000

static unsigned char inited = 0;

int Init(unsigned long adr, unsigned long clk, unsigned long fnc)
{
    uint8_t result;
    
    if (inited != 0)
    {
        return 0;
    }
    
    result = bspNorFlashInit();
    if (result != 0)
    {
        return 1;
    }
    inited = 1;
    
    return 0;
}

int UnInit(unsigned long fnc)
{
    return 0;
}

int BlankCheck(unsigned long adr, unsigned long sz, unsigned char pat)
{
    return 0;
}

int EraseChip(void)
{
    bspNorFlashEraseChip();
    
    return 0;
}

int EraseSector(unsigned long adr)
{
    bspNorFlashEraseSector(adr - FlashDeviceStartAddressOffset);
    
    return 0;
}

int ProgramPage(unsigned long adr, unsigned long sz, unsigned char *buf)
{
    uint8_t result;
    
    result = bspNorFlashWriteBytes(adr - FlashDeviceStartAddressOffset, buf, sz);
    if (result != 0)
    {
        return 1;
    }
    
    return 0;
}

static unsigned char readBuf[256];
unsigned long Verify(unsigned long adr, unsigned long sz, unsigned char *buf)
{
    unsigned long sizeIndex;
    unsigned long compareSize;
    unsigned long compareIndex;
    
    for (sizeIndex=0; sizeIndex<sz; sizeIndex+=256)
    {
        bspNorFlashReadBytes(adr - FlashDeviceStartAddressOffset + sizeIndex, readBuf, 256);
        
        if ((sz - sizeIndex) >= 256)
        {
            compareSize = 256;
        }
        else
        {
            compareSize = sz - sizeIndex;
        }
        
        for (compareIndex=0; compareIndex<compareSize; compareIndex++)
        {
            if (readBuf[compareIndex] != buf[sizeIndex + compareIndex])
            {
                return (adr + sizeIndex + compareIndex);
            }
        }
    }
    
    return (adr + sz);
}
