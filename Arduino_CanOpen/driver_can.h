/*=============================================================================
 * Author: Spacebeetech - Navegacion
 * Date: 23/02/2023
 * Board: Arduino Mega
 * Entorno de programacion: Ide arduino 1.8.19
 *
 * Descripcion: Libreria CanOpen para arduino con periferico CAN. Descripcion de periferico CAN
 *===========================================================================*/
/*==================[Definiciones]================================*/
#ifndef _driver_can_H
#define _driver_can_H

/*=====================[ Inclusiones ]============================*/
#include <Arduino.h>
#include <SPI.h>
#include <mcp2515.h>

/*=====================[Variables]================================*/
struct CanOpen_frame {
    uint32_t   can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    uint8_t    can_dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
    uint8_t    data[16] __attribute__((aligned(8)));
};

/*=================[Prototipos de funciones]======================*/
void CAN_peripheral_initialization(void);
void Driver_can_sendMessage(const struct CanOpen_frame *frame, uint8_t type);
bool Driver_can_readMessage(struct CanOpen_frame *frame);



#endif
