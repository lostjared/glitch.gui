/* some of the later filters in this file where written with the help of Ai */

#ifndef _LAYER_FILTER_H_
#define _LAYER_FILTER_H_

#include"acidcam/ac.h"
#include "../new_filter.hpp"
#include "../layer.hpp"
#include "../lfo.hpp"
#include "../cv_fractal.hpp"
#include<random>
#include<chrono>
#include<cmath>

class Layer_AlphaBlend25 : public FilterFunc {
public:
    void init() override {
        
    }
    void setLayer(Layer *layer) {
        layer_ = layer;
    }
    void proc(cv::Mat &frame) override {
        cv::Mat layer1;
        if(layer_->hasNext()) {
            if(layer_->read(layer1)) {
                cv::Mat resized;
                cv::resize(layer1, resized, frame.size());
                for(int z = 0; z < frame.rows; ++z) {
                    for(int i = 0; i < frame.cols; ++i) {
                        cv::Vec3b &pix1 = frame.at<cv::Vec3b>(z, i);
                        cv::Vec3b pix2;
                        setvec(pix2,resized.at<cv::Vec3b>(z, i));
                        for(int q = 0; q < 3; ++q) {
                            pix1[q] = ac::wrap_cast((0.75 * pix1[q]) + (0.25 * pix2[q]));
                        }
                    }
                }
            }
        }
    }
    void clear() override {
        
    }
    ~Layer_AlphaBlend25() {
        
    }
private:
    Layer *layer_;
    
};

class Layer_AlphaBlend50 : public FilterFunc {
public:
    void init() override {
        
    }
    void setLayer(Layer *layer) {
        layer_ = layer;
    }
    void proc(cv::Mat &frame) override {
        cv::Mat layer1;
        if(layer_->hasNext()) {
            if(layer_->read(layer1)) {
                cv::Mat resized;
                cv::resize(layer1, resized, frame.size());
                for(int z = 0; z < frame.rows; ++z) {
                    for(int i = 0; i < frame.cols; ++i) {
                        cv::Vec3b &pix1 = frame.at<cv::Vec3b>(z, i);
                        cv::Vec3b pix2;
                        setvec(pix2,resized.at<cv::Vec3b>(z, i));
                        for(int q = 0; q < 3; ++q) {
                            pix1[q] = ac::wrap_cast((0.5 * pix1[q]) + (0.5 * pix2[q]));
                        }
                    }
                }
            }
        }
    }
    void clear() override {
        
    }
    ~Layer_AlphaBlend50() {
        
    }
private:
    Layer *layer_;
};

class Layer_AlphaBlend75 : public FilterFunc {
public:
    void init() override {
        
    }
    void setLayer(Layer *layer) {
        layer_ = layer;
    }
    void proc(cv::Mat &frame) override {
        cv::Mat layer1;
        if(layer_->hasNext()) {
            if(layer_->read(layer1)) {
                cv::Mat resized;
                cv::resize(layer1, resized, frame.size());
                for(int z = 0; z < frame.rows; ++z) {
                    for(int i = 0; i < frame.cols; ++i) {
                        cv::Vec3b &pix1 = frame.at<cv::Vec3b>(z, i);
                        cv::Vec3b pix2;
                        setvec(pix2,resized.at<cv::Vec3b>(z, i));
                        for(int q = 0; q < 3; ++q) {
                            pix1[q] = ac::wrap_cast((0.25 * pix1[q]) + (0.75 * pix2[q]));
                        }
                    }
                }
            }
        }
    }
    void clear() override {
        
    }
    ~Layer_AlphaBlend75() {
        
    }
private:
    Layer *layer_;
};

// intertwine

class Layer_0_Intertwine : public FilterFunc {
public:
    void init() override {
        pos_col = 0;
        max_col = 50;
    }
    void setLayer(Layer *layer) {
        layer_ = layer;
    }
    void proc(cv::Mat &frame) override {
        cv::Mat layer1;
        if(layer_->hasNext()) {
            if(layer_->read(layer1)) {
                cv::Mat resized;
                cv::resize(layer1, resized, frame.size());
                for(int z = 0; z < frame.rows; ++z) {
                    for(int i = 0; i < frame.cols; ++i) {
                        cv::Vec3b &pix1 = frame.at<cv::Vec3b>(z, i);
                        cv::Vec3b pix2;
                        setvec(pix2,resized.at<cv::Vec3b>(z, i));
                        if(pos_col == 0) {
                            setvec(pix1, pix2);
                        }
                        index_col ++;
                        if(index_col >= max_col) {
                            index_col = 0;
                            pos_col = !pos_col;
                        }
                    }
                }
            }
        }
        max_col ++;
        if(max_col > 100) {
            max_col = 50;
        }
    }
    void clear() override {
        
    }
    
    ~Layer_0_Intertwine() {
        
    }
private:
    Layer *layer_;
    int index_col = 0;
    int max_col = 50;
    int pos_col = 0;
};



class Layer012_AlphaBlend : public FilterFunc {
public:
    void init() override {
        
    }
    void setLayer(Layer *layer1, Layer *layer2, Layer *layer3) {
        layer_[0] = layer1;
        layer_[1] = layer2;
        layer_[2] = layer3;
    }
    void proc(cv::Mat &frame) override {
        cv::Mat layers[3];
        if(layer_[0]->hasNext() && layer_[1]->hasNext() && layer_[2]->hasNext()) {
            if(layer_[0]->read(layers[0]) && layer_[1]->read(layers[1]) && layer_[2]->read(layers[2])) {
                cv::Mat resized[3];
                cv::resize(layers[0], resized[0], frame.size());
                cv::resize(layers[1], resized[1], frame.size());
                cv::resize(layers[2], resized[2], frame.size());
                for(int z = 0; z < frame.rows; ++z) {
                    for(int i = 0; i < frame.cols; ++i) {
                        cv::Vec3b &pix1 = frame.at<cv::Vec3b>(z, i);
                        cv::Vec3b pix2[3];
                        setvec(pix2[0],resized[0].at<cv::Vec3b>(z, i));
                        setvec(pix2[1],resized[1].at<cv::Vec3b>(z, i));
                        setvec(pix2[2],resized[2].at<cv::Vec3b>(z, i));
                        
                        for(int q = 0; q < 3; ++q) {
                            pix1[q] = ac::wrap_cast((0.25 * pix1[q]) + (0.25 * pix2[0][q]) + (0.25 * pix2[1][q]) + (0.25 * pix2[2][q]));
                        }
                    }
                }
            }
        }
    }
    void clear() override {
        
    }
    ~Layer012_AlphaBlend() {
        
    }
private:
    Layer *layer_[3];
};

class Layer012_AlphaBlend_Xor : public FilterFunc {
public:
    void init() override {
        
    }
    void setLayer(Layer *layer1, Layer *layer2, Layer *layer3) {
        layer_[0] = layer1;
        layer_[1] = layer2;
        layer_[2] = layer3;
    }
    void proc(cv::Mat &frame) override {
        cv::Mat layers[3];
        if(layer_[0]->hasNext() && layer_[1]->hasNext() && layer_[2]->hasNext()) {
            if(layer_[0]->read(layers[0]) && layer_[1]->read(layers[1]) && layer_[2]->read(layers[2])) {
                cv::Mat resized[3];
                cv::resize(layers[0], resized[0], frame.size());
                cv::resize(layers[1], resized[1], frame.size());
                cv::resize(layers[2], resized[2], frame.size());
                for(int z = 0; z < frame.rows; ++z) {
                    for(int i = 0; i < frame.cols; ++i) {
                        cv::Vec3b &pix1 = frame.at<cv::Vec3b>(z, i);
                        cv::Vec3b pix2[3];
                        setvec(pix2[0],resized[0].at<cv::Vec3b>(z, i));
                        setvec(pix2[1],resized[1].at<cv::Vec3b>(z, i));
                        setvec(pix2[2],resized[2].at<cv::Vec3b>(z, i));
                        
                        for(int q = 0; q < 3; ++q) {
                            unsigned char value = pix1[q];
                            pix1[q] = ac::wrap_cast((0.25 * pix1[q]) + (0.25 * pix2[0][q]) + (0.25 * pix2[1][q]) + (0.25 * pix2[2][q]));
                            pix1[q] ^= value;
                        }
                    }
                }
            }
        }
        
        
    }
    void clear() override {
        
    }
    ~Layer012_AlphaBlend_Xor() {
        
    }
private:
    Layer *layer_[3];
};

// 012 Channel Merge
class Layer012_ChannelMerge : public FilterFunc {
public:
    void init() override {
        
    }
    void setLayer(Layer *layer1, Layer *layer2, Layer *layer3) {
        layer_[0] = layer1;
        layer_[1] = layer2;
        layer_[2] = layer3;
    }
    void proc(cv::Mat &frame) override {
        cv::Mat layers[3];
        if(layer_[0]->hasNext() && layer_[1]->hasNext() && layer_[2]->hasNext()) {
            if(layer_[0]->read(layers[0]) && layer_[1]->read(layers[1]) && layer_[2]->read(layers[2])) {
                cv::Mat resized[3];
                cv::resize(layers[0], resized[0], frame.size());
                cv::resize(layers[1], resized[1], frame.size());
                cv::resize(layers[2], resized[2], frame.size());
                for(int z = 0; z < frame.rows; ++z) {
                    for(int i = 0; i < frame.cols; ++i) {
                        cv::Vec3b &pix1 = frame.at<cv::Vec3b>(z, i);
                        cv::Vec3b pix2[3];
                        setvec(pix2[0],resized[0].at<cv::Vec3b>(z, i));
                        setvec(pix2[1],resized[1].at<cv::Vec3b>(z, i));
                        setvec(pix2[2],resized[2].at<cv::Vec3b>(z, i));
                        pix1[0] = cv::saturate_cast<uchar>((0.25 * pix1[0]) + (0.75 * pix2[0][0]));
                        pix1[1] = cv::saturate_cast<uchar>((0.25 * pix1[1]) + (0.75 * pix2[1][1]));
                        pix1[2] = cv::saturate_cast<uchar>((0.25 * pix1[2]) + (0.75 * pix2[2][2]));
                    }
                }
            }
        }
    }
    
    void clear() override {
        
    }
    ~Layer012_ChannelMerge(){}
    
private:
    Layer *layer_[3];
};

//012 Slide Show
class Layer012_SlideShow : public FilterFunc {
public:
    void init() override {
        alpha = 0.2f;
        index_val = 0;
        dir = 1;
    }
    void setLayer(Layer *layer1, Layer *layer2, Layer *layer3) {
        layer_[0] = layer1;
        layer_[1] = layer2;
        layer_[2] = layer3;
    }
    void proc(cv::Mat &frame) override {
        cv::Mat layers[3];
        if(layer_[0]->hasNext() && layer_[1]->hasNext() && layer_[2]->hasNext()) {
            if(layer_[0]->read(layers[0]) && layer_[1]->read(layers[1]) && layer_[2]->read(layers[2])) {
                cv::Mat resized[3];
                cv::resize(layers[0], resized[0], frame.size());
                cv::resize(layers[1], resized[1], frame.size());
                cv::resize(layers[2], resized[2], frame.size());
                for(int z = 0; z < frame.rows; ++z) {
                    for(int i = 0; i < frame.cols; ++i) {
                        cv::Vec3b &pix1 = frame.at<cv::Vec3b>(z, i);
                        cv::Vec3b pix2[3];
                        setvec(pix2[0],resized[0].at<cv::Vec3b>(z, i));
                        setvec(pix2[1],resized[1].at<cv::Vec3b>(z, i));
                        setvec(pix2[2],resized[2].at<cv::Vec3b>(z, i));
                        for(int q = 0; q < 3 && index_val <= 2; ++q) {
                            pix1[q] = ac::wrap_cast(( alpha * pix1[q] ) + ( (1-alpha ) * pix2[index_val][q]) );
                        }
                        
                    }
                }
            }
        }
        
        if(dir == 1) {
            alpha += 0.01f;
            if(alpha >= 1.0f) {
                alpha = 1.0f;
                dir = 0;
            }
        } else if(dir == 0) {
            alpha -= 0.01f;
            if(alpha <= 0.2f) {
                alpha = 0.2f;
                index_val ++;
                if(index_val > 2) index_val = 0;
                dir = 1;
            }
        }
    }
    
    void clear() override {
        
    }
    
    ~Layer012_SlideShow() {
        
    }
    
private:
    Layer *layer_[3];
    float alpha = 0.2f;
    int dir = 1;
    int index_val = 0;
    
};

// fade

class Layer_AlphaBlendFade01 : public FilterFunc {
public:
    void init() override {
        alpha = 0.1;
        
        inc = 0.01;
        dir = 1;
    }
    
    void setXor(bool x) {
        on = x;
    }
    
    void setLayer(Layer *layer1, Layer *layer2) {
        layer_[0] = layer1;
        layer_[1] = layer2;
    }
    void proc(cv::Mat &frame) override {
        cv::Mat layers[2];
        if(layer_[0]->hasNext() && layer_[1]->hasNext()) {
            if(layer_[0]->read(layers[0]) && layer_[1]->read(layers[1])) {
                cv::Mat resized[2];
                cv::resize(layers[0], resized[0], frame.size());
                cv::resize(layers[1], resized[1], frame.size());
                for(int z = 0; z < frame.rows; ++z) {
                    for(int i = 0; i < frame.cols; ++i) {
                        cv::Vec3b &pix1 = frame.at<cv::Vec3b>(z, i);
                        cv::Vec3b pix2[2];
                        setvec(pix2[0],resized[0].at<cv::Vec3b>(z, i));
                        setvec(pix2[1],resized[1].at<cv::Vec3b>(z, i));
                        for(int q = 0; q < 3; ++q) {
                            unsigned char value = cv::saturate_cast<uchar>((0.5 * pix2[0][q]) + (0.5 * pix2[1][q]));
                            pix1[q] = cv::saturate_cast<uchar>((alpha * pix1[q]) + ((1-alpha) * value));
                            if(on == true)
                                pix1[q] ^= value;
                        }
                    }
                }
            }
        }
        if(dir == 1) {
            alpha += inc;
            if(alpha >= 1.0) {
                alpha = 1.0;
                dir = 0;
            }
        } else {
            alpha -= inc;
            if(alpha <= 0.1) {
                alpha = 0.1;
                dir = 1;
            }
        }
    }
    void clear() override {
        
    }
    ~Layer_AlphaBlendFade01() {
        
    }
private:
    Layer *layer_[2];
    double alpha = 0.1;
    double inc = 0.01;
    int dir = 1;
    bool on = false;
};

