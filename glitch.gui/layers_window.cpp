#include"layers_window.hpp"
#include<QIcon>
#include<QTextStream>
#include<QFileDialog>
#include "new_filter.hpp"

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


bool checkThere(std::string src, const std::vector<std::string> &keys) {

    std::string s;
    for(size_t i = 0; i < src.length(); ++i) {
         s += tolower(src[i]);
    }
    for(auto &i : keys) {
        if(s.find(i) != std::string::npos)
            return true;
    }    
    return false;
}

Layer::Layer(const QString &filename) {
    open(filename);
}

Layer::~Layer() {
    if(is_open) {
        std::cout << "Releasing Layer: " << filename_.toStdString() << "\n";
    }
}

bool Layer::open(const QString &filename) {
    filename_ = filename;
    if(checkThere(filename.toStdString(), {".png", ".jpg", ".bmp"})) {
        type_ = LayerType::IMAGE;
        src_image = cv::imread(filename.toStdString());
        if(!src_image.empty()) {
            is_open = true;
            width = src_image.cols;
            height = src_image.rows;
            frame_index = 0;
            frame_count = 0;
            fps = 0.0;      
            return true;
        }
        else
            is_open = false;
    } else if(checkThere(filename.toStdString(), {".mp4", ".mkv", ".mov", ".m4v", ".avi"})) {
        type_ = LayerType::VIDEO;
        src_cap.open(filename.toStdString());
        if(src_cap.isOpened()) {
            is_open = true;
            width = static_cast<int>(src_cap.get(cv::CAP_PROP_FRAME_WIDTH));
            height = static_cast<int>(src_cap.get(cv::CAP_PROP_FRAME_HEIGHT));
            fps = src_cap.get(cv::CAP_PROP_FPS);
            frame_index = 0;
            frame_count = static_cast<int>(src_cap.get(cv::CAP_PROP_FRAME_COUNT));
            return true;
        } else {
            is_open = false;
            return false;
        }   
    }
    return false;
}

void Layer::close() {
    if(type_ == LayerType::IMAGE) {
        src_image.release();
    } else {
        src_cap.release();
    }
    is_open = false;
}

LayerType Layer::getType() {
    return type_;
}
 
QString  Layer::getFilename() {
    return filename_;
}

bool Layer::hasNext() {

    if(is_open == false)
        return false;

    if(type_ == LayerType::IMAGE)
        return true;

    if(type_ == LayerType::VIDEO && src_cap.isOpened())
        return true;

    return false;
}

bool Layer::read(cv::Mat &frame) {
    if(type_ == LayerType::IMAGE) {
        frame = src_image.clone();
        return true;
    }
    if(!src_cap.read(frame)) {
        frame_index = 0;
        src_cap.set(cv::CAP_PROP_POS_FRAMES, 0);
        src_cap.read(frame);
        if(!src_cap.isOpened()) {
            is_open = false;
            return false;
        }
    }
    frame_index ++;
    return true;
}

void Layer::getInfo(int &w, int &h, double &f, int &fc, int &fi) {
    w = width;
    h = height;
    f = fps;
    fc = frame_count;
    fi = frame_index;
}

QString Layer::getText() {
        if(is_open == false) {
            return "[Slot closed]";
        }
        QString text;
        QTextStream stream(&text);
        int w = 0, h = 0, fc = 0, fi = 0;
        double fps;
        getInfo(w, h, fps, fc, fi); 
        if(getType() == LayerType::IMAGE) {
            stream << "Mode: [IMAGE] - size [" << w << "x" << h << "]\n";
        } else {
        stream << "Mode: [VIDEO] - size [" << w << "x" << h << "]\n<br>Frame Count: " << fc << "\n<br>Frame Index: " << fi << "\n<br>FPS: " << fps << "\n\n";
    }
    return text;
}

LayersWindow::LayersWindow(QWidget *parent) : QDialog(parent) {
    setGeometry(500, 250, 385, 240);
    setFixedSize(385, 240);
    setWindowTitle("Layers Window");
    setWindowIcon(QIcon(":/images/icon.png"));

    //layer_name = new QLabel(tr("Filename (iamge/video)"), this);
    //layer_name->setGeometry(10, 10, 200, 25);

    layer_set = new QPushButton(tr("Select"), this);
    layer_set->setGeometry(210, 10, 75, 25);

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

    // 0

    Layer_AlphaBlend25 *layer0_blend25 = new Layer_AlphaBlend25();
    layer0_blend25->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_AlphaBlend25", layer0_blend25});

    Layer_AlphaBlend50 *layer0_blend50 = new Layer_AlphaBlend50();
    layer0_blend50->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_AlphaBlend50", layer0_blend50});

    Layer_AlphaBlend75 *layer0_blend75 = new Layer_AlphaBlend75();
    layer0_blend75->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_AlphaBlend75", layer0_blend75});

    // 1

    Layer_AlphaBlend25 *layer1_blend25 = new Layer_AlphaBlend25();
    layer1_blend25->setLayer(&layer2);
    new_filter_list.push_back({"New_Layer_1_AlphaBlend25", layer1_blend25});

    Layer_AlphaBlend50 *layer1_blend50 = new Layer_AlphaBlend50();
    layer1_blend50->setLayer(&layer2);
    new_filter_list.push_back({"New_Layer_1_AlphaBlend50", layer1_blend50});

    Layer_AlphaBlend75 *layer1_blend75 = new Layer_AlphaBlend75();
    layer1_blend75->setLayer(&layer2);
    new_filter_list.push_back({"New_Layer_1_AlphaBlend75", layer1_blend75});

    // 2

    Layer_AlphaBlend25 *layer2_blend25 = new Layer_AlphaBlend25();
    layer2_blend25->setLayer(&layer3);
    new_filter_list.push_back({"New_Layer_2_AlphaBlend25", layer2_blend25});

    Layer_AlphaBlend50 *layer2_blend50 = new Layer_AlphaBlend50();
    layer2_blend50->setLayer(&layer3);
    new_filter_list.push_back({"New_Layer_2_AlphaBlend50", layer2_blend50});

    Layer_AlphaBlend75 *layer2_blend75 = new Layer_AlphaBlend75();
    layer2_blend75->setLayer(&layer3);
    new_filter_list.push_back({"New_Layer_2_AlphaBlend75", layer2_blend75});

    Layer012_AlphaBlend *layer012_blend = new Layer012_AlphaBlend();
    layer012_blend->setLayer(&layer1, &layer2, &layer3);
    new_filter_list.push_back({"New_Layer_012_AlphaBlend", layer012_blend});

    Layer012_AlphaBlend_Xor *layer012_blendx = new Layer012_AlphaBlend_Xor();
    layer012_blendx->setLayer(&layer1, &layer2, &layer3);
    new_filter_list.push_back({"New_Layer_012_AlphaBlend_Xor", layer012_blendx});
 
    // Fade
    Layer_AlphaBlendFade01 *layer01_fade = new Layer_AlphaBlendFade01();
    layer01_fade->setLayer(&layer1, &layer2);
    new_filter_list.push_back({"New_Layer_01_Fade", layer01_fade});

    connect(layer_index, SIGNAL(currentIndexChanged(int)), this, SLOT(setIndexLayer(int)));
    layer_text->setText("[Slot Closed");
}

void LayersWindow::setLayer() {
    QString path = "";
    QString filename = QFileDialog::getOpenFileName(this,tr("Open Image/Video"), path, tr("Image/Video Files (*.png *.jpg *.bmp *.avi *.mov *.mp4 *.mkv)"));
    if(filename != "") {
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

