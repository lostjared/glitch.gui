#include"frame_collection.hpp"

FrameCollection::FrameCollection() {
    setMaxFrames(8);
}

FrameCollection::FrameCollection(size_t max) {
    setMaxFrames(max);
}

FrameCollection::FrameCollection(const FrameCollection &f) : max_frames{f.max_frames}, frames{f.frames} {}
FrameCollection::FrameCollection(FrameCollection &&f) : max_frames{f.max_frames}, frames{std::move(f.frames)} {}

FrameCollection &FrameCollection::operator=(const FrameCollection &f) {
    max_frames = f.max_frames;
    if(!frames.empty())
        frames.erase(frames.begin(), frames.end());        
    std::copy(f.frames.begin(), f.frames.end(), std::back_inserter(frames));
    return *this;
}
 
 FrameCollection &FrameCollection::operator=(FrameCollection &&f) {
    max_frames = f.max_frames;
    frames = std::move(f.frames);
    return *this;
 }


void FrameCollection::shiftFrames(const cv::Mat &frame) {
    if(frames.size() < max_frames) {
        for(size_t i = 0; i < max_frames; ++i) {
            frames.push_back(frame);
        }
        return;
       
    }
    frames.push_back(frame);
    frames.pop_front();
}

void FrameCollection::clear() {
    if(!frames.empty()) {
        frames.erase(frames.begin(), frames.end());
    }
}

size_t FrameCollection::count() const {
    return frames.size();
}

const cv::Mat &FrameCollection::operator[](size_t pos) const {
    return frames[pos];
}
 
cv::Mat &FrameCollection::operator[](size_t pos) {
    return frames[pos];
}
  
void FrameCollection::setMaxFrames(size_t max) {
    max_frames = max;
}

void FrameCollection::set(size_t index, const cv::Mat &frame) {
    frames[index] = frame.clone();
}

bool FrameCollection::get(size_t index, cv::Mat &frame) {
    if(index < frames.size()) {
        frame = frames[index];
        return true;
    }
    return false;
}

cv::Mat &FrameCollection::get_frame(size_t index) {
    return frames[index];
}
