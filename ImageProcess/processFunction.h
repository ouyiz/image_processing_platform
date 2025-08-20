#pragma once
#include "ImageProcess.h"
Mat glass(Mat src, int h, int w, int n);
Mat relief(Mat src, Mat gray, int h, int w,int n);
Mat scuplture(Mat src, Mat gray, int h, int w, int n);
Mat oil(Mat src, Mat gray, int h, int w);
Mat myMask(Mat src, int h, int w, int n);
Mat sketch(Mat src, Mat gray, int h, int w,int n1,int n2);
Mat old(Mat src, int h, int w);
Mat fleet(Mat src,  int h, int w,int n);
Mat cartoon(Mat src, Mat gray, int h, int w, int res);
Mat histogramEqualization(Mat src, Mat gray, int h, int w);
Mat illumination(Mat src, int h, int w, int n);
Mat dim(Mat src, int h, int w, int n);

Mat casting(Mat src, int h, int w);
Mat frozen(Mat src, int h, int w);
Mat comic(Mat src, int h, int w);
Mat feather(Mat src, int h, int w, double n);
Mat watercolor(Mat src, int n, float m);
Mat vignetting(Mat src, int h, int w, double r, double p);
Mat colorTemperature(Mat src, int n);
Mat saturability(Mat src, double n);
Mat luminance(Mat src, double n);
Mat contrast(Mat src, double n);
Mat hue(Mat src, int n);
Mat granular(Mat src, int n);
Mat sharpen(Mat input, double n);
Mat HighLight(cv::Mat input, int light);
Mat Shadow(cv::Mat input, int light);
Mat reversal(Mat src);
Mat grey(Mat src);
Mat whiteAndBlack(Mat src, int n);
Mat homochromy(Mat src, int n);
Mat linedraw(Mat src);
Mat convex(Mat src, int n);
Mat concave(Mat src, int n);
Mat neon(Mat src, int n);
Mat ghost(Mat src, int n);