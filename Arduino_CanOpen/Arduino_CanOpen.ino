/*=============================================================================
 * Author: Spacebeetech - Navegacion
 * Date: 23/02/2023
 * Board: Arduino Mega
 * Entorno de programacion: Ide arduino 1.8.19
 *
 * Descripcion: Emulador EPOS4
 *              Cambiar nodo ID de CanOpen en "CanOpen_Arduino.h"   
 *              Cambiar diccionario de CanOpen en "Dictionary.h"
 *===========================================================================*/

#include "CanOpen_Arduino.h"

#include <stdint.h>

#include "encoder_manager.h"
#include "motor_driver.h"
#include "motor_controller.h"
#include "Epos_emulator.h"
#include "Define.h"

// Motor 1
EncoderManager encoder1(M1_ratioGB);
MotorDriver motorDriver1(M1_En, M1_in1, M1_in2);
MotorController controller1(&encoder1, &motorDriver1);
Epos_emulator Epos1(Can_nodeid_client1, M1_nBits, M1_CPT, &controller1, 0);

// Motor 2
EncoderManager encoder2(M2_ratioGB);
MotorDriver motorDriver2(M2_En, M2_in1, M2_in2);
MotorController controller2(&encoder2, &motorDriver2);
Epos_emulator Epos2(Can_nodeid_client2, M2_nBits, M2_CPT, &controller2, 1);

// Motor 3
EncoderManager encoder3(M3_ratioGB);
MotorDriver motorDriver3(M3_En, M3_in1, M3_in2);
MotorController controller3(&encoder3, &motorDriver3);
Epos_emulator Epos3(Can_nodeid_client3, M3_nBits, M3_CPT, &controller3, 2);

// Motor 4
EncoderManager encoder4(M4_ratioGB);
MotorDriver motorDriver4(M4_En, M4_in1, M4_in2);
MotorController controller4(&encoder4, &motorDriver4);
Epos_emulator Epos4(Can_nodeid_client4, M4_nBits, M4_CPT, &controller4, 3);

// Motor 5
EncoderManager encoder5(M5_ratioGB);
MotorDriver motorDriver5(M5_En, M5_in1, M5_in2);
MotorController controller5(&encoder5, &motorDriver5);
Epos_emulator Epos5(Can_nodeid_client5, M5_nBits, M5_CPT, &controller5, 4);

// Motor 6
EncoderManager encoder6(M6_ratioGB);
MotorDriver motorDriver6(M6_En, M6_in1, M6_in2);
MotorController controller6(&encoder6, &motorDriver6);
Epos_emulator Epos6(Can_nodeid_client6, M6_nBits, M6_CPT, &controller6, 5);

double setpoints[] = {275, 91,
                      280, 92,
                      285, 93,
                      290, 94,
                      295, 95,
                      300, 96,
                      305, 97,
                      310, 98,
                      315, 99,
                      320, 100,
                      325, 101,
                      330, 102,
                      335, 103,
                      340, 104,
                      345, 105,
                      350, 106,
                      355, 107,
                      360, 108,
                      0, 109,
                      5, 110,
                      10, 111,
                      15, 112,
                      20, 113,
                      25, 114,
                      30, 115,
                      35, 116,
                      40, 117,
                      45, 118,
                      50, 119,
                      55, 120,
                      60, 125,
                      65, 130,
                      66, 135,
                      67, 140,
                      68, 145,
                      69, 150,
                      70, 155,
                      71, 160,
                      72, 165,
                      73, 170,
                      74, 175,
                      75, 180,
                      76, 185,
                      77, 190,
                      78, 195,
                      79, 200,
                      80, 205,
                      81, 210,
                      82, 215,
                      83, 220,
                      84, 225,
                      85, 230,
                      86, 235,
                      87, 240,
                      88, 245,
                      89, 250,
                      90, 255,
                      91, 260,
                      92, 265,
                      93, 270,
                      94, 275,
                      95, 280,
                      96, 285,
                      97, 290,
                      98, 295,
                      99, 300,
                      100, 305,
                      101, 310,
                      102, 315,
                      103, 320,
                      104, 325,
                      105, 330,
                      106, 335,
                      107, 340,
                      108, 345,
                      109, 350,
                      110, 355,
                      111, 360,
                      112, 0,
                      113, 5,
                      114, 10,
                      115, 15,
                      116, 20,
                      117, 25,
                      118, 30,
                      119, 35,
                      120, 40,
                      125, 45,
                      130, 50,
                      135, 55,
                      140, 60,
                      145, 65,
                      150, 66,
                      155, 67,
                      160, 68,
                      165, 69,
                      170, 70,
                      175, 71,
                      180, 72,
                      185, 73,
                      190, 74,
                      195, 75,
                      200, 76,
                      205, 77,
                      210, 78,
                      215, 79,
                      220, 80,
                      225, 81,
                      230, 82,
                      235, 83,
                      240, 84,
                      245, 85,
                      250, 86,
                      255, 87,
                      260, 88,
                      265, 89,
                      270, 90};
