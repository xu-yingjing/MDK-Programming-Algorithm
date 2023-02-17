#ifndef __BSP_NORFLASH_H
#define __BSP_NORFLASH_H

uint8_t bspNorFlashInit(void);
void bspNorFlashEraseSector(uint32_t address);
void bspNorFlashEraseChip(void);
uint8_t bspNorFlashReadBytes(uint32_t address, uint8_t *bytes, uint32_t length);
uint8_t bspNorFlashWriteBytes(uint32_t address, uint8_t *bytes, uint32_t length);

#endif /* __BSP_NORFLASH_H */
