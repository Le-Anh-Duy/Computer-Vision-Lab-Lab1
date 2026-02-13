#include "libs.hpp"
#include "functions.hpp"


int main(int argc, char** argv) {
	cv::Mat input = cv::imread(argv[2], cv::IMREAD_COLOR);
	cv::Mat result = get_cv_func(argv[1])(input, {argc == 4 ? "null" : std::string(argv[4])});
	cv::imwrite(argv[3], result);
	return 0;
}

