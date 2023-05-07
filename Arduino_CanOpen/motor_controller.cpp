#include "motor_controller.h"

#include <Arduino.h>

#define DEFAULT_PROPORTIONAL_COEFFICIENT 1
#define DEFAULT_ERROR_THRESHOLD 2

MotorController::MotorController(EncoderManager *encoder, MotorDriver *motorDriver) {
    _encoder = encoder;
    _motorDriver = motorDriver;

    _rotDirection = 0;
    _k = DEFAULT_PROPORTIONAL_COEFFICIENT;
    _errorThreshold = DEFAULT_ERROR_THRESHOLD;
}

void MotorController::update(double targetPosition) {
    double error = targetPosition - _encoder->getCurrentPosition();
    _rotDirection = _motorDriver->updateRotation(error);
    int pwm = 0;
    if (abs(error) > _errorThreshold) {
        pwm = abs(error) * _k;
    }
    _motorDriver->updatePwm(pwm);
}

void MotorController::resetEncoderCount() {
    _encoder->resetCount();
}

void MotorController::interruptZ() {
    _encoder->updateCount(_rotDirection);
}
