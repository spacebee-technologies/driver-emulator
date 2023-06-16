#ifndef MOTOR_CONTROLLER_H_
#define MOTOR_CONTROLLER_H_

#include "encoder_manager.h"
#include "motor_driver.h"

class MotorController {
    private:
        double getError(double targetPosition);

        EncoderManager *_encoder;
        MotorDriver *_motorDriver;
        int _rotDirection;
        double _k;  // Proportional coefficient for control
        double _errorThreshold;

    public:
        MotorController(EncoderManager *encoder, MotorDriver *motorDriver);
        void update(double targetPosition);
        void resetEncoderCount();
        void interruptZ();
};

#endif  // MOTOR_CONTROLLER_H_
