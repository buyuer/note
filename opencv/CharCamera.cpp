/*
 * @Author:DingXinTong
 * @Date  :2018-12-18
 */

#include <opencv2/opencv.hpp>

int main()
{
    cv::VideoCapture camera;
    cv::Mat frame, grayFrame, thresholdFrame, resFrame;

    const char str[8][2] = { "u", "p", "r", "e", "U", "P", "R", "E" };
    cv::RNG rng(123);

    int thresholdValue = 100;
    int mode = 0;

    camera.open(0);

    cv::namedWindow("charFrame");

    cv::createTrackbar("threshold", "charFrame", &thresholdValue, 255,
                       [](int, void*) -> void {});
    cv::createTrackbar("mode", "charFrame", &mode, 1,
                       [](int, void*) -> void {});

    while (camera.grab()) {
        camera.operator>>(frame);
        cv::Mat charFrame(frame.size(), CV_8UC1, cv::Scalar::all(0));
        cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        threshold(grayFrame, thresholdFrame, thresholdValue, 255,
                  cv::THRESH_BINARY);
        // cv::Canny(thresholdFrame, resFrame, 30, 90);
        resFrame = thresholdFrame;

        for (int row = 0; row < resFrame.rows; row += 5) {
            auto* rowP = resFrame.ptr<unsigned char>(row);
            for (int col = 0; col < resFrame.cols; col += 10) {
                if (*(rowP + col) == 255 * mode) {
                    putText(charFrame, str[rng.uniform(0, sizeof(str) / 2)],
                            cv::Point(col, row), cv::FONT_HERSHEY_SIMPLEX, 0.5,
                            cv::Scalar(255));
                }
            }
        }

        cv::imshow("Canny", resFrame);
        cv::imshow("frame", frame);
        cv::imshow("charFrame", charFrame);

        auto key = cv::waitKey(1);
        if (key == 27)
            break;
    }

    return 0;
}
