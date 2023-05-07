#include "encoder_manager.h"

EncoderManager::EncoderManager(int ratioGearbox) {
    _ratioGearbox = ratioGearbox;
    _count = 0;
}

double EncoderManager::getCurrentPosition() {
    return _count * (360.0 / _ratioGearbox);
}

void EncoderManager::updateCount(int direction) {
    if (!direction)
        _count++;
    else
        _count--;
}

void EncoderManager::resetCount() {
    _count = 0;
}
