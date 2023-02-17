#include "apm32e10x.h"
#include "apm32e10x_rcm.h"
#include "apm32e10x_gpio.h"
#include "apm32e10x_spi.h"
#include "bsp_norflash.h"

#include <stdio.h>

#define NORFLASHSPI_CS_LOW()                    GPIO_WriteBitValue(GPIOB, GPIO_PIN_12, BIT_RESET)
#define NORFLASHSPI_CS_HIGH()                   GPIO_WriteBitValue(GPIOB, GPIO_PIN_12, BIT_SET)

#define NORFLASH_READ_JEDEC_ID                  (0x9F)
#define NORFLASH_READ_STATUS_REGISTER_1         (0x05)
#define NORFLASH_WRITE_ENABLE                   (0x06)
#define NORFLASH_PAGE_PROGRAM                   (0x02)
#define NORFLASH_SECTOR_ERASE                   (0x20)
#define NORFLASH_CHIP_ERASE                     (0xC7)
#define NORFLASH_FAST_READ                      (0x0B)

#define NORFLASH_SECTOR_SIZE                    (4096U)
#define NORFLASH_PAGE_SIZE                      (256U)

#define NORFLASH_GET_SECTOR_ADDRESS(address)    (address & ~(NORFLASH_SECTOR_SIZE - 1))

static __INLINE uint8_t NorFlashSPITransmitReceive(uint8_t txData)
{
    uint8_t rxData;
    
    while (SPI_I2S_ReadStatusFlag(SPI1, SPI_FLAG_TXBE) != SET);
    SPI_I2S_TxData(SPI1, txData);
    
    while (SPI_I2S_ReadStatusFlag(SPI1, SPI_FLAG_RXBNE) != SET);
    rxData = SPI_I2S_RxData(SPI1);
    
    return rxData;
}

uint8_t bspNorFlashInit(void)
{
    GPIO_Config_T gpioConfig;
    SPI_Config_T spiConfig;
    uint32_t NorFlashID;
    uint8_t result = 0;
    
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SPI1);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOB);
    
    gpioConfig.pin = GPIO_PIN_13 | GPIO_PIN_15;
    gpioConfig.speed = GPIO_SPEED_50MHz;
    gpioConfig.mode = GPIO_MODE_AF_PP;
    GPIO_Config(GPIOB, &gpioConfig);
    
    gpioConfig.pin = GPIO_PIN_14;
    gpioConfig.mode = GPIO_MODE_IN_PU;
    GPIO_Config(GPIOB, &gpioConfig);
    
    gpioConfig.pin = GPIO_PIN_12;
    gpioConfig.speed = GPIO_SPEED_50MHz;
    gpioConfig.mode = GPIO_MODE_OUT_PP;
    GPIO_Config(GPIOB, &gpioConfig);
    
    NORFLASHSPI_CS_HIGH();
    
    spiConfig.mode = SPI_MODE_MASTER;
    spiConfig.length = SPI_DATA_LENGTH_8B;
    spiConfig.phase = SPI_CLKPHA_1EDGE;
    spiConfig.polarity = SPI_CLKPOL_LOW;
    spiConfig.nss = SPI_NSS_SOFT;
    spiConfig.firstBit = SPI_FIRSTBIT_MSB;
    spiConfig.direction = SPI_DIRECTION_2LINES_FULLDUPLEX;
    spiConfig.baudrateDiv = SPI_BAUDRATE_DIV_2;
    spiConfig.crcPolynomial = 0x0007;
    SPI_Config(SPI2, &spiConfig);
    SPI_DisableCRC(SPI2);
    SPI_Enable(SPI2);
    
    NORFLASHSPI_CS_LOW();
    NorFlashSPITransmitReceive(NORFLASH_READ_JEDEC_ID);
    NorFlashID = NorFlashSPITransmitReceive(0xFF) << 16;
    NorFlashID |= NorFlashSPITransmitReceive(0xFF) << 8;
    NorFlashID |= NorFlashSPITransmitReceive(0xFF);
    if (NorFlashID != 0xEF4018)
    {
        result = 1;
    }
    NORFLASHSPI_CS_HIGH();
    
    return result;
}

static void NorFlashWaitBusy(uint16_t waitTimeUnit)
{
    uint8_t register1;
    
    NORFLASHSPI_CS_LOW();
    NorFlashSPITransmitReceive(NORFLASH_READ_STATUS_REGISTER_1);
    do {
        register1 = NorFlashSPITransmitReceive(0xFF);
    } while ((register1 & (1 << 0)) != 0);
    NORFLASHSPI_CS_HIGH();
}

static void NorFlashEnableWrite(void)
{
    NORFLASHSPI_CS_LOW();
    NorFlashSPITransmitReceive(NORFLASH_WRITE_ENABLE);
    NORFLASHSPI_CS_HIGH();
}

