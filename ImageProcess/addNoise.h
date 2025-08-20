#pragma once
#include "ImageProcess.h"
class AddNoise {
public:
	Mat gaussNoise(Mat src, double sigma, double mean);
	Mat rayleighNoise(Mat src, double sigma, double mean);
	Mat gammaNoise(Mat src, float alpha, float beta);
	Mat exponentialNoise(Mat src, double lambda);
	Mat uniformNoise(Mat src, double maxVal);
	Mat saltandPepperNoise(Mat src, double n);
	Mat periodicNoise(Mat src, double amplitude, double nx, double ny);
};