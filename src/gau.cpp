// https://www.geeksforgeeks.org/blogs/gaussian-filter-generation-c/
#include "gau.hpp"
#include <typeinfo>

std::vector <float> gauss_construct(int k) {
    float sigma = 1;
    float s = 2.0 * sigma * sigma;

    float sum = 0;
    int r = k / 2;

    std::vector <float> kernel(k * k, 0);

    for (int i = -r; i <= r; i++) {
        for (int j = -r; j <= r; j ++) {
            float val = std::exp(-(i * i + j * j) / s) / (M_PI * s);
            kernel[(i + r) * k  + (j + r)] = val;
            sum += val;
        }
    }

    for (float &x: kernel) x /= sum;
    return kernel;
}

extern cv::Mat gau(const cv::Mat &image, const std::vector<std::any> &args) {
    if (args.empty()) return image.clone();
    int k = std::stoi(std::any_cast<std::string>(args[0]));
    
    cv::Mat res = cv::Mat(image.size(), image.type());
    
    if (k % 2 == 0) {
        std::cerr << "Kernel size must be odd" << std::endl;
        return res;
    }
    std::vector <float> kernel = gauss_construct(k);
    apply_filter(image, res, kernel, k, k);
    return res;
}