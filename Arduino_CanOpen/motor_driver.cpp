#include "motor_driver.h"

#include <Arduino.h>

#define DEFAULT_PWM_MAX 20
#define DEFAULT_PWM_MIN 5

MotorDriver::MotorDriver(uint8_t enable, uint8_t in1, uint8_t in2) {
    _enable = enable;
    _in1 = in1;
    _in2 = in2;

    _pwmMax = DEFAULT_PWM_MAX;
    _pwmMin = DEFAULT_PWM_MIN;

    pinMode(_enable, OUTPUT);
    pinMode(_in1, OUTPUT);
    pinMode(_in2, OUTPUT);
    analogWrite(_enable, 0);
    digitalWrite(_in1, HIGH);
    digitalWrite(_in2, LOW);
}

int MotorDriver::updateRotation(double error) {
    int direction = 0;
    if (error >= 0) {
        direction = 0;
        digitalWrite(_in1, LOW);
        digitalWrite(_in2, HIGH);
    } else {
        direction = 1;
        digitalWrite(_in1, HIGH);
        digitalWrite(_in2, LOW);
    }
    return direction;
}

void MotorDriver::updatePwm(int pwm) {
    if (pwm > _pwmMax) { pwm = _pwmMax; }
    if (pwm < _pwmMin) { pwm = _pwmMin; }
    analogWrite(_enable, pwm);
}
