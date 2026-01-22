/* FFmpeg write OpenCV video via pipe */
#ifndef  __FFMPEG_WRITE_H_
#define __FFMPEG_WRITE_H_

#include<iostream>
#include<string>
#include<cstdlib>
#include<opencv2/opencv.hpp>
#include<sstream>

extern std::string ffmpeg_path;

enum class FFmpegCodec {
    LIBX264,
    LIBX265,
    H264_NVENC,
    HEVC_NVENC,
    H264_VAAPI,
    HEVC_VAAPI
};

std::string codecToString(FFmpegCodec codec);
FFmpegCodec stringToCodec(const std::string &codec_str);

FILE *open_ffmpeg(const char *output, const char *codec, const char *dst_res, const char *fps, const char *crf);
FILE *ffmpeg_open(const char *output, FFmpegCodec codec, const char *dst_res, const char *fps, const char *crf);
void write_ffmpeg(FILE *fptr, cv::Mat &frame);
void mux_audio(const char *output, const char *src, const char *final_file);
void rotate_90(const char *output, const char *src, const char *deg);
void close_stdout();
void list_devices();
#endif
