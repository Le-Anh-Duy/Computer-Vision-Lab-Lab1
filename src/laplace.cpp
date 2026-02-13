#include "laplace.hpp"
#include "rgb2gray.hpp"
#include "gau.hpp"

extern cv::Mat laplace(const cv::Mat &image, const std::vector<std::any> &args) {
    if (args.empty()) return image.clone();

    std::vector <float> kernel {
        1, 1, 1,
        1, -8, 1,
        1, 1, 1 
    };
    
    
    cv::Mat gray = rgb2gray(image, {0});
    cv::Mat blur = gau(gray, {std::string("3")});
    cv::Mat res = cv::Mat(blur.size(), blur.type());

    apply_filter(blur, res, kernel, 3, 3);

    return res;
}