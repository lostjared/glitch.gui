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

class Knob {
public:
    Knob() = default;
    
    void setRandom(bool r) {
        random_value = r;
    }

    void initValues(double v, double s, double min_, double max_) {
        value_ = v;
        speed = s;
        min = min_;
        max = max_;
    }

    void initValues(double v, double s, double min_, double max_, int d) {
        value_ =v;
        speed = s;
        min = min_;
        max = max_;
        dir = d;
    }

    void setDirection(int d) {
        dir = d;
    }

    void turnRight(double x) {
        value_ += x;
    }
    void turnLeft(double x) {
        value_ -= x;
    }
    void setSpeed(double s) {
        speed = s;
    }

    double nextValue() {
        double s = speed;
        if(random_value) 
            s = rand()%10 * 0.01f;

        if(dir == 1) {
            value_ += s;
            if(value_ >= max) {
                value_ = max;
                dir = 0;
            }       
        } else {
            value_ -= s;
            if(value_ <= min) {
                value_ = min;
                dir = 1;
            }
        }
        return value_;
    }
    double value() { return value_; }

private:
    double value_ = 1.0, speed = 0.1, min = 0.1, max = 2.0;
    int dir = 1;
    bool random_value = false;
};

#endif