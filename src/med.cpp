#include "med.hpp"
#include <algorithm>

extern cv::Mat med(const cv::Mat &image, const std::vector <std::any> &args) {
    if (args.empty()) return image.clone();
    
    int k = std::stoi(std::any_cast<std::string>(args[0]));

    if (k%2 == 0) {
        std::cerr << "Kernel size should be odd" << std::endl;
        return image.clone();
    }

    cv::Mat res = cv::Mat::zeros(image.size(), image.type());
    int nChannels = res.channels();

    int radiusX = k / 2;
    int radiusY = k / 2;
    int r = res.rows, c = res.cols;
    
    std::vector <unsigned char> save;
    save.reserve(k * k);

    for (int i = 0; i < r; i ++) {
        for (int j = 0; j < c; j ++) {
            for (int ch = 0; ch < nChannels; ch ++) {
                save.clear();

                for (int ki = -radiusY; ki <= radiusY; ki++) {
                    for (int kj = -radiusX; kj <= radiusX; kj++) {
                        int ni = i + ki, nj = j + kj;
                        if (ni < 0 || nj < 0 || ni >= r || nj >= c) continue;
                        save.push_back(
                            nChannels == 3 ? image.at<cv::Vec3b>(ni, nj)[ch] : image.at<uchar>(ni, nj)
                        );

                    }
                }

                std::sort(save.begin(), save.end());
                int val = 0;
                if (save.size() % 2 == 0) {
                    val = save[save.size() / 2] + save[save.size() / 2 - 1];
                    val /= 2;
                } else {
                    val = save[save.size() / 2];
                }

                if (val > 255) val = 255;
                if (val < 0) val = 0;

                if (nChannels == 3)
                    res.at<cv::Vec3b>(i, j)[ch] = val;
                else
                    res.at<uchar>(i, j) = val;
            }
        }
    }

    return res;
}
