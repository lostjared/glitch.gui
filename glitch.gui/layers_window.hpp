#ifndef __LAYERS_WINDOW_H__
#define __LAYERS_WINDOW_H__

#include"acidcam/ac.h"
#include<QDialog>
#include<QLabel>
#include<QPushButton>
#include<QTextEdit>
#include<QComboBox>
#include"layer.hpp"

class MainWindow;

class LayersWindow : public QDialog {
    Q_OBJECT
public:
    LayersWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *m);
    Layer layer1;
    Layer layer2;
    Layer layer3;
    std::vector<Layer *> layers;
private:
    QLabel *layer_name;
    QTextEdit *layer_text;
    QPushButton *layer_set, *layer_clear;
    QComboBox *layer_index;
    MainWindow *main_window;

public slots:
    void setLayer();
    void clearLayer();
    void setIndexLayer(int layer);
};

#endif