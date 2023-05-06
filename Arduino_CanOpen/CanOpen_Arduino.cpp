/*=============================================================================
 * Author: Spacebeetech - Navegacion
 * Date: 23/02/2023
 * Board: Arduino Mega
 * Entorno de programacion: Ide arduino 1.8.19
 *
 * Descripcion: Libreria CanOpen para arduino con periferico CAN
 *===========================================================================*/

/*=====================[ Inclusiones ]============================*/
#include "CanOpen_Arduino.h"
#include "driver_can.h"
#include "Dictionary.h"
#include <stdint.h>

/*=====================[Variables]================================*/  
struct CanOpen_frame canMsg_send; //Para enviar
struct CanOpen_frame canMsg_rec;  //Para recibir
uint8_t CANopen_nodeid=  0x05;
uint8_t CANopen_id_nodos[CANopen_cantNodos_client];

/*=====================[Implementaciones]==============================*/

/*========================================================================
  Funcion: Canopen_Set_client_nodeid
  Descripcion: Configura los id de los nodos clientes. Sirve para tener varios clientes en el mismo codigo (permite manejar varios id)
  Parametro de entrada: Puntero a la variable que contiene el arreglo de ids
  Retorna:   true  = si se envio correctamente
             false = si no se pudo enviar
  ========================================================================*/
void Canopen_Set_client_nodeid(uint8_t *ids){
    for(uint8_t i=0; i<CANopen_cantNodos_client; i++ ){
        CANopen_id_nodos[i]=ids[i];
    }
}

/*========================================================================
  Funcion: CANopen_BootUp
  Descripcion: Envia mensaje de inicio BootUp por MCAN
  Sin parametro de entrada
  Retorna:   true  = si se envio correctamente
             false = si no se pudo enviar
  ========================================================================*/
bool CANopen_BootUp(void){
    //Manda los datos
    for(uint8_t i=0; i<CANopen_cantNodos_client ;i++){     //Recorro el arreglo que contiene los ID de los nodos clientes
        canMsg_send.can_id  = 0x700 + CANopen_id_nodos[i];
        canMsg_send.can_dlc = 8;
        for(int i=0; i<8; i++){
            canMsg_send.data[i]=0;
            }
        Driver_can_sendMessage(&canMsg_send, 0);
    }
    return true;
}

/*========================================================================
  Funcion: CANopen_STOP
  Descripcion: Pasa al estado stop de la maquina de estados de CANopen
  Sin parametro de entrada
  No retorna nada
  ========================================================================*/
void CANopen_STOP(void){
   state = CANopen_STOPPED;
}

/*========================================================================
  Funcion: CANopen_Write_Dictionary
  Descripcion: Escribe dato en el diccionario de objetos
  Parametro de entrada:  uint16_t index     = indice donde se desea escribir
                         uint8_t subindex   = subindice donde se desea escribir
                         uint32_t data      = dato a escribir
                         uint8_t dictionary = diccionario al cual se desea escribir (32, 16, 8)
  Retorna:               True si se puedo escribir
                         False si no se puedo escribir
  Importante:            Esta funcion implementa seccion critica
  ========================================================================*/
