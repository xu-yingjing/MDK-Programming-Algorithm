/**************************************************************************//**
 * @file     FlashDev.c
 * @brief    Flash Device Description for New Device Flash
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

struct FlashDevice const FlashDevice =
{
    FLASH_DRV_VERS,             // Driver Version, do not modify!
    "ATK-DNH750_QSPI_W25Q64JV", // Device Name
    EXTSPI,                     // Device Type
    0x90000000,                 // Device Start Address
    0x00800000,                 // Device Size in Bytes
    0x00000100,                 // Programming Page Size
    0x00000000,                 // Reserved, must be 0
    0xFF,                       // Initial Content of Erased Memory
    100000,                     // Program Page Timeout in mSec
    100000,                     // Erase Sector Timeout in mSec
    
    // Specify Size and Address of Sectors
    0x00001000, 0x00000000,     // Sector Size in Bytes and Address
    SECTOR_END
};
