#ifndef _LFO_H__P
#define _LFO_H__P

#include <cmath>

class LFO {
public:
    LFO() = default;

    LFO(float frequency, float sampleRate) : mFrequency(frequency), mSampleRate(sampleRate) {
        updateIncrement();
    }

    void setSample(float s) {
        mSampleRate = s;
    }

    void setFrequency(float frequency) {
        mFrequency = frequency;
        updateIncrement();
    }
    float nextSample() {
        float sample = sinf(mPhase);
        mPhase += mPhaseIncrement;
        if (mPhase >= 2.0f * M_PI) {
            mPhase -= 2.0f * M_PI;
        }
        return sample;
    }

private:
    float mFrequency;
    float mSampleRate;
    float mPhase = 0.0f;
    float mPhaseIncrement;

    void updateIncrement() {
        mPhaseIncrement = (2.0f * M_PI * mFrequency) / mSampleRate;
    }
};

#endif