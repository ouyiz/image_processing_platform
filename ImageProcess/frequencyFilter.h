#pragma once
#include "ImageProcess.h"
class FrequencyFilter
{
public:
	Mat idealLowPassFilter(Mat src, int n);
	Mat idealHighPassFilter(Mat src, int n);
	Mat gaussHighPassFilter(Mat src, int n);
	Mat gaussLowPassFilter(Mat src, int n);
	Mat butterworthHighPassFilter(Mat src, int n, int b);
	Mat butterworthLowPassFilter(Mat src, int n, int b);
};


