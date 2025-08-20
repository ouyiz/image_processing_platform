#pragma once
#include "ImageProcess.h"
class SpatialFilter {
public:
	//均值滤波
	Mat averageFiltering(Mat src, int n);

	//高斯滤波
	Mat gaussianFilter(Mat src, int n);

	//中值滤波
	Mat medianFilter(Mat src, int n);

	//最小值滤波
	Mat minFilter(Mat src, int n);

	//最大值滤波
	Mat maxFilter(Mat src, int n);

	//Roberts滤波
	Mat robertsFilter(Mat src,int n);

	//Prewitt滤波
	Mat prewittFilter(Mat src, int n);

	//Sobel滤波
	Mat sobelFilter(Mat src, int n);

	//Laplacian滤波
	Mat laplacianFilter(Mat src, int n);
};