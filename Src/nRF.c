/*
 * @Descripttion: 
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-10-13 21:03:13
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-10-20 16:47:05
 */

#include "nRF.h"
#include "nRF24L01.h"

/**
 * @name: Oreo097
 * @msg: 定义CSN和CE针脚的函数
 * @param {type} 
 * @return {type} 
 */
void NRF_DEF(pin CE_PIN, pin CSN_PIN)
{
    info.CE = CE_PIN;
    info.CSN = CSN_PIN;
}

void NRF_CE(uint8_t status)
{
    HAL_GPIO_WritePin(info.CE.gpio_group, info.CE.pin, 0);
}

void NRF_CSN(uint8_t status)
{
    HAL_GPIO_WritePin(info.CSN.gpio_group, info.CE.pin, status);
}

uint8_t nrf_write_reg(uint16_t regaddr, uint8_t *pdata, uint8_t size)
{
    uint8_t status;
    NRF_CSN(0); //官方文档说明每次执行command指令的时候CSN必须从高到低跳变，拉低csn
    status = HAL_SPI_Transmit(NRF_SPI, W_REGISTER + regaddr, sizeof(regaddr), 6);
    HAL_SPI_Transmit(NRF_SPI, pdata, size, 6);
    NRF_CSN(1); //拉高csn
    return status;
}

uint8_t nrf_read_reg(uint16_t regaddr, uint8_t *pdata, uint8_t size)
{
    uint8_t status;
    NRF_CSN(0); //拉低csn
    status = HAL_SPI_Transmit(NRF_SPI, R_REGISTER + regaddr, sizeof(regaddr), 6);
    HAL_SPI_Receive(NRF_SPI, pdata, size, 6);
    NRF_CE(1); //拉高csn
    return status;
}

uint8_t nrf_read_buff(uint16_t bufaddr, uint8_t *pdata, uint8_t size) //读buff
{
}

uint8_t nrf_write_buff(uint16_t buffaddr, uint8_t *pdata, uint8_t size) //写buff
{
}
/**
 * @name: Oreo097
 * @msg: 上电初始化函数
 * @param {type} 
 * @return {type} 
 */

// void NRF_INIT_TX()
// {
//     uint8_t command
// }

/**
 * @name: Oreo097
 * @msg: 初始化接收函数
 * @param {type} 
 * @return {type} 
 */
void NRF_INIT_RX()
{
    //初始化为RX模式
    //配置过程为
    //拉低CE
    //配置
    uint8_t order;
    order = 0x0f;
    NRF_CE(0); //CE拉低开始配置

    NRF_CE(1); //ce拉高进入RX模式
}

/**
 * @name: Oreo097
 * @msg: 初始化发送函数
 * @param {type} 
 * @return {type} 
 */
void NRF_INIT_TX()
{
    uint8_t order;
    order = 0x0e;
    NRF_CE(1);
}

void nrf_config_tx() //设置config寄存器为TX模式
{
    nrf_write_reg(NRF_CONFIG, &order, sizeof(order)); //配置CONFIG寄存器
}

void nrf_config_rx() //设置config寄存器为RX模式
{
    nrf_write_reg(NRF_CONFIG, &order, sizeof(order)); //配置CONFIG寄存器
}

void nrf_set_channel(int channel) //
{
    nrf_write_reg(RF_CH, &channel, sizeof(channel));
}

void nrf_set_rx_addr(uint8_t p, int *addr) //设置RX pipe和地址
{
    switch (p)
    {
    case 0:
        nrf_write_reg(RX_ADDR_P0, addr, 5);
    case 1:
        nrf_write_reg(RX_ADDR_P1, addr, 5);
    case 2:
        nrf_write_reg(RX_ADDR_P2, addr, 5);
    case 3:
        nrf_write_reg(RX_ADDR_P3, addr, 5);
    case 4:
        nrf_write_reg(RX_ADDR_P4, addr, 5);
    case 5:
        nrf_write_reg(RX_ADDR_P5, addr, 5);
    }
}

void nrf_set_tx_addr(int *addr) //设置TX地址
{
    nrf_write_reg(TX_ADDR, addr, 5);
}
