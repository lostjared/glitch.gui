#ifndef _CV_FRACTAL_HPP
#define _CV_FRACTAL_HPP
#include<opencv2/opencv.hpp>
#include<complex>
#include<thread>
#include<random>

namespace cv_fract {
    template<typename F>
    void UseMultipleThreads(cv::Mat &frame, const int &cores, F func) {
        const int size = frame.rows/cores;
        std::vector<std::thread> values;
        for(int i = 0; i < cores; ++i) {
            values.push_back(std::thread(func, &frame, i*size, frame.cols, size));
        }
        for(unsigned int i = 0; i < values.size(); ++i) {
            values[i].join();
        }
    }
    class CV_Fractal {
    public:
        CV_Fractal() : gen{rd()}, dist_int(0, 255) {
            loadPalette();
        }
        CV_Fractal(const double &center_real_, const double &center_imag_, const double &zoom, const int &iterations_, const int &thread_count_) : gen{rd()}, dist_int(0, 255)  {
            initParameters(center_real_, center_imag_, zoom, iterations_, thread_count_);
            loadPalette();
        }
        void initParameters(const double &center_real_, const double &center_imag_, const double &zoom, const int &iterations_, const int &thread_count_) {
            center_real = center_real_;
            center_imag = center_imag_;
            zoom_ = zoom;
            iterations = iterations_;
            tc = thread_count_;
            if(iterations > 0)
                MAX_ITER = iterations;
            else 
                std::cerr << "Error invalid iterations\n";
        }

        void setZoom(const double &z) {
            zoom_ = z;
        }

        void resetPalette() {
            loadPalette();            
        }

        void draw(cv::Mat &frame) {
             const double aspect_ratio = static_cast<double>(frame.cols) / frame.rows;
             const double range_real = 4.0 / zoom_; 
             const double range_imag = range_real / aspect_ratio;
             const double start = center_real - range_real / 2;
             const double end = center_real + range_real / 2;
             const double im_start = center_imag - range_imag / 2;
             const double im_end = center_imag + range_imag / 2;
             DrawFractal(frame, start, end, im_start, im_end, tc);
        }
        void draw_s(cv::Mat &frame) {
             const double aspect_ratio = static_cast<double>(frame.cols) / frame.rows;
             const double range_real = 4.0 / zoom_; 
             const double range_imag = range_real / aspect_ratio;
             const double start = center_real - range_real / 2;
             const double end = center_real + range_real / 2;
             const double im_start = center_imag - range_imag / 2;
             const double im_end = center_imag + range_imag / 2;
             DrawFractal(frame, start, end, im_start, im_end);
        }
    private:
        double center_real, center_imag;
        double zoom_;
        int iterations;
        int tc; 
        int MAX_ITER=80;
        std::vector<cv::Vec3b> color_palette;
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_int_distribution<> dist_int;

        void loadPalette() {
            color_palette.resize(MAX_ITER);
            for(int i = 0; i < MAX_ITER; ++i) {
                const unsigned char r = dist_int(gen);
                const unsigned char g = dist_int(gen);
                const unsigned char b = dist_int(gen);
                color_palette[i] = cv::Vec3b(b, g, r);
            }
        }

        int mandelbrot(const std::complex<double> &c) {
            int n = 0;
            std::complex<double> z(0, 0);
            while(std::abs(z) <= 2 && n < MAX_ITER) {
                z = z*z+c;
                n ++;
            }
            return n;
        }

        void drawPixel(const int &width, const int &height, cv::Vec3b &pixel, const int &i, const int &z, const double &start, const double &end, const double &im_start, const double &im_end) {
            const double w = (double(i)/double(width));
            const double h = (double(z)/double(height));
            const std::complex<double> c(start + w * (end - start), im_start + h * (im_end - im_start));
            const int n = mandelbrot(c);
             if (n == MAX_ITER) {
                pixel[0] = 0;
                pixel[1] = 0;
                pixel[2] = 0;
            } else {
                pixel = color_palette[n];
            }
        }
        void DrawFractal(cv::Mat &frame, const double &start, const double &end, const double &im_start, const double &im_end, const int &thread_count) {
          static auto callback = [&](cv::Mat *frame, const int &offset, const int &cols, const int &size) {
                for(int z = offset; z <  offset+size; ++z) {
                    for(int i = 0; i < cols; ++i) {
                        cv::Vec3b &pixel = frame->at<cv::Vec3b>(z, i);
                        drawPixel(frame->cols, frame->rows, pixel, i, z, start, end, im_start, im_end);
                    }
                }
            };
            UseMultipleThreads(frame, thread_count, callback);
        }  
        void DrawFractal(cv::Mat &frame,const double &start, const double &end, const double &im_start, const double &im_end) {
            for(int z = 0; z < frame.rows; ++z) {
                for(int i = 0; i < frame.cols; ++i) {
                    cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                    drawPixel(frame.cols, frame.rows, pixel, i, z, start, end, im_start, im_end);
                }
            }
        }
    };   
}



#endif