// Difference

class Layer_Difference : public FilterFunc {
public:
    void init() override {
        
    }
    void setLayer(Layer *layer) {
        layer_ = layer;
    }
    void proc(cv::Mat &frame) override {
        collection.shiftFrames(frame);
        cv::Mat layer1;
        if(layer_->hasNext()) {
            if(layer_->read(layer1)) {
                cv::Mat resized;
                cv::resize(layer1, resized, frame.size());
                for(int z = 0; z < frame.rows; ++z) {
                    for(int i = 0; i < frame.cols; ++i) {
                        cv::Vec3b &pix1 = frame.at<cv::Vec3b>(z, i);
                        cv::Vec3b &pix_f = collection.at(6)->at<cv::Vec3b>(z, i);
                        cv::Vec3b pix2;
                        setvec(pix2,resized.at<cv::Vec3b>(z, i));
                        for(int q = 0; q < 3; ++q) {
                            if(std::abs(pix1[q]-pix_f[q]) > 25) {
                                pix1[q] = pix2[q];
                            }
                        }
                    }
                }
            }
        }
    }
    void clear() override {
        collection.clear();
    }
    ~Layer_Difference() {
        
    }
private:
    Layer *layer_;
    FrameCollection collection;
};

// DIfference Xor

class Layer_Difference_Xor : public FilterFunc {
public:
    void init() override {
        
    }
    void setLayer(Layer *layer) {
        layer_ = layer;
    }
    void proc(cv::Mat &frame) override {
        collection.shiftFrames(frame);
        cv::Mat layer1;
        if(layer_->hasNext()) {
            if(layer_->read(layer1)) {
                cv::Mat resized;
                cv::resize(layer1, resized, frame.size());
                for(int z = 0; z < frame.rows; ++z) {
                    for(int i = 0; i < frame.cols; ++i) {
                        cv::Vec3b &pix1 = frame.at<cv::Vec3b>(z, i);
                        cv::Vec3b &pix_f = collection.at(6)->at<cv::Vec3b>(z, i);
                        cv::Vec3b pix2;
                        setvec(pix2,resized.at<cv::Vec3b>(z, i));
                        for(int q = 0; q < 3; ++q) {
                            if(std::abs(pix1[q]-pix_f[q]) > 25) {
                                pix1[q] ^= pix2[q];
                            }
                        }
                    }
                }
            }
        }
    }
    void clear() override {
        collection.clear();
    }
    ~Layer_Difference_Xor() {
        
    }
private:
    Layer *layer_;
    FrameCollection collection;
};

// Fill != 0

class Layer_Fill_NotZero : public FilterFunc {
public:
    void init() override {
        
    }
    void setLayer(Layer *layer) {
        layer_ = layer;
    }
    void proc(cv::Mat &frame) override {
        cv::Mat layer1;
        if(layer_->hasNext()) {
            if(layer_->read(layer1)) {
                cv::Mat resized;
                cv::resize(layer1, resized, frame.size());
                for(int z = 0; z < frame.rows; ++z) {
                    for(int i = 0; i < frame.cols; ++i) {
                        cv::Vec3b &pix1 = frame.at<cv::Vec3b>(z, i);
                        if(pix1[0] > 4 && pix1[1] > 4 && pix1[2] > 4) {
                            setvec(pix1,resized.at<cv::Vec3b>(z, i));
                        }
                    }
                }
            }
        }
    }
    void clear() override {
        
    }
    
    ~Layer_Fill_NotZero() {
        
    }
private:
    Layer *layer_;
    
};

class Layer_Fill_Zero : public FilterFunc {
public:
    void init() override {
        
    }
    void setLayer(Layer *layer) {
        layer_ = layer;
    }
    void proc(cv::Mat &frame) override {
        cv::Mat layer1;
        if(layer_->hasNext()) {
            if(layer_->read(layer1)) {
                cv::Mat resized;
                cv::resize(layer1, resized, frame.size());
                for(int z = 0; z < frame.rows; ++z) {
                    for(int i = 0; i < frame.cols; ++i) {
                        cv::Vec3b &pix1 = frame.at<cv::Vec3b>(z, i);
                        if(pix1[0] < 25 && pix1[1] < 25 && pix1[2] < 25) {
                            setvec(pix1,resized.at<cv::Vec3b>(z, i));
                        }
                    }
                }
            }
        }
    }
    void clear() override {
        
    }
    
    ~Layer_Fill_Zero() {
        
    }
private:
    Layer *layer_;
};

class Layer_Fill_White : public FilterFunc {
public:
    void init() override {
        
    }
    void setLayer(Layer *layer) {
        layer_ = layer;
    }
    void proc(cv::Mat &frame) override {
        cv::Mat layer1;
        if(layer_->hasNext()) {
            if(layer_->read(layer1)) {
                cv::Mat resized;
                cv::resize(layer1, resized, frame.size());
                for(int z = 0; z < frame.rows; ++z) {
                    for(int i = 0; i < frame.cols; ++i) {
                        cv::Vec3b &pix1 = frame.at<cv::Vec3b>(z, i);
                        if(pix1[0] > 225 && pix1[1] > 225 && pix1[2] > 225) {
                            setvec(pix1,resized.at<cv::Vec3b>(z, i));
                        }
                    }
                }
            }
        }
    }
    void clear() override {
        
    }
private:
    Layer *layer_;
};

class Layer0_Wave : public FilterFunc {
public:
    void init() override {
        
    }
    void setLayer(Layer *layer) {
        layer_ = layer;
    }
    void proc(cv::Mat &frame) override {
        cv::Mat layer1;
        if(layer_->hasNext()) {
            if(layer_->read(layer1)) {
                cv::Mat resized;
                cv::resize(layer1, resized, frame.size());
                cv::Mat temp_frame = frame.clone();
                double amplitude = 25.0; // Amplitude of the wave
                double frequency = 2 * 3.14 / 180.0; // Frequency of the wave
                double phase_shift_speed = 0.05; // Speed of the phase shift change               
                // Update phase shift based on time_counter
                double phase_shift_x = time_counter * phase_shift_speed;
                double phase_shift_y = time_counter * phase_shift_speed;
                for(int y = 0; y < frame.rows; y++) {
                    for(int x = 0; x < frame.cols; x++) {
                        // Applying moving wave distortion with dynamic phase shifts
                        int dx = static_cast<int>(amplitude * sin(frequency * y + phase_shift_y));
                        int dy = static_cast<int>(amplitude * cos(frequency * x + phase_shift_x));
                        int new_x = x + dx;
                        int new_y = y + dy;
                        
                        if(new_x >= 0 && new_x < frame.cols && new_y >= 0 && new_y < frame.rows) {
                            cv::Vec3b &pix1 = temp_frame.at<cv::Vec3b>(new_y, new_x);
                            cv::Vec3b &pix2 = resized.at<cv::Vec3b>(new_y, new_x);
                            cv::Vec3b &pixel = frame.at<cv::Vec3b>(y, x);
                            for(int q = 0; q < 3; ++q) {
                                pixel[q] = ac::wrap_cast((0.5 * pix1[q]) + (0.5 * pix2[q]));
                            }
                        }
                    }
                }
                time_counter++;
            }
        }
    }
    void clear() override {
        
    }
    
    ~Layer0_Wave() {
    }
private:
    Layer *layer_;
    int time_counter = 0;
};

class Layer0_XorWave : public FilterFunc {
public:
    void init() override {
        
    }
    void setLayer(Layer *layer) {
        layer_ = layer;
    }
    void proc(cv::Mat &frame) override {
        cv::Mat layer1;
        if(layer_->hasNext()) {
            if(layer_->read(layer1)) {
                cv::Mat resized;
                cv::resize(layer1, resized, frame.size());            
                cv::Mat temp_frame = frame.clone();
                // Parameters to customize the wave effect
                double amplitude = 25.0; // Amplitude of the wave
                double frequency = 2 * 3.14 / 180.0; // Frequency of the wave
                double phase_shift_speed = 0.05; // Speed of the phase shift change
                // Update phase shift based on time_counter
                double phase_shift_x = time_counter * phase_shift_speed;
                double phase_shift_y = time_counter * phase_shift_speed;
                
                for(int y = 0; y < frame.rows; y++) {
                    for(int x = 0; x < frame.cols; x++) {
                        // Applying moving wave distortion with dynamic phase shifts
                        int dx = static_cast<int>(amplitude * sin(frequency * y + phase_shift_y));
                        int dy = static_cast<int>(amplitude * cos(frequency * x + phase_shift_x));
                        int new_x = x + dx;
                        int new_y = y + dy;        
                        if(new_x >= 0 && new_x < frame.cols && new_y >= 0 && new_y < frame.rows) {
                            cv::Vec3b &pix1 = temp_frame.at<cv::Vec3b>(new_y, new_x);
                            cv::Vec3b &pix2 = resized.at<cv::Vec3b>(new_y, new_x);
                            cv::Vec3b &pixel = frame.at<cv::Vec3b>(y, x);
                            for(int q = 0; q < 3; ++q) {
                                pixel[q] ^= ac::wrap_cast((0.5 * pix1[q]) + (0.5 * pix2[q]));
                            }
                        }
                    }
                }
                time_counter++;
            }
        }
    }
    void clear() override {
        
    }
    
    ~Layer0_XorWave() {
    }
private:
    Layer *layer_;
    int time_counter = 0;
};

