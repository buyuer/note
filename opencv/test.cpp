#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char* argv[])
{
    std::cout << CV_VERSION << std::endl;
    cv::Mat m1(4, 4, CV_8UC1);
    for (auto pixel = m1.begin<char>(); pixel not_eq m1.end<char>(); ++pixel) {
        *pixel = 10;
    }
    cv::Mat m2 = m1;
    for (auto pixel = m2.begin<char>(); pixel not_eq m2.end<char>(); ++pixel) {
        std::cout << (int)*pixel << std::endl;
    }
}