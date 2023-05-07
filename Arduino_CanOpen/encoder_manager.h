#ifndef ENCODER_MANAGER_H_
#define ENCODER_MANAGER_H_

class EncoderManager {
    private:
        int _count;
        int _ratioGearbox;

    public:
        EncoderManager(int ratioGearbox);
        double getCurrentPosition();
        void updateCount(int direction);
        void resetCount();
};

#endif  // ENCODER_MANAGER_H_
