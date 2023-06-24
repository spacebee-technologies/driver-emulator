/*=============================================================================
 * Author: Spacebeetech - Navegacion
 * Date: 23/02/2023
 * Board: Arduino Mega
 * Entorno de programacion: Ide arduino 1.8.19
 *
 * Descripcion: Libreria Emulador de EPOS4
 *===========================================================================*/

/*=====================[ Inclusiones ]============================*/
#include <Arduino.h>

#include "Epos_emulator.h"
#include "CanOpen_Arduino.h"
#include "Define.h"

#define ANGLE_FACTOR 100

uint8_t ids[CANopen_cantNodos_client]={Can_nodeid_client3, Can_nodeid_client2, Can_nodeid_client1, Can_nodeid_client4, Can_nodeid_client5, Can_nodeid_client6};

Epos_emulator::Epos_emulator(uint8_t Can_nodeid, int nBits, int CPT, MotorController *controller, uint8_t numeroDiccionario){
    _nodeid = Can_nodeid;
    _numeroDiccionario = numeroDiccionario;
    _nBits = nBits;
    _CPT = CPT;

    //Valores iniciales:
    _controller = controller;
    _setpoint = 360;   // degrees
}

void Epos_emulator::init(){
   
}

void Epos_emulator::Execute(double newSetpoint) {
  _controller->update(newSetpoint);
}

void Epos_emulator::interruptZ() {
    _controller->interruptZ();
}

void Epos_emulator::obtener_setpoint() {
   //Variables para obtener valores del diccionario
  uint32_t data=0;
  CANopen_Read_Dictionary(0x60FF, 0x00, &data, 32, _nodeid);        //Obtengo setpoint desde el diccionario
 Serial.print("Nodo: ");
 Serial.print(_nodeid);
 Serial.print(" setpoint VEL: ");
 Serial.print(data);
 Serial.print(" pos: ");
 CANopen_Read_Dictionary(0x607A, 0x00, &data, 32, _nodeid);        //Obtengo setpoint desde el diccionario
 Serial.println(data);
}

void Epos_Emulator_init(void){
     Canopen_Set_client_nodeid(ids);
}

void Epos_CanOpen_Consult(void){
     //CANopen
    //verifico si hay mensaje SDO CANopen
    uint16_t index=0x0000;    //Variable donde se guarda el index modificado por SDO
    uint8_t  subindex=0x00;   //Variable donde se guarda el subindex modificado por SDO
    uint8_t  Nodeid=0x00;     //Variable donde se guarda el nodeid del diccionario modificado por SDO
    uint8_t  res = CANopen_SDO_Expedited_Read(&index, &subindex, &Nodeid);

    if(res==0){
        //Serial.print("Node: "); Serial.print(Nodeid); Serial.println(": Mensaje SDO recibido y se escribio dato sobre diccionario");          //En index y subindex se guarda el diccionario que se sobreescrtibio
    }else{
        if(res==4){
            //Serial.print("Node: "); Serial.print(Nodeid);  Serial.println(": Mensaje SDO recibido y dato de diccioanrio enviado correctamente"); //En index y subindex se guarda el diccionario que se envio
        }else{
            //Serial.println("Error");
        }
    }
}
