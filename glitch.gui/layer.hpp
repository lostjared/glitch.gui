#ifndef __LAYER_H
#define __LAYER_H

#include"acidcam/ac.h"
#include<QDialog>

bool checkThere(std::string src, const std::vector<std::string> &keys);
enum class LayerType { IMAGE, VIDEO };

class Layer {
public:
    Layer() = default;
    Layer(const QString &filename);
    ~Layer();
    bool open(const QString &filename);
    bool is_opened() const { return is_open; }
    void close();
    
    LayerType getType();
    QString  getFilename();

    bool hasNext();
    bool read(cv::Mat &frame);
    void getInfo(int &w, int &h, double &f, int &fc, int &fi);

    QString getText();
    
protected:
    QString filename_;
    LayerType type_;
    int width = 0, height = 0;
    double fps = 0.0;
    int frame_count = 0, frame_index = 0;
    bool is_open = false;
    cv::Mat src_image;
    cv::VideoCapture src_cap;
};

#endif