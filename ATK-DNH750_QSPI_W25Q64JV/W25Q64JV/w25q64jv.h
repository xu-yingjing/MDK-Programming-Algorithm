/**
 ****************************************************************************************************
 * @file        w25q64jv.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-06-27
 * @brief       W25Q64JV��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 * 
 * ʵ��ƽ̨:����ԭ�� ������ H750������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 * 
 ****************************************************************************************************
 */

#ifndef __W25Q64JV_H
#define __W25Q64JV_H

#include "stm32h7xx_hal.h"

extern QSPI_HandleTypeDef hqspi;

/* �������� */
HAL_StatusTypeDef w25q64jv_init(void);                                          /* ��ʼ��W25Q64JV */
HAL_StatusTypeDef w25q64jv_enable_memory_mapped_mode(void);                     /* ʹ��W25Q64JV�ڴ�ӳ�� */
HAL_StatusTypeDef w25q64jv_erase_sector(uint32_t sector_address);               /* ����W25Q64JV���� */
HAL_StatusTypeDef w25q64jv_page_program(uint32_t page_address, uint8_t *data);  /* W25Q64JVҳ��� */
HAL_StatusTypeDef w25q64jv_erase_chip(void);                                    /* ����W25Q64JV */

#endif
