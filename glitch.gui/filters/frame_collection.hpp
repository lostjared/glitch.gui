#ifndef _FRAME_COL_H_
#define _FRAME_COL_H_

#include<deque>
#include"acidcam/ac.h"

class FrameCollection {
public:
    FrameCollection();
    FrameCollection(size_t max);
    void shiftFrames(cv::Mat &frame);
    const cv::Mat &operator[](size_t pos) const;
    cv::Mat &operator[](size_t pos);
    void setMaxFrames(size_t max);
    void clear();
    size_t count() const;
private:
    size_t max_frames;
    std::deque<cv::Mat> frames;
};


#endif