double setpoint1;
double setpoint2;
double t0;
double t1;
int i;

void setup() {

  Serial.begin(115200);

  //Inicializo Emulador Epos
  Epos_Emulator_init();   //Si o si se debe llamar antes de CANope_init
  
  //Inicializo CANopen
  uint8_t resultado=CANopen_init();
  if (resultado == 0){ Serial.println("CANopen was initialized and is in pre-operational mode"); }
  if (resultado == 1){ Serial.println("Error al mandar mensaje Boot_Up");  CANopen_STOP(); }
 
  //Configuro interrupciones del encoder (no logre que se configuren dentro de la clase)
  attachInterrupt(digitalPinToInterrupt(M1_Z_PIN), interrupt_E1, RISING);
  attachInterrupt(digitalPinToInterrupt(M2_Z_PIN), interrupt_E2, RISING);
  attachInterrupt(digitalPinToInterrupt(M3_Z_PIN), interrupt_E3, RISING);
  attachInterrupt(digitalPinToInterrupt(M4_Z_PIN), interrupt_E4, RISING);
  attachInterrupt(digitalPinToInterrupt(M5_Z_PIN), interrupt_E5, RISING);
  attachInterrupt(digitalPinToInterrupt(M6_Z_PIN), interrupt_E6, RISING);
  
  //Configuro interupcion que genera el mudolo can cuando recibe mensaje
  pinMode(ModuloCAN_INTERRUPT_PIN, INPUT_PULLUP);
  PCICR |= (1 << PCIE1);     // Habilita la interrupción para el grupo PCINT[23:16] (PCMSK2)
  PCMSK1 |= (1 << PCINT10);   // Habilita la interrupción para el pin digital 14 (PCINT20)
  sei();                     // Habilita las interrupciones globales

  controller1.resetEncoderCount();
  controller2.resetEncoderCount();
  controller3.resetEncoderCount();
  controller4.resetEncoderCount();
  controller5.resetEncoderCount();
  controller6.resetEncoderCount();

  t0 = millis();
  t1 = millis();
  i = 0;
}


ISR(PCINT1_vect) {
  sei();
  if(digitalRead(ModuloCAN_INTERRUPT_PIN)==LOW){  //Si la interupcion fue por flanco de bajada
    Epos_CanOpen_Consult();     //Consulta si hay mensajes nuevos disponibles de can y los procesa segun sea lectura o escritura de diccionario
    
  }
}

void loop() {
  t1 = millis();
  if (t1 - t0 > 100) {
    setpoint1 = setpoints[2*i];
    setpoint2 = setpoints[2*i+1];
    Serial.print("i = "); Serial.print(i); Serial.print(" - setpoint1 = "); Serial.print(setpoint1); Serial.print(" - setpoint2 = "); Serial.println(setpoint2);
    i++;
    if (i >= sizeof(setpoints)/sizeof(double)/2) { i = 0; }
    t0 = t1;
  }
  Epos1.Execute(setpoint1);            //Ejecuta el proceso de la emulacion del EPOS1. Busca en su OD el modo de operacion, habilitacion, setpoint, etc y ejecuta el control del motor.
  Epos2.Execute(setpoint2);            //Idem
  Epos3.Execute(setpoint1);            //Idem
  Epos4.Execute(setpoint2);            //Idem
  Epos5.Execute(setpoint1);            //Idem
  Epos6.Execute(setpoint2);            //Idem
}

void interrupt_E1(){  Epos1.interruptZ(); }
void interrupt_E2(){  Epos2.interruptZ(); }
void interrupt_E3(){  Epos3.interruptZ(); }
void interrupt_E4(){  Epos4.interruptZ(); }
void interrupt_E5(){  Epos5.interruptZ(); }
void interrupt_E6(){  Epos6.interruptZ(); }
