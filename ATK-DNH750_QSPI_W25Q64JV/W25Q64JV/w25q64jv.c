/**
 ****************************************************************************************************
 * @file        w25q64jv.c
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

#include "w25q64jv.h"
#include "main.h"

/* 指令定义 */
#define ENABLE_RESET_INST               0x66
#define RESET_DEVICE_INST               0x99
#define JEDEC_ID_INST                   0x9F
#define WRITE_ENABLE_INST               0x06
#define READ_STATUS_REGISTER1_INST      0x05
#define READ_STATUS_REGISTER2_INST      0x35
#define WRITE_STATUS_REGISTER2_INST     0x31
#define FAST_READ_QUAD_IO_INST          0xEB
#define SECTOR_ERASE_INST               0x20
#define QUAD_INPUT_PAGE_PROGRAM_INST    0x32
#define CHIP_ERASE_INST                 0xC7

/**
 * @brief   复位W25Q64JV
 * @param   无
 * @retval  操作结果
 * @arg     HAL_OK: 成功
 * @arg     HAL_ERROR: 失败
 */
static HAL_StatusTypeDef w25q64jv_reset(void)
{
    QSPI_CommandTypeDef qspi_command_struct = {0};
    
    /* Enable Reset */
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = ENABLE_RESET_INST;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_NONE;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    if (HAL_QSPI_Command(&hqspi, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    /* Reset Device */
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = RESET_DEVICE_INST;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_NONE;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    if (HAL_QSPI_Command(&hqspi, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    HAL_Delay(1);
    
    /* Enable Reset */
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_2_LINES;
    qspi_command_struct.Instruction = ENABLE_RESET_INST;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_NONE;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    if (HAL_QSPI_Command(&hqspi, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    /* Reset Device */
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_2_LINES;
    qspi_command_struct.Instruction = RESET_DEVICE_INST;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_NONE;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    if (HAL_QSPI_Command(&hqspi, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    HAL_Delay(1);
    
    /* Enable Reset */
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_4_LINES;
    qspi_command_struct.Instruction = ENABLE_RESET_INST;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_NONE;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    if (HAL_QSPI_Command(&hqspi, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    /* Reset Device */
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_4_LINES;
    qspi_command_struct.Instruction = RESET_DEVICE_INST;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_NONE;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    if (HAL_QSPI_Command(&hqspi, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    HAL_Delay(1);
    
    return HAL_OK;
}

/**
 * @brief   自动轮询状态等待W25Q64JV就绪
 * @param   timeout: 等待超时时间
 * @retval  操作结果
 * @arg     HAL_OK: 成功
 * @arg     HAL_ERROR: 失败
 */
static HAL_StatusTypeDef w25q64jv_auto_polling_ready(uint32_t timeout)
{
    QSPI_CommandTypeDef qspi_command_struct = {0};
    QSPI_AutoPollingTypeDef qspi_autopolling_struct = {0};
    
    /* Read Ststus Register-1 */
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = READ_STATUS_REGISTER1_INST;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_1_LINE;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    qspi_autopolling_struct.Match = 0x00;
    qspi_autopolling_struct.Mask = 0x01;
    qspi_autopolling_struct.Interval = 0x10;
    qspi_autopolling_struct.StatusBytesSize = 1;
    qspi_autopolling_struct.MatchMode = QSPI_MATCH_MODE_AND;
    qspi_autopolling_struct.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;
    if (HAL_QSPI_AutoPolling(&hqspi, &qspi_command_struct, &qspi_autopolling_struct, timeout) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    return HAL_OK;
}

/**
 * @brief   校验W25Q64JV ID
 * @param   无
 * @retval  校验结果
 * @arg     HAL_OK: 成功
 * @arg     HAL_ERROR: 失败
 */
static HAL_StatusTypeDef w25q64jv_check_id(void)
{
    QSPI_CommandTypeDef qspi_command_struct = {0};
    uint32_t jedec_id = 0;
    
    /* JEDEC ID */
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = JEDEC_ID_INST;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_1_LINE;
    qspi_command_struct.NbData = 3;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    if (HAL_QSPI_Command(&hqspi, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    if (HAL_QSPI_Receive(&hqspi, (uint8_t *)&jedec_id, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    if (jedec_id != 0x001740EF)
    {
        return HAL_ERROR;
    }
    
    return HAL_OK;
}

/**
 * @brief   W25Q64JV写使能
 * @param   无
 * @retval  操作结果
 * @arg     HAL_OK: 成功
 * @arg     HAL_ERROR: 失败
 */
static HAL_StatusTypeDef w25q64jv_write_enable(void)
{
    QSPI_CommandTypeDef qspi_command_struct = {0};
    QSPI_AutoPollingTypeDef qspi_autopolling_struct = {0};
    
    /* Write Enable */
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = WRITE_ENABLE_INST;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_NONE;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    if (HAL_QSPI_Command(&hqspi, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    /* Read Ststus Register-1 */
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = READ_STATUS_REGISTER1_INST;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_1_LINE;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    qspi_autopolling_struct.Match = 0x02;
    qspi_autopolling_struct.Mask = 0x02;
    qspi_autopolling_struct.Interval = 0x10;
    qspi_autopolling_struct.StatusBytesSize = 1;
    qspi_autopolling_struct.MatchMode = QSPI_MATCH_MODE_AND;
    qspi_autopolling_struct.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;
    if (HAL_QSPI_AutoPolling(&hqspi, &qspi_command_struct, &qspi_autopolling_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    return HAL_OK;
}

/**
 * @brief   使能W25Q64JV Quad SPI
 * @param   无
 * @retval  操作结果
 * @arg     HAL_OK: 成功
 * @arg     HAL_ERROR: 失败
 */
static HAL_StatusTypeDef w25q64jv_quad_enable(void)
{
    QSPI_CommandTypeDef qspi_command_struct = {0};
    uint8_t status_register2;
    
    /* Read Status Register-2 */
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = READ_STATUS_REGISTER2_INST;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_1_LINE;
    qspi_command_struct.NbData = 1;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    if (HAL_QSPI_Command(&hqspi, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    if (HAL_QSPI_Receive(&hqspi, &status_register2, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    status_register2 |= 1 << 1;
    
    if (w25q64jv_write_enable() != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    /* Write Status Register-2 */
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = WRITE_STATUS_REGISTER2_INST;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_1_LINE;
    qspi_command_struct.NbData = 1;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    if (HAL_QSPI_Command(&hqspi, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    if (HAL_QSPI_Transmit(&hqspi, &status_register2, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    if (w25q64jv_auto_polling_ready(HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    return HAL_OK;
}

/**
 * @brief   初始化W25Q64JV
 * @param   无
 * @retval  初始化结果
 * @arg     HAL_OK: 成功
 * @arg     HAL_ERROR: 失败
 */
HAL_StatusTypeDef w25q64jv_init(void)
{
    __IO uint8_t *ptr;
    uint32_t i;
    
    ptr = (__IO uint8_t *)&hqspi;
    for (i=0; i<sizeof(hqspi); i++)
    {
        *ptr++ = 0x00;
    }
    hqspi.Instance = QUADSPI;
    if (HAL_QSPI_DeInit(&hqspi) != HAL_OK)
    {
        return HAL_ERROR;
    }
    MX_QUADSPI_Init();
    
    if (w25q64jv_reset() != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    if (w25q64jv_auto_polling_ready(HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    if (w25q64jv_check_id() != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    if (w25q64jv_quad_enable() != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    return HAL_OK;
}

/**
 * @brief   使能W25Q64JV内存映射
 * @param   无
 * @retval  操作结果
 * @arg     HAL_OK: 成功
 * @arg     HAL_ERROR: 失败
 */
HAL_StatusTypeDef w25q64jv_enable_memory_mapped_mode(void)
{
    QSPI_CommandTypeDef qspi_command_struct = {0};
    QSPI_MemoryMappedTypeDef qspi_memory_mapped_struct = {0};
    
    if (w25q64jv_write_enable() != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    /* Fast Read */
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = FAST_READ_QUAD_IO_INST;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_4_LINES;
    qspi_command_struct.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 6;
    qspi_command_struct.DataMode = QSPI_DATA_4_LINES;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    
    qspi_memory_mapped_struct.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;
    if (HAL_QSPI_MemoryMapped(&hqspi, &qspi_command_struct, &qspi_memory_mapped_struct) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    return HAL_OK;
}

/**
 * @brief   擦除W25Q64JV扇区
 * @param   sector_address: 扇区地址
 * @retval  擦除结果
 * @arg     HAL_OK: 成功
 * @arg     HAL_ERROR: 失败
 */
HAL_StatusTypeDef w25q64jv_erase_sector(uint32_t sector_address)
{
    QSPI_CommandTypeDef qspi_command_struct = {0};
    
    if (w25q64jv_write_enable() != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    /* Sector Erase */
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = SECTOR_ERASE_INST;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_1_LINE;
    qspi_command_struct.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_command_struct.Address = sector_address;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_NONE;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    if (HAL_QSPI_Command(&hqspi, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    if (w25q64jv_auto_polling_ready(HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    return HAL_OK;
}

/**
 * @brief   W25Q64JV页编程
 * @param   page_address: 页地址
 * @param   data: 编程数据
 * @retval  编程结果
 * @arg     HAL_OK: 成功
 * @arg     HAL_ERROR: 失败
 */
HAL_StatusTypeDef w25q64jv_page_program(uint32_t page_address, uint8_t *data)
{
    QSPI_CommandTypeDef qspi_command_struct = {0};
    
    if (w25q64jv_write_enable() != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    /* Quad Input Page Program */
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = QUAD_INPUT_PAGE_PROGRAM_INST;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_1_LINE;
    qspi_command_struct.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_command_struct.Address = page_address;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_4_LINES;
    qspi_command_struct.NbData = 0x100;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    if (HAL_QSPI_Command(&hqspi, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    if (HAL_QSPI_Transmit(&hqspi, data, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    if (w25q64jv_auto_polling_ready(HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    return HAL_OK;
}

/**
 * @brief   擦除W25Q64JV
 * @param   无
 * @retval  擦除结果
 * @arg     HAL_OK: 成功
 * @arg     HAL_ERROR: 失败
 */
HAL_StatusTypeDef w25q64jv_erase_chip(void)
{
    QSPI_CommandTypeDef qspi_command_struct = {0};
    
    if (w25q64jv_write_enable() != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    /* Sector Erase */
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = CHIP_ERASE_INST;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_NONE;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    if (HAL_QSPI_Command(&hqspi, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    if (w25q64jv_auto_polling_ready(100000) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    return HAL_OK;
}
