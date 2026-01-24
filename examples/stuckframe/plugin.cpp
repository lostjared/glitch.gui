#include "acidcam/ac.h"

static constexpr int MAX = 16;
static ac::MatrixCollection<MAX> collection;

extern "C" void init() {
    std::cout <<"stuckframe initialized...\n";
    srand(static_cast<unsigned int>(time(0)));
}

extern "C" void rls() {
    ac::release_all_objects();
}

extern "C" void clear() {
    std::cout << "Clear called..\n";
    ac::release_all_objects();
}

extern "C" void proc(cv::Mat  &frame) {
    collection.shiftFrames(frame);
      static int off = 0;
      static int array[] = { 1, 2, 2, 3, 3, 3 };
      static int array_off = 0;
      for(int z = 0; z < frame.rows; ++z) {
          for(int i = 0; i < frame.cols; ++i) {
              cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
              cv::Mat &f = collection.frames[off];
              cv::Vec3b pix = f.at<cv::Vec3b>(z, i);
              pixel = pix;
              off += array[array_off];
              if(off > MAX - 1) {
                  off = 0;
              }
          }
      }
      array_off++;
      if(array_off > 5)
          array_off = 0;
}

