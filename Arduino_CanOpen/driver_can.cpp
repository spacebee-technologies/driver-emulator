/*=============================================================================
 * Author: Spacebeetech - Navegacion
 * Date: 23/02/2023
 * Board: Arduino Mega
 * Entorno de programacion: Ide arduino 1.8.19
 *
 * Descripcion: Libreria CanOpen para arduino con periferico CAN. Descripcion de periferico CAN
 *===========================================================================*/

/*=====================[ Inclusiones ]============================*/
#include "driver_can.h"
#include <stdint.h>

/*=====================[Variables]================================*/
struct can_frame can_send; //Para enviar
struct can_frame can_rec;  //Para recibir
MCP2515 mcp2515(53);

/*=====================[Implementaciones]==============================*/

/*========================================================================
  Funcion: CAN_peripheral_initialization
  Descripcion: Configura e inicializa el periferico can
  Sin parametro de entrada
  No retorna nada
  ========================================================================*/
void CAN_peripheral_initialization(void){
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setConfigMode();
  mcp2515.setFilterMask(MCP2515::MASK0, false, 0x7F0); //Desde 0x600 a 0x60F
  mcp2515.setFilter(MCP2515::RXF0, false, 0x600);
  mcp2515.setFilter(MCP2515::RXF1, false, 0x600);
  //Set Mask 1 to Check All Bits (0x7FF)
  mcp2515.setFilterMask(MCP2515::MASK1, false, 0x7F0);
  //Set Filters 2 to 5 to Filter Only CAN ID on 0x1AD
  mcp2515.setFilter(MCP2515::RXF2, false, 0x600);
  mcp2515.setFilter(MCP2515::RXF3, false, 0x600);
  mcp2515.setFilter(MCP2515::RXF4, false, 0x600);
  mcp2515.setFilter(MCP2515::RXF5, false, 0x600);
  mcp2515.setNormalMode();
}

/*========================================================================
  Funcion: Driver_can_sendMessage
  Descripcion: Envia un mensaje por el periferico CAN
  Parametro de entrada:
                        CanOpen_frame *frame: Estructura que contiene la informacion del mensaje a enviar
                        uint8_t type:         Variable para distingir si es mensaje normal o FD. 0=normar 1=FD
  No retorna nada
  ========================================================================*/
void Driver_can_sendMessage(const struct CanOpen_frame *frame, uint8_t type){
    if(type == 0){
        can_send.can_id  = frame->can_id;
        can_send.can_dlc = frame->can_dlc;
        for(int i=0; i<can_send.can_dlc; i++){
            can_send.data[i]=frame->data[i];
        }
        mcp2515.sendMessage(&can_send);
    }else{
        //MCP2515 no soporta mensajes FD
    }
}

/*========================================================================
  Funcion: Driver_can_readMessage
  Descripcion: Recibe un mensaje por el periferico CAN
  Parametro de entrada:
                        CanOpen_frame *frame: Estructura donde se guardara el mensaje recibido
  Retorna:              true:  si se realizo con exito
                        false: si se realizo con errores
  ========================================================================*/
bool Driver_can_readMessage(struct CanOpen_frame *frame){
    if(mcp2515.readMessage(&can_rec) == MCP2515::ERROR_OK){
        frame->can_id = can_rec.can_id;
        frame->can_dlc= can_rec.can_dlc;
        for(int i=0; i<8; i++){
            frame->data[i]= can_rec.data[i];
        }
        return true;
    }else{
        return false;
    }
}
    
