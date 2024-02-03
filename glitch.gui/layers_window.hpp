#ifndef __LAYERS_WINDOW_H__
#define __LAYERS_WINDOW_H__

#include"acidcam/ac.h"
#include<QDialog>
#include<QLabel>
#include<QPushButton>
#include<QTextEdit>
#include<QComboBox>

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

class LayersWindow : public QDialog {
    Q_OBJECT
public:
    LayersWindow(QWidget *parent = 0);
    Layer layer1;
    Layer layer2;
    Layer layer3;
    std::vector<Layer *> layers;
private:
    QLabel *layer_name;
    QTextEdit *layer_text;
    QPushButton *layer_set, *layer_clear;
    QComboBox *layer_index;

public slots:
    void setLayer();
    void clearLayer();
    void setIndexLayer(int layer);
};

#endif