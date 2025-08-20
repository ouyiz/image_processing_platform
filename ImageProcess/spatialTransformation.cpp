#include"spatialTransformation.h"

//任意旋转
Mat SpatialTransformation::rotation(Mat src, int n) {
	int h = src.rows;
	int w = src.cols;
	Point2f center(w / 2.0, h / 2.0);

	Mat M = getRotationMatrix2D(center, n, 1.0);
	double cos = abs(M.at<double>(0, 0));
	double sin = abs(M.at<double>(0, 1));

	int nW = (int)(h * sin + w * cos);
	int nH = (int)(h * cos + w * sin);

	M.at<double>(0, 2) += (nW / 2.0) - center.x;
	M.at<double>(1, 2) += (nH / 2.0) - center.y;

	Mat dst;
	warpAffine(src, dst, M, Size(nW, nH));
	return dst;
}

//缩放
Mat SpatialTransformation::zoom(Mat src, double nx, double ny) {
	if (nx != 0 && ny != 0) {
		Mat dst;
		int h = src.rows;
		int w = src.cols;
		resize(src, dst, Size(w * ny, h * nx), 0, 0, INTER_LINEAR);
		return dst;
	}
	else return src;
}

//镜像
Mat SpatialTransformation::mirror(Mat src, int n) {
	Mat dst;
	flip(src,dst, n);
	return dst;
}