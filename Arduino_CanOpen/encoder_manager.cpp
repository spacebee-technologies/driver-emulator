#include "encoder_manager.h"

EncoderManager::EncoderManager(int ratioGearbox) {
    _ratioGearbox = ratioGearbox;
    _count = 0;
}

/**
 * @brief Get the absolute position in degrees relative to the physical initial
 *        position
 *
 * @return double Absolute position in degrees
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
    if (!direction)
        _count++;
    else
        _count--;
}

/**
 * @brief Reset count to zero
 */
void EncoderManager::resetCount() {
    _count = 0;
}
