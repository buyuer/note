#include <opencv2/opencv.hpp>
#include <vector>

cv::Mat MoveDetect(cv::Mat last, cv::Mat present)
{
    cv::Mat                             grayPresent, diff, result;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i>              hierarchy;
    cv::cvtColor(last, last, cv::COLOR_BGR2GRAY);
    cv::cvtColor(present, grayPresent, cv::COLOR_BGR2GRAY);
    cv::absdiff(grayPresent, last, diff);
    cv::threshold(diff, diff, 50, 255, cv::THRESH_BINARY);
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::erode(diff, diff, element);
    cv::dilate(diff, diff, element);
    result = diff.clone();
    cv::Canny(diff, diff, 3, 9);
    cv::findContours(diff, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    cv::drawContours(present, contours, -1, cv::Scalar(0, 0, 255));
    std::vector<cv::Rect> rect(contours.size());
    return result;
}

int main(int argc, char **argv)
{
    cv::VideoCapture video;
    cv::Mat          present, last;
    video.open(0);
    video >> last;
    cv::waitKey(30);
    while (video.grab())
    {
        video >> present;
        auto result = MoveDetect(last, present);
        last        = present.clone();

        cv::imshow("result", result);
        cv::imshow("present", present);

        if (cv::waitKey(30) == 27)
        {
            break;
        };
    }
}
