#pragma once
#include "rgb2gray.hpp"
#include "contrast.hpp"
#include "brightness.hpp"
#include "avg.hpp"
#include "med.hpp"
#include "gau.hpp"
#include "sobel.hpp"
#include "laplace.hpp"
#include "libs.hpp"

using ImageFunc = cv::Mat (*)(const cv::Mat&, const std::vector<std::any>&);
ImageFunc get_cv_func(const std::string &cmd);