bool CANopen_Write_Dictionary(uint16_t index, uint8_t subindex, uint32_t data, uint8_t dictionary, uint8_t CANopen_nodeid2){
    uint8_t posicion_diccionario_nodoid=0;                 //Variable para almacenar la posicion del diccionario
    for(uint8_t i=0; i<CANopen_cantNodos_client; i++){     //Recorro el arreglo que contiene los ID de los nodos clientes
        if(CANopen_id_nodos[i]==CANopen_nodeid2){          //Si el nodo corresponde al id con el que se esta trabajando actualmente
            posicion_diccionario_nodoid=i;                 //Guardo posicion
            break;                                         //Salgo del for
        }   
    }
    bool retorno = false;
    if(dictionary==32){
        uint16_t  tamanio_dic=sizeof(dictionary32)/(8*CANopen_cantNodos_client);       //Obtengo numeros de elementos del diccionario
        for(uint16_t i=0; i<tamanio_dic;i++){               //Recorro el diccionario
                                                            //Busco index y subindex indicados
            if(dictionary32[posicion_diccionario_nodoid][i].Index==index && dictionary32[posicion_diccionario_nodoid][i].Subindex==subindex){
                if(dictionary32[posicion_diccionario_nodoid][i].Attribute==0){           //Si el atributo permite escritura
                    dictionary32[posicion_diccionario_nodoid][i].Data=data;              //Escribo dato en diccionario
                    retorno=true;
                }
            }
        }
    }
    
    if(dictionary==16){
        uint16_t  tamanio_dic=sizeof(dictionary16)/(6*CANopen_cantNodos_client);       //Obtengo numeros de elementos del diccionario
        for(uint16_t i=0; i<tamanio_dic;i++){               //Recorro el diccionario
                                                            //Busco index y subindex indicados
            if(dictionary16[posicion_diccionario_nodoid][i].Index==index && dictionary16[posicion_diccionario_nodoid][i].Subindex==subindex){
                if(dictionary16[posicion_diccionario_nodoid][i].Attribute==0){           //Si el atributo permite escritura
                    dictionary16[posicion_diccionario_nodoid][i].Data=(uint16_t)data;    //Escribo dato en diccionario
                    retorno=true;
                }
            }
        }
    }
    
    if(dictionary==8){
        uint16_t  tamanio_dic=sizeof(dictionary8)/(5*CANopen_cantNodos_client);        //Obtengo numeros de elementos del diccionario
        for(uint16_t i=0; i<tamanio_dic;i++){               //Recorro el diccionario
                                                            //Busco index y subindex indicados
            if(dictionary8[posicion_diccionario_nodoid][i].Index==index && dictionary8[posicion_diccionario_nodoid][i].Subindex==subindex){
                if(dictionary8[posicion_diccionario_nodoid][i].Attribute==0){            //Si el atributo permite escritura
                    dictionary8[posicion_diccionario_nodoid][i].Data=(uint8_t)data;      //Escribo dato en diccionario
                    retorno=true;
                }
            }
        }
    }
    return retorno;
}

/*========================================================================
  Funcion: CANopen_Read_Dictionary
  Descripcion: Lee dato en el diccionario de objetos
  Parametro de entrada:  uint16_t index     = indice donde se desea leer
                         uint8_t subindex   = subindice donde se desea leer
                         uint32_t* data     = puntero a la variable donde se quiere guardar al dato
                         uint8_t dictionary = diccionario al cual se desea escribir (32, 16, 8)
                         uint8_t CANopen_nodeid = Id del nodo del cual llego el mensaje. Se utiliza para tener diferentes nodos en el mismo arduino. De esta forma podemos crear varios nodos con diferentes ID y diccionarios
  Retorna:               True si se puedo leer
                         False si no se puedo leer
  Importante:            Esta funcion implementa seccion critica
  ========================================================================*/
