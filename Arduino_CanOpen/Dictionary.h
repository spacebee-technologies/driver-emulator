/*=============================================================================
 * Author: Spacebeetech - Navegacion
 * Date: 23/02/2023
 * Board: Arduino Mega
 * Entorno de programacion: Ide arduino 1.8.19
 *
 * Descripcion: Diccionario basico para CANopen
 *===========================================================================*/

/*=====================[Variables]================================*/  

typedef struct diccionario32 {                        //Diccionario para datos de 4 bytes
        uint16_t Index;
        uint8_t  Subindex;
        uint8_t  Attribute;
        uint32_t Data;
        } diccionario32;

typedef struct diccionario16 {                        //Diccionario para datos de 2 bytes
        uint16_t Index;
        uint8_t  Subindex;
        uint8_t  Attribute;
        uint16_t Data;
        } diccionario16;

typedef struct diccionario8 {                        //Diccionario para datos de 1 byte
            uint16_t Index;
            uint8_t  Subindex;
            uint8_t  Attribute;
            uint8_t Data;
            } diccionario8;  
        
   

diccionario32 dictionary32[CANopen_cantNodos_client][17]={
    {   //DICCIONARIO PARA NODO 1
        //Index     Subindex     Attribute         Data
        { 0x6080,    0x00,           0,          0x00000000},   //Velocidad maxima del motor
        { 0x3001,    0x01,           0,          0x00000004},   //Corriente nominal del motor
        { 0x3001,    0x02,           0,          0x00000000},   //Maxima corriente admisible
        { 0x607F,    0x00,           0,          0x00000000},   //límite de velocidad en un movimiento PPM o PVM
        { 0x6085,    0x00,           0,          0x00000005},   //Determinar la deceleración del perfil de parada rápida
        { 0x60C5,    0x00,           0,          0x00000000},   //Aceleración máxima permitida
        { 0x607A,    0x00,           0,          0x00000000},   //Posición a la que se supone que debe moverse el variador 
        { 0x60FF,    0x00,           0,          0x00000000},   //Velociad a la que se supone que debe moverse el variador 
        { 0x6081,    0x00,           0,          0x00000000},   //velocidad normalmente alcanzada al final de la rampa de aceleración durante un movimiento perfilado
        { 0x6083,    0x00,           0,          0x00000000},   //Rampa de aceleración durante un movimiento
        { 0x6084,    0x00,           0,          0x00000000},   //Rampa de deceleración durante un movimiento
        { 0x6064,    0x00,           0,          0x00000000},   //Posicion actual
        { 0x30A1,    0x01,           0,          0x000F4240},   //Ganancia P para control de posicion  (uA/rad)    default: 1 A/rad
        { 0x30A1,    0x02,           0,          0x00000000},   //Ganancia I para control de posicion  [uA/rad s]        
        { 0x30A1,    0x03,           0,          0x00000000},   //Ganancia D para control de posicion  [uA s/rad] 
        { 0x30A2,    0x01,           0,          0x00000001},   //Ganancia P para control de velocidad [uA s/rad]
        { 0x30A2,    0x02,           0,          0x00000000}    //Ganancia I para control de velocidad [uA/rad]
    },
    {   //DICCIONARIO PARA NODO 2
        //Index     Subindex     Attribute         Data
        { 0x6080,    0x00,           0,          0x00000000},   //Velocidad maxima del motor
        { 0x3001,    0x01,           0,          0x00000002},   //Corriente nominal del motor
        { 0x3001,    0x02,           0,          0x00000000},   //Maxima corriente admisible
        { 0x607F,    0x00,           0,          0x00000000},   //límite de velocidad en un movimiento PPM o PVM
        { 0x6085,    0x00,           0,          0x00000005},   //Determinar la deceleración del perfil de parada rápida
        { 0x60C5,    0x00,           0,          0x00000000},   //Aceleración máxima permitida
        { 0x607A,    0x00,           0,          0x00000000},   //Posición a la que se supone que debe moverse el variador 
        { 0x60FF,    0x00,           0,          0x00000000},   //Velociad a la que se supone que debe moverse el variador 
        { 0x6081,    0x00,           0,          0x00000000},   //velocidad normalmente alcanzada al final de la rampa de aceleración durante un movimiento perfilado
        { 0x6083,    0x00,           0,          0x00000000},   //Rampa de aceleración durante un movimiento
        { 0x6084,    0x00,           0,          0x00000000},   //Rampa de deceleración durante un movimiento
        { 0x6064,    0x00,           0,          0x00000000},   //Posicion actual
        { 0x30A1,    0x01,           0,          0x000F4240},   //Ganancia P para control de posicion  (uA/rad)    default: 1 A/rad
        { 0x30A1,    0x02,           0,          0x00000000},   //Ganancia I para control de posicion  [uA/rad s]        
        { 0x30A1,    0x03,           0,          0x00000000},   //Ganancia D para control de posicion  [uA s/rad] 
        { 0x30A2,    0x01,           0,          0x00000001},   //Ganancia P para control de velocidad [uA s/rad]
        { 0x30A2,    0x02,           0,          0x00000000}    //Ganancia I para control de velocidad [uA/rad]
    },
    {   //DICCIONARIO PARA NODO 3
        //Index     Subindex     Attribute         Data
        { 0x6080,    0x00,           0,          0x00000000},   //Velocidad maxima del motor
        { 0x3001,    0x01,           0,          0x00000006},   //Corriente nominal del motor
        { 0x3001,    0x02,           0,          0x00000000},   //Maxima corriente admisible
        { 0x607F,    0x00,           0,          0x00000000},   //límite de velocidad en un movimiento PPM o PVM
        { 0x6085,    0x00,           0,          0x00000005},   //Determinar la deceleración del perfil de parada rápida
        { 0x60C5,    0x00,           0,          0x00000000},   //Aceleración máxima permitida
        { 0x607A,    0x00,           0,          0x00000000},   //Posición a la que se supone que debe moverse el variador 
        { 0x60FF,    0x00,           0,          0x00000000},   //Velociad a la que se supone que debe moverse el variador 
        { 0x6081,    0x00,           0,          0x00000000},   //velocidad normalmente alcanzada al final de la rampa de aceleración durante un movimiento perfilado
        { 0x6083,    0x00,           0,          0x00000000},   //Rampa de aceleración durante un movimiento
        { 0x6084,    0x00,           0,          0x00000000},   //Rampa de deceleración durante un movimiento
        { 0x6064,    0x00,           0,          0x00000000},   //Posicion actual
        { 0x30A1,    0x01,           0,          0x000F4240},   //Ganancia P para control de posicion  (uA/rad)    default: 1 A/rad
        { 0x30A1,    0x02,           0,          0x00000000},   //Ganancia I para control de posicion  [uA/rad s]        
        { 0x30A1,    0x03,           0,          0x00000000},   //Ganancia D para control de posicion  [uA s/rad] 
        { 0x30A2,    0x01,           0,          0x00000001},   //Ganancia P para control de velocidad [uA s/rad]
        { 0x30A2,    0x02,           0,          0x00000000}    //Ganancia I para control de velocidad [uA/rad]
    },
    {   //DICCIONARIO PARA NODO 4
        //Index     Subindex     Attribute         Data
        { 0x6080,    0x00,           0,          0x00000000},   //Velocidad maxima del motor
        { 0x3001,    0x01,           0,          0x00000000},   //Corriente nominal del motor
        { 0x3001,    0x02,           0,          0x00000000},   //Maxima corriente admisible
        { 0x607F,    0x00,           0,          0x00000000},   //límite de velocidad en un movimiento PPM o PVM
        { 0x6085,    0x00,           0,          0x00000005},   //Determinar la deceleración del perfil de parada rápida
        { 0x60C5,    0x00,           0,          0x00000000},   //Aceleración máxima permitida
        { 0x607A,    0x00,           0,          0x00000000},   //Posición a la que se supone que debe moverse el variador 
        { 0x60FF,    0x00,           0,          0x00000000},   //Velociad a la que se supone que debe moverse el variador 
        { 0x6081,    0x00,           0,          0x00000000},   //velocidad normalmente alcanzada al final de la rampa de aceleración durante un movimiento perfilado
        { 0x6083,    0x00,           0,          0x00000000},   //Rampa de aceleración durante un movimiento
        { 0x6084,    0x00,           0,          0x00000000},   //Rampa de deceleración durante un movimiento
        { 0x6064,    0x00,           0,          0x00000000},   //Posicion actual
        { 0x30A1,    0x01,           0,          0x000F4240},   //Ganancia P para control de posicion  (uA/rad)    default: 1 A/rad
        { 0x30A1,    0x02,           0,          0x00000000},   //Ganancia I para control de posicion  [uA/rad s]        
        { 0x30A1,    0x03,           0,          0x00000000},   //Ganancia D para control de posicion  [uA s/rad] 
        { 0x30A2,    0x01,           0,          0x00000001},   //Ganancia P para control de velocidad [uA s/rad]
        { 0x30A2,    0x02,           0,          0x00000000}    //Ganancia I para control de velocidad [uA/rad]
    },
    {   //DICCIONARIO PARA NODO 5
        //Index     Subindex     Attribute         Data
        { 0x6080,    0x00,           0,          0x00000000},   //Velocidad maxima del motor
        { 0x3001,    0x01,           0,          0x00000009},   //Corriente nominal del motor
        { 0x3001,    0x02,           0,          0x00000000},   //Maxima corriente admisible
        { 0x607F,    0x00,           0,          0x00000000},   //límite de velocidad en un movimiento PPM o PVM
        { 0x6085,    0x00,           0,          0x00000005},   //Determinar la deceleración del perfil de parada rápida
        { 0x60C5,    0x00,           0,          0x00000000},   //Aceleración máxima permitida
        { 0x607A,    0x00,           0,          0x00000000},   //Posición a la que se supone que debe moverse el variador 
        { 0x60FF,    0x00,           0,          0x00000000},   //Velociad a la que se supone que debe moverse el variador 
        { 0x6081,    0x00,           0,          0x00000000},   //velocidad normalmente alcanzada al final de la rampa de aceleración durante un movimiento perfilado
        { 0x6083,    0x00,           0,          0x00000000},   //Rampa de aceleración durante un movimiento
        { 0x6084,    0x00,           0,          0x00000000},   //Rampa de deceleración durante un movimiento
        { 0x6064,    0x00,           0,          0x00000000},   //Posicion actual
        { 0x30A1,    0x01,           0,          0x000F4240},   //Ganancia P para control de posicion  (uA/rad)    default: 1 A/rad
        { 0x30A1,    0x02,           0,          0x00000000},   //Ganancia I para control de posicion  [uA/rad s]        
        { 0x30A1,    0x03,           0,          0x00000000},   //Ganancia D para control de posicion  [uA s/rad] 
        { 0x30A2,    0x01,           0,          0x00000001},   //Ganancia P para control de velocidad [uA s/rad]
        { 0x30A2,    0x02,           0,          0x00000000}    //Ganancia I para control de velocidad [uA/rad]
    },
    {   //DICCIONARIO PARA NODO 6
        //Index     Subindex     Attribute         Data
        { 0x6080,    0x00,           0,          0x00000000},   //Velocidad maxima del motor
        { 0x3001,    0x01,           0,          0x00000000},   //Corriente nominal del motor
        { 0x3001,    0x02,           0,          0x00000000},   //Maxima corriente admisible
        { 0x607F,    0x00,           0,          0x00000000},   //límite de velocidad en un movimiento PPM o PVM
        { 0x6085,    0x00,           0,          0x00000005},   //Determinar la deceleración del perfil de parada rápida
        { 0x60C5,    0x00,           0,          0x00000000},   //Aceleración máxima permitida
        { 0x607A,    0x00,           0,          0x00000000},   //Posición a la que se supone que debe moverse el variador 
        { 0x60FF,    0x00,           0,          0x00000000},   //Velociad a la que se supone que debe moverse el variador 
        { 0x6081,    0x00,           0,          0x00000000},   //velocidad normalmente alcanzada al final de la rampa de aceleración durante un movimiento perfilado
        { 0x6083,    0x00,           0,          0x00000000},   //Rampa de aceleración durante un movimiento
        { 0x6084,    0x00,           0,          0x00000000},   //Rampa de deceleración durante un movimiento
        { 0x6064,    0x00,           0,          0x00000000},   //Posicion actual
        { 0x30A1,    0x01,           0,          0x000F4240},   //Ganancia P para control de posicion  (uA/rad)    default: 1 A/rad
        { 0x30A1,    0x02,           0,          0x00000000},   //Ganancia I para control de posicion  [uA/rad s]        
        { 0x30A1,    0x03,           0,          0x00000000},   //Ganancia D para control de posicion  [uA s/rad] 
        { 0x30A2,    0x01,           0,          0x00000001},   //Ganancia P para control de velocidad [uA s/rad]
        { 0x30A2,    0x02,           0,          0x00000000}    //Ganancia I para control de velocidad [uA/rad]
    }
}; 

