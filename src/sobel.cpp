#include "sobel.hpp"
#include "rgb2gray.hpp"
#include "gau.hpp"

float dist(float x, float y) {
    return std::sqrt(x * x + y * y);
}

extern cv::Mat sobel(const cv::Mat &image, const std::vector<std::any> &args) {
    if (args.empty()) return image.clone();
    
    // int k = std::stoi(std::any_cast<std::string>(args[0]));
    
    
    
    std::vector <float> dx {
        1, 0, -1,
        2, 0, -2,
        1, 0, -1 
    };
    
    
    std::vector <float> dy {
        1, 2, 1,
        0, 0, 0,
        -1, -2, -1 
    };
    
    cv::Mat gray;
    if (image.channels() == 3) gray = rgb2gray(image, {"0"}); else gray = image;
    cv::Mat gauImage = gau(gray, {std::string("3")});
    
    cv::Mat res = cv::Mat(gray.size(), gray.type());
    
    cv::Mat gx = cv::Mat(gray.size(), gray.type());
    cv::Mat gy = cv::Mat(gray.size(), gray.type());
    apply_filter(gauImage, gx, dx, 3, 3);
    apply_filter(gauImage, gy, dy, 3, 3);

    int rows = gauImage.rows, cols = gauImage.cols;

    for (int i = 0; i < rows; i ++)
        for (int j = 0; j < cols; j ++) {
            int val = dist(gx.at<uchar>(i, j), gy.at<uchar>(i, j));
            if (val > 255) val = 255;
            if (val < 0) val = 0;

            res.at<uchar>(i, j) = val;
        }

    return res;
}