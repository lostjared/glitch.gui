#include"layers_window.hpp"
#include<QIcon>
#include<QTextStream>
#include<QFileDialog>
#include "new_filter.hpp"
#include"main_window.hpp"
#include"pref_window.hpp"
#include"filters/layer_filter.hpp"

LayersWindow::LayersWindow(QWidget *parent) : QDialog(parent) {
    setGeometry(500, 250, 385, 240);
    setFixedSize(385, 240);
    setWindowTitle("Layers Window");
    setWindowIcon(QIcon(":/images/icon.png"));

    layer_set = new QPushButton(tr("Select"), this);
    layer_set->setGeometry(215, 10, 75, 25);

    connect(layer_set, SIGNAL(clicked()), this, SLOT(setLayer()));

    layer_clear = new QPushButton(tr("Clear"), this);
    layer_clear->setGeometry(295, 10, 75, 25);

    connect(layer_clear, SIGNAL(clicked()), this, SLOT(clearLayer()));

    layer_text = new QTextEdit(this);
    layer_text->setGeometry(10,40, width()-20, 180);
    layer_text->setReadOnly(true);   

    layer_index = new QComboBox(this);
    layer_index->setGeometry(10, 10, 200, 25);

    layer_index->addItem("0: Clear");
    layer_index->addItem("1: Clear");
    layer_index->addItem("2: Clear");

    layer_index->setCurrentIndex(0);

    layers.push_back(&layer1);
    layers.push_back(&layer2);
    layers.push_back(&layer3);

    add_layer_filters(layer1,layer2,layer3);

    connect(layer_index, SIGNAL(currentIndexChanged(int)), this, SLOT(setIndexLayer(int)));
    layer_text->setText("[Slot Closed]");
}

void LayersWindow::setMainWindow(MainWindow *m) {
    main_window = m;
}

void LayersWindow::setLayer() {
    QString path = "";

   if(main_window->pref_window->savePath())
        path = settings.value("image_layer_path").toString();

    QString filename = QFileDialog::getOpenFileName(this,tr("Open Image/Video"), path, tr("Image/Video Files (*.png *.jpg *.bmp *.avi *.mov *.mp4 *.mkv)"));
    if(filename != "") {

        if(main_window->pref_window->savePath())
            settings.setValue("image_layer_path", filename);
    
        int index = layer_index->currentIndex();
        if(index >= 0 && layers[index]->open(filename)) {
            layer_text->setHtml(layers[index]->getText());
            QString text;
            QTextStream stream(&text);
            stream << index << ": " << filename;
            layer_index->setItemText(index, text);
        } else {
            layer_text->setHtml("Loading <b>failed</b>...");
        }
    }
}

void LayersWindow::clearLayer() {
    int index = layer_index->currentIndex();
    if(index >= 0) {
        layers[index]->close();
        QString text;
        QTextStream stream(&text);
        stream << index << ": Clear";
        layer_index->setItemText(index, text);
        layer_text->setHtml("Layer closed\n");
    }
}

void LayersWindow::setIndexLayer(int) {
    int index = layer_index->currentIndex();
    layer_text->setHtml(layers[index]->getText());
}

