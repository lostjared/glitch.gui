#ifndef _LAYER_FILTER_H_
#define _LAYER_FILTER_H_

#include"acidcam/ac.h"
#include "../new_filter.hpp"
#include "../layer.hpp"
#include "../lfo.hpp"
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
                        if(pix1[0] < 4 && pix1[1] < 4 && pix1[2] < 4) {
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
    Knob amp;
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
    Knob amp;
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
private:
    Layer *layer_ = nullptr;
    cv::Mat newBg; 
    void backgroundReplacement(const cv::Mat& src, cv::Mat& dst) {
        cv::Mat hsv;
        cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
        cv::Scalar lowerGreen(35, 50, 50);
        cv::Scalar upperGreen(85, 255, 255);
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
    Layer_0_GlitchBleed() : gen(rd()), dist(1, 4), distRow(0, 5), distHeight(1, 75) {
        init();
    }

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
        for (int z = y1; z < y1 + y2; ++z) {
            for (int i = offset_x; i < frame.cols; ++i) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                const cv::Vec3b &pix2 = cp.at<cv::Vec3b>(z, i);
                for (int q = 0; q < 3; ++q) {
                    pixel[q] = static_cast<uchar>(alpha * pixel[q] + invAlpha * pix2[q]);
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
    ColorGradientShift() {
        startColor = cv::Scalar(255, 0, 0); 
        endColor = cv::Scalar(0, 0, 255); 
    }
    void init() override {}
    void clear() override {}
    void proc(cv::Mat &frame) override {
        updateColors();
        cv::Mat gradient(frame.size(), CV_8UC3);
        createDynamicGradient(gradient);
        cv::addWeighted(frame, 0.5, gradient, 0.5, 0.0, frame);
    }
private:
    cv::Scalar startColor, endColor;
    void updateColors() {
        auto time = std::chrono::system_clock::now();
        auto since_epoch = time.time_since_epoch();
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(since_epoch).count();
        double hueStart = (std::sin(seconds * 0.1) + 1) * 90; 
        double hueEnd = (std::sin(seconds * 0.1 + 3.14159) + 1) * 90; 
        cv::Mat hsvStart(1, 1, CV_8UC3, cv::Scalar(hueStart, 255, 255));
        cv::Mat hsvEnd(1, 1, CV_8UC3, cv::Scalar(hueEnd, 255, 255));
        cv::cvtColor(hsvStart, hsvStart, cv::COLOR_HSV2BGR);
        cv::cvtColor(hsvEnd, hsvEnd, cv::COLOR_HSV2BGR);
        startColor = hsvStart.at<cv::Vec3b>(0, 0);
        endColor = hsvEnd.at<cv::Vec3b>(0, 0);
    }
    void createDynamicGradient(cv::Mat &gradient) {
        for (int x = 0; x < gradient.cols; x++) {
            double alpha = static_cast<double>(x) / gradient.cols;
            cv::Scalar col = startColor * (1.0 - alpha) + endColor * alpha;
            for (int y = 0; y < gradient.rows; y++) {
                gradient.at<cv::Vec3b>(y, x) = cv::Vec3b(static_cast<uchar>(col[0]), static_cast<uchar>(col[1]), static_cast<uchar>(col[2]));
            }
        }
    }
};

void add_layer_filters(Layer&,Layer&,Layer&);

#endif
