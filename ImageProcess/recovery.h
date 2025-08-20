#pragma once
#include "ImageProcess.h"
class Recovery {
public:
	Mat geometricMean(Mat src, int n);
	Mat harmonicMean(Mat src, int n);
	Mat antiharmonicMean(Mat src, int n,int q);
	Mat midpoint(Mat src, int n);
	Mat alphaTrimmedMean(Mat src, int n, double dd);
	Mat adaptiveNoiseCancel(Mat src, int n);
	Mat adaptiveMedian(Mat src, int n, int Smax);
	uchar adaptiveMedianSmall(Mat src, int k,int i, int j, int n, int Smax);
};