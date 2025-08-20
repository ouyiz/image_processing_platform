#pragma once
#include "ImageProcess.h"
class GreyTransform {
public:
	//灰度反转
	Mat reversal(Mat src);

	//对数变换
	Mat logTransform(Mat src, int n);

	//伽马变换
	Mat gamma(Mat src, int n,double m);

	//直方图均衡化
	Mat histogramEqualization(Mat src);
};
