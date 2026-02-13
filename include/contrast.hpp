// implement basic contrast editting I = a * (I - b) + b, b = 128
#include "libs.hpp"
extern cv::Mat contrast(const cv::Mat &image, const std::vector <std::any> &args);