class Layer_Matrix_Diff : public FilterFunc {
public:
    void init() override {
        
    }
    void setLayer(Layer *layer) {
        layer_ = layer;
    }
    void proc(cv::Mat &frame) override {
        collection.shiftFrames(frame);
        cv::Mat layer1;
        if(layer_->hasNext()) {
            if(layer_->read(layer1)) {
                cv::Mat resized;
                cv::resize(layer1, resized, frame.size());
                for(int z = 0; z < frame.rows; ++z) {
                    for(int i = 0; i < frame.cols; ++i) {
                        cv::Vec3b &pix1 = frame.at<cv::Vec3b>(z, i);
                        for(int f = 0; f < collection.size(); ++f) {
                            cv::Vec3b p;
                            setvec(p,collection.frames[f].at<cv::Vec3b>(z, i));
                            if(std::abs((pix1[0]+pix1[1]+pix1[2])-(p[0]+p[1]+p[2])) > 50) {
                                setvec(pix1, resized.at<cv::Vec3b>(z, i));
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    void clear() override {
        ac::release_all_objects();
    }
    
    ~Layer_Matrix_Diff() {
        
    }
private:
    Layer *layer_;
    ac::MatrixCollection<8> collection;
    
};

// use same video for layer 0
class Layer_Variable_Diff : public FilterFunc {
public:
    void init() override {
        var = 16;
        dir = 1;
    }
    void setLayer(Layer *layer) {
        layer_ = layer;
    }
    void proc(cv::Mat &frame) override {
        cv::Mat layer1;
        if(layer_->hasNext()) {
            collection.shiftFrames(frame);
            if(layer_->read(layer1)) {
                cv::Mat resized;
                cv::resize(layer1, resized, frame.size());
                ac::RSquare(resized);
                for(int z = 0; z < frame.rows; ++z) {
                    for(int i = 0; i < frame.cols; ++i) {
                        cv::Vec3b &pix1 = frame.at<cv::Vec3b>(z, i);
                        cv::Vec3b pix2;
                        setvec(pix2, collection.frames[6].at<cv::Vec3b>(z, i));
                        for(int q = 0; q < 3; ++q) {
                            if(std::abs(pix1[q]-pix2[q]) > var) {
                                pix1[q] = resized.at<cv::Vec3b>(z, i)[q];
                            }
                        }
                    }
                }
            }
        }
        if(dir == 1) {
            ++var;
            if(var >= 32) {
                var = 32;
                dir = 0;
            }
        } else {
            --var;
            if(var <= 16) {
                var = 16;
                dir = 1;
            }
        }
    }
    void clear() override {
        ac::release_all_objects();
    }
    
    ~Layer_Variable_Diff() {
        
    }
private:
    Layer *layer_;
    int var = 16;
    int dir = 1;
    ac::MatrixCollection<8> collection;
};

class Layer_Matrix_Color : public FilterFunc {
public:
    void init() override {
        
    }
    void setLayer(Layer *layer) {
        layer_ = layer;
    }
    void proc(cv::Mat &frame) override {
        collection.shiftFrames(frame);
        cv::Mat layer1;
        cv::Mat *src[3];
        src[0] = &collection.frames[0];
        src[1] = &collection.frames[3];
        src[2] = &collection.frames[6];
        
        if(layer_->hasNext()) {
            if(layer_->read(layer1)) {
                cv::Mat resized;
                cv::resize(layer1, resized, frame.size());
                for(int z = 0; z < frame.rows; ++z) {
                    for(int i = 0; i < frame.cols; ++i) {
                        cv::Vec3b &pix1 = frame.at<cv::Vec3b>(z, i);
                        cv::Vec3b &lsrc = resized.at<cv::Vec3b>(z, i);
                        for(int q = 0; q <3; ++q) {
                            pix1[q] = cv::saturate_cast<uchar>((src[q]->at<cv::Vec3b>(z, i)[q]) + (0.25 * lsrc[q]));
                        }
                    }
                }
            }
        }
    }
    void clear() override {
        ac::release_all_objects();
    }
    
    ~Layer_Matrix_Color() {
        
    }
private:
    Layer *layer_;
    ac::MatrixCollection<8> collection;
};

// Pic Adjust

class Layer_PictureAdjust : public FilterFunc {
public:
    void init() override {
        
    }
    void setLayer(Layer *layer) {
        layer_ = layer;
    }
    void proc(cv::Mat &src_frame) override {
        cv::Mat layer1;
        if(layer_->hasNext()) {
            if(layer_->read(layer1)) {
                cv::Mat frame;
                cv::resize(layer1, frame, src_frame.size());
                
                if(collection.empty()) {
                    srand(static_cast<unsigned int>(time(0)));
                    collection.shiftFrames(frame);
                }
                else
                    collection.shiftFrames(frame);
                
                
                static bool flash = true;
                if(flash) {
                    static int offset = 0;
                    int size_y = 0;
                    
                    size_y = rand()%frame.rows;
                    
                    for(int z = 0; z < frame.rows/2; ++z) {
                        for(int i = 0; i < frame.cols; ++i) {
                            cv::Vec3b &pixel = src_frame.at<cv::Vec3b>(z, i);
                            int cy = AC_GetFZ(frame.rows-1, z, size_y);
                            if(cy >= 0 && cy < frame.rows) {
                                cv::Vec3b pix;
                                setvec(pix,collection.frames[offset].at<cv::Vec3b>(cy, i));
                                for(int q = 0; q < 3; ++q) {
                                    pixel[q] = ac::wrap_cast((0.5 * pixel[q] ) + (0.5 * pix[q]));
                                }
                            }
                        }
                        size_y ++;
                    }
                    
                    for(int z = frame.rows/2; z < frame.rows; ++z) {
                        
                        for(int i = 0; i < frame.cols; ++i) {
                            cv::Vec3b &pixel = src_frame.at<cv::Vec3b>(z, i);
                            int cy = AC_GetFZ(frame.rows-1, z, size_y);
                            if(cy >= 0 && cy < frame.rows) {
                                cv::Vec3b &pix = collection.frames[offset].at<cv::Vec3b>(cy, i);
                                for(int q = 0; q < 3; ++q) {
                                    pixel[q] = ac::wrap_cast((0.5 * pixel[q] ) + (0.5 * pix[q]));
                                }
                            }
                        }
                        size_y --;
                    }
                    
                    if(++offset > (MAX-1)) {
                        offset = 0;
                    }
                    
                } else {
                    static int offset = 0;
                    static int size_y = frame.rows/16;
                    
                    for(int z = 0; z < frame.rows; ++z) {
                        for(int i = 0; i < frame.cols; ++i) {
                            cv::Vec3b &pixel = src_frame.at<cv::Vec3b>(z, i);
                            int cy = AC_GetFZ(frame.rows-1, z, size_y);
                            if(cy >= 0 && cy < frame.rows && i >= 0 && i < frame.cols) {
                                cv::Vec3b &pix = collection.frames[offset].at<cv::Vec3b>(cy, i);
                                for(int q = 0; q < 3; ++q) {
                                    pixel[q] = ac::wrap_cast((0.5 * pixel[q] ) + (0.5 * pix[q]));
                                }
                            }
                        }
                        size_y ++;
                        if(size_y > frame.rows*2)
                            size_y = frame.rows/16;
                    }
                    
                    if(++offset > (MAX-1)) {
                        offset = 0;
                    }
                }
                
                flash = (flash == true) ? false : true;
                
            }
        }
    }
    void clear() override {
        ac::release_all_objects();
    }
    ~Layer_PictureAdjust() {
        
    }
private:
    Layer *layer_;
    static constexpr int MAX=8;
    ac::MatrixCollection<MAX> collection;
    
};

// 

// Light
class Light_Increase : public FilterFunc {
public:
    void init() override {
    }
    void proc(cv::Mat &frame) override {
        for(int z = 0; z < frame.rows; ++z) {
            for(int i = 0; i < frame.cols; ++i) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                for(int q = 0; q < 3; ++q) {
                    pixel[q] = cv::saturate_cast<uchar>((pixel[q]*1.25));
                }
            }
        }
    }
    void clear() override {
    }
    ~Light_Increase() {
        
    }
private:
    
};

// Light Echo
class Light_Echo : public FilterFunc {
public:
    void init() override {
    }
    void proc(cv::Mat &frame) override {
        for(int z = 0; z < frame.rows; ++z) {
            for(int i = 0; i < frame.cols; ++i) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                cv::Vec3b pixel_val[2];
                setvec(pixel_val[0], frame.at<cv::Vec3b>(z/2, i/2));
                setvec(pixel_val[1], frame.at<cv::Vec3b>(z/4, i/4));
                for(int q = 0; q < 3; ++q) {
                    pixel[q] = cv::saturate_cast<uchar>((pixel[q] * 0.5) + (pixel_val[0][q] * 0.25) + (pixel_val[1][q] * 0.25));
                }
            }
        }
    }
    void clear() override {
    }
    ~Light_Echo() {
    }
private:
};

class Light_Wrap : public FilterFunc {
public:
    void init() override {
    }
    void proc(cv::Mat &frame) override {
        for(int z = 0; z < frame.rows; ++z) {
            for(int i = 0; i < frame.cols; ++i) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                cv::Vec3b pixel_val[2];
                setvec(pixel_val[0], frame.at<cv::Vec3b>(z/2, i/2));
                setvec(pixel_val[1], frame.at<cv::Vec3b>(z/4, i/4));
                for(int q = 0; q < 3; ++q) {
                    pixel[q] = ac::wrap_cast((pixel[q] * 0.5) + (pixel_val[0][q] * 0.5) + (pixel_val[1][q] * 0.5));
                }
            }
        }
    }
    void clear() override {
    }
    ~Light_Wrap()  {}
private:
};

class MedianBlend_Low : public FilterFunc {
public:
    void init() override {
    }
    void proc(cv::Mat &frame) override {
        cv::Mat m;
        cv::resize(frame, m, cv::Size(640, 480));
        ac::MedianBlendMultiThreadByThree(m);
        cv::resize(m, frame, frame.size());
    }
    void clear() override {
        ac::release_all_objects();
    }
    ~MedianBlend_Low()  {}
private:
};

// Metal Low
class MetalBlend_Low : public FilterFunc {
public:
    void init() override {
    }
    void proc(cv::Mat &frame) override {
        cv::Mat m;
        cv::resize(frame, m, cv::Size(640, 480));
        ac::MetalMedianBlend(m);
        cv::resize(m, frame, frame.size());
    }
    void clear() override {
        ac::release_all_objects();
    }
    ~MetalBlend_Low()  {}
private:
};

// Resize and Lower quality
class StandardDef : public FilterFunc {
public:
    void init() override {
    }
    void proc(cv::Mat &frame) override {
        cv::Mat m;
        cv::resize(frame, m, cv::Size(640, 480));
        cv::resize(m, frame, frame.size());
    }
    void clear() override {
        
    }
    ~StandardDef()  {}
private:
};

// Scaling Def
class ScalingDef : public FilterFunc {
public:
    void init() override {
        scale_size = 320;
        p = 320/4;
        dir = 1;
    }
    void proc(cv::Mat &frame) override {
        cv::Mat m;
        cv::resize(frame, m, cv::Size(scale_size, scale_size));
        cv::resize(m, frame, frame.size());
        if(dir == 1) {
            scale_size += p;
            if(scale_size > 1920) {
                dir = 0;
            }
        } else {
            scale_size -= p;
            if(scale_size <= 320) {
                dir = 1;
            }
        }
    }
    void clear() override {
        
    }
    
    ~ScalingDef() {}
private:
    int scale_size = 320;
    int p = 320/4;
    int dir = 1;
};


class AlphaSin : public FilterFunc {
public:
    void init() override {
        alpha.setSample(44100.0f);
        alpha.setFrequency(255.0f);

    }
    void proc(cv::Mat &frame) override {

        float a = alpha.nextSample();

        for(int z = 0; z < frame.rows; ++z) {
            for(int i = 0; i < frame.cols; ++i) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                for(int q = 0; q < 3; ++q) {
                    pixel[q] = ac::wrap_cast(pixel[q]*a);
                }
            }
        }
    }
    void clear() override {
        
    }
    ~AlphaSin() {}
private:
    LFO alpha;
};

class LFOWave : public FilterFunc {
public:
    void init() override {
        amp.initValues(1.0, 0.1, 25.0, 50.0);
        amp.setRandom(true);
        speed.initValues(0.1, 0.1, 0.1, 2.0);
    }
    void proc(cv::Mat &frame) override {
        cv::Mat temp_frame = frame.clone();
        double phase_shift_speed = speed.nextValue();
        double phase_shift_x = time_counter * phase_shift_speed;
        double phase_shift_y = time_counter * phase_shift_speed;
        double frequency = 2 * 3.14 / 180.0;
        double amplitude = amp.nextValue();
         for(int y = 0; y < frame.rows; y++) {
            for(int x = 0; x < frame.cols; x++) {
                int dx = static_cast<int>(amplitude * sin(frequency * y + phase_shift_y));
                int dy = static_cast<int>(amplitude * cos(frequency * x + phase_shift_x));
                int new_x = x + dx;
                int new_y = y + dy;
                if(new_x >= 0 && new_x < frame.cols && new_y >= 0 && new_y < frame.rows) {
                    frame.at<cv::Vec3b>(y, x) = temp_frame.at<cv::Vec3b>(new_y, new_x);
                }
            }
        }
        time_counter++;
    }
    void clear() override {
        
    }
    ~LFOWave() {}
private: 
    KnobRandom amp;
    Knob speed;
    int time_counter = 0;
};

class Wave_Freq : public FilterFunc {
public:
    void init() override {
        amp.initValues(1.0, 0.1, 25.0, 30.0);
        amp.setRandom(true);
        freq.setSample(44100.0f);
        freq.setFrequency(1.0f);
        srand(static_cast<int>(time(0)));
        frequency = 2 * 3.14 / 180.0;
        freq_k.initValues(0.1, 0.001, 0.1, 25.0);
    }
    void proc(cv::Mat &frame) override {
        cv::Mat temp_frame = frame.clone();
        double phase_shift_speed = (rand()%10 * 0.1) + freq.nextSample();
        double phase_shift_x = time_counter * phase_shift_speed;
        double phase_shift_y = time_counter * phase_shift_speed;
        frequency += freq_k.nextValue();
        double amplitude = amp.nextValue();
         for(int y = 0; y < frame.rows; y++) {
            for(int x = 0; x < frame.cols; x++) {
                int dx = static_cast<int>(amplitude * sin(frequency * y + phase_shift_y));
                int dy = static_cast<int>(amplitude * cos(frequency * x + phase_shift_x));
                int new_x = x + dx;
                int new_y = y + dy;
                if(new_x >= 0 && new_x < frame.cols && new_y >= 0 && new_y < frame.rows) {
                    frame.at<cv::Vec3b>(y, x) = temp_frame.at<cv::Vec3b>(new_y, new_x);
                }
            }
        }
        time_counter++;
    }
    void clear() override {   

    }
    ~Wave_Freq() {}
private: 
    KnobRandom amp;
    Knob freq_k;
    LFO freq;
    int time_counter = 0;
    double frequency = 0;
}; 

class Scrambler : public FilterFunc {
public:
    void init() override {
        block_size.initValues(50, 4.0, 50.0, 100.0);

    }
    void proc(cv::Mat &frame) override {
        scrambleBlocks(frame, time, frequency, sampleRate);
        time += 1.0f;
    }
    void clear() override {}
    ~Scrambler() {}    
private:

    float time = 0.0f;
    float frequency = 0.1f; 
    float sampleRate = 30.0f;
    Knob block_size;
    int blockSize = 25;

    void scrambleBlocks(cv::Mat& image, float time, float frequency, float sampleRate) {
        blockSize = block_size.nextValue();
        int blocksX = image.cols / blockSize;
        int blocksY = image.rows / blockSize;
        blockSize = std::min(image.cols/ blocksX, image.rows / blocksY);
        std::vector<cv::Mat> blocks;
        for (int y = 0; y < blocksY; ++y) {
            for (int x = 0; x < blocksX; ++x) {
                int startX = x * blockSize;
                int startY = y * blockSize;
                int endX = std::min(startX + blockSize, image.cols);
                int endY = std::min(startY + blockSize, image.rows);
                cv::Rect blockRect(startX, startY, endX - startX, endY - startY);
                blocks.push_back(image(blockRect).clone());
            }
        }
        float lfoValue = lfo(time, frequency, sampleRate);
        int shift = static_cast<int>((lfoValue + 1) * (blocks.size() - 1) / 2); 
        std::rotate(blocks.begin(), blocks.begin() + shift, blocks.end());
        for (int y = 0; y < blocksY; ++y) {
            for (int x = 0; x < blocksX; ++x) {
                cv::Rect blockRect(x * blockSize, y * blockSize, blockSize, blockSize);
                if (blockRect.x + blockRect.width > image.cols) blockRect.width = image.cols - blockRect.x;
                if (blockRect.y + blockRect.height > image.rows) blockRect.height = image.rows - blockRect.y;
                blocks[y * blocksX + x].copyTo(image(blockRect));
            }
        }
    }

    float lfo(float time, float frequency, float sampleRate) {
        return sinf(2.0f * CV_PI * frequency * time / sampleRate);
    }
};

class GradientLFO : public FilterFunc {
public:
    void init() override {}
    void proc(cv::Mat &frame) override {
        applyLfoModulatedGradient(frame, time, frequency, sampleRate);
        time += 2.0f;
    }
    void clear() override {}
    ~GradientLFO() {}
private:
    float time = 0.0f;
    float frequency = 0.1f;
    float sampleRate = 30.0f; 
    void applyLfoModulatedGradient(cv::Mat& frame, float time, float frequency, float sampleRate) {
        auto lfo = [&](float time) -> float {
            return (sinf(2.0f * CV_PI * frequency * time / sampleRate) + 1.0f) / 2.0f; 
        };

        float lfoValue = lfo(time);

        for (int y = 0; y < frame.rows; ++y) {
            for (int x = 0; x < frame.cols; ++x) {
                float gradientValue = static_cast<float>(x) / frame.cols; 
                gradientValue *= lfoValue; 
                cv::Vec3b color = frame.at<cv::Vec3b>(y, x);
                color[0] = cv::saturate_cast<uchar>(color[0] * (1.0 - gradientValue) + (gradientValue * 255));
                frame.at<cv::Vec3b>(y, x) = color;
            }
        }
    }
};

class AlphaKnobs : public FilterFunc {
public:
    void init() override {
        alpha[0].initValues(1.0, 0.01, 0.1, 2.0);
        alpha[1].initValues(2.0, 0.02, 0.1, 2.0);
        alpha[2].initValues(1.0, 0.03, 0.1, 2.0);
    }
    void proc(cv::Mat &frame) override {

        /*
        alpha[0].setSpeed(255.0 / (frame.rows * 3));
        alpha[1].setSpeed(255.0 / (frame.rows * 3));
        alpha[2].setSpeed(255.0 / (frame.rows * 3));
        */
                 
        for(int z = 0; z < frame.rows; ++z) {
            for(int i = 0; i < frame.cols; ++i) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                for(int q = 0; q < 3; ++q) {
                    double val = alpha[q].nextValue();
                    pixel[q] = ac::wrap_cast((255-pixel[q]) * val);
                }
            }
        }
    }
    void clear() override {
        
    }
    ~AlphaKnobs() {}
private:
    Knob alpha[3];
};

// thanks GPT for helping me understand this :)
class DynamicGradientOverlay : public FilterFunc {
public:
    DynamicGradientOverlay() : colorShiftLFO(0.1f, 30.0f) {
        opacityKnob.initValues(0.5, 0.01, 0.1, 0.9); 
    }

    void proc(cv::Mat &frame) override {
        applyDynamicGradient(frame, time);
        time += 1.0f; 
    }

    void clear() override {

    }
    void init() override {
       opacityKnob.initValues(0.5, 0.01, 0.1, 0.9); 
    }

private:
    float time = 0.0f;
    LFO colorShiftLFO;
    Knob opacityKnob; 

    void applyDynamicGradient(cv::Mat& frame, float) {
        cv::Mat gradient = frame.clone();
        float hueShift = colorShiftLFO.nextSample() * 0.5f + 0.5f;

        for (int y = 0; y < gradient.rows; ++y) {
            uchar intensity = static_cast<uchar>(255 * (static_cast<float>(y) / gradient.rows));
            cv::Vec3b color = hsvToBgr(hueShift * 180, 255, intensity);
            for (int x = 0; x < gradient.cols; ++x) {
                gradient.at<cv::Vec3b>(y, x) = color;
            }
        }
        double alpha = opacityKnob.nextValue(); // Use Knob to determine alpha dynamically
        cv::addWeighted(frame, 1 - alpha, gradient, alpha, 0, frame);
    }

    cv::Vec3b hsvToBgr(float hue, float saturation, float value) {
        cv::Mat hsv(1, 1, CV_8UC3, cv::Scalar(hue, saturation, value));
        cv::Mat bgr;
        cv::cvtColor(hsv, bgr, cv::COLOR_HSV2BGR);
        return bgr.at<cv::Vec3b>(0, 0);
    }
};

class ThreshEffect : public FilterFunc {
public:
    void proc(cv::Mat &frame) override {
        cv::Mat gray, thresh;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::threshold(gray, thresh, 128, 255, cv::THRESH_BINARY);
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(thresh.clone(), contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        cv::Mat glitchEffect = frame.clone();
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> uniDist(-20, 20); 
        for (size_t i = 0; i < contours.size(); i++) {
            if (rng() % 2) { 
                std::vector<cv::Point> movedContour;
                for (auto &pt : contours[i]) {
                    int dx = uniDist(rng); 
                    int dy = uniDist(rng); 
                    movedContour.push_back(cv::Point(pt.x + dx, pt.y + dy));
                }
                cv::drawContours(glitchEffect, std::vector<std::vector<cv::Point>>{movedContour}, -1, cv::Scalar(rand()%255, rand()%255, rand()%255), 2);
            }
        }
        frame = glitchEffect;
    }    
    void init() override {}
    void clear() override {}
};

class ThreshEffect_Layer : public FilterFunc {
public:

    void initLayer(Layer *l) {
        layer_ = l;
    }

    void init() override {}
    void clear() override {}

    void proc(cv::Mat &frame) override {
       if(layer_->hasNext()) {
            cv::Mat layerx;
            if(layer_->read(layerx)) {
                cv::Mat resized;
                cv::resize(layerx, resized, frame.size());
                cv::Mat gray, thresh, overlayImage;
                cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
                cv::threshold(gray, thresh, 128, 255, cv::THRESH_BINARY);
                std::vector<std::vector<cv::Point>> contours;
                cv::findContours(thresh.clone(), contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
                cv::Mat mask = cv::Mat::zeros(frame.size(), CV_8UC1);
                std::mt19937 rng(std::random_device{}());
                for (size_t i = 0; i < contours.size(); i++) {
                    if (rng() % 2) {
                        cv::drawContours(mask, contours, static_cast<int>(i), cv::Scalar(255), cv::FILLED);
                    }
                 }
                cv::Mat resizedOverlay;
                resizedOverlay = resized;
                cv::Mat overlayResult;
                frame.copyTo(overlayResult);
                resizedOverlay.copyTo(overlayResult, mask);
                frame = overlayResult;
            }
        } 
    }
private:
    Layer *layer_;
};

class CartoonEffect : public FilterFunc {
public:
    void init() override {}
    void clear() override {}
    void proc(cv::Mat &frame) override {
        cv::Mat dst;
        cartoonEffect(frame, dst);
        frame = dst;
    }
private:
    void cartoonEffect(const cv::Mat& src, cv::Mat& dst) {
        cv::Mat resized, edges, imgColor;
        float resizeScale = 0.5; 
        cv::resize(src, resized, cv::Size(), resizeScale, resizeScale, cv::INTER_LINEAR);
        cv::cvtColor(resized, edges, cv::COLOR_BGR2GRAY);
        cv::medianBlur(edges, edges, 5);
        cv::adaptiveThreshold(edges, edges, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 9, 2);
        cv::cvtColor(edges, edges, cv::COLOR_GRAY2BGR);
        cv::pyrMeanShiftFiltering(resized, imgColor, 10, 25, 2);
        cv::bitwise_and(imgColor, edges, dst);
        cv::resize(dst, dst, src.size(), 0, 0, cv::INTER_LINEAR);
    }
};



class BackgroundReplacementEffect : public FilterFunc {
public:
    BackgroundReplacementEffect() : low_color(35, 50, 50), high_color(85,255,255) {}
    void setLayer(Layer *layer_x) {
        layer_ = layer_x;
    }
    void init() override {}
    void clear() override {}
    void proc(cv::Mat &frame) override {
        if(layer_ != nullptr && layer_->hasNext()) {
            cv::Mat layer_n;
            if(layer_->read(layer_n)) {
                cv::resize(layer_n, newBg, frame.size());
                cv::Mat dst;
                backgroundReplacement(frame, dst);
                frame = dst;
            }
        }
    }

    void setLow(const cv::Scalar &color1) {
        low_color = color1;
    }
    void setHigh(const cv::Scalar &color2) {
        high_color = color2;
    }
private:
    Layer *layer_ = nullptr;
    cv::Mat newBg; 
    cv::Scalar low_color, high_color;
    void backgroundReplacement(const cv::Mat& src, cv::Mat& dst) {
        cv::Mat hsv;
        cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
        cv::Scalar lowerGreen(low_color);
        cv::Scalar upperGreen(high_color);
        cv::Mat mask;
        cv::inRange(hsv, lowerGreen, upperGreen, mask);
        cv::bitwise_not(mask, mask);
        cv::Mat backgroundResized;
        if (newBg.size() != src.size()) {
            cv::resize(newBg, backgroundResized, src.size(), 0, 0, cv::INTER_LINEAR);
        } else {
            backgroundResized = newBg;
        }
        cv::Mat foreground;
        src.copyTo(foreground, mask);
        backgroundResized.copyTo(dst, ~mask);
        cv::add(foreground, dst, dst, mask);
    }
};

class GreenScreenEffect : public FilterFunc {
public:
    GreenScreenEffect() : low(35, 100, 50), high(85, 255, 255) {}
    void init() override {}
    void setLayer(Layer *layer_) {
        layer = layer_;
    }
    
    void setLow(const cv::Scalar &l) {
        low = l;
    }
    void setHigh(const cv::Scalar &h) {
        high = h;
    }

    void proc(cv::Mat &frame) override {
        if(layer == nullptr) return;
        cv::Mat mat;
        if(layer->hasNext() && layer->read(mat)) {
            cv::Mat mask, result;
            cv::Mat resized;
            cv::resize(mat, resized, frame.size());
            chromaKeyMask(frame, mask);
            refineMask(mask);
            frame.copyTo(result, mask);
            for(int z = 0; z < frame.rows; ++z) {
                for(int i = 0; i < frame.cols; ++i) {
                    cv::Vec3b pixel = result.at<cv::Vec3b>(z, i);
                    cv::Vec3b &pix = frame.at<cv::Vec3b>(z, i);
                    if(pixel == cv::Vec3b(0, 0, 0)) {
                        cv::Vec3b src1 = frame.at<cv::Vec3b>(z, i);
                        cv::Vec3b src2 = resized.at<cv::Vec3b>(z, i);
                        for(int q = 0; q < 3; ++q) {
                            pix[q] = ac::wrap_cast( (0.5 * src1[q]) + (0.5 * src2[q]) );
                        }
                    } else {
                        pix = cv::Vec3b(0, 0, 0);
                    }
                }
            }
        }
    }
    void clear() override {}

private:
    cv::Scalar low, high;
    Layer *layer = nullptr;
    void chromaKeyMask(const cv::Mat &frame, cv::Mat &mask) {
        cv::Mat hsvFrame;
        cv::cvtColor(frame, hsvFrame, cv::COLOR_BGR2HSV);
        cv::inRange(hsvFrame, low, high, mask);
    }
    void refineMask(cv::Mat &mask) {
        cv::erode(mask, mask, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
        cv::dilate(mask, mask, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
        cv::medianBlur(mask, mask, 7);
    }
};

class FilmGrain : public FilterFunc {
public:
    FilmGrain() : distribution(0.0, 25.0) { 
        random_engine.seed(std::chrono::system_clock::now().time_since_epoch().count());
    }

    void init() override {
    }

    void proc(cv::Mat &frame) override {
        for (int y = 0; y < frame.rows; y++) {
            for (int x = 0; x < frame.cols; x++) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(y, x);
                for (int c = 0; c < frame.channels(); c++) {
                    double grain = distribution(random_engine);
                    int newValue = cv::saturate_cast<uchar>(pixel[c] + grain);
                    pixel[c] = static_cast<uchar>(newValue);
                }
            }
        }
    }

    void clear() override {}
    ~FilmGrain() {}
private:
    std::default_random_engine random_engine;
    std::normal_distribution<double> distribution;
};

class Layer_0_DualAlphaScale : public FilterFunc {
public:
    void setLayer(Layer *layer_x) {
        layer_ = layer_x;
        off.initValues(1.0, 0.2, 1.0, 2.0);
    }
    void init() override {}
    void clear() override {}
    void proc(cv::Mat &frame) override {
        if(layer_ != nullptr && layer_->hasNext()) {
            cv::Mat layer_n;
            cv::Mat resized;
            if(layer_->read(layer_n)) {
                double off_val = off.nextValue();
                cv::resize(layer_n, resized, frame.size());
                for(int z = 0; z < frame.rows; ++z) {
                    for(int i = 0; i < frame.cols; ++i) {
                        cv::Vec3b pixel = frame.at<cv::Vec3b>(z, i);
                        cv::Vec3b pixel_r = resized.at<cv::Vec3b>(z, i);
                        for(int q = 0; q < 3; ++q) {
                            pixel[q] = ac::wrap_cast((pixel[q]+pixel_r[q])*off_val);
                         }
                         frame.at<cv::Vec3b>(z, i) = pixel;
                    }
                }
            }
        }
    }
private:
    Layer *layer_ = nullptr;
    Knob off;
};

class Layer_0_DualAlphaBlend : public FilterFunc {
public:
    void setLayer(Layer *layer_x) {
        layer_ = layer_x;
        off.initValues(1.0, 0.2, 1.0, 3.0);
    }
    void init() override {}
    void clear() override {}
    void proc(cv::Mat &frame) override {
        if(layer_ != nullptr && layer_->hasNext()) {
            cv::Mat layer_n;
            cv::Mat resized;
            if(layer_->read(layer_n)) {
                double off_val = off.nextValue();
                cv::resize(layer_n, resized, frame.size());
                for(int z = 0; z < frame.rows; ++z) {
                    for(int i = 0; i < frame.cols; ++i) {
                        cv::Vec3b pixel = frame.at<cv::Vec3b>(z, i);
                        cv::Vec3b pixel_r = resized.at<cv::Vec3b>(z, i);
                        for(int q = 0; q < 3; ++q) {
                            pixel[q] = ac::wrap_cast(((0.5 * pixel[q])+(0.5 * pixel_r[q]))*off_val);
                         }
                         frame.at<cv::Vec3b>(z, i) = pixel;
                    }
                }
            }
        }
    }
private:
    Layer *layer_ = nullptr;
    Knob off;
};

class Layer_0_DualAlphaDir : public FilterFunc {
public:
    void setLayer(Layer *layer_x) {
        layer_ = layer_x;
         k_front.initValues(1.0, 0.2, 1.0, 3.0);
         k_layer.initValues(3.0, 0.2, 1.0, 3.0, 1);

    }
    void init() override {}
    void clear() override {}
    void proc(cv::Mat &frame) override {
        if(layer_ != nullptr && layer_->hasNext()) {
            cv::Mat layer_n;
            cv::Mat resized;
            if(layer_->read(layer_n)) {
                double off_val = k_front.nextValue();
                double off_val2 = k_layer.nextValue();

                cv::resize(layer_n, resized, frame.size());
                for(int z = 0; z < frame.rows; ++z) {
                    for(int i = 0; i < frame.cols; ++i) {
                        cv::Vec3b pixel = frame.at<cv::Vec3b>(z, i);
                        cv::Vec3b pixel_r = resized.at<cv::Vec3b>(z, i);
                        for(int q =0;  q < 3; ++q) {
                            double value1 = (pixel[q]*off_val);
                            double value2 = (pixel_r[q]*off_val2);
                            pixel[q] = ac::wrap_cast(value1+value2);
                        }
                         frame.at<cv::Vec3b>(z, i) = pixel;
                    }
                }
            }
        }
    }
private:
    Layer *layer_ = nullptr;
    Knob k_front;
    Knob k_layer;
};

class WaterColor : public FilterFunc {
public:
    void init() override {}
    void clear() override {}
    void proc(cv::Mat &frame) override {
        cv::Mat dst;
        wcEffect(frame, dst);
        frame = dst;
    }
private:
    void wcEffect(const cv::Mat& frame, cv::Mat& watercolor) {
        cv::Mat blurred;
        cv::medianBlur(frame, blurred, 7);
        cv::Mat gray, edges;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::Canny(gray, edges, 50, 150);
        cv::Mat edgesInv = 255 - edges;
        cv::cvtColor(edgesInv, edgesInv, cv::COLOR_GRAY2BGR);
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2,2));
        cv::dilate(edgesInv, edgesInv, kernel);
        cv::bitwise_and(blurred, edgesInv, watercolor);
    }
};

class MedianNoiseReduction : public FilterFunc {
public:
    void init() override {}
    void clear() override {}
    void proc(cv::Mat &frame) override {
        cv::medianBlur(frame, frame, 5);
    }
};

class BilateralNoiseReduction : public FilterFunc {
public:
    void init() override {}
    void clear() override {}
    void proc(cv::Mat &frame) override {
        if (frame.type() != CV_8UC1 && frame.type() != CV_8UC3) {
            frame.convertTo(frame, CV_8UC3);
        }
        cv::Mat temp;
        cv::bilateralFilter(frame, temp, 9, 75, 75); 
        frame = temp;
    }
};


class BlackEdgeFilter : public FilterFunc {
public:
    void init() override {}
    void clear() override {}
    void proc(cv::Mat &frame) override {
        cv::Mat edges, edgesInverted;
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::Canny(gray, edges, 100, 200); 
        cv::bitwise_not(edges, edgesInverted);
        cv::Mat blackEdges(frame.size(), frame.type(), cv::Scalar::all(0));
        frame.copyTo(blackEdges, edgesInverted);
        frame = blackEdges;
    }
};

class Layer_0_EdgeFilter : public FilterFunc {
public:
    void setLayer(Layer *l) {
        layer_ = l;
    }
    void init() override {}
    void clear() override {}
    void proc(cv::Mat &frame) override {
        if(layer_ != nullptr && layer_->hasNext()) {
            cv::Mat frame2;
            if(layer_->read(frame2)) {
                cv::resize(frame2, frame2, frame.size());
                cv::Mat edges, gray;
                cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
                cv::Canny(gray, edges, 100, 200); 
                cv::Mat dilatedEdges;
                int dilationSize = 2; 
                cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(2 * dilationSize + 1, 2 * dilationSize + 1),cv::Point(dilationSize, dilationSize));
                cv::dilate(edges, dilatedEdges, element);
                frame2.copyTo(frame, dilatedEdges);
            }
        }
    }
private:
    Layer *layer_ = nullptr;
};

class Layer_0_GlitchBleed : public FilterFunc {
public:
    Layer_0_GlitchBleed() : gen(rd()), dist(1, 4), distRow(0, 5), distHeight(1, 75) {} 

    void setLayer(Layer *l) {
        layer_ = l;
    }

    void init() override {
        for (int i = 0; i < 5; ++i) {
            knobs[i].initValues(0.1 * i, 0.1, 0.1, 1.0);
        }
        wait = 60 * dist(gen); // Initialize wait with a random value
    }

    void clear() override {}

    void proc(cv::Mat &frame) override {
        if (layer_ != nullptr && layer_->hasNext()) {
            cv::Mat frame2;
            if (layer_->read(frame2)) {
                cv::resize(frame2, frame2, frame.size());
                if (++delay > wait) {
                    set_num = dist(gen);
                    delay = 0;
                    wait = 60 * dist(gen);
                }
                int num = set_num;
                for (int i = 0; i < num; ++i) {
                    fillRect(i, frame, frame2, rand_(0, frame.rows - 50), distHeight(gen));
                }
            }
        }
    }
    
private:
    Layer *layer_ = nullptr;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dist; 
    std::uniform_int_distribution<> distRow;
    std::uniform_int_distribution<> distHeight;

    void fillRect(int index, cv::Mat &frame, const cv::Mat &cp, int y1, int y2) {
        int offset_x = distRow(gen);
        double alpha = knobs[index].nextValue();
        double invAlpha = 1 - alpha;
        for (int z = y1; z < y1 + y2 && z < frame.rows; ++z) {
            for (int i = offset_x; i < frame.cols; ++i) {
                if(i >= 0 && i < frame.cols && z >= 0 && z < frame.rows) {
                    cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                    const cv::Vec3b &pix2 = cp.at<cv::Vec3b>(z, i);
                    for (int q = 0; q < 3; ++q) {
                        pixel[q] = static_cast<uchar>(alpha * pixel[q] + invAlpha * pix2[q]);
                    }
                }
            }
        }
    }

    int rand_(int min, int max) {
        std::uniform_int_distribution<> distr(min, max);
        return distr(gen);
    }

    Knob knobs[5];
    int set_num = 1;
    int delay = 0;
    int wait;
};

class AlphaRandom : public FilterFunc {
public:

    AlphaRandom() : gen{rd()}, dist(1.0, 3.0) { }
    void init() override {}
    void clear() override {}
    
    void proc(cv::Mat &frame) override{
        double alpha = rand_();
        for(int z = 0; z < frame.rows; ++z) {
            for(int i = 0; i < frame.cols; ++i) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                for(int q = 0; q < 3; ++q) {
                    pixel[q] =  ac::wrap_cast(pixel[q]*alpha);
                }
            }
        }
    }

    double rand_() { return dist(gen); }

private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dist;
  
};

class New_MedianBlend : public FilterFunc {
public:
    New_MedianBlend() : gen{rd()}, dist(3, 7) {}
    void init() override { }
    void clear() override { collection.clear(); }    
    void proc(cv::Mat &frame) override{
        int r = dist(gen);
        for(int m = 0; m < r; ++m) {
            cv::medianBlur(frame, frame, 5);
        }
        collection.shiftFrames(frame);     
        if (collection.size() < collection.capacity()) return;
        for (int z = 0; z < frame.rows; ++z) {
            for (int i = 0; i < frame.cols; ++i) {
                cv::Scalar value(0, 0, 0);
                for (int j = 0; j < static_cast<int>(collection.size()); ++j) {
                    cv::Vec3b pixel = collection[j].at<cv::Vec3b>(z, i);
                    for (int q = 0; q < 3; ++q) {
                        value[q] += pixel[q];
                    }
                }
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                for(int j = 0; j < 3; ++j) {
                   int val = 1+static_cast<int>(value[j]);
                    pixel[j] = static_cast<unsigned char>(pixel[j] ^ val);
                }
            }
        }
    }
private:
    New_MatrixCollection<8> collection;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;
};

class New_ColorScale : public FilterFunc {
public:
    New_ColorScale() : gen{rd()}, dist(0.1, 1.0) { }
    void init() override {
        for(int i = 0; i < 3; ++i) {
            knobs[i].initValues(dist(gen),0.01, 0.1, 1.0);
        }
    }
    void clear() override {
        init();        
    }
    void proc(cv::Mat &frame) override{
        cv::Scalar vals(knobs[0].nextValue(), knobs[1].nextValue(), knobs[2].nextValue());
        for(int z = 0; z < frame.rows; ++z) {
            for(int i = 0; i < frame.cols; ++i) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                for(int q = 0; q < 3; ++q) {
                    pixel[q] = cv::saturate_cast<uchar>(pixel[q]*vals[q]);
                }
            }
        }
    }
private:
    Knob knobs[3];
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dist;
};

