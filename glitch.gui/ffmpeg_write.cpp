
#include "ffmpeg_write.h"
#include<sstream>
#include<fstream>
#ifndef _WIN32
#include<unistd.h>
#endif

#ifdef __APPLE__
std::string ffmpeg_path = "ffmpeg";
#else
std::string ffmpeg_path = "ffmpeg";
#endif
extern void sendString(const std::string &s);

char buffer[1024*1024];
std::fstream file;
int stdout_save;

std::string codecToString(FFmpegCodec codec) {
    switch(codec) {
        case FFmpegCodec::LIBX264:
            return "libx264";
        case FFmpegCodec::LIBX265:
            return "libx265";
        case FFmpegCodec::H264_NVENC:
            return "h264_nvenc";
        case FFmpegCodec::HEVC_NVENC:
            return "hevc_nvenc";
        case FFmpegCodec::H264_VAAPI:
            return "h264_vaapi";
        case FFmpegCodec::HEVC_VAAPI:
            return "hevc_vaapi";
        default:
            return "libx264";
    }
}

FFmpegCodec stringToCodec(const std::string &codec_str) {
    if(codec_str == "libx265") return FFmpegCodec::LIBX265;
    if(codec_str == "h264_nvenc") return FFmpegCodec::H264_NVENC;
    if(codec_str == "hevc_nvenc") return FFmpegCodec::HEVC_NVENC;
    if(codec_str == "h264_vaapi") return FFmpegCodec::H264_VAAPI;
    if(codec_str == "hevc_vaapi") return FFmpegCodec::HEVC_VAAPI;
    return FFmpegCodec::LIBX264;
}

FILE *ffmpeg_open(const char *output, FFmpegCodec codec, const char *dst_res, const char *fps, const char *crf) {
    std::string codec_str = codecToString(codec);
    std::string tag;
    std::string pix_fmt = "yuv420p";
    std::string preset;
    std::string quality_arg;
    
    if(codec == FFmpegCodec::LIBX265) {
        tag = "-tag:v hvc1";
        preset = "-preset fast";
        quality_arg = std::string("-crf ") + crf;
    } else if(codec == FFmpegCodec::LIBX264) {
        preset = "-preset fast";
        quality_arg = std::string("-crf ") + crf;
    } else if(codec == FFmpegCodec::H264_NVENC) {
        quality_arg = std::string("-cq ") + crf;
    } else if(codec == FFmpegCodec::HEVC_NVENC) {
        quality_arg = std::string("-cq ") + crf;
    } else if(codec == FFmpegCodec::H264_VAAPI) {
        pix_fmt = "vaapi";
        quality_arg = std::string("-qp ") + crf;
    } else if(codec == FFmpegCodec::HEVC_VAAPI) {
        pix_fmt = "vaapi";
        quality_arg = std::string("-qp ") + crf;
    }
    
    std::ostringstream stream;
    stream << ffmpeg_path << " -y -s " << dst_res << " -pixel_format bgr24 -f rawvideo -r " << fps 
           << " -i pipe: -c:v " << codec_str;
    
    if(!quality_arg.empty()) {
        stream << " " << quality_arg;
    }
    if(!preset.empty()) {
        stream << " " << preset;
    }
    if(!pix_fmt.empty() && pix_fmt != "yuv420p") {
        stream << " -pix_fmt " << pix_fmt;
    } else if(pix_fmt == "yuv420p") {
        stream << " -pix_fmt yuv420p";
    }
    if(!tag.empty()) {
        stream << " " << tag;
    }
    
    stream << " \"" << output << "\"";
    
    std::cout << "glitch_gui: " << stream.str() << "\n";
    
#ifndef _WIN32
    FILE *fptr = popen(stream.str().c_str(), "w");
#else
    FILE *fptr = _popen(stream.str().c_str(), "wb");
#endif
    if(!fptr) {
        std::cerr << "Error: could not open ffmpeg\n";
        return 0;
    }
    return fptr;
}

FILE *open_ffmpeg(const char *output, const char *codec, const char *dst_res, const char *fps, const char *crf) {
    FFmpegCodec codec_enum = stringToCodec(codec);
    return ffmpeg_open(output, codec_enum, dst_res, fps, crf);
}


void list_devices() {
#ifdef __APPLE__
    std::string s = ffmpeg_path + " -list_devices true -f avfoundation -i dummy";
    FILE *fptr = popen(s.c_str(), "r");
    if(!fptr) {
        std::cout << "glitch_gui: Error: could not read file...\n";
        exit(0);
    }
    pclose(fptr);
#endif
}

void write_ffmpeg(FILE *fptr, cv::Mat &frame) {
    fwrite(frame.ptr(), sizeof(char), frame.total()*frame.elemSize(), fptr);
}

void close_stdout() {
    
}

void mux_audio(const char *output, const char *src, const char *final_file) {
    std::ostringstream stream;
    stream << ffmpeg_path << " -y -i \"" << output << "\" -i \"" << src << "\" -c copy -map 0:v:0 -map 1:a:0? -shortest \"" << final_file << "\"";
    std::cout << "glitch_gui: " << stream.str() << "\n";
#ifndef _WIN32
    FILE *fptr = popen(stream.str().c_str(), "r");
#else
    FILE *fptr = _popen(stream.str().c_str(), "r");
#endif
    if(!fptr) {
        std::cerr << "Error: could not open ffmpeg\n";
        return;
    }
#ifndef _WIN32
    pclose(fptr);
#else
    _pclose(fptr);
#endif
}

void rotate_90(const char *output, const char *src, const char *deg) {
    std::ostringstream stream;
    if(std::string(deg)!="transpose") {
        stream << ffmpeg_path << " -y -i \"" << output << "\" -c copy  -metadata:s:v:0 rotate=" << deg <<" \"" << src << "\"";
    } else {
        stream << ffmpeg_path << " -y -i \"" << output << "\" -vf \"transpose=0\" \"" << src << "\"";
    }
    std::cout << "glitch_gui: " << stream.str() << "\n";
#ifndef _WIN32
    FILE *fptr = popen(stream.str().c_str(), "r");
#else
    FILE *fptr = _popen(stream.str().c_str(), "r");
#endif
    if(!fptr) {
        std::cerr << "Error: could not open ffmpeg\n";
        return;
    }
#ifndef _WIN32
    pclose(fptr);
#else
    _pclose(fptr);
#endif
    
}

