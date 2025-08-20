#pragma once
#include"ImageProcess.h"
class ImageSegmentation {
public:
	Mat histogramSegmentation(Mat src,int type);
	Mat iterativeThresholdSegmentation(Mat src, int n, int type);
	Mat otsuSegmentation(Mat src,int type);
	Mat KmeansSegmentation(Mat src, int n);
	Mat meanShiftSegmentation(Mat src, int sp, int sr);
	Mat watershedSegmentation(Mat src);
	Mat grabCutSegmentation(Mat src, Rect rect);
	Mat regionalGrowth(Mat src, Point pbegin, int thresh1, int thresh2, int thresh3,int n);
};