class ColorGradientShift : public FilterFunc {
public:
    ColorGradientShift(float fps) : frameRate(fps) {
        startColor = cv::Scalar(255, 0, 0); 

        endColor = cv::Scalar(0, 0, 255); 
    }
    void init() override {}
    void clear() override {}
    void proc(cv::Mat &frame) override {
       float video_t = frameCount / frameRate;
       updateColors(video_t);
       cv::Mat gradient(frame.size(), CV_8UC3);
       createDynamicGradient(gradient);
       cv::addWeighted(frame, 0.5, gradient, 0.5, 0.0, frame);
       frameCount ++;
    }
private:
    cv::Scalar startColor, endColor;
    float frameRate; 
    long long frameCount = 0; 

    void updateColors(float videoTimeInSeconds) {
        double hueStart = (std::sin(videoTimeInSeconds * 0.1) + 1) * 90; // Ranges from 0 to 180
        double hueEnd = (std::sin(videoTimeInSeconds * 0.1 + 3.14159) + 1) * 90; // Offset sine wave
        cv::Mat hsvStart(1, 1, CV_8UC3, cv::Scalar(hueStart, 255, 255));
        cv::Mat hsvEnd(1, 1, CV_8UC3, cv::Scalar(hueEnd, 255, 255));
        cv::cvtColor(hsvStart, hsvStart, cv::COLOR_HSV2BGR);
        cv::cvtColor(hsvEnd, hsvEnd, cv::COLOR_HSV2BGR);
        startColor = hsvStart.at<cv::Vec3b>(0, 0);
        endColor = hsvEnd.at<cv::Vec3b>(0, 0);
    }
    void createDynamicGradient(cv::Mat &gradient) {
        cv::Mat gradientF(gradient.size(), CV_32FC3);
        for (int x = 0; x < gradientF.cols; x++) {
            double alpha = static_cast<double>(x) / (gradientF.cols - 1); 
            cv::Scalar col = startColor * (1.0 - alpha) + endColor * alpha;
            for (int y = 0; y < gradientF.rows; y++) {
                gradientF.at<cv::Vec3f>(y, x) = cv::Vec3f(static_cast<float>(col[0]), static_cast<float>(col[1]), static_cast<float>(col[2]));
            }
        }   
        gradientF.convertTo(gradient, CV_8UC3);
    }
};