bool CANopen_Read_Dictionary(uint16_t index, uint8_t subindex, uint32_t *data, uint8_t dictionary, uint8_t CANopen_nodeid2){
    uint8_t posicion_diccionario_nodoid=0;                 //Variable para almacenar la posicion del diccionario
    for(uint8_t i=0; i<CANopen_cantNodos_client ;i++){     //Recorro el arreglo que contiene los ID de los nodos clientes
        if(CANopen_id_nodos[i]==CANopen_nodeid2){           //Si el nodo corresponde al id con el que se esta trabajando actualmente
            posicion_diccionario_nodoid=i;                 //Guardo posicion
            break;                                         //Salgo del for
        }   
    }
    bool retorno = false;
    if(dictionary==32){
        uint16_t  tamanio_dic=sizeof(dictionary32)/(8*CANopen_cantNodos_client);       //Obtengo numeros de elementos del diccionario
        for(uint16_t i=0; i<tamanio_dic;i++){               //Recorro el diccionario
                                                            //Busco index y subindex indicados
            if(dictionary32[posicion_diccionario_nodoid][i].Index==index && dictionary32[posicion_diccionario_nodoid][i].Subindex==subindex){
                if(dictionary32[posicion_diccionario_nodoid][i].Attribute==0){           //Si el atributo permite leer
                    *data=dictionary32[posicion_diccionario_nodoid][i].Data;             //Escribo dato en diccionario
                    retorno=true;
                }
            }
        }
    }
    
    if(dictionary==16){       
        uint16_t  tamanio_dic=sizeof(dictionary16)/(6*CANopen_cantNodos_client);       //Obtengo numeros de elementos del diccionario
        for(uint16_t i=0; i<tamanio_dic;i++){               //Recorro el diccionario
                                                            //Busco index y subindex indicados
            if(dictionary16[posicion_diccionario_nodoid][i].Index==index && dictionary16[posicion_diccionario_nodoid][i].Subindex==subindex){
                if(dictionary16[posicion_diccionario_nodoid][i].Attribute==0){           //Si el atributo permite leer
                    *data=(uint32_t)dictionary16[posicion_diccionario_nodoid][i].Data;   //Escribo dato en diccionario
                    retorno=true;
                }
            }
        }
    }
    
    if(dictionary==8){
        uint16_t  tamanio_dic=sizeof(dictionary8)/(5*CANopen_cantNodos_client);        //Obtengo numeros de elementos del diccionario
        for(uint16_t i=0; i<tamanio_dic;i++){               //Recorro el diccionario
                                                            //Busco index y subindex indicados
            if((dictionary8[posicion_diccionario_nodoid][i].Index==index) && (dictionary8[posicion_diccionario_nodoid][i].Subindex==subindex)){
                if(dictionary8[posicion_diccionario_nodoid][i].Attribute==0){            //Si el atributo permite leer
                    *data=(uint32_t)dictionary8[posicion_diccionario_nodoid][i].Data;    //Escribo dato en diccionario
                    retorno=true;
                }
            }
        }
    }
    return retorno;
}

/*========================================================================
  Funcion: CANopen_init
  Descripcion: Establece la configuracion del periferico can y cambia el estado de la maquina de estado CANopen
  Sin parametro de entrada
  Rertorna: uint8_t   0 = resultado ok
                      1 = Error al mandar mensaje Boot_Up
  ========================================================================*/
uint8_t CANopen_init(void){
    CAN_peripheral_initialization();
    state = CANopen_PRE_OPERATIONAL;                                //Cambio estado de la maquina de estado de CANopen
    if(Boot_up == 1){                                       //Si esta activo el Boot_up
        if(CANopen_BootUp()==false){ return 1; }            //Envio mensaje de inicio y verifico errores
    }
    return 0;                                               //Retorno OK
}

