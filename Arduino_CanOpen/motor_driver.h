#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

#include <stdint.h>

class MotorDriver {
    private:
        uint8_t _enable;
        uint8_t _in1;
        uint8_t _in2;
        int _pwmMax;
        int _pwmMin;

    public:
        MotorDriver(uint8_t enable, uint8_t in1, uint8_t in2);
        int computeMotorDirection(double error);
        void updatePwm(int pwm);
};

#endif  // MOTOR_DRIVER_H_