static void NorFlashWritePage(uint32_t address, uint8_t *bytes, uint16_t length)
{
    uint16_t byteIndex;
    
    NorFlashEnableWrite();
    
    NORFLASHSPI_CS_LOW();
    NorFlashSPITransmitReceive(NORFLASH_PAGE_PROGRAM);
    NorFlashSPITransmitReceive((address >> 16) & 0xFF);
    NorFlashSPITransmitReceive((address >> 8) & 0xFF);
    NorFlashSPITransmitReceive(address & 0xFF);
    for (byteIndex=0; byteIndex<length; byteIndex++)
    {
        NorFlashSPITransmitReceive(bytes[byteIndex]);
    }
    NORFLASHSPI_CS_HIGH();
    
    NorFlashWaitBusy(1);
}

static void NorFlashWritePages(uint32_t address, uint8_t *bytes, uint32_t length)
{
    uint16_t pageRemainByte;
    uint16_t onceWriteByte;
    
    pageRemainByte = NORFLASH_PAGE_SIZE - (address & (NORFLASH_PAGE_SIZE - 1));
    
    while (length != 0)
    {
        onceWriteByte = (length > pageRemainByte) ? pageRemainByte : length;
        NorFlashWritePage(address, bytes, onceWriteByte);
        
        address += onceWriteByte;
        bytes += onceWriteByte;
        length -= onceWriteByte;
        pageRemainByte = NORFLASH_PAGE_SIZE;
    }
}

void bspNorFlashEraseSector(uint32_t address)
{
    address &= ~((uint32_t)0xFFF);
    
    NorFlashEnableWrite();
    
    NORFLASHSPI_CS_LOW();
    NorFlashSPITransmitReceive(NORFLASH_SECTOR_ERASE);
    NorFlashSPITransmitReceive((address >> 16) & 0xFF);
    NorFlashSPITransmitReceive((address >> 8) & 0xFF);
    NorFlashSPITransmitReceive(address & 0xFF);
    NORFLASHSPI_CS_HIGH();
    
    NorFlashWaitBusy(10);
}

void bspNorFlashEraseChip(void)
{
    NorFlashEnableWrite();
    
    NORFLASHSPI_CS_LOW();
    NorFlashSPITransmitReceive(NORFLASH_CHIP_ERASE);
    NORFLASHSPI_CS_HIGH();
    
    NorFlashWaitBusy(1000);
}

uint8_t bspNorFlashReadBytes(uint32_t address, uint8_t *bytes, uint32_t length)
{
    uint32_t byteIndex;
    
    if ((address + length) > 0x1000000)
    {
        return 1;
    }
    
    NORFLASHSPI_CS_LOW();
    NorFlashSPITransmitReceive(NORFLASH_FAST_READ);
    NorFlashSPITransmitReceive((address >> 16) & 0xFF);
    NorFlashSPITransmitReceive((address >> 8) & 0xFF);
    NorFlashSPITransmitReceive(address & 0xFF);
    NorFlashSPITransmitReceive(0xFF);
    for (byteIndex=0; byteIndex<length; byteIndex++)
    {
        bytes[byteIndex] = NorFlashSPITransmitReceive(0xFF);
    }
    NORFLASHSPI_CS_HIGH();
    
    return 0;
}

static uint8_t NorFlashSectorBuf[4096];

uint8_t bspNorFlashWriteBytes(uint32_t address, uint8_t *bytes, uint32_t length)
{
    uint16_t sectorOffsetByte;
    uint16_t sectorRemainByte;
    uint16_t byteIndex;
    uint16_t onceWriteByte;
    
    if ((address + length) > 0x1000000)
    {
        return 1;
    }
    
    sectorOffsetByte = address & (NORFLASH_SECTOR_SIZE - 1);
    sectorRemainByte = NORFLASH_SECTOR_SIZE - sectorOffsetByte;
    
    while (length != 0)
    {
        onceWriteByte = (length > sectorRemainByte) ? sectorRemainByte : length;
        bspNorFlashReadBytes(NORFLASH_GET_SECTOR_ADDRESS(address), NorFlashSectorBuf, NORFLASH_SECTOR_SIZE);
        for (byteIndex=sectorOffsetByte; byteIndex<(sectorOffsetByte+onceWriteByte); byteIndex++)
        {
            if (NorFlashSectorBuf[byteIndex] != 0xFF)
            {
                break;
            }
        }
        
        if (byteIndex < (sectorOffsetByte + onceWriteByte))
        {
            bspNorFlashEraseSector(NORFLASH_GET_SECTOR_ADDRESS(address));
            for (byteIndex=sectorOffsetByte; byteIndex<(sectorOffsetByte+onceWriteByte); byteIndex++)
            {
                NorFlashSectorBuf[byteIndex] = bytes[byteIndex - sectorOffsetByte];
            }
            NorFlashWritePages(NORFLASH_GET_SECTOR_ADDRESS(address), NorFlashSectorBuf, NORFLASH_SECTOR_SIZE);
        }
        else
        {
            NorFlashWritePages(address, bytes, onceWriteByte);
        }
        
        address += onceWriteByte;
        bytes += onceWriteByte;
        length -= onceWriteByte;
        sectorOffsetByte = 0;
        sectorRemainByte = NORFLASH_SECTOR_SIZE;
    }
    
    return 0;
}
