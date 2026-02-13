#include "convolution.hpp"

extern void apply_filter(const cv::Mat& src, cv::Mat &dst, const std::vector<float>& kernel, int kw, int kh) {

    if (kw % 2 == 0 || kh % 2 == 0) {
        std::cerr << "Kernel size should be odd" << std::endl;
        return;
    }

    int nChanels = src.channels();
    dst = cv::Mat::zeros(src.size(), src.type());

    int radiusX = kw / 2;
    int radiusY = kh / 2;
    int r = src.rows, c = src.cols;

    for (int i = 0; i < r; i ++) {
        for (int j = 0; j < c; j ++) {
            for (int ch = 0; ch < nChanels; ch ++) {
                float val = 0;

                for (int ki = -radiusY; ki <= radiusY; ki++) {
                    for (int kj = -radiusX; kj <= radiusX; kj++) {
                        int ni = i + ki, nj = j + kj;
                        if (ni < 0 || nj < 0 || ni >= r || nj >= c) continue;


                        if (nChanels == 3) {
                            val += 1.0 * src.at<cv::Vec3b>(ni, nj)[ch] * kernel[(ki + radiusY) * kw + (kj + radiusX)];
                        } else {
                            val += 1.0 * src.at<uchar>(ni, nj) * kernel[(ki + radiusY) * kw + (kj + radiusX)];
                        }        
                    }
                }

                if (val > 255) val = 255; 
                if (val < 0) val = 0;

                if (nChanels == 3) {
                    dst.at<cv::Vec3b>(i, j)[ch] = val;
                } else {
                    dst.at<uchar>(i, j) = val;
                }        
            }
        }
    }
}
