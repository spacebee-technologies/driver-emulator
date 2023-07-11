/*=============================================================================
 * Author: Spacebeetech - Navegacion
 * Date: 23/02/2023
 * Board: Arduino Mega
 * Entorno de programacion: Ide arduino 1.8.19
 *
 * Descripcion: Libreria CanOpen para arduino con periferico CAN
 *===========================================================================*/

/*==================[Definiciones]================================*/
#ifndef _CanOpen_Arduino_H
#define _CanOpen_Arduino_H

#define CANopen_cantNodos_client 6
//#define CANopen_nodeid 0x05

#define CAN_send_timeout     4                             //Tiempo de espera en ms para verificar el envio correcto de mensaje por can
#define Boot_up 1     //1 Si se quiere enviar mensaje Boot-up luego de pasar al estado pre-operacional  o 0 para desactivar

#define CANopen_RSDO_timeout    1 
#define CANopen_SDO_mode_client 0                          //Modo maestro
#define CANopen_SDO_mode_server 1                          //Modo Esclavo
#define CANopen_SDO_timeout     10                         //Tiempo de espera en ms para recibir respuesta de servidor
#define CANopen_SDO_command_writing_request_4byte     0x23 //(rx) Solicitud de escritura de 4 bytes
#define CANopen_SDO_command_writing_request_2byte     0x2B //(rx) Solicitud de escritura de 2 bytes
#define CANopen_SDO_command_writing_request_1byte     0x2F //(rx) Solicitud de escritura de 1 byte
#define CANopen_SDO_command_write_Confirmation        0x60 //(tx) Confirmacion de escritura a cliente (maestro) desde servidor (esclavo)
#define CANopen_SDO_command_read_request              0x40 //(rx) Solicitud de lectura (upload) - solicitud de parametro a servidor (esclavo)
#define CANopen_SDO_command_response_parameter_4byte  0x43 //(tx) Respuesta envio de parametro a cliente (4 bytes)
#define CANopen_SDO_command_response_parameter_2byte  0x4B //(tx) Respuesta envio de parametro a cliente (2 bytes)
#define CANopen_SDO_command_response_parameter_1byte  0x4F //(tx) Respuesta envio de parametro a cliente (1 byte)
#define CANopen_SDO_command_transfer_aborted          0x80 //(tx) Transferencia de datos abortada, envio mensaje de error a cliente (No sopoerado en esta libreria)

/*=====================[ Inclusiones ]============================*/
#include <Arduino.h>

/*=================[Prototipos de funciones]======================*/
bool CANopen_Write_Dictionary(uint16_t index, uint8_t subindex, uint32_t data, uint8_t dictionary, uint8_t CANopen_nodeid2);
bool CANopen_Read_Dictionary(uint16_t index, uint8_t subindex, uint32_t *data, uint8_t dictionary, uint8_t CANopen_nodeid2);
void Canopen_Set_client_nodeid(uint8_t *ids);
uint8_t CANopen_init(void);
uint8_t CANopen_SDO_Expedited_Write(uint8_t node_id, uint8_t command, uint16_t index, uint8_t subindex,  uint8_t *data, uint8_t mode, uint8_t data_len);
uint8_t CANopen_SDO_Expedited_Read(uint16_t *index, uint8_t *subindex, uint8_t *node_id_client);
void CANopen_STOP(void);

/*=====================[Variables]================================*/

//uint8_t CANopen_id_nodos[10]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

typedef enum
    {
        CANopen_INITIALIZATION,             //Estado de inicializacion, luego de configurarse se pasa al siguiente estado
        CANopen_PRE_OPERATIONAL,            //Estado pre operacional (solo responde a comandos NMT, SDO, SYNC, Time stamp o Hearbeat)
        CANopen_OPERATIONAL,                //Estado operacional (se activa el soporte de PDOs ademas de los comandos anteriores)
        CANopen_STOPPED,                    //Estado parado, deja inactivos todos los objetos de comunicación posibles (no se pueden enviar ni recibir PDOs ni SDOs), excepto a los comandos NMT que pueden cambiar a cualquiera de los estados restantes y Heartbeat. Es decir, un nodo solo puede realizar vigilancia de nodos o latidos, pero no puede recibir ni transmitir mensajes.
    } CANopen_STATES;                       //Enumaracion de los estados posibles de la maquina de estado CANopen

volatile static CANopen_STATES state = CANopen_INITIALIZATION; //Variable para guardar el estado de la aplicaciÃ³n
  
#endif