class GradientBoxes : public FilterFunc {
private:
    struct BoxGradient {
        cv::Scalar startColor;
        cv::Scalar endColor;
        double shiftSpeed;
        BoxGradient() : startColor(cv::Scalar::all(0)), endColor(cv::Scalar::all(0)), shiftSpeed(0.005) {}
        void update(float elapsedTime) {
            double hueStart = fmod((std::sin(elapsedTime * shiftSpeed) + 1) * 90, 180); // Range is 0 to 180
            double hueEnd = fmod((std::sin(elapsedTime * shiftSpeed + 3.14159) + 1) * 90, 180); // Offset sine wave
            cv::Mat hsvStart(1, 1, CV_8UC3, cv::Scalar(hueStart, 255, 255));
            cv::Mat hsvEnd(1, 1, CV_8UC3, cv::Scalar(hueEnd, 255, 255));
            cv::cvtColor(hsvStart, hsvStart, cv::COLOR_HSV2BGR);
            cv::cvtColor(hsvEnd, hsvEnd, cv::COLOR_HSV2BGR);
            startColor = hsvStart.at<cv::Vec3b>(0, 0);
            endColor = hsvEnd.at<cv::Vec3b>(0, 0);
        }
    };
    std::vector<BoxGradient> gradients;
    int gridRows;
    int gridCols;
public:
    GradientBoxes(int rows, int cols, float fps) : gridRows(rows), gridCols(cols), frame_rate(fps), current_frames(0) {
        gradients.resize(gridRows * gridCols);
    }

    void init() override {
    }

    void proc(cv::Mat &frame) override {
        float elapsedTime = current_frames / frame_rate;
        for (auto& grad : gradients) {
            grad.update(elapsedTime);
        }
        int boxWidth = frame.cols / gridCols;
        int boxHeight = frame.rows / gridRows;
        cv::Mat frame_copy = frame.clone();
        for (int row = 0; row < gridRows; ++row) {
            for (int col = 0; col < gridCols; ++col) {
                cv::Rect boxRect(col * boxWidth, row * boxHeight, boxWidth, boxHeight);
                drawGradientBox(frame_copy, boxRect, gradients[row * gridCols + col]);
            }
        }
        cv::addWeighted(frame_copy, 0.5, frame, 0.5, 0.0, frame);
        current_frames++;
    }
private:
    float frame_rate;
    long long current_frames;
    void drawGradientBox(cv::Mat &frame, const cv::Rect &box, const BoxGradient &gradient) {
        for (int y = box.y; y < box.y + box.height; ++y) {
            for (int x = box.x; x < box.x + box.width; ++x) {
                double alpha = static_cast<double>(x - box.x) / box.width;
                cv::Scalar col = gradient.startColor * (1.0 - alpha) + gradient.endColor * alpha;
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(y, x);
                pixel = cv::Vec3b(static_cast<uchar>(col[0]), static_cast<uchar>(col[1]), static_cast<uchar>(col[2]));
            }
        }
    }
};

class FrameStoreSmash : public FilterFunc {
public:
    explicit FrameStoreSmash(int squareSize = 25) : gen(rd()), squareSize(squareSize), maxSquaresPerFrame(300) {}
    struct Rectangle {
        int x, y, width, height;
        Rectangle() : x{0}, y{0}, width{0}, height{0} {}
        Rectangle(int _x, int _y, int _w, int _h) : x{_x}, y{_y}, width{_w}, height{_h} {}
    };
    void init() override {
        cap_ = false;
        rects.clear();
    }
    void proc(cv::Mat &frame) override {
        if (!cap_) {
            captured = frame.clone();
            cap_ = true;
            maxSquaresPerFrame = frame.cols;
            initSquares(frame);
        }
        removeSquares();
        if (rects.empty()) {
            cap_ = false; 
            return; 
        }
        for (const auto &rect : rects) {
           if(captured.size() != frame.size()) {
                cap_ = false;
                return;
            } else {
                 copyRect(captured, frame, rect);
            }
        }
    }
    void clear() override {
        cap_ = false;
    }
private:
    bool cap_ = false;
    cv::Mat captured;
    std::vector<Rectangle> rects;
    std::random_device rd;
    std::mt19937 gen;
    int squareSize;
    int maxSquaresPerFrame; 
    void initSquares(const cv::Mat &frame) {
        int cols = frame.cols / squareSize;
        int rows = frame.rows / squareSize;
        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                rects.emplace_back(x * squareSize, y * squareSize, squareSize, squareSize);
            }
        }
    }
    void removeSquares() {
        std::shuffle(rects.begin(), rects.end(), gen); 
        int removeCount = std::uniform_int_distribution<>(1,maxSquaresPerFrame)(gen); 
        removeCount = std::min(removeCount, static_cast<int>(rects.size())); 
        rects.erase(rects.end() - removeCount, rects.end()); 
    }

    void copyRect(const cv::Mat &src, cv::Mat &dst, const Rectangle &rc) {
        cv::Rect roi(rc.x, rc.y, rc.width, rc.height);
        if (roi.x + roi.width <= src.cols && roi.y + roi.height <= src.rows) { 
            src(roi).copyTo(dst(roi));
        }
    }
};

