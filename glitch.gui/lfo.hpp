#ifndef _LFO_H__P
#define _LFO_H__P

#include<cmath>
#include<iostream>

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
    KnobT() : value_{}, speed{}, min_{}, max_{} {}
    KnobT(const KnobT<T> &type) : value_{type.value_}, speed{type.speed}, min_{type.min}, max_{type.max} {}
    KnobT(KnobT<T> &&type) : value_{type.value_}, speed{type.speed}, min_{type.min}, max_{type.max} {}
    
    KnobT(T v, T s, T min_x, T max_x) {
        initvalues(v, s, min_x, max_x);
    }
    
    KnobT(T v, T s, T min_x, T max_x, int d) {
        initValues(v, s, min_x, max_x, d);
    }
    
    KnobT<T> operator=(const KnobT<T> &type) {
        value_ = type.value_;
        speed = type.speed;
        min_ = type.min_;
        max_ = type.max_;
        return *this;
    }

    KnobT<T> operator=(KnobT<T> &&type) {
        value_ = type.value_;
        speed = type.speed;
        min_ = type.min_;
        max_ = type.max_;
        return *this;
    }

    void initValues(T v, T s, T min_x, T max_x) {
        value_ = v;
        speed = s;
        min_ = min_x;
        max_ = max_x;
    }
    void initValues(T v, T s, T min_x, T max_x, int d) {
        value_ =v;
        speed = s;
        min_ = min_x;
        max_ = max_x;
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
            if(value_ >= max_) {
                value_ = max_;
                dir = 0;
            }       
        } else {
            value_ -= s;
            if(value_ <= min_) { 
                value_ = min_;
                dir = 1;
            }
        }
        return value_;
    }
    T value() { return value_; }
protected:
    T value_, speed, min_, max_;
    int dir = 1;
};

using Knob = KnobT<double>;

class KnobRandom : public KnobT<double> {
public:
    KnobRandom() : gen{rd()}, dist(0, 10) {}
    void setRandom(bool r) {
        random_value = r;
    } 
    double nextValue() {
        double s = speed;
        if(random_value) {
            s = (dist(gen) * 0.1);
        }
        if(dir == 1) {
            value_ += s;
            if(value_ >= max_) {
                value_ = max_;
                dir = 0;
            }       
        } else {
            value_ -= s;
            if(value_ <= min_) {
                value_ = min_;
                dir = 1;
            }
        }
        return value_; 
    }
private:
    bool random_value = false;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;
};

class KnobGrow : public KnobT<double> {
public:
    KnobGrow() : grow_{} {}
    void setMaxGrow(double grow) {
        grow_ = grow;
        start_max = max_;
    }

    double nextValue() {
        double s = speed;
        if(dir == 1) {
            value_ += s;
            if(value_ >= max_) {
                value_ = max_;
                dir = 0;
                if(g_max == 1) {
                    max_ += s;
                    if(max_ >= grow_) {
                        g_max = 0;
                    }
                } else {
                    max_ -= s;
                    if(max_ <= start_max) {
                        max_ = start_max;
                        g_max = 1;
                    }
                }
            }
        } else {
            value_ -= s;
            if(value_ <= min_ || value_ <= 0) {
                value_ = min_;
                dir = 1;
            }
        }
        return value_;
    }
private:
    double grow_;
    double start_max;
    int g_max = 1;
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