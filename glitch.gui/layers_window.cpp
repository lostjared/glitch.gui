#include"layers_window.hpp"
#include<QIcon>
#include<QTextStream>
#include<QFileDialog>
#include "new_filter.hpp"
#include"main_window.hpp"
#include"pref_window.hpp"
#include"filters/layer_filter.hpp"
#include"debug_window.hpp"
#include<QVBoxLayout>
#include<QHBoxLayout>

LayersWindow::LayersWindow(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Layers Window");
    setWindowIcon(QIcon(":/images/icon.png"));
    setMinimumSize(350, 220);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(8);
    
    QHBoxLayout *selectRow = new QHBoxLayout();
    selectRow->setSpacing(8);
    layer_index = new QComboBox(this);
    layer_index->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    layer_index->addItem("0: Clear");
    layer_index->addItem("1: Clear");
    layer_index->addItem("2: Clear");
    layer_index->setCurrentIndex(0);
    layer_set = new QPushButton(tr("Select"), this);
    layer_set->setMinimumWidth(75);
    connect(layer_set, SIGNAL(clicked()), this, SLOT(setLayer()));
    layer_clear = new QPushButton(tr("Clear"), this);
    layer_clear->setMinimumWidth(75);
    connect(layer_clear, SIGNAL(clicked()), this, SLOT(clearLayer()));
    selectRow->addWidget(layer_index);
    selectRow->addWidget(layer_set);
    selectRow->addWidget(layer_clear);
    mainLayout->addLayout(selectRow);
    
    layer_text = new QTextEdit(this);
    layer_text->setReadOnly(true);
    layer_text->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(layer_text, 1);
    
    setLayout(mainLayout);

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
            main_window->debug_window->Log("gui: Layer set to: " + text + "\n");
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
        main_window->debug_window->Log("gui: Layer set to: " + text + "\n");
    }
}

void LayersWindow::setIndexLayer(int) {
    int index = layer_index->currentIndex();
    layer_text->setHtml(layers[index]->getText());
}

