#ifndef _LAYER_FILTER_H_
#define _LAYER_FILTER_H_

#include"acidcam/ac.h"
#include "../new_filter.hpp"
#include "../layer.hpp"


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

// fade

class Layer_AlphaBlendFade01 : public FilterFunc {
public:
    void init() override {
        alpha = 0.1;
        inc = 0.01;
        dir = 1;
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

void add_layer_filters(Layer&,Layer&,Layer&);


#endif