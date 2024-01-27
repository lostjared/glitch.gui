#include<iostream>
#include<string>
#include"../plugin_program.hpp"
#include<opencv2/opencv.hpp>

int main(int argc, char **argv) {
    
    if(argc == 3) {
        cv::VideoCapture cap;
        cap.open(argv[2]);
        if(cap.isOpened()) {
            QString fname = argv[1];
            Plugin_Program *prog = new Plugin_Program(fname);
            if(!prog) {
                std::cerr << "plugin: Error on allocation..\n";
                exit(EXIT_FAILURE);
            }
            prog->f_init();
            bool active = true;
            cv::namedWindow("plug-test");
            while(active) {
                cv::Mat frame;
                if(!cap.read(frame)) {
                    cap.open(argv[2]);
                    if(!cap.isOpened()) {
                        std::cerr << "Error opening video file..\n";
                        exit(EXIT_FAILURE);
                    }
                }
                prog->f_proc(frame);
                cv::imshow("plug-test", frame);
                if(cv::pollKey() != 0) {
                    active = false;
                }
            }
            prog->f_clear();
            prog->f_rls();
            delete prog;
        } else {
            std::cerr << "Error capture device could not load plug.data.mp4\n";
            exit(EXIT_FAILURE);
        }
    }
}
