#include "avg.hpp"

extern cv::Mat avg(const cv::Mat &image, const std::vector<std::any> &args) {
    if (args.empty()) return image.clone();
    
    int k = std::stoi(std::any_cast<std::string>(args[0]));
    
    cv::Mat res = cv::Mat(image.size(), image.type());
    
    if (k % 2 == 0) {
        std::cerr << "Kernel size must be odd" << std::endl;
        return res;
    }
    std::vector <float> kernel(k * k, 1.0 / (k * k));
    apply_filter(image, res, kernel, k, k);
    return res;
}