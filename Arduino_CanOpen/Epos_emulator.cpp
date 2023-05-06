/*=============================================================================
 * Author: Spacebeetech - Navegacion
 * Date: 23/02/2023
 * Board: Arduino Mega
 * Entorno de programacion: Ide arduino 1.8.19
 *
 * Descripcion: Libreria Emulador de EPOS4
 *===========================================================================*/

/*=====================[ Inclusiones ]============================*/
#include "Epos_emulator.h"
#include <Arduino.h>
#include "CanOpen_Arduino.h"
#include "Define.h"

const int PWM_MAX = 20;
const int PWM_MIN = 5;
const double threshold=2;

uint8_t ids[CANopen_cantNodos_client]={Can_nodeid_client3, Can_nodeid_client2, Can_nodeid_client1, Can_nodeid_client4, Can_nodeid_client5, Can_nodeid_client6};

Epos_emulator::Epos_emulator(uint8_t Can_nodeid, uint8_t Z_PIN, int nBits, int CPT, int ratioGB, uint8_t En, uint8_t in1, uint8_t in2, uint8_t numeroDiccionario){
    _nodeid = Can_nodeid;
    _En = En;
    _in1 = in1;
    _in2 = in2;
    _numeroDiccionario = numeroDiccionario;
    _Z_PIN = Z_PIN;
    _nBits = nBits;
    _CPT = CPT;
    _ratioGB = ratioGB;

    pinMode(En, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    //Valores iniciales:
    _currentPos = 0.0; // degrees
    _rotDirection = 0; // CW
    _error = 0;        // degrees
    _setpoint = 360;   // degrees
    _count = 0;
    _PWM = 0;
    _threshold = 2;    // degrees    
}

int updateRotation(int inA, int inB, double error)
{
  int rotDirection = 0;
  if (error >= 0)
  {
    rotDirection = 0;
    digitalWrite(inA, HIGH);
    digitalWrite(inB, LOW);
  }
  else
  {
    rotDirection = 1;
    digitalWrite(inA, LOW);
    digitalWrite(inB, HIGH);
  }
  return rotDirection;
}

void controlLoop(double error, double K, int en)
{
  int PWM = 0;
  if (abs(error) > threshold)
  {
    PWM = abs(error) * K;
    if (PWM > PWM_MAX)
      PWM = PWM_MAX;
    if (PWM < PWM_MIN)
      PWM = PWM_MIN;
  }

  analogWrite(en, PWM); // Send PWM signal to L298N Enable pin
}

void Epos_emulator::init(){
   
}

void Epos_emulator::Execute(){
  
  //Variables para obtener valores del diccionario
  uint32_t dataa=0;

  uint16_t index2=0x6060;
  uint8_t subindex2=0x00;
  
  //Verificar si el modo esta en on o off para activar o desactivar enable puente H
  CANopen_Read_Dictionary(0x6040, 0x00, &dataa, 16, _nodeid);            //Obtengo estado driver desde el diccionario
  /*
  if((dataa & 0x0F)==0x07){                                              //Si los primero 4 bytes estan en "0111", el epos esta en modo "operation enabled"
    digitalWrite(_En, HIGH);                                             //Activo el puente H
  }else{
    digitalWrite(_En, LOW);                                              //Desactivo el puente H
  }
  */

  //Obtengo modo de operacion del epos
  CANopen_Read_Dictionary(0x6060, 0x00, &dataa, 8, _nodeid);             //Obtengo modo
  
  if(dataa == 0x01){                                                     //Si el modo es PPM
    if(_set_cero==0){                                                    //Si nunca se seteo en cero, hago un home
      if(true==false){                                                   //Mientras el encoder no detecte posicion cero
        //Muevo el motor con pwm fijo
        //analogWrite(pin_pwm1_motor,127);
      }else{
        _count=0;
        _set_cero=1;
      }
    }else{                 
        CANopen_Read_Dictionary(0x607A, 0x00, &dataa, 32, _nodeid);        //Obtengo setpoint desde el diccionario
        //Control proporcional para posicion
        _setpoint=dataa;
        CANopen_Read_Dictionary(0x30A1, 0x01, &dataa, 32, _nodeid);        //Obtengo k desde el diccionario
        /*
        Serial.print("Nodo: ");
        Serial.print(_nodeid);
        Serial.print(" Ganancia P: ");
        Serial.print(dataa);
        double K=-dataa/1000000;
        Serial.print(" Ganancia P: ");
        Serial.println(K);
        */
        double K=1;
        _error=_setpoint-_count*(360.0 / _ratioGB);
        //Serial.println(_count);
        _rotDirection = updateRotation(_in2,_in1,_error);
        controlLoop(_error, K , _En);
    }
  }else{
    CANopen_Read_Dictionary(0x6060, 0x00, &dataa, 8, _nodeid);              //Obtengo modo
    if(dataa == 0x09){                                                      //Si esta en modo velocidad
        //Serial.print("PWM: ");
        CANopen_Read_Dictionary(0x60FF, 0x00, &dataa, 32, _nodeid);         //Obtengo setpoint desde el diccionario
        _setpoint=dataa;
        //Control Proporcional para velocidad
      
    }else{
      //Serial.print("Modo: "); Serial.println(dataa);
    }
  }
}

void Epos_emulator::interruptZ() {
  if (!_rotDirection)
    _count++;
  else
    _count--;
}

void Epos_emulator::obtener_setpoint() {
   //Variables para obtener valores del diccionario
  uint32_t dataa=0;
  CANopen_Read_Dictionary(0x60FF, 0x00, &dataa, 32, _nodeid);        //Obtengo setpoint desde el diccionario
 Serial.print("Nodo: ");
 Serial.print(_nodeid);
 Serial.print(" setpoint VEL: ");
 Serial.print(dataa);
 Serial.print(" pos: ");
 CANopen_Read_Dictionary(0x607A, 0x00, &dataa, 32, _nodeid);        //Obtengo setpoint desde el diccionario
 Serial.println(dataa);
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
