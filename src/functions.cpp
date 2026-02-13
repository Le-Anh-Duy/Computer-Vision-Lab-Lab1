#include "functions.hpp"

std::vector <std::string> commands_list = {"-rgb2gray", "-contrast", "-brightness", "-avg", "-med", "-gau", "-sobel", "-laplace"};
std::vector <ImageFunc> functions_list = {rgb2gray, contrast, brightness, avg, med, gau, sobel, laplace};

ImageFunc get_cv_func(const std::string &cmd) {
    std::cout << "trying to get " << cmd << '\n';
    for (int i = 0; i < commands_list.size(); i++) if (commands_list[i] == cmd) {
        return functions_list[i];
    }

    return nullptr;
}
