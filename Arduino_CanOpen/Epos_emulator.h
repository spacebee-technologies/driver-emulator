/*=============================================================================
 * Author: Spacebeetech - Navegacion
 * Date: 23/02/2023
 * Board: Arduino Mega
 * Entorno de programacion: Ide arduino 1.8.19
 *
 * Descripcion: Libreria Emulador de EPOS4
 *===========================================================================*/

/*==================[Definiciones]================================*/
#ifndef Epos_emulator_H
#define Epos_emulator_H

/*=====================[ Inclusiones ]============================*/
#include <Arduino.h>

class Epos_emulator
{
    private: 
        uint8_t _En;
        uint8_t _in1;
        uint8_t _in2;
        uint8_t _nodeid;
        uint8_t _numeroDiccionario;
        uint8_t _Z_PIN;
        int _nBits;
        int _CPT;
        int _ratioGB;
        double _currentPos;  // degrees
        double _threshold;   // degrees
        double _error;       // degrees
        double _setpoint;    // degrees
        bool _rotDirection;  // CW
        volatile uint32_t _count;
        int _PWM;
        uint8_t _set_cero;
        
    public: 
        Epos_emulator(uint8_t Can_nodeid, uint8_t Z_PIN, int nBits, int CPT, int ratioGB, uint8_t En, uint8_t in1, uint8_t in2, uint8_t numeroDiccionario);
        void init();
        void Execute();
        void interruptZ();
        void obtener_setpoint();
};

void Epos_CanOpen_Consult(void);
void Epos_Emulator_init(void);

#endif
