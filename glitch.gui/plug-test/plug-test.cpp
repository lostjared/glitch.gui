#include<iostream>
#include<string>
#include"../plugin_program.hpp"
#include<opencv2/opencv.hpp>

int main(int argc, char **argv) {
    if(argc == 2) {
        QString fname = argv[1]; 
        Plugin_Program *prog = new Plugin_Program(fname);
        if(!prog) {
            std::cerr << "plugin: Error on allocation..\n";
            exit(EXIT_FAILURE);
        }       
        prog->f_init();
        cv::Mat frame;
        frame.create(240, 320, CV_8UC3);   
        for(int i = 0; i < 25; ++i) {
            prog->f_proc(frame);
        }
        prog->f_clear();
        prog->f_rls();
        delete prog;
    }
}