/*========================================================================
  Funcion: CANopen_SDO_Expedited_Write
  Descripcion: Envia un mensaje SDO
  Parametro de entrada:     uint8_t node_id  = id del nodo con el cual se desea comunicar si esta en modo cliente o el propio id del dispositivo si se esta en modo servidor
                            uint8_t command  = Describe la operacion del comando SDO (lectura/escritura), puede ser:
                                                0x22 = (rx) Solicitud de escritura > 4 bytes
                                                0x23 = (rx) Solicitud de escritura de 4 bytes
                                                0x2B = (rx) Solicitud de escritura de 2 bytes
                                                0x2F = (rx) Solicitud de escritura de 1 byte
                                                0x60 = (tx) Confirmacion de escritura a cliente (maestro) desde servidor (esclavo)
                                                0x40 = (rx) Solicitud de lectura (upload) - solicitud de parametro a servidor (esclavo)
                                                0x43 = (tx) Respuesta envio de parametro a cliente (4 bytes)
                                                0x4B = (tx) Respuesta envio de parametro a cliente (2 bytes)
                                                0x4F = (tx) Respuesta envio de parametro a cliente (1 byte)
                                                0x80 = (tx) Transferencia de datos abortada, envio mensaje de error a cliente (No sopoerado en esta libreria)
                            uint16_t index   = Indice del diccionario al que se desea acceder (2 bytes)
                            uint8_t subindex = Subindice deldiccionario al que se desea acceder (1 byte)
                            uint8_t data     = Dato a escribir en el diccionario, si es peticion de informacion data tiene que contener todos ceros (4 bytes) y luego se pasan los datos recibidos a esta variable
                            uint8_t mode     = Modo cliente (maestro) = 0  Modo servidor(esclavo) = 1
                            uint8_t data_len = TAamaño del mensaje a enviar. El tamaño puede ser de 0 bytes hasta 11 byte. cuando se envia hasta 4 bytes, se envia por can normal, cuando se envia mas de 4 bytes, se envia por can FD. 
  Retorna:                  0  = si se envio y recibio correctamente
                            2  = si no se obtuvo respuesta del servidor (solo funciona con mensajes SDO en modo cliente)
                            3  = si la respuesta del servidor no corresponde con el mensaje enviado (solo funciona con mensajes SDO en modo cliente)
                            4  = si la maquina de estados no paso la inicializacion
  Funcionamiento: Se debe llamar cuando se quiere mandar un mensaje SDO CANopen por MCAN
                  Funcionamiento interno cada vez que se llamaa esta funcion:
                  Genera el header a enviar por MCAN con la forma de un mensaje SDO y lo envia por MCAN.
                  Si esta en modo cliente, espera a recibir un mensaje can con la confirmacion de escritura sobre diccionario o una recepcion de dato (segun el comando seleccionado).
                  Si esta en modo servidor(esclavo), finaliza la funcion sin esperar confirmacion, es decir solo envia el dato.
========================================================================*/
uint8_t CANopen_SDO_Expedited_Write(uint8_t node_id, uint8_t command, uint16_t index, uint8_t subindex,  uint8_t *data, uint8_t mode, uint8_t data_len){
    if(state==CANopen_PRE_OPERATIONAL || state==CANopen_OPERATIONAL){        //Si el estado del CANopen permite mensajes SDO
        static uint8_t message[8] = {0}; 
        message[0]=command;                                                  //Byte 0 (comando SDO)
        message[1]=index & 0xFF;                                             //Byte 1 Index LSB (byte menos significativo)
        message[2]=index >> 8;                                               //Byte 2 Index MSB (byte mas significativo)
        message[3]=subindex;                                                 //Byte 3 Subindex
        for(uint8_t i=0; i<data_len; i++){
             message[4+i]=data[data_len-1-i];
        }

        uint32_t id =0x000;

        if(mode==CANopen_SDO_mode_client){
           id = 0x600 + node_id;
        }else{
           id = 0x580 + node_id;
        }
        
        //Envio mensaje por can
        canMsg_send.can_id=id;
        canMsg_send.can_dlc = 4+data_len;
        for(int i=0; i<16; i++){
          canMsg_send.data[i]=message[i];
          }

        if(data_len>4){
            Driver_can_sendMessage(&canMsg_send, 1);                        //Si el tamaño del mensaje es mayor a 4 bytes, lo envio por FD ya que el estandar normal de can no permite enviar mas de 8 bytes (4bytes de payload + 4 de datos)
        }else{
            Driver_can_sendMessage(&canMsg_send, 0);                        //Si el mensaje es menor a 4 bytes, lo envio por CAN comun
        }
        
        
        //Si esta en modo cliente, espero respuesta desde el servidor
        if(mode==CANopen_SDO_mode_client){
          uint8_t interacciones=0;
          uint8_t retornar=9;                                                //Inicializo en un valor no utilizado
          //Bucle infinito con timeout para verificar la recepcion en periferico can  
          while(true){
            if (Driver_can_readMessage(&canMsg_rec) == true) {              //Si recibi mensaje por can
                //Verifico que el mensaje recibido sea el correcto
                if(canMsg_rec.can_id!=0x580 + node_id){                      //Si la respuesta no es del servidor o no es un mensaje sdo tx 
                    retornar = 3;
                    break;                                                   //Salgo del while
                }
                if(canMsg_rec.data[0]==0x60||canMsg_rec.data[0]==0x43||canMsg_rec.data[0]==0x4B||canMsg_rec.data[0]==0x4F){ //Si la respuesta es un comando de respuesta
                    if(canMsg_rec.data[0]==0x60){                            //Si el mensaje es de confirmacion de escritura
                        retornar = 0;
                        break;                                               //Salgo del while
                    }else{                                                   //Sino verifico que el diccionario de respuesta corresponda con el enviado
                        if(canMsg_rec.data[1]==(index & 0xFF) && canMsg_rec.data[2]==(index >> 8) && (canMsg_rec.data[3]==subindex)){
                            //paso el dato recibido a la variable apuntada en la funcion
                            data[0]=canMsg_rec.data[7];
                            data[1]=canMsg_rec.data[6];
                            data[2]=canMsg_rec.data[5];
                            data[3]=canMsg_rec.data[4];
                            retornar = 0;
                            break;                                          //Salgo del while
                        }else{
                            retornar = 3;
                            break;                                          //Salgo del while
                        }
                    }
                }else{                                                      //Si la respuesta no es un comando de respuesta
                    retornar = 3;
                    break;                                                  //Salgo del while
                }
            }else{
                interacciones++;
              }
              
            if(interacciones*1>=CANopen_SDO_timeout){
                    retornar = 2;
                    break;                                                  //Salgo del while true
                }
            delay(1);
           }
         return retornar;                                                   //Retorno desde la funcion
        }
        return 0;                                                           //Retorno desde la funcion
    }else{
        return 4;                                                           //Retorno desde la funcion
    }
}


