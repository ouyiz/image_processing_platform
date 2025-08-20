#pragma once
#include "ImageProcess.h"
class Enhance {
public:
	//晕影
	Mat vignetting(Mat src, int h, int w, double r, double p);
	//色温
	Mat colorTemperature(Mat src, int n);
	//饱和度
	Mat saturability(Mat src, double n);
	//亮度
	Mat luminance(Mat src, double n);
	//对比度
	Mat contrast(Mat src, double n);
	//色相
	Mat hue(Mat src, int n);
	//颗粒度
	Mat granular(Mat src, int n);
	//锐化
	Mat sharpen(Mat input, double n);
	//高光
	Mat HighLight(cv::Mat input, int light);
	//阴影
	Mat Shadow(cv::Mat input, int light);
};