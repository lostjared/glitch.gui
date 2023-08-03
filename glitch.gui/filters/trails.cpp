#include"trails.hpp"

void SimpleTrails::init() {
    
}

void SimpleTrails::proc(cv::Mat &frame) {
    collection.shiftFrames(frame);
    ac::AlphaBlend(collection[0], frame, frame, 0.5);
    ac::AlphaBlend(collection[3], frame, frame, 0.5);
    ac::AlphaBlend(collection[7], frame, frame, 0.5);
}

void SimpleTrails::clear() {
    //   std::cout << "cleared: " << collection.count() << " frames\n";
    collection.clear();
}

SimpleTrails::~SimpleTrails() {
    
}