class Flash : public FilterFunc {
public:
    Flash() : gen{rd()}, dist(0, 255) {}
    void init() override {

    }
    void proc(cv::Mat &frame) override {
        on = !on;
        if(on == false)
            return;
        cv::Scalar color(dist(gen), dist(gen), dist(gen));        
        cv::Mat image(frame.size(), CV_8UC3, color);
        frame = image;
    }
    void clear() override {}
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;
    bool on = false;
};

class Layer_0_Swap : public FilterFunc {
public:
    Layer_0_Swap() {}
    void setLayer(Layer *l_) {
        layer_ = l_;
    }
    void init() override {

    }
    void proc(cv::Mat &frame) override {
        on = !on;
        if(on == false)
            return;
        if(layer_ != nullptr && layer_->hasNext()) {
            cv::Mat resized;
            if(layer_->read(resized)) {
                cv::resize(resized, resized, frame.size());
                frame = resized;                
            }
        }
    }
    void clear() override {}
private:
    Layer *layer_ = nullptr;
    bool on = false;
};

class Layer_012_Index : public FilterFunc {
public:
    Layer_012_Index() : gen{rd()}, dist(0, 2) {
        layers.push_back(0);
        layers.push_back(1);
        layers.push_back(2);
    }

    void setLayers(Layer *l1, Layer *l2, Layer *l3) {
        layer_[0] = l1;
        layer_[1] = l2;
        layer_[2] = l3;
    }

    void setMode(int m) {
        mode = m;
    }

    void init() override { 
        index = 0;
        mode = 0;
        sindex = 0;
    }

    void clear() override { }

    void proc(cv::Mat &frame) override {
        onv = !onv;
        if(onv == false)
            return;

        if(layer_[0] != nullptr && layer_[1] != nullptr && layer_[2] != nullptr) {
            int f_pos = 0;
            switch(mode) {
                case 0: 
                f_pos = index++;
                if(index > 2) 
                    index = 0;
                break;
                case 1:
                   if(sindex >= 0&& sindex <= 2) {
                        f_pos = layers[sindex];
                   }
                   sindex++;
                   if(sindex > 2) {
                        std::shuffle(layers.begin(), layers.end(), gen);
                        sindex = 0;
                   }                    
                break;
                case 2: 
                    f_pos = dist(gen);
                break;
            }

            if(layer_[f_pos]->hasNext()) {
                cv::Mat new_l;
                if(layer_[f_pos]->read(new_l)) {
                    cv::Mat resized;
                    cv::resize(new_l, resized, frame.size());
                    frame = resized;
                    return;                    
                }
            }
        }
    }
private:
    Layer *layer_[3] = {nullptr};
    std::vector<int> layers;
    int index = 0;
    int sindex = 0;
    int mode = 0;
    bool onv = false;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;
};

class New_MedianBlend3 : public FilterFunc {
public:
    New_MedianBlend3() : gen{rd()}, dist(3, 7) {}
    
    void setLayers(Layer *_l1, Layer *_l2, Layer *_l3) {
        layer_[0] = _l1;
        layer_[1] = _l2;
        layer_[2] = _l3;
    }

    void init() override { }
    void clear() override { collection.clear(); }    
    void proc(cv::Mat &frame) override{
        if(layer_[0] == nullptr || layer_[1] == nullptr || layer_[2] == nullptr) {
            return;
        }
        cv::Mat resized[3];
        for(int j = 0; j < 3; ++j) {
            if(!layer_[j]->hasNext()) {
                return;
            }
            cv::Mat clayer;
            if(layer_[j]->read(clayer)) {
                cv::resize(clayer, resized[j], frame.size());
            }
        }
        int r = dist(gen);
        for(int m = 0; m < r; ++m) {
            cv::medianBlur(frame, frame, 5);
        }
        collection.shiftFrames(frame);     
        for(int j = 0; j < 3; ++j) {
            collection.shiftFrames(resized[j]);
        }
        if (collection.size() < collection.capacity()) return;
        for (int z = 0; z < frame.rows; ++z) {
            for (int i = 0; i < frame.cols; ++i) {
                cv::Scalar value(0, 0, 0);
                for (int j = 0; j < static_cast<int>(collection.size()); ++j) {
                    cv::Vec3b pixel = collection[j].at<cv::Vec3b>(z, i);
                    for (int q = 0; q < 3; ++q) {
                        value[q] += pixel[q];
                    }
                }
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                for(int j = 0; j < 3; ++j) {
                   int val = 1+static_cast<int>(value[j]);
                    pixel[j] = static_cast<unsigned char>(pixel[j] ^ val);
                }
            }
        }
    }
private:
    New_MatrixCollection<8> collection;
    Layer *layer_[3] = {nullptr};
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;
};

class Layer_012_AlphaBlendConcat : public FilterFunc {
public:

    Layer_012_AlphaBlendConcat() : gen{rd()}, dist(0.1, 1.0), dist_inc(0.01, 0.1), dist_max(1.5, 2.0), idist(0, 1) {}

    void setLayers(Layer *_l1, Layer *_l2, Layer *_l3) {
        layer_[0] = _l1;
        layer_[1] = _l2;
        layer_[2] = _l3;
    }

    void setRandomNot(bool n) {
        random_not = n;
    }
    void setRandomDir(bool rand_dir) {
        dir = rand_dir;
    }
    void setOverflow(bool m) {
        overflow_max = m;
    }

    void init() override {
        std::cout << "Layer_012_AlphaBlendConcat init, setting values\n";
        for(int j = 0;  j < 3; ++j) {
            if(dir == true) 
                knobs[j].initValues(dist(gen), dist_inc(gen), 0.1, dist_max(gen), idist(gen));
            else
                knobs[j].initValues(dist(gen), 0.1, 0.1, 2.0);
        }
    }
    void clear() override { init(); }
    void proc(cv::Mat &frame) override {
        if(layer_[0] == nullptr || layer_[1] == nullptr || layer_[2] == nullptr)
            return;
        cv::Mat resized[3];
        double alpha[3];
        for(int j = 0; j < 3; ++j) {
            if(!layer_[j]->hasNext())
                return;

            cv::Mat cur_frame;
            if(!layer_[j]->read(cur_frame)) 
                return;

            cv::resize(cur_frame, resized[j], frame.size());

            if(random_not == true && rand()%2 == 0)
                cv::bitwise_not(resized[j], resized[j]);

            alpha[j] = knobs[j].nextValue();
        }
        for(int z = 0; z < frame.rows; ++z) {
            for(int i = 0; i < frame.cols; ++i) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                cv::Vec3b pix[3];
                pix[0] = resized[0].at<cv::Vec3b>(z, i);
                pix[1] = resized[1].at<cv::Vec3b>(z, i);
                pix[2] = resized[2].at<cv::Vec3b>(z, i);
                for(int j = 0; j < 3; ++j) {
                    if(overflow_max == false)
                        pixel[j] = ac::wrap_cast(pixel[j]+((alpha[0]*pix[0][j]) + (alpha[1]*pix[1][j]) + (alpha[2]*pix[2][j])));
                    else 
                        pixel[j] = ac::wrap_cast( (pixel[j] * 0.4) + (( (alpha[0]*pix[0][j])*0.2 + (alpha[1]*pix[1][j])*0.2 + (alpha[2]*pix[2][j])*0.2 ) * 0.9 ) );
                }
            }
        }
    }
private:
    Layer *layer_[3] = {nullptr};
    Knob knobs[3];
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dist, dist_inc, dist_max;
    std::uniform_int_distribution<> idist;
    bool dir = false;
    bool overflow_max  = false;
    bool random_not = false;
};

class PencilSketchFilter : public FilterFunc {
public:
    PencilSketchFilter() {}
    void init() override {}
    void proc(cv::Mat &frame) override {
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::Mat grayInv;
        cv::bitwise_not(gray, grayInv);
        cv::Mat blurImg;
        cv::GaussianBlur(grayInv, blurImg, cv::Size(21, 21), 0, 0);
        cv::Mat sketch;
        cv::divide(gray, 255-blurImg, sketch, 256.0);
        cv::cvtColor(sketch, frame, cv::COLOR_GRAY2BGR);
    }
    void clear() override {}
private:
};

class OldPhotograph : public FilterFunc {
public:
    OldPhotograph() {}
    void init() override {

    }
    void proc(cv::Mat &frame) override {
       Sepia(frame);
       Vignette(frame);
    }
    void clear() override { }
private:
    void Sepia(cv::Mat &image) {
        if (image.empty()) {
            return;
        }
        for (int y = 0; y < image.rows; y++) {
            for (int x = 0; x < image.cols; x++) {
                cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
                uchar blue = pixel[0];
                uchar green = pixel[1];
                uchar red = pixel[2];
                uchar newRed = std::min(255, int(0.393 * red + 0.769 * green + 0.189 * blue));
                uchar newGreen = std::min(255, int(0.349 * red + 0.686 * green + 0.168 * blue));
                uchar newBlue = std::min(255, int(0.272 * red + 0.534 * green + 0.131 * blue));
                image.at<cv::Vec3b>(y, x) = cv::Vec3b(newBlue, newGreen, newRed);
           }
        }
    }
    void Vignette(cv::Mat& src) {
        int w = src.cols;
        int h = src.rows;
        cv::Mat mask(src.size(), CV_32F, cv::Scalar(1));
        cv::Point center = cv::Point(w / 2, h / 2);
        double maxDist = std::sqrt(center.x*center.x + center.y*center.y);
        for(int i = 0; i < h; ++i) {
            for(int j = 0; j < w; ++j) {
                double dist = std::sqrt((i - center.y) * (i - center.y) + (j - center.x) * (j - center.x));
                double scale = 0.5 * (1.0 + std::cos(dist/maxDist * 3.14159265));
                mask.at<float>(i,j) = std::max(scale, 0.0);
            }
        }
        cv::Mat srcFloat;
        src.convertTo(srcFloat, CV_32FC3);
        std::vector<cv::Mat> channels(3);
        cv::split(srcFloat, channels);
        for (auto& channel : channels) {
            channel = channel.mul(mask);
        }
        cv::merge(channels, srcFloat);
        srcFloat.convertTo(src, CV_8UC3);
    }
};

class FishEyeLens : public FilterFunc {
public:
    FishEyeLens() = default;
    FishEyeLens(double d) {
        distortion_.initValues(0.0001,d, 0.0001, 2.0);
    }
    void setFixed(double d) {
        distortion_.initValues(d, 0.001, 0.0001, 2.0);
        fixed_ = true;
    }
    void init() override {}
    void proc(cv::Mat &frame) override {
        frame = fisheyeEffect(frame);
    }
    void clear() override {}

private:

    cv::Mat fisheyeEffect(const cv::Mat &inputImage) {
        cv::Mat outputImage = cv::Mat::zeros(inputImage.size(), inputImage.type());
        double centerX = inputImage.cols / 2.0;
        double centerY = inputImage.rows / 2.0;
        double radius = std::min(centerX, centerY);
        double distortion = (fixed_ == true) ? distortion_.value() : distortion_.nextValue();
        for (int y = 0; y < inputImage.rows; y++) {
            for (int x = 0; x < inputImage.cols; x++) {
                double deltaX = (x - centerX) / radius;
                double deltaY = (y - centerY) / radius;
                double distanceSquared = deltaX * deltaX + deltaY * deltaY;
                double factor = 1.0 / (1.0 + distortion * distanceSquared);
                int srcX = std::clamp(int(centerX + deltaX * factor * radius), 0, inputImage.cols - 1);
                int srcY = std::clamp(int(centerY + deltaY * factor * radius), 0, inputImage.rows - 1);
                outputImage.at<cv::Vec3b>(y, x) = inputImage.at<cv::Vec3b>(srcY, srcX);
            }
        }
        return outputImage;
    }
    Knob distortion_; 
    bool fixed_ = false;
};

class FunhouseMirror : public FilterFunc {
public:
    FunhouseMirror() {
        frequency.initValues(2.0, 0.2, 2.0, 10.0);
        amp.initValues(20, 1, 20, 40);
        grow_v.initValues(2.0, 0.2, 2.0, 10.0);
        grow_v.setMaxGrow(15.0);
    }
    void init() override {}
    void proc(cv::Mat &frame) override { 
        cv::Mat output;
        switch(effect) {
            case 0:
                mirrorEffectHorizontal(frame, output);
            break;
            case 1:
               mirrorEffectVertical(frame, output);
            break;
        }
        frame = output;
    }
    void setEffect(int e) { effect = e; }
    void setGrowType(int t) { grow_type = t; }
    void clear() override {}
    void setSpeed(double d) {
        frequency.initValues(2.0, d, 2.0, 10.0);
        amp.initValues(20, 1, 20, 40);
        grow_v.initValues(2.0, d, 2.0, 10.0);
        grow_v.setMaxGrow(15.0);
    }
private:
    void mirrorEffectHorizontal(cv::Mat &src, cv::Mat &dst) {
        if (src.empty()) {
            return;
        }
        dst = src.clone();
        double waveFrequency = (grow_type == 0) ? frequency.nextValue() : grow_v.nextValue(); 
        double waveAmplitude = amp.nextValue(); 
        for (int y = 0; y < src.rows; y++) {
            for (int x = 0; x < src.cols; x++) {
                int newX = x + static_cast<int>(std::sin(static_cast<double>(y) / src.rows * waveFrequency * 2.0 * CV_PI) * waveAmplitude);
                newX = std::min(std::max(newX, 0), src.cols - 1);
                dst.at<cv::Vec3b>(y, newX) = src.at<cv::Vec3b>(y, x);
            }
        }
    }
    void mirrorEffectVertical(cv::Mat &src, cv::Mat &dst) {
        if (src.empty()) {
            return;
        }
        dst = src.clone();
        double waveFrequency = (grow_type == 0) ? frequency.nextValue() : grow_v.nextValue();
        double waveAmplitude = amp.nextValue(); 
        for (int y = 0; y < src.rows; y++) {
            for (int x = 0; x < src.cols; x++) {
                int newY = y + static_cast<int>(std::sin(static_cast<double>(x) / src.cols * waveFrequency * 2.0 * CV_PI) * waveAmplitude);
                newY = std::min(std::max(newY, 0), src.rows - 1);
                dst.at<cv::Vec3b>(newY, x) = src.at<cv::Vec3b>(y, x);
            }
        }
    }
    Knob frequency;  
    KnobT<int> amp;
    int effect = 0, grow_type = 0;
    KnobGrow grow_v;
};

