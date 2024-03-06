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

template<typename T>
class KnobT {
public:
    KnobT() = default;
    void initValues(T v, T s, T min_, T max_) {
        value_ = v;
        speed = s;
        min = min_;
        max = max_;
    }
    void initValues(T v, T s, T min_, T max_, T d) {
        value_ =v;
        speed = s;
        min = min_;
        max = max_;
        dir = d;
    }
    void setDirection(int d) {
        dir = d;
    }
    void turnRight(T x) {
        value_ += x;
    }
    void turnLeft(T x) {
        value_ -= x;
    }
    void setSpeed(T s) {
        speed = s;
    }
    T nextValue() {
        T s = speed;

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
    T value() { return value_; }
protected:
    T value_ = 1.0, speed = 0.1, min = 0.1, max = 2.0;
    int dir = 1;
};

using Knob = KnobT<double>;

class KnobRandom : public KnobT<double> {
public:
    KnobRandom() = default;
    
    void setRandom(bool r) {
        random_value = r;
    }
    
    double nextValue() {
        double s = speed;
        if(random_value) {
            s = (rand()%10 * 0.1);
        }
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
private:
    bool random_value = false;
};

template<size_t N>
class New_MatrixCollection {
public:
    std::vector<cv::Mat> frames;
    New_MatrixCollection() {
        frames.reserve(N);
    }
    void shiftFrames(const cv::Mat& newFrame) {
        if (frames.size() >= N) {
            frames.erase(frames.begin());
        }
        frames.push_back(newFrame.clone());
    }
    void clear() {
        if(!frames.empty())
            frames.erase(frames.begin(), frames.end());
    }
    size_t size() const {
        return frames.size();
    }
    size_t capacity() const { return N; }
    const cv::Mat& operator[](size_t index) const {
        return frames[index];
    }
};


#endif