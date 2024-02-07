#include"layer.hpp"

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