/*========================================================================
  Funcion: CANopen_SDO_Expedited_Read
  Descripcion: Recibe un mensaje can y comprueba que sea un mensaje SDO
  Parametro de entrada:     uint16_t *index:         Puntero de la variable donde se desea guardar el index el diccionario modificado o enviado por SDO
                            uint8_t *subindex:       Puntero de la variable donde se desea guardar el subindex el diccionario modificado o enviado por SDO
                            uint8_t *node_id_client: Puntero de la variable donde se desea guardar el id del nodo del diccionario modificado o enviado por SDO
  Retorna:                  0 = Mensaje SDO recibido y es escritura sobre diccionario
                            3 = Si el mensaje recibido no es SDO Rx
                            4 = Mensaje SDO recibido y parametros enviados correctamente
                            5 = Mensaje SDO recibido pero no es para este dispositivo (id diferente)
                            6 = Mensaje SDO recibido y parametros enviados incorrectamente
                            7 = Maquina de estado no esta en preoperation o superior
  Funcionamiento: Se debe llamar continuamente a esta funcion desde alguna tarea u funcion para verificar constantemente la llega de un nuevo mensaje CANopen
                  Funcionamiento interno cada vez que se llamaa esta funcion:
                  En caso de recibir correctamente un mensaje SDO CANopen, se anliza si es de escritura o lectura sobre el diccionario ya sea dato de 32 bits.
                  Si es de escritura, guarda el dato recibido en el diccionario correspondiente en el index y subindex indicado en el mensaje
                  Si es de lectura, se lee el valor del diccionario correspondiente en el index y subindex indicado en el mensaje CANopen y luego se envia por CANopen mediante mensaje SDO con la funcion CANopen_SDO_Expedited_Write()
  ========================================================================*/
