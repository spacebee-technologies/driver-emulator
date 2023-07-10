#include "motor_controller.h"

#include <Arduino.h>

#define DEFAULT_PROPORTIONAL_COEFFICIENT 1
#define DEFAULT_ERROR_THRESHOLD 0.5

MotorController::MotorController(EncoderManager *encoder, MotorDriver *motorDriver) {
    _encoder = encoder;
    _motorDriver = motorDriver;

    _rotDirection = 0;
    _k = DEFAULT_PROPORTIONAL_COEFFICIENT;
    _errorThreshold = DEFAULT_ERROR_THRESHOLD;
}

/**
 * @brief Compute and update motor driver parameters (PWM and direction)
 *
 * @param targetPosition Expected position in degrees in the [0, 360] range
 */
void MotorController::update(double targetPosition) {
    double error = getError(targetPosition);
    _rotDirection = _motorDriver->computeMotorDirection(error);
    int pwm = 0;
    if (abs(error) > _errorThreshold) {
        pwm = abs(error) * _k;
    }
    _motorDriver->updatePwm(pwm);
}

/**
 * @brief Reset encoder tick count to zero
 */
void MotorController::resetEncoderCount() {
    _encoder->resetCount();
}

/**
 * @brief Interrupt handler to increment or decrement encoder tick count
 */
void MotorController::interruptZ() {
    _encoder->updateCount(_rotDirection);
}

/**
 * @brief Compute and get the direct or the complementary errors
 *
 * @param targetPosition Target position in the [0, 360] degrees range
 * @return double Computed error
 */
double MotorController::getError(double targetPosition) {
    double e1 = targetPosition - _encoder->getCurrentPosition();
    double e2 = targetPosition + 360 - _encoder->getCurrentPosition();
    double e3 = targetPosition - 360 - _encoder->getCurrentPosition();
    if ((abs(e1) <= abs(e2)) && (abs(e1) <= abs(e3)))
        return e1;
    if ((abs(e2) <= abs(e1)) && (abs(e2) <= abs(e3)))
        return e2;
    return e3;
}
