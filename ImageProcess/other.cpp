#include "other.h"
void fftshift(Mat& src, Mat& dst)
{
	dst = src.clone();
	if (dst.type() != CV_32F) dst.convertTo(dst, CV_32F);

	for (int r = 0; r < dst.rows; ++r)
	{
		for (int c = 0; c < dst.cols; ++c)
		{
			if ((r + c) % 2 != 0)
				dst.at<float>(r, c) = -dst.at<float>(r, c);
		}
	}
}

//频谱图
void Other::showSpectrogram(Mat src)
{
	vector<Mat> channels;
	split(src, channels);
	//1.获得最佳DFT尺寸(因为DFT执行偶数大小的阵列速度更快)
	int w = getOptimalDFTSize(src.cols);
	int h = getOptimalDFTSize(src.rows);

	for (int i = 0; i < 3; i++) {
		Mat padded;
		//2.使用填充形成hxw大小的
		copyMakeBorder(channels[i], padded, 0, h - channels[i].rows, 0, w - channels[i].cols, BORDER_CONSTANT, Scalar::all(0));
		//3.移到中心
		fftshift(padded,padded);
		Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
		Mat complexI;
		merge(planes, 2, complexI);
		//4.计算图像的DFT
		dft(complexI, complexI);
		split(complexI, planes);
		//5.取幅值
		magnitude(planes[0], planes[1], planes[0]);
		Mat magI = planes[0];
		//6.取对数
		magI += Scalar::all(1);  // 取对数前将所有的像素都加1，防止log0
		log(magI, magI);  // 取对数
		normalize(magI, magI, 0, 1, NORM_MINMAX);  // 归一化
		magI.convertTo(magI, CV_8U, 255.0);
		string windowName = (i == 0) ? "B" : (i == 1) ? "G" : "R";
		imshow(windowName, magI);
	}
}

//直方图
void Other::showHistogram(Mat src) {
	//分成3通道
	vector<Mat>channels;
	split(src, channels);
	//颜色
	Scalar s[3];
	s[0] = Scalar(255, 0, 0);
	s[1] = Scalar(0, 255, 0);
	s[2] = Scalar(0, 0, 255);
	for (int k = 0; k < 3; k++) {
		Mat hist;//存储计算得到的直方图
		const int histSize[] = { 256 };
		float pranges[] = { 0, 255 };
		const float* ranges[] = { pranges };
		calcHist(&channels[k], 1, 0, Mat(), hist, 1, histSize, ranges, true, false);
		int scale = 2;
		int hist_height = 256;
		Mat hist_img = Mat::zeros(hist_height, 256 * scale, CV_8UC3);//定义了绘制直方图的参数
		double max_val;
		minMaxLoc(hist, 0, &max_val, 0, 0);//计算直方图的最大值
		for (int i = 0; i < 256; i++)
		{
			float bin_val = hist.at<float>(i);
			int intensity = cvRound(bin_val * hist_height / max_val);//计算其在直方图中的高度
			rectangle(hist_img, Point(i * scale, hist_height - 1), Point((i + 1) * scale - 1, hist_height - intensity), s[k]);//根据高度绘制矩形条
		}
		if (k == 0) {
			imshow("B", hist_img);
		}
		if (k == 1) {
			imshow("G", hist_img);
		}
		if (k == 2) {
			imshow("R", hist_img);
		}
	}
}