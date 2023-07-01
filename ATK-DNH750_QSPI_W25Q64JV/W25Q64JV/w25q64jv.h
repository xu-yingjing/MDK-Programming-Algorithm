/**
 ****************************************************************************************************
 * @file        w25q64jv.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-06-27
 * @brief       W25Q64JV驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 * 
 * 实验平台:正点原子 北极星 H750开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 * 
 ****************************************************************************************************
 */

#ifndef __W25Q64JV_H
#define __W25Q64JV_H

#include "stm32h7xx_hal.h"

extern QSPI_HandleTypeDef hqspi;

/* 函数声明 */
HAL_StatusTypeDef w25q64jv_init(void);                                          /* 初始化W25Q64JV */
HAL_StatusTypeDef w25q64jv_enable_memory_mapped_mode(void);                     /* 使能W25Q64JV内存映射 */
HAL_StatusTypeDef w25q64jv_erase_sector(uint32_t sector_address);               /* 擦除W25Q64JV扇区 */
HAL_StatusTypeDef w25q64jv_page_program(uint32_t page_address, uint8_t *data);  /* W25Q64JV页编程 */
HAL_StatusTypeDef w25q64jv_erase_chip(void);                                    /* 擦除W25Q64JV */

#endif
