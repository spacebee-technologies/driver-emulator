#include "encoder_manager.h"

EncoderManager::EncoderManager(int ratioGearbox) {
    _ratioGearbox = ratioGearbox;
    _count = 0;
}

/**
 * @brief Get the absolute position of the encoder in the [0, 360] degrees
 *        range, where the value 0 corresponds to the physical initial position
 *
 * @return double Absolute position in degrees in the [0, 360] range
 */
double EncoderManager::getCurrentPosition() {
    return _count * (360.0 / _ratioGearbox);
}

/**
 * @brief Increment or decrement the ticks count
 *
 * @param direction 0 to increment and any other value to decrement
 */
void EncoderManager::updateCount(int direction) {
    if (!direction) {
        _count++;
    } else {
        _count--;
    }
    if (_count > _ratioGearbox) { _count = 0; }
    if (_count < 0) { _count = _ratioGearbox; }
}

/**
 * @brief Reset count to zero
 */
void EncoderManager::resetCount() {
    _count = 0;
}
