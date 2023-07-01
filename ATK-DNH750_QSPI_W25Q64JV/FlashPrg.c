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
 * @brief   ��ʼ������Flash
 * @param   adr: Flashӳ���ַ
 * @param   clk: ʱ��Ƶ��
 * @param   fnc: ������
 * @arg     1: ����
 * @arg     2: ���
 * @arg     3: У��
 * @retval  ��ʼ�����
 * @arg     0: �ɹ�
 * @arg     1: ʧ��
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
 * @brief   ����ʼ������Flash
 * @param   fnc: ������
 * @arg     1: ����
 * @arg     2: ���
 * @arg     3: У��
 * @retval  ����ʼ�����
 * @arg     0: �ɹ�
 * @arg     1: ʧ��
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
 * @brief   ����Flash����
 * @param   adr: ����ӳ���ַ
 * @retval  �������
 * @arg     0: �ɹ�
 * @arg     1: ʧ��
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
 * @brief   ���Flashҳ
 * @param   adr: ҳӳ���ַ
 * @param   sz: ҳ��С
 * @param   buf: �������
 * @retval  ��̽��
 * @arg     0: �ɹ�
 * @arg     1: ʧ��
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
 * @brief   Flash������У��
 * @param   adr: У�����ʼӳ���ַ
 * @param   sz: У��Ĵ�С
 * @param   pat: ����Ŀ�����
 * @retval  У����
 * @arg     0: �ɹ�
 * @arg     1: ʧ��
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
 * @brief   ����Flash
 * @param   ��
 * @retval  �������
 * @arg     0: �ɹ�
 * @arg     1: ʧ��
 */
int EraseChip(void)
{
    w25q64jv_erase_chip();
    
    return 0;
}

/**
 * @brief   У��Flash
 * @param   adr: У�����ʼӳ���ַ
 * @param   sz: У��Ĵ�С
 * @param   buf: ԭʼ����
 * @retval  У�������ĩӳ���ַ��У������ӳ���ַ
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
