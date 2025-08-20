#include"greyTransform.h"
#include<math.h>

//灰度反转
Mat GreyTransform::reversal(Mat src) {
    Mat dst = src.clone();
    Mat lookupTable(1, 256, CV_8U);
    uchar* p = lookupTable.data;
    for (int i = 0; i < 256; i++)
        p[i] = 255 - i;
    LUT(src, lookupTable, dst);
    return dst;
}

//对数变换
Mat GreyTransform::logTransform(Mat src, int n) {
	
    Mat dst = src.clone();
    Mat lookupTable(1, 256, CV_8U);
    uchar* p = lookupTable.data;
    for (int i = 0; i < 256; i++) {
		p[i] = (n * (log(1.0 + i)));

    }
    Mat dst1;
    LUT(dst, lookupTable, dst1);
    normalize(dst1, dst1, 0, 255, NORM_MINMAX);
    return dst1;
}

//伽马变换
Mat  GreyTransform::gamma(Mat src, int n,double m) {
	int h = src.rows;
	int w = src.cols;
	int d = src.channels();
	Mat new_img(h, w, CV_32FC3);

	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			for (int k = 0; k < d; ++k) {
				new_img.at<Vec3f>(i, j)[k] = n * pow(src.at<Vec3b>(i, j)[k], m);
				
			}
		}
	}

	normalize(new_img, new_img, 0, 255, NORM_MINMAX);
	convertScaleAbs(new_img, new_img);

	return new_img;
}


//直方图均衡化
Mat GreyTransform::histogramEqualization(Mat src) {
    int h = src.rows;
    int w = src.cols;
    Mat dst(h, w, CV_8UC3, Scalar(0, 0, 0));
    vector<Mat> channels;
    split(src, channels);
    Mat b = channels[0];
    Mat g = channels[1];
    Mat r = channels[2];
    Mat bH, gH, rH;
    equalizeHist(b, bH);
    equalizeHist(g, gH);
    equalizeHist(r, rH);
    vector<Mat> channelsH = { bH, gH, rH };
    merge(channelsH, dst);
    return dst;
}