diccionario16 dictionary16[CANopen_cantNodos_client][2]={
    {   //DICCIONARIO PARA NODO 1
        //Index     Subindex     Attribute         Data
        { 0x6040,    0x00,           0,          0x0000},       //Controlword    
        { 0x0000,    0x00,           0,          0x0000}
    },
    {   //DICCIONARIO PARA NODO 2
        //Index     Subindex     Attribute         Data
        { 0x6040,    0x00,           0,          0x0000},       //Controlword   
        { 0x0000,    0x00,           0,          0x0000}
    },
    {   //DICCIONARIO PARA NODO 3
        //Index     Subindex     Attribute         Data
        { 0x6040,    0x00,           0,          0x0000},       //Controlword     
        { 0x0000,    0x00,           0,          0x0000}
    },
    {   //DICCIONARIO PARA NODO 4
        //Index     Subindex     Attribute         Data
        { 0x6040,    0x00,           0,          0x0000},       //Controlword     
        { 0x0000,    0x00,           0,          0x0000}
    },
    {   //DICCIONARIO PARA NODO 5
        //Index     Subindex     Attribute         Data
        { 0x6040,    0x00,           0,          0x0000},       //Controlword     
        { 0x0000,    0x00,           0,          0x0000}
    },
    {   //DICCIONARIO PARA NODO 6
        //Index     Subindex     Attribute         Data
        { 0x6040,    0x00,           0,          0x0000},       //Controlword     
        { 0x0000,    0x00,           0,          0x0000}
    }
}; 