uint8_t CANopen_SDO_Expedited_Read(uint16_t *index, uint8_t *subindex, uint8_t *node_id_client){
  
    uint8_t retornar=7;                                                   //Inicializo en un valor no utilizado
    if(state==CANopen_PRE_OPERATIONAL || state==CANopen_OPERATIONAL){
      if (Driver_can_readMessage(&canMsg_rec) == true) {                  //Si recibi mensaje por can
        //Verifico que el mensaje recibido sea el correcto
        if(canMsg_rec.can_id>=0x601 && canMsg_rec.can_id<=0x67F){         //Si el mensaje tiene cobid SDO Rx
            //Verifico si el mensaje tiene un ID valido con los id declarados en el arreglo CANopen_id_nodos
             uint8_t resultadoo=0;                                        //Variable para indicar si el nodo ID corresponde
             for(uint8_t i=0; i<CANopen_cantNodos_client; i++){           //Recorro el arreglo CANopen_id_nodos
                if(canMsg_rec.can_id==(0x600+CANopen_id_nodos[i])){        //Si el id del mensaje recibido corresponde el actual CANopen_id_nodos
                    CANopen_nodeid=CANopen_id_nodos[i];                   //Guardo el id al que corresponde para poder realizar todo el proceso que sigue
                    *node_id_client=CANopen_id_nodos[i]; 
                    resultadoo=1;                                         //Indico que el Nodo ID corresponde
                    break;                                                //Salgo del FOR
                }
             }
             if(resultadoo==1){                                           //Si el mensaje esta dedicado a uno de los nodos establecido en el arreglo CANopen_id_nodos
                if(canMsg_rec.data[0]==0x40){                             //Si el comando SDO es lectura
                    *index=(canMsg_rec.data[2]<<8)+canMsg_rec.data[1];    //Paso index
                    *subindex=canMsg_rec.data[3];                         //Paso subindex
                    retornar = 4;                                         //Indico que se retorna Mensaje SDO recibido y es necesario enviar parametros del diccionario
                }
  
                if(canMsg_rec.data[0]==0x23){                             //Si el comando SDO es escritura de 4 bytes
                    *index=(canMsg_rec.data[2]<<8)+canMsg_rec.data[1];    //Paso index
                    *subindex=canMsg_rec.data[3];                         //Paso subindex
                    uint32_t data=(canMsg_rec.data[7]<<24)+(canMsg_rec.data[6]<<16)+(canMsg_rec.data[5]<<8)+canMsg_rec.data[4];
                    CANopen_Write_Dictionary(*index, *subindex, data, 32, CANopen_nodeid); //Escribo diccionario de objetos
                    
                    retornar = 0;                                         //Indico que se retorna ok
                }
                
                if(canMsg_rec.data[0]==0x2B){                             //Si el comando SDO es escritura de 2 bytes
                    *index=(canMsg_rec.data[2]<<8)+canMsg_rec.data[1];    //Paso index
                    *subindex=canMsg_rec.data[3];                         //Paso subindex
                    uint16_t data=(canMsg_rec.data[5]<<8)+canMsg_rec.data[4];
                    CANopen_Write_Dictionary(*index, *subindex, data, 16, CANopen_nodeid);//Escribo diccionario de objetos
                    /*
                    Serial.print(canMsg_rec.data[4], HEX);
                        Serial.print(" ");
                        Serial.print(canMsg_rec.data[5], HEX);
                        */
                    retornar = 0;                                         //Indico que se retorna ok
                }
    
                if(canMsg_rec.data[0]==0x2F){                             //Si el comando SDO es escritura de 1 byte
                    *index=(canMsg_rec.data[2]<<8)+canMsg_rec.data[1];   //Paso index
                    *subindex=canMsg_rec.data[3];                         //Paso subindex
                    uint8_t data=canMsg_rec.data[4];
                    CANopen_Write_Dictionary(*index, *subindex, data, 8, CANopen_nodeid); //Escribo diccionario de objetos
                    
                    retornar = 0;                                     //Indico que se retorna ok
                }
            }else{
                retornar = 5;                                         //Indico que se retorna que el mensaje sdo es para otro nodo id
            }
        }else{
            retornar = 3;                                             //Indico que se retorna que no es mensaje con cobid SDO Rx
        }
  
        if(retornar==0){                                              //Si el comando recibido era de escritura y se escribio con exito, Envio mensaje de confirmacion
          uint8_t data_ff[3]={0};
          CANopen_SDO_Expedited_Write(CANopen_nodeid, 0x60, *index, *subindex,  data_ff, CANopen_SDO_mode_server, 4);
        }
  
        if(retornar==4){                                                 //Si el comando recibido era de lectura, envio dato desde el diccionario
          uint32_t dataa;                                                //Variable para guardar el dato del diccionario

          if(CANopen_Read_Dictionary(*index, *subindex, &dataa, 32, CANopen_nodeid)==true){ //Si existe el dato en el diccionario
                  uint8_t data_byte[3]={0};  
                  //En el diccionario se guarda el dato siendo primero el byte mas siginificativo. Para transmitir por CANopen es necesario transmitir primero el byte menos significativo (por eso se espeja el dato)
                  data_byte[3]=(uint8_t)(dataa & 0x0F);
                  data_byte[2]=(uint8_t)((dataa>>8) & 0x0F);
                  data_byte[1]=(uint8_t)((dataa>>16) & 0x0F);
                  data_byte[0]=(uint8_t)((dataa>>24) & 0x0F);
                  if(CANopen_SDO_Expedited_Write(CANopen_nodeid, 0x43, *index, *subindex,  data_byte, CANopen_SDO_mode_server, 4)!=0){   //Si no se envio correctamente el dato
                      retornar=6;
                  }
              }else{
                  if(CANopen_Read_Dictionary(*index,*subindex, &dataa, 16, CANopen_nodeid)==true){ //Si existe el dato en el diccionario
                      uint8_t data_byte[3]={0};  
                      //En el diccionario se guarda el dato siendo primero el byte mas siginificativo. Para transmitir por CANopen es necesario transmitir primero el byte menos significativo (por eso se espeja el dato)
                      data_byte[1]=(uint8_t)(dataa & 0x0F);
                      data_byte[0]=(uint8_t)((dataa >> 8) & 0x0F);
                      if(CANopen_SDO_Expedited_Write(CANopen_nodeid, 0x4B, *index, *subindex,  data_byte, CANopen_SDO_mode_server, 2)!=0){   //Si no se envio correctamente el dato
                          retornar=6;
                      }
                  }else{
                      if(CANopen_Read_Dictionary(*index,*subindex, &dataa, 8, CANopen_nodeid)==true){  //Si existe el dato en el diccionario
                          uint8_t data_byte[3]={0};  
                          //En el diccionario se guarda el dato siendo primero el byte mas siginificativo. Para transmitir por CANopen es necesario transmitir primero el byte menos significativo (por eso se espeja el dato)
                          data_byte[0]=(uint8_t)(dataa & 0x0F);
                          if(CANopen_SDO_Expedited_Write(CANopen_nodeid, 0x4F, *index, *subindex,  data_byte, CANopen_SDO_mode_server, 1)!=0){   //Si no se envio correctamente el dato
                              retornar=6;
                          }
                      }else{
                          retornar=6;
                      }
                  }
              }                       
          
      }
      
      return retornar;                                                //Retorno desde la funcion
    }
  } 
  return retornar;                                                   //Retorno desde la funcion
  *node_id_client=CANopen_nodeid;
}
