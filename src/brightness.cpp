#include "brightness.hpp"
#include <cmath>
#include <vector>
#include <iostream>

std::vector<uchar> createLUT_brightness(float a) {
    std::vector<uchar> lut(256);
    for (int i = 0; i < 256; i++) {
        float val = i + a;
        
        if (val > 255) val = 255;
        if (val < 0) val = 0;
        
        lut[i] = (uchar)val;
    }
    return lut;
}

extern cv::Mat brightness(const cv::Mat &image, const std::vector<std::any> &args) {
    if (args.empty()) return image.clone();
    
    float c = std::stof(std::any_cast<std::string>(args[0]));

    cv::Mat res = cv::Mat(image.size(), image.type());

    std::vector<uchar> lut = createLUT_brightness(c);

    int h = image.rows;
    int w = image.cols;
    int channels = image.channels(); 
    for (int i = 0; i < h; i++) {
        const uchar* in_row = image.ptr<const uchar>(i);
        uchar* out_row = res.ptr<uchar>(i);

        for (int j = 0; j < w * channels; j++) {
            out_row[j] = lut[in_row[j]];
        }
    }

    return res;
}