class RGB_Shift : public FilterFunc {
public:
    RGB_Shift() : gen{rd()}, dist(30, 40) {}
    void init() override { 
        shift.initValues(dist(gen), 1.0, 30.0, 40.0);
    }

    void proc(cv::Mat &frame) override {
        if(frame.cols < 240)
            return;
        cv::Mat frame_copy = frame.clone();
        double value = shift.value();
        for(int z = 0; z < frame.rows; ++z) {
            for(int i = 0; i < frame.cols; ++i) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                int shifted_val = i + value;
                if (shifted_val >= frame.cols) 
                    continue;
                cv::Vec3b pix = frame_copy.at<cv::Vec3b>(z, shifted_val);
                pixel[index] = pix[index];
            }
        }
        if(++index > 2) 
            index = 0;
    }
    void clear() override {
        init();
    }
private:
    Knob shift;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;
    int index = 0;
};

class CropEdges : public FilterFunc {
public:
    CropEdges() {}
    void init() override { }
    void proc(cv::Mat &frame) override { 
        cv::Mat frame_copy;
        if(!frame.empty()) {
            int col_expand = frame.cols/4;
            int row_expand = frame.rows/4;
            cv::resize(frame, frame_copy, cv::Size(frame.cols+(col_expand), frame.rows+(row_expand)));
            for(int z = 0; z < frame.rows; ++z) {
                for(int i = 0; i < frame.cols; ++i) {
                    if(i < frame.cols && i+col_expand < frame_copy.cols && z < frame.rows && z < frame_copy.rows)
                        frame.at<cv::Vec3b>(z, i)  = frame_copy.at<cv::Vec3b>(z, i+(col_expand/2));
                }
            }
        }
    }
    void clear() override {}
};

class Fractal : public FilterFunc {
public:
    Fractal() = default;
    void init() override {
        zoom_knob.initValues(1.0, 100.0, 1.0, 25000.0);
        fractal.initParameters(-0.743643887032151,0.142625924205330,1.0,120,4);
    }

    void initValues(double z_real, double z_imag, double z_zoom, int iter, double speed, double z_max) {
        fractal.initParameters(z_real, z_imag, z_zoom, iter, 4);
        zoom_knob.initValues(z_zoom, speed, 1.0, z_max);
    }

    void resize(bool resize_frame) {
        resize_ = resize_frame;
    }
    void proc(cv::Mat &frame) override {
        cv::Mat frac_frame;
        fractal.resetPalette();
        if(resize_ == false) {
            frac_frame.create(frame.size(), CV_8UC3);
            fractal.setZoom(zoom_knob.nextValue());
            fractal.draw(frac_frame); // uses threads
            cv::addWeighted(frame, 0.5, frac_frame, 0.5, 0, frame);
        } else {
            frac_frame.create(cv::Size(640, 360), CV_8UC3);
            fractal.setZoom(zoom_knob.nextValue());
            fractal.draw(frac_frame); // uses threads
            cv::resize(frac_frame, frac_frame, frame.size());
            cv::addWeighted(frame, 0.5, frac_frame, 0.5, 0, frame);
        }
    }  
    void clear() override {}
private:
    cv_fract::CV_Fractal fractal;
    Knob zoom_knob;
    bool resize_ = false;
};

class PopArt : public FilterFunc {
public:
    PopArt(float sat_mult = 1.5f, int quant_div = 64) : sat_mult(sat_mult), quant_div(quant_div) {}
    void init() override {}
    void proc(cv::Mat& frame) override {
        if (!frame.empty()) {
            frame = popArtEffect(frame);
        }
    }
    void clear() override {}
private:
    float sat_mult;
    int quant_div;
    cv::Mat popArtEffect(const cv::Mat& src) {
        cv::Mat img, dst, color_tf;
        cv::cvtColor(src, img, cv::COLOR_BGR2HSV);
        img = img / quant_div * quant_div + quant_div / 2;
        std::vector<cv::Mat> hsv_ch(3);
        cv::split(img, hsv_ch);
        hsv_ch[1] = cv::min(hsv_ch[1] * sat_mult, 255.0f);
        cv::merge(hsv_ch, color_tf);
        cv::cvtColor(color_tf, dst, cv::COLOR_HSV2BGR);
        return dst;
    }
};

class SlitScan : public FilterFunc {
public:
    SlitScan(int slitHeight = 1, int outputWidthx = 640, int outputHeightx= 480) : slitHeight(slitHeight), outputWidth(outputWidthx), outputHeight(outputHeightx), currentPosition(0) {}
    void init() override {
        currentPosition = 0;
        if(!slitScanImg.empty())
            slitScanImg.release();
    }
    void proc(cv::Mat& frame) override {
        if (frame.empty()) return;
        cv::Size orig = frame.size();
        cv::resize(frame, frame, cv::Size(outputWidth, outputHeight));
        if(slitScanImg.empty()) {
            slitScanImg = frame.clone();
        }
        cv::Rect roi(0, currentPosition, frame.cols, slitHeight);
        if (currentPosition + slitHeight <= frame.rows) { 
            cv::Mat slit = frame(roi);
            slit.copyTo(slitScanImg(roi));
            currentPosition += slitHeight;
        } else {
            currentPosition = 0; 
        }
        slitScanImg.copyTo(frame);
        cv::resize(frame, frame, orig);
    }
    void clear() override { init(); }
private:
    int slitHeight;
    int outputWidth;
    int outputHeight;
    int currentPosition;
    cv::Mat slitScanImg; 
};

class Ripple : public FilterFunc {
public:
    Ripple(float wavelength = 20.0f, float amplitude = 10.0f, float phaseShift = 0.0f) {
        wave_length.initValues(wavelength, 0.1f, 1.0f, 30.0f);
        amp.initValues(amplitude, 0.1f, 1.0f, 30.0f);
        phase_shift.initValues(phaseShift, 0.1f, 0.0f, 3.0f);
    }
    void init() override {}
    void proc(cv::Mat &frame) override {
        if (!frame.empty()) {
            ripple(frame);
        }
    }
    void clear() override {}

private:
    KnobT<float> wave_length;
    KnobT<float> amp;
    KnobT<float> phase_shift;

    void ripple(cv::Mat &frame) {
        float wavelength = wave_length.nextValue();
        float amplitude = amp.nextValue();
        float phaseShift = phase_shift.nextValue();
        cv::Mat dst = frame.clone();
        int rows = frame.rows;
        int cols = frame.cols;
        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                float newX = x + amplitude * std::sin(2.0 * CV_PI * y / wavelength + phaseShift);
                float newY = y + amplitude * std::sin(2.0 * CV_PI * x / wavelength + phaseShift);
                if (newX >= 0 && newX < cols && newY >= 0 && newY < rows) {
                    cv::Vec3b pixelValue = frame.at<cv::Vec3b>(cv::Point(newX, newY));
                    dst.at<cv::Vec3b>(cv::Point(x, y)) = pixelValue;
                }
            }
        }
        frame = std::move(dst);
    }
};

class VanGoghEffect : public FilterFunc {
public:
    VanGoghEffect() {}
    void init() override {}
    void proc(cv::Mat &frame) override {
        if (!frame.empty()) {
            vanGoghEffect(frame);
            starryNightColors(frame);
        }
    }
    void clear() override {}
private:
    void vanGoghEffect(cv::Mat &frame) {
        cv::Mat img, edges, edgeEnhanced;
        cv::bilateralFilter(frame, img, 9, 75, 75);
        cv::Canny(img, edges, 100, 200);
        cv::cvtColor(edges, edges, cv::COLOR_GRAY2BGR);
        edgeEnhanced = img - edges;
        frame = edgeEnhanced;
    }
    void starryNightColors(cv::Mat &frame) {
        cv::Mat hsvImage;
        cv::cvtColor(frame, hsvImage, cv::COLOR_BGR2HSV);
        for (int y = 0; y < hsvImage.rows; ++y) {
            for (int x = 0; x < hsvImage.cols; ++x) {
                cv::Vec3b &pixel = hsvImage.at<cv::Vec3b>(y, x);
                if (pixel[0] >= 90 && pixel[0] <= 140) { 
                    pixel[1] = cv::saturate_cast<uchar>(pixel[1] * 1.5); 
                    pixel[2] = cv::saturate_cast<uchar>(std::min(255.0, pixel[2] * 1.1));
                }
                if (pixel[0] >= 20 && pixel[0] <= 30) { 
                    pixel[1] = cv::saturate_cast<uchar>(pixel[1] * 1.5); 
                    pixel[2] = cv::saturate_cast<uchar>(std::min(255.0, pixel[2] * 1.2)); 
                }
            }
        }
        cv::cvtColor(hsvImage, frame, cv::COLOR_HSV2BGR);
        frame.convertTo(frame, -1, 1.3, 15); 
    }   
};

class PixelSort_RGB : public FilterFunc {
public:
    PixelSort_RGB() {}
    void init() override {}
    void proc(cv::Mat &frame) override {
        pixelSort(frame);
    }
    void clear() override {}
private:
    void pixelSort(cv::Mat &frame) {
        for(int z = 0; z < frame.rows; ++z) {
            std::vector<cv::Vec3b> pixels;
            for(int i = 0; i < frame.cols; ++i) {
                pixels.push_back(frame.at<cv::Vec3b>(z, i));
            }
            std::sort(pixels.begin(), pixels.end(), [](cv::Vec3b &v1, cv::Vec3b &v2) {
                int len1 = v1[0] + v1[1] + v1[2];
                int len2 = v2[0] + v2[1] + v2[2];
                return len1 < len2;
            });
            for(int i = 0; i < frame.cols; ++i) {
                frame.at<cv::Vec3b>(z, i) = pixels[i];
            }            
        }
    }
};

class KaleidoscopeEffect : public FilterFunc {
public:
    KaleidoscopeEffect(int segments = 8) : segments(segments) {}
    void init() override {}
    void proc(cv::Mat &frame) override {
        if (!frame.empty()) {
            applyKaleidoscopeEffect(frame);
        }
    }
    void clear() override {}

private:
    int segments; 
    void applyKaleidoscopeEffect(cv::Mat &frame) {
        cv::Mat result = frame.clone();
        double angle = 360.0 / segments;
        cv::Point center(frame.cols/2, frame.rows/2 );
        int radius = std::min(center.x, center.y);
        cv::Mat mask = cv::Mat::zeros(frame.size(), CV_8U);
        std::vector<cv::Point> polyPoints;
        polyPoints.push_back(center);
        polyPoints.push_back(cv::Point(center.x + radius * cos((-angle/2) * CV_PI / 180.0),
                                       center.y + radius * sin((-angle/2) * CV_PI / 180.0)));
        polyPoints.push_back(cv::Point(center.x + radius * cos((angle/2) * CV_PI / 180.0),
                                       center.y + radius * sin((angle/2) * CV_PI / 180.0)));

        cv::fillConvexPoly(mask, polyPoints, cv::Scalar(255));
        for (int i = 0; i < segments; ++i) {
            cv::Mat rotated, rotatedMask;
            float currentAngle = (angle * i) + (angle / 2); 
            cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, currentAngle, 1.0);
            cv::warpAffine(frame, rotated, rotationMatrix, frame.size());
            cv::warpAffine(mask, rotatedMask, rotationMatrix, mask.size());
            rotated.copyTo(result, rotatedMask);
        }
        frame = result;
    }
};

class TwirlEffect : public FilterFunc {
public:
    TwirlEffect(cv::Point2f center = cv::Point2f(-1, -1)) : center(center) {
        strength_x.initValues(1.0, 0.1, -30.0, 30.0);
    }
    void init() override {}
    void proc(cv::Mat &frame) override {
        if (!frame.empty()) {
            applyTwirlEffect(frame);
        }
    }
    void clear() override {}

private:
    Knob strength_x; 
    cv::Point2f center;

    void applyTwirlEffect(cv::Mat &frame) {
        float strength = strength_x.nextValue();
        if (center.x == -1 && center.y == -1) {
            center = cv::Point2f(frame.cols / 2.0f, frame.rows / 2.0f);
        }
        cv::Mat result = frame.clone();
        for (int y = 0; y < frame.rows; y++) {
            for (int x = 0; x < frame.cols; x++) {
                cv::Point2f p(x, y);
                cv::Point2f delta = p - center;
                float radius = cv::sqrt(delta.x*delta.x + delta.y*delta.y);
                float angle = std::atan2(delta.y, delta.x) + strength * (radius / std::max(frame.cols, frame.rows));
                int srcX = cv::saturate_cast<int>(center.x + radius * std::cos(angle));
                int srcY = cv::saturate_cast<int>(center.y + radius * std::sin(angle));
                if (srcX >= 0 && srcX < frame.cols && srcY >= 0 && srcY < frame.rows) {
                    result.at<cv::Vec3b>(y, x) = frame.at<cv::Vec3b>(srcY, srcX);
                }
            }
        }
        frame = result;
    }
};

class InfiniteZoom : public FilterFunc {
public:
    InfiniteZoom()  {
            zoom_f.initValues(1.0f, 0.01f, 1.0f, 2.0f);
    }
    void init() override {}
    void proc(cv::Mat &frame) override {
        if (frame.empty()) return;
        applyInfiniteZoom(frame);
    }
    void clear() override {}

private:
    float zoomFactor;
    KnobT<float> zoom_f;

