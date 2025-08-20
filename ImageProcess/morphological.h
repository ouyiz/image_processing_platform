#pragma once
#include "ImageProcess.h"
class Morphological {
public:
	Mat expansion(Mat src, int n);
	Mat erosion(Mat src, int n);
	Mat openOperation(Mat src, int n);
	Mat closeOperation(Mat src, int n);
	Mat topHat(Mat src, int n);
	Mat lowHat(Mat src, int n);
	Mat hitMiss(Mat src, int n);
	Mat boundaryExtraction(Mat src, int n);
	Mat areaFill(Mat src, Point pstart, int n);
	Mat connectedComponentExtraction(Mat src, int n);
	Mat convexShell(Mat src);
	Mat refinement(Mat src, int n, int type);
	Mat coarsening(Mat src, int n, int type);
};
