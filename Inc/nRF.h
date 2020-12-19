/*
 * @Descripttion: 
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-10-13 20:53:47
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-10-20 16:46:02
 */

#include"nRF24L01.h"
#include "main.h"
#include "stm32f1xx_hal.h"

#ifndef __NRF_H__
#define __NRF_H__

#define GPIO_GROUP GPIO_TypeDef

#define NRF_SPI SPI1

typedef struct
{
    GPIO_GROUP *gpio_group;
    uint8_t pin;
}pin;

struct 
{
    pin CE;
    pin CSN;
}info;

struct 
{
    uint8_t pipe_0[5];
    uint8_t pipe_share;
    uint8_t pipe_1;
    uint8_t pipe_2;
    uint8_t pipe_3;
    uint8_t pipe_4;
}pipe;


void NRF_DEF();

void NRF_INIT_RX();

void NRF_INIT_TX();

void NRF_CE();

void NRF_CSN();


// /*command word*/

// #define R_REGISTER 0//官方文档中是000A AAAA 后边5个A意思是寄存器地址
// #define W_REGISTER 32


// #define R_RX_PAYLOAD 97
// #define W_TX_PAYLOAD 160
// #define FLUSH_TX 225
// #define FLUSH_RX 226

#endif