
#include "ImageProcess.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    system("chcp 65001");
    QApplication a(argc, argv);
    ImageProcess w;
    w.show();
    return a.exec();
}
/*
#include <opencv2/core.hpp>
#include <iostream>

int main() {
    std::cout << "OpenCV版本: " << CV_VERSION << std::endl;         // 编译时版本
    std::cout << "运行时版本: " << cv::getVersionString() << std::endl;
    return 0;
}
*/