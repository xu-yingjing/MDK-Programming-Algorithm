/**************************************************************************//**
 * @file     FlashPrg.c
 * @brief    Flash Programming Functions adapted for New Device Flash
 * @version  V1.0.0
 * @date     10. January 2018
 ******************************************************************************/
/*
 * Copyright (c) 2010-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include "FlashOS.h"        // FlashOS Structures

/* 
   Mandatory Flash Programming Functions (Called by FlashOS):
                int Init        (unsigned long adr,   // Initialize Flash
                                 unsigned long clk,
                                 unsigned long fnc);
                int UnInit      (unsigned long fnc);  // De-initialize Flash
                int EraseSector (unsigned long adr);  // Erase Sector Function
                int ProgramPage (unsigned long adr,   // Program Page Function
                                 unsigned long sz,
                                 unsigned char *buf);

   Optional  Flash Programming Functions (Called by FlashOS):
                int BlankCheck  (unsigned long adr,   // Blank Check
                                 unsigned long sz,
                                 unsigned char pat);
                int EraseChip   (void);               // Erase complete Device
      unsigned long Verify      (unsigned long adr,   // Verify Function
                                 unsigned long sz,
                                 unsigned char *buf);

       - BlanckCheck  is necessary if Flash space is not mapped into CPU memory space
       - Verify       is necessary if Flash space is not mapped into CPU memory space
       - if EraseChip is not provided than EraseSector for all sectors is called
*/

#include "main.h"
#include "w25q64jv.h"

unsigned long mapped_base_address;

/**
 * @brief   初始化操作Flash
 * @param   adr: Flash映射地址
 * @param   clk: 时钟频率
 * @param   fnc: 操作码
 * @arg     1: 擦除
 * @arg     2: 编程
 * @arg     3: 校验
 * @retval  初始化结果
 * @arg     0: 成功
 * @arg     1: 失败
 */
int Init(unsigned long adr, unsigned long clk, unsigned long fnc)
{
    mapped_base_address = 0;
    
    __disable_irq();
    SystemInit();
    HAL_Init();
    SystemClock_Config();
    SystemCoreClockUpdate();
    
    if (w25q64jv_init() != HAL_OK)
    {
        return 1;
    }
    
    mapped_base_address = adr;
    
    return 0;
}

/**
 * @brief   反初始化操作Flash
 * @param   fnc: 操作码
 * @arg     1: 擦除
 * @arg     2: 编程
 * @arg     3: 校验
 * @retval  反初始化结果
 * @arg     0: 成功
 * @arg     1: 失败
 */
int UnInit(unsigned long fnc)
{
    if (hqspi.State != HAL_QSPI_STATE_BUSY_MEM_MAPPED)
    {
        if (w25q64jv_enable_memory_mapped_mode() != HAL_OK)
        {
            return 1;
        }
    }
    
    return 0;
}

/**
 * @brief   擦除Flash扇区
 * @param   adr: 扇区映射地址
 * @retval  擦除结果
 * @arg     0: 成功
 * @arg     1: 失败
 */
int EraseSector(unsigned long adr)
{
    adr -= mapped_base_address;
    if (w25q64jv_erase_sector(adr) != HAL_OK)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief   编程Flash页
 * @param   adr: 页映射地址
 * @param   sz: 页大小
 * @param   buf: 编程数据
 * @retval  编程结果
 * @arg     0: 成功
 * @arg     1: 失败
 */
int ProgramPage(unsigned long adr, unsigned long sz, unsigned char *buf)
{
    adr -= mapped_base_address;
    if (w25q64jv_page_program(adr, buf) != HAL_OK)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief   Flash空数据校验
 * @param   adr: 校验的起始映射地址
 * @param   sz: 校验的大小
 * @param   pat: 定义的空数据
 * @retval  校验结果
 * @arg     0: 成功
 * @arg     1: 失败
 */
int BlankCheck(unsigned long adr, unsigned long sz, unsigned char pat)
{
    int ret = 0;
    volatile unsigned long i;
    
    if (hqspi.State != HAL_QSPI_STATE_BUSY_MEM_MAPPED)
    {
        if (w25q64jv_enable_memory_mapped_mode() != HAL_OK)
        {
            ret = 1;
        }
    }
    
    if (ret == 0)
    {
        for (i=0; i<sz; i++)
        {
            if ((*((volatile unsigned char *)(adr + i))) != pat)
            {
                ret = 1;
                break;
            }
        }
    }
    
    if (w25q64jv_init() != HAL_OK)
    {
        HAL_Delay(100);
        if (w25q64jv_init() != HAL_OK)
        {
            ret = 1;
        }
    }
    
    return ret;
}

/**
 * @brief   擦除Flash
 * @param   无
 * @retval  擦除结果
 * @arg     0: 成功
 * @arg     1: 失败
 */
int EraseChip(void)
{
    w25q64jv_erase_chip();
    
    return 0;
}

/**
 * @brief   校验Flash
 * @param   adr: 校验的起始映射地址
 * @param   sz: 校验的大小
 * @param   buf: 原始数据
 * @retval  校验区域的末映射地址或校验出错的映射地址
 */
unsigned long Verify(unsigned long adr, unsigned long sz, unsigned char *buf)
{
    volatile unsigned long i;
    volatile unsigned long ret = adr + sz;
    
    if (hqspi.State != HAL_QSPI_STATE_BUSY_MEM_MAPPED)
    {
        if (w25q64jv_enable_memory_mapped_mode() != HAL_OK)
        {
            ret = 0;
        }
    }
    
    if (ret != 0)
    {
        for (i=0; i<sz; i++)
        {
            if ((*((volatile unsigned char *)(adr + i))) != buf[i])
            {
                ret = adr + i;
                break;
            }
        }
    }
    
    return ret;
}
