#pragma once
#include "ImageProcess.h"
class SpatialTransformation {
public:
	Mat rotation(Mat src, int n);
	Mat zoom(Mat src, double nx, double ny);
	Mat mirror(Mat src, int n);
};