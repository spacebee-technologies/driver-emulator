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

#include "motor_controller.h"

class Epos_emulator
{
    private: 
        MotorController *_controller;
        uint8_t _nodeid;
        uint8_t _numeroDiccionario;
        int _nBits;
        int _CPT;
        double _error;       // degrees
        double _setpoint;    // degrees
        uint8_t _set_cero;

    public: 
        Epos_emulator(uint8_t Can_nodeid, int nBits, int CPT, MotorController *controller, uint8_t numeroDiccionario);
        void init();
        void Execute();
        void interruptZ();
        void obtener_setpoint();
};

void Epos_CanOpen_Consult(void);
void Epos_Emulator_init(void);

#endif