diccionario8 dictionary8[CANopen_cantNodos_client][2]={
    {   //DICCIONARIO PARA NODO 1
        //Index     Subindex     Attribute         Data
        { 0x6060,    0x00,           0,            0x00},           //Modo de control    
        { 0x0000,    0x00,           0,            0x00}
    },
    {   //DICCIONARIO PARA NODO 2
        //Index     Subindex     Attribute         Data
        { 0x6060,    0x00,           0,            0x00},           //Modo de control    
        { 0x0000,    0x00,           0,            0x00}
    },
    {   //DICCIONARIO PARA NODO 3
        //Index     Subindex     Attribute         Data
        { 0x6060,    0x00,           0,            0x00},           //Modo de control    
        { 0x0000,    0x00,           0,            0x00}
    },
    {   //DICCIONARIO PARA NODO 4
        //Index     Subindex     Attribute         Data
        { 0x6060,    0x00,           0,            0x00},           //Modo de control    
        { 0x0000,    0x00,           0,            0x00}
    },
    {   //DICCIONARIO PARA NODO 5
        //Index     Subindex     Attribute         Data
        { 0x6060,    0x00,           0,            0x00},           //Modo de control    
        { 0x0000,    0x00,           0,            0x00}
    },
    {   //DICCIONARIO PARA NODO 6
        //Index     Subindex     Attribute         Data
        { 0x6060,    0x00,           0,            0x00},           //Modo de control    
        { 0x0000,    0x00,           0,            0x00}
    }
}; 