    void applyInfiniteZoom(cv::Mat &frame) {
        cv::Mat originalFrame = frame.clone();
        cv::Mat resizedFrame, croppedFrame;
        zoomFactor = zoom_f.nextValue();        
        cv::Size newSize(static_cast<int>(originalFrame.cols / zoomFactor), static_cast<int>(originalFrame.rows / zoomFactor));
        cv::resize(originalFrame, resizedFrame, newSize);
        int offsetX = (resizedFrame.cols - originalFrame.cols) / 2;
        int offsetY = (resizedFrame.rows - originalFrame.rows) / 2;
        offsetX = std::max(offsetX, 0);
        offsetY = std::max(offsetY, 0);
        cv::Rect roi(offsetX, offsetY, std::min(originalFrame.cols, resizedFrame.cols), std::min(originalFrame.rows, resizedFrame.rows));
        croppedFrame = resizedFrame(roi);
        if (croppedFrame.size() != originalFrame.size()) {
            croppedFrame.copyTo(originalFrame(cv::Rect(0, 0, croppedFrame.cols, croppedFrame.rows)));
        } else {
            croppedFrame.copyTo(originalFrame);
        }
        cv::addWeighted(frame, 0.5, originalFrame, 0.5, 0.0, frame);
    }
};

class ColorMap : public FilterFunc {
public:
    ColorMap(int color_map = 0) : color_map(color_map) { }    
    void init() override {}
    void proc(cv::Mat &frame) override {
        cv::Mat gray, colored;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::applyColorMap(gray, colored, color_map);
        frame = colored;
    }
    void clear() override {}
private:
    int color_map = 0;
};

class CrystalBallEffect : public FilterFunc {
public:
    CrystalBallEffect(float radius = 0.5, cv::Point2f center = cv::Point2f(-1, -1), bool increase_ = false) 
        : radius(radius), center(center) {
        if (center == cv::Point2f(-1, -1)) {
            centerSet = false;
        } else {
            centerSet = true;
        }
        rad.initValues(radius, 0.01, 0.1, 2.0);
        increase = increase_;
    }
    void init() override {}
    void proc(cv::Mat &frame) override {
        if (!frame.empty()) {
            applyCrystalBallEffect(frame);
        }
    }
    void clear() override {}
private:
    KnobT<float> rad;
    float radius; 
    cv::Point2f center; 
    bool centerSet;
    bool increase;

    void applyCrystalBallEffect(cv::Mat &frame) {
        radius = (increase == true) ? rad.nextValue() : rad.value();
        if (!centerSet) {
            center = cv::Point2f(frame.cols / 2.0f, frame.rows / 2.0f);
        }
        cv::Mat result = frame.clone();
        float maxRadius = std::min(frame.cols, frame.rows) * radius;
        for (int y = 0; y < frame.rows; ++y) {
            for (int x = 0; x < frame.cols; ++x) {
                cv::Point2f p(x, y);
                cv::Point2f delta = p - center;
                float dist = cv::sqrt(delta.x * delta.x + delta.y * delta.y);
                if (dist < maxRadius) {
                    float scaleFactor = 1.0 - std::sqrt(dist / maxRadius);
                    int newX = static_cast<int>(center.x + delta.x * scaleFactor);
                    int newY = static_cast<int>(center.y + delta.y * scaleFactor);
                    newX = std::min(std::max(newX, 0), frame.cols - 1);
                    newY = std::min(std::max(newY, 0), frame.rows - 1);
                    result.at<cv::Vec3b>(y, x) = frame.at<cv::Vec3b>(cv::Point(newX, newY));
                }
            }
        }
        frame = result;
    }
};


class StretchSqueezeEffect : public FilterFunc {
public:
    StretchSqueezeEffect(float strength = 0.5) : strength(strength) {
        strength_.initValues(strength, 0.01, 0.1, 2.0);

    }
    void init() override {}
    void proc(cv::Mat &frame) override {
        if (!frame.empty()) {
            applyStretchSqueezeEffect(frame);
        }
    }
    void clear() override {}

private:
    float strength; 
    KnobT<float> strength_;

    void applyStretchSqueezeEffect(cv::Mat &frame) {
        strength = strength_.nextValue();
        cv::Mat result = frame.clone();
        int center_y = frame.rows / 2;

        for (int y = 0; y < frame.rows; ++y) {
            float factor = 1 + strength * (static_cast<float>(y - center_y) / center_y);
            for (int x = 0; x < frame.cols; ++x) {
                int srcY = static_cast<int>(center_y + (y - center_y) / factor);
                if (srcY >= 0 && srcY < frame.rows) {
                    result.at<cv::Vec3b>(y, x) = frame.at<cv::Vec3b>(srcY, x);
                }
            }
        }
        frame = result;
    }
};

class RGB_Real_Increase : public FilterFunc {
public:
    RGB_Real_Increase() : gen{rd()}, dist(1.0, 255.0), dist_int(0, 1) {}

    void initRGB() {
        for(int i = 0; i < 3; ++i) {
            rgb[i].initValues(dist(gen), 0.1, 1.0, 255.0,dist_int(gen));
        }
    }

    void init() override {
        initRGB();
    }
    
    void proc(cv::Mat &frame) override {
        double values[3] = { rgb[0].nextValue(), rgb[1].nextValue(), rgb[2].nextValue() };
        for(int z = 0; z < frame.rows; ++z) {
            for(int i = 0; i < frame.cols; ++i) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                for(int q = 0; q < 3; ++q) {
                    pixel[q] = cv::saturate_cast<uchar>(values[q]+pixel[q]);
                }
            }
        }    
    }
    void clear() override {
        initRGB();
    }
private:
    Knob rgb[3];
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dist;
    std::uniform_int_distribution<> dist_int;

};

class MirrorBallEffect : public FilterFunc {
public:
    MirrorBallEffect() {}
    void init() override {}
    void proc(cv::Mat &frame) override {
        if (!frame.empty()) {
            applyMirrorBallEffect(frame);
        }
    }
    void clear() override {}
private:
    void applyMirrorBallEffect(cv::Mat &frame) {
        cv::Mat output = frame.clone();
        cv::Point2f center(frame.cols / 2.0f, frame.rows / 2.0f);
        float maxDist = cv::norm(center); 

        for (int y = 0; y < frame.rows; y++) {
            for (int x = 0; x < frame.cols; x++) {
                cv::Point2f delta(x - center.x, y - center.y);
                float dist = cv::norm(delta);
                float normDist = dist / maxDist;
                float scaleFactor = 1.0f - std::cos(normDist * CV_PI / 2.0f);
                cv::Point2f srcPos = center + scaleFactor * delta;
                srcPos.x = cv::min(cv::max(srcPos.x, 0.0f), static_cast<float>(frame.cols - 1));
                srcPos.y = cv::min(cv::max(srcPos.y, 0.0f), static_cast<float>(frame.rows - 1));
                cv::Vec3b color = frame.at<cv::Vec3b>(cv::Point(static_cast<int>(srcPos.x), static_cast<int>(srcPos.y)));
                output.at<cv::Vec3b>(y, x) = color;
            }
        }

        frame = output;
    }
};

class MorphologicalWarpEffect : public FilterFunc {
public:
    MorphologicalWarpEffect() {}
    void init() override {
        warp.initValues(5, 1, 5, 50);
    }
    void proc(cv::Mat &frame) override {
        if (!frame.empty()) {
            applyMorphologicalWarp(frame);
        }
    }
    void clear() override {}

private:
    void applyMorphologicalWarp(cv::Mat &frame) {
        cv::Mat warped;
        int morph_size = warp.nextValue(); 
        cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE,
                      cv::Size(2 * morph_size + 1, 2 * morph_size + 1),
                      cv::Point(morph_size, morph_size));
        cv::erode(frame, warped, element);
        cv::dilate(warped, warped, element); 
        double alpha = 0.5;
        cv::addWeighted(frame, alpha, warped, 1 - alpha, 0.0, frame);
    }

    KnobT<int> warp;

};

class InfraredEffect : public FilterFunc {
public:
    InfraredEffect() {}
    void init() override {}
    void proc(cv::Mat &frame) override {
        if (!frame.empty()) {
            applyInfraredEffect(frame);
        }
    }
    void clear() override {}

private:
    void applyInfraredEffect(cv::Mat &frame) {
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::Mat inverted = 255 - gray;
        cv::applyColorMap(inverted, frame, cv::COLORMAP_PINK);
        frame.convertTo(frame, -1, 1.5, 0); 
    }
};

class StarburstEffect : public FilterFunc {
public:
    StarburstEffect(cv::Point lightSource = cv::Point(-1, -1), int intensity = 100) 
        : lightSource(lightSource), intensity(intensity) {}
    void init() override {}
    void proc(cv::Mat &frame) override {
        if (!frame.empty()) {
            applyStarburstEffect(frame);
        }
    }
    void clear() override {}
private:
    cv::Point lightSource; 
    int intensity;
    void applyStarburstEffect(cv::Mat &frame) {
        if (lightSource.x == -1 && lightSource.y == -1) {
          lightSource = cv::Point(frame.cols - 50, 50); 
        }
        intensity = std::abs(std::sin(cv::getTickCount() / cv::getTickFrequency()) * 1200);
        cv::Mat overlay = cv::Mat::zeros(frame.size(), frame.type());
        double radius = intensity;
        cv::circle(overlay, lightSource, radius, cv::Scalar(255, 255, 255), -1, cv::LINE_AA);
        cv::addWeighted(frame, 0.5, overlay, 0.5, 0, frame);
    }
};

class LensFlareEffect : public FilterFunc {
public:
    LensFlareEffect(cv::Point lightSource = cv::Point(-1, -1), int intensity = 100)
        : lightSource(lightSource), intensity(intensity) {
            intense.initValues(intensity, 1, intensity, 300);
        }

    void init() override {}
    void proc(cv::Mat &frame) override {
        if (!frame.empty()) {
            applyLensFlareEffect(frame);
        }
    }
    void clear() override {}

private:
    cv::Point lightSource;
    int intensity;
    KnobT<int> intense;

    void applyLensFlareEffect(cv::Mat &frame) {
        cv::Mat source = frame.clone();
        intensity = intense.nextValue();
        if (lightSource.x == -1 && lightSource.y == -1) {
            lightSource = cv::Point(frame.cols / 4, frame.rows / 4);
        }
        addGlow(frame, lightSource, intensity);
        addStreaks(frame, lightSource, intensity, 4); 
        cv::addWeighted(frame, 0.5, source, 0.5, 0, frame);
    }

    void addGlow(cv::Mat &frame, cv::Point source, int intensity) {
        float radius = intensity * 2.0f; 
        cv::circle(frame, source, radius, cv::Scalar(255, 255, 255), -1, cv::LINE_AA);
    }

    void addStreaks(cv::Mat &frame, cv::Point source, int intensity, int count) {
        float length = intensity * 5.0f; 
        float angleStep = CV_PI * 2 / count;
        for (int i = 0; i < count; ++i) {
            float angle = i * angleStep;
            cv::Point end(source.x + length * cos(angle), source.y + length * sin(angle));
            cv::line(frame, source, end, cv::Scalar(255, 255, 255), intensity / 20, cv::LINE_AA); 
        }
    }
};

class AnimatedColorMapEffect : public FilterFunc {
public:
    AnimatedColorMapEffect(int max = 10) : max_maps{max} , map_index{0} {}
    void init() override {}
    void proc(cv::Mat &frame) override { 
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::Mat mapped;
        cv::applyColorMap(gray, mapped, map_index);
        ++map_index;
        if(map_index > max_maps)
            map_index = 0;
    
       frame = mapped;
    }
    void clear() override { }
private:
    int max_maps, map_index;
};

class BackgroundSubtractionFilter : public FilterFunc {
public:
    BackgroundSubtractionFilter(bool blend) : blend{blend} {
        pMOG2 = cv::createBackgroundSubtractorMOG2();
    }
    
   void init() override {}
    
  void proc(cv::Mat &frame) override {
        cv::Mat fgMask;
        pMOG2->apply(frame, fgMask, learningRate);
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7, 7));
        cv::dilate(fgMask, fgMask, kernel, cv::Point(-1, -1), 2);
        cv::morphologyEx(fgMask, fgMask, cv::MORPH_CLOSE, kernel);
        cv::medianBlur(fgMask, fgMask, 5);
        cv::Mat foreground;
        frame.copyTo(foreground, fgMask);
        if(blend)
            cv::addWeighted(frame, 0.5, foreground, 0.5, 0, frame);
        else
             frame = foreground;
    }

    
    void clear() override {}

private:
    cv::Ptr<cv::BackgroundSubtractorMOG2> pMOG2;
    double learningRate = -1; 
    bool blend = false;
};

class AugmentedSketchesEffect : public FilterFunc {
public:
    AugmentedSketchesEffect() : lastPosition(-1, -1) {}
    void init() override {}
    void proc(cv::Mat &frame) override {
        cv::Mat sketchFrame = createSketch(frame);
        frame = sketchFrame; 
    }
    void clear() override {}
private:
    cv::Point lastPosition;
    cv::Mat createSketch(const cv::Mat &frame) {
        cv::Mat gray, edges, dilatedEdges, sketchFrame;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(gray, gray, cv::Size(5, 5), 0);
        cv::Canny(gray, edges, 30, 90);
        cv::Mat dilationKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        cv::dilate(edges, dilatedEdges, dilationKernel);
        cv::bitwise_not(dilatedEdges, edges);
        cv::cvtColor(edges, sketchFrame, cv::COLOR_GRAY2BGR);
        return sketchFrame;
    }
};

class MultipleExposureEffect : public FilterFunc {
public:
    MultipleExposureEffect(size_t bufferLength = 4) : bufferLength(bufferLength) {}
    void init() override {}
    void proc(cv::Mat &frame) override {
        addToBuffer(frame);
        frame = blendBuffer();
    }
    void clear() override {
        frameBuffer.clear();
    }

private:
    std::deque<cv::Mat> frameBuffer;
    size_t bufferLength;

    void addToBuffer(const cv::Mat &frame) {
        cv::Mat currentFrame;
        frame.copyTo(currentFrame);
        if (frameBuffer.size() >= bufferLength) {
            frameBuffer.pop_front();
        }
        frameBuffer.push_back(currentFrame);
    }

    cv::Mat blendBuffer() {
        cv::Mat blended = cv::Mat::zeros(frameBuffer.front().size(), frameBuffer.front().type());
        float weight = 1.0f / static_cast<float>(frameBuffer.size());
        for (const auto& frame : frameBuffer) {
            cv::addWeighted(blended, 1.0, frame, weight, 0.0, blended);
        }
        return blended;
    }
};


void add_layer_filters(Layer&,Layer&,Layer&);

#endif
