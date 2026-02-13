#include "rgb2gray.hpp"

extern cv::Mat rgb2gray(const cv::Mat &image, const std::vector <std::any> &args) {

    
    int w = image.cols, h = image.rows;
    int ws = image.step[0], num_channels = image.step[1];
    
    cv::Mat res = cv::Mat(h, w, CV_8UC1, cv::Scalar::all(0));

    uchar* data = (uchar*)image.data;
    uchar* res_ptr = (uchar*)res.data;

    for (int i = 0; i < h; i++, data += ws) {
        uchar* row = data;
        for (int j = 0; j < w; j ++, row += num_channels, res_ptr++) {
            // bgr
            // using the rec601 luma fomula to calculate grayscale
            uchar Y = std::min(255.0, 0.114 * row[0] +
                     0.587 * row[1] +
                    0.299 * row[2]);

            *res_ptr = Y;
        }
    }

    return res;
}