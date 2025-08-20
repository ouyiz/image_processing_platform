#include "frequencyFilter.h"

//进行位移的函数
//用(-1)^(x+y)乘以输入图像来进行中心变化。
void fftshift(const cv::Mat& src, cv::Mat& dst)
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


//理想低通滤波器
Mat FrequencyFilter::idealLowPassFilter(Mat src, int n) {
	vector<Mat> channals;
	Mat outimgI[] = { Mat::zeros(src.size(), CV_8UC1),Mat::zeros(src.size(), CV_8UC1) ,Mat::zeros(src.size(), CV_8UC1) };
	split(src, channals);
	Mat kernelI;
	//1.获得最佳DFT尺寸(因为DFT执行偶数大小的阵列速度更快)
	int w = getOptimalDFTSize(src.cols);
	int h = getOptimalDFTSize(src.rows);
	//5.得到H(u,v)
	Mat H(h, w, CV_32FC1, Scalar::all(0));
	int cy = H.rows / 2;
	int cx = H.cols / 2;
	for (int i = 0; i < H.rows; ++i)
	{
		float* H_data = H.ptr<float>(i);
		for (int j = 0; j < H.cols; ++j)
		{
			double d = sqrt(pow(i - cy, 2) + pow(j - cx, 2));
			if (d <= (double)n)
				H_data[j] = 1.f;
		}
	}
	Mat p[] = { H.clone(), H.clone() };
	merge(p, 2, kernelI);
	for (int i = 0; i < 3; i++) {
		//2.使用填充形成hxw大小的
		Mat padded;
		copyMakeBorder(channals[i], padded, 0, h - channals[i].rows, 0, w - channals[i].cols, BORDER_CONSTANT, Scalar::all(0));
		Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
		//3.移到中心
		fftshift(planes[0], planes[0]);
		Mat complexF;
		merge(planes, 2, complexF);
		//4.计算图像的DFT，即F(u,v)
		dft(complexF, complexF);
		Mat complexFH;
		//6.用滤波函数H(u,v)乘以F(u,v)
		multiply(complexF, kernelI, complexFH);
		//7.进行逆 DFT 变换，只输出实部
		Mat ifft;
		idft(complexFH, ifft, DFT_REAL_OUTPUT);
		//8.用(-1)x+y乘以7中的结果。
		fftshift(ifft, ifft);
		//将所有小于 0 的像素值置为 0
		for (int r = 0; r < ifft.rows; ++r)
		{
			for (int c = 0; c < ifft.cols; ++c)
			{
				if (ifft.at<float>(r, c) < 0)
					ifft.at<float>(r, c) = 0.0;
			}
		}
		//对图像进行归一化处理，将像素值范围限定在 0 到 1 之间
		normalize(ifft, ifft, 0, 1, NORM_MINMAX);
		ifft.convertTo(ifft, CV_8UC1, 255);
		//将处理后的图像裁剪为原始图像的大小
		ifft(Rect(0, 0, channals[i].cols, channals[i].rows)).copyTo(outimgI[i]);
	}
	Mat res;
	merge(outimgI, 3, res);
	return res;
}


//理想高通滤波
Mat FrequencyFilter::idealHighPassFilter(Mat src, int n) {
	vector<Mat> channals;
	Mat outimgI[] = { Mat::zeros(src.size(), CV_8UC1),Mat::zeros(src.size(), CV_8UC1) ,Mat::zeros(src.size(), CV_8UC1) };
	split(src, channals);
	Mat kernelI;
	//1.获得最佳DFT尺寸(因为DFT执行偶数大小的阵列速度更快)
	int w = getOptimalDFTSize(src.cols);
	int h = getOptimalDFTSize(src.rows);
	//5.得到H(u,v)
	Mat H(h, w, CV_32FC1, Scalar::all(1.f));
	int cy = H.rows / 2;
	int cx = H.cols / 2;
	for (int i = 0; i < H.rows; ++i)
	{
		float* H_data = H.ptr<float>(i);
		for (int j = 0; j < H.cols; ++j)
		{
			double d = sqrt(pow(i - cy, 2) + pow(j - cx, 2));
			if (d <= (double)n)
				H_data[j] = 0;
		}
	}
	Mat p[] = { H.clone(), H.clone() };
	merge(p, 2, kernelI);
	for (int i = 0; i < 3; i++) {
		//2.使用填充形成hxw大小的
		Mat padded;
		copyMakeBorder(channals[i], padded, 0, h - channals[i].rows, 0, w - channals[i].cols, BORDER_CONSTANT, Scalar::all(0));
		Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
		//3.移到中心
		fftshift(planes[0], planes[0]);
		Mat complexF;
		merge(planes, 2, complexF);
		//4.计算图像的DFT，即F(u,v)
		dft(complexF, complexF);
		Mat complexFH;
		//6.用滤波函数H(u,v)乘以F(u,v)
		multiply(complexF, kernelI, complexFH);
		//7.进行逆 DFT 变换，只输出实部
		Mat ifft;
		idft(complexFH, ifft, DFT_REAL_OUTPUT);
		//8.用(-1)x+y乘以7中的结果。
		fftshift(ifft, ifft);
		//将所有小于 0 的像素值置为 0
		for (int r = 0; r < ifft.rows; ++r)
		{
			for (int c = 0; c < ifft.cols; ++c)
			{
				if (ifft.at<float>(r, c) < 0)
					ifft.at<float>(r, c) = 0.0;
			}
		}
		//对图像进行归一化处理，将像素值范围限定在 0 到 1 之间
		normalize(ifft, ifft, 0, 1, NORM_MINMAX);
		ifft.convertTo(ifft, CV_8UC1, 255);
		//将处理后的图像裁剪为原始图像的大小
		ifft(Rect(0, 0, channals[i].cols, channals[i].rows)).copyTo(outimgI[i]);
	}
	Mat res;
	merge(outimgI, 3, res);
	return res;
}

//高斯低通滤波器
Mat FrequencyFilter::gaussLowPassFilter(Mat src, int n) {
	vector<Mat> channals;
	Mat outimgI[] = { Mat::zeros(src.size(), CV_8UC1),Mat::zeros(src.size(), CV_8UC1) ,Mat::zeros(src.size(), CV_8UC1) };
	split(src, channals);
	Mat kernelI;
	//1.获得最佳DFT尺寸(因为DFT执行偶数大小的阵列速度更快)
	int w = getOptimalDFTSize(src.cols);
	int h = getOptimalDFTSize(src.rows);
	//5.得到H(u,v)
	Mat H(h, w, CV_32FC1);
	int cy = H.rows / 2;
	int cx = H.cols / 2;
	for (int i = 0; i < H.rows; ++i)
	{
		float* H_data = H.ptr<float>(i);
		for (int j = 0; j < H.cols; ++j)
		{
			double d = sqrt(pow(i - cy, 2) + pow(j - cx, 2));
			H_data[j] = expf((-d * d) / (2 * n * n));
		}
	}
	Mat p[] = { H.clone(), H.clone() };
	merge(p, 2, kernelI);
	for (int i = 0; i < 3; i++) {
		//2.使用填充形成hxw大小的
		Mat padded;
		copyMakeBorder(channals[i], padded, 0, h - channals[i].rows, 0, w - channals[i].cols, BORDER_CONSTANT, Scalar::all(0));
		Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
		//3.移到中心
		fftshift(planes[0], planes[0]);
		Mat complexF;
		merge(planes, 2, complexF);
		//4.计算图像的DFT，即F(u,v)
		dft(complexF, complexF);
		Mat complexFH;
		//6.用滤波函数H(u,v)乘以F(u,v)
		multiply(complexF, kernelI, complexFH);
		//7.进行逆 DFT 变换，只输出实部
		Mat ifft;
		idft(complexFH, ifft, DFT_REAL_OUTPUT);
		//8.用(-1)x+y乘以7中的结果。
		fftshift(ifft, ifft);
		//将所有小于 0 的像素值置为 0
		for (int r = 0; r < ifft.rows; ++r)
		{
			for (int c = 0; c < ifft.cols; ++c)
			{
				if (ifft.at<float>(r, c) < 0)
					ifft.at<float>(r, c) = 0.0;
			}
		}
		//对图像进行归一化处理，将像素值范围限定在 0 到 1 之间
		normalize(ifft, ifft, 0, 1, NORM_MINMAX);
		ifft.convertTo(ifft, CV_8UC1, 255);
		//将处理后的图像裁剪为原始图像的大小
		ifft(Rect(0, 0, channals[i].cols, channals[i].rows)).copyTo(outimgI[i]);
	}
	Mat res;
	merge(outimgI, 3, res);
	return res;
}

//高斯高通滤波器
Mat FrequencyFilter::gaussHighPassFilter(Mat src, int n) {
	vector<Mat> channals;
	Mat outimgI[] = { Mat::zeros(src.size(), CV_8UC1),Mat::zeros(src.size(), CV_8UC1) ,Mat::zeros(src.size(), CV_8UC1) };
	split(src, channals);
	Mat kernelI;
	//1.获得最佳DFT尺寸(因为DFT执行偶数大小的阵列速度更快)
	int w = getOptimalDFTSize(src.cols);
	int h = getOptimalDFTSize(src.rows);
	//5.得到H(u,v)
	Mat H(h, w, CV_32FC1);
	int cy = H.rows / 2;
	int cx = H.cols / 2;
	for (int i = 0; i < H.rows; ++i)
	{
		float* H_data = H.ptr<float>(i);
		for (int j = 0; j < H.cols; ++j)
		{
			double d = sqrt(pow(i - cy, 2) + pow(j - cx, 2));
			H_data[j] = 1 - expf((-d * d) / (2 * n * n));
		}
	}
	Mat p[] = { H.clone(), H.clone() };
	merge(p, 2, kernelI);
	for (int i = 0; i < 3; i++) {
		//2.使用填充形成hxw大小的
		Mat padded;
		copyMakeBorder(channals[i], padded, 0, h - channals[i].rows, 0, w - channals[i].cols, BORDER_CONSTANT, Scalar::all(0));
		Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
		//3.移到中心
		fftshift(planes[0], planes[0]);
		Mat complexF;
		merge(planes, 2, complexF);
		//4.计算图像的DFT，即F(u,v)
		dft(complexF, complexF);
		Mat complexFH;
		//6.用滤波函数H(u,v)乘以F(u,v)
		multiply(complexF, kernelI, complexFH);
		//7.进行逆 DFT 变换，只输出实部
		Mat ifft;
		idft(complexFH, ifft, DFT_REAL_OUTPUT);
		//8.用(-1)x+y乘以7中的结果。
		fftshift(ifft, ifft);
		//将所有小于 0 的像素值置为 0
		for (int r = 0; r < ifft.rows; ++r)
		{
			for (int c = 0; c < ifft.cols; ++c)
			{
				if (ifft.at<float>(r, c) < 0)
					ifft.at<float>(r, c) = 0.0;
			}
		}
		//对图像进行归一化处理，将像素值范围限定在 0 到 1 之间
		normalize(ifft, ifft, 0, 1, NORM_MINMAX);
		ifft.convertTo(ifft, CV_8UC1, 255);
		//将处理后的图像裁剪为原始图像的大小
		ifft(Rect(0, 0, channals[i].cols, channals[i].rows)).copyTo(outimgI[i]);
	}
	Mat res;
	merge(outimgI, 3, res);
	return res;
}

//butterworth低通滤波器
Mat FrequencyFilter::butterworthLowPassFilter(Mat src, int n, int b) {
	vector<Mat> channals;
	Mat outimgI[] = { Mat::zeros(src.size(), CV_8UC1),Mat::zeros(src.size(), CV_8UC1) ,Mat::zeros(src.size(), CV_8UC1) };
	split(src, channals);
	Mat kernelI;
	//1.获得最佳DFT尺寸(因为DFT执行偶数大小的阵列速度更快)
	int w = getOptimalDFTSize(src.cols);
	int h = getOptimalDFTSize(src.rows);
	//5.得到H(u,v)
	Mat H(h, w, CV_32FC1);
	int cy = H.rows / 2;
	int cx = H.cols / 2;
	for (int i = 0; i < H.rows; ++i)
	{
		float* H_data = H.ptr<float>(i);
		for (int j = 0; j < H.cols; ++j)
		{
			double d = sqrt(pow(i - cy, 2) + pow(j - cx, 2));
			H_data[j] = 1.0 / (1 + pow(d / n, 2 * b));
		}
	}
	Mat p[] = { H.clone(), H.clone() };
	merge(p, 2, kernelI);
	for (int i = 0; i < 3; i++) {
		//2.使用填充形成hxw大小的
		Mat padded;
		copyMakeBorder(channals[i], padded, 0, h - channals[i].rows, 0, w - channals[i].cols, BORDER_CONSTANT, Scalar::all(0));
		Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
		//3.移到中心
		fftshift(planes[0], planes[0]);
		Mat complexF;
		merge(planes, 2, complexF);
		//4.计算图像的DFT，即F(u,v)
		dft(complexF, complexF);
		Mat complexFH;
		//6.用滤波函数H(u,v)乘以F(u,v)
		multiply(complexF, kernelI, complexFH);
		//7.进行逆 DFT 变换，只输出实部
		Mat ifft;
		idft(complexFH, ifft, DFT_REAL_OUTPUT);
		//8.用(-1)x+y乘以7中的结果。
		fftshift(ifft, ifft);
		//将所有小于 0 的像素值置为 0
		for (int r = 0; r < ifft.rows; ++r)
		{
			for (int c = 0; c < ifft.cols; ++c)
			{
				if (ifft.at<float>(r, c) < 0)
					ifft.at<float>(r, c) = 0.0;
			}
		}
		//对图像进行归一化处理，将像素值范围限定在 0 到 1 之间
		normalize(ifft, ifft, 0, 1, NORM_MINMAX);
		ifft.convertTo(ifft, CV_8UC1, 255);
		//将处理后的图像裁剪为原始图像的大小
		ifft(Rect(0, 0, channals[i].cols, channals[i].rows)).copyTo(outimgI[i]);
	}
	Mat res;
	merge(outimgI, 3, res);
	return res;
}
//butterworth高通滤波器
Mat FrequencyFilter::butterworthHighPassFilter(Mat src, int n, int b) {
	vector<Mat> channals;
	Mat outimgI[] = { Mat::zeros(src.size(), CV_8UC1),Mat::zeros(src.size(), CV_8UC1) ,Mat::zeros(src.size(), CV_8UC1) };
	split(src, channals);
	Mat kernelI;
	//1.获得最佳DFT尺寸(因为DFT执行偶数大小的阵列速度更快)
	int w = getOptimalDFTSize(src.cols);
	int h = getOptimalDFTSize(src.rows);
	//5.得到H(u,v)
	Mat H(h, w, CV_32FC1);
	int cy = H.rows / 2;
	int cx = H.cols / 2;
	for (int i = 0; i < H.rows; ++i)
	{
		float* H_data = H.ptr<float>(i);
		for (int j = 0; j < H.cols; ++j)
		{
			double d = sqrt(pow(i - cy, 2) + pow(j - cx, 2));
			H_data[j] = 1.0 / (1 + pow(n / d, 2 * b));
		}
	}
	Mat p[] = { H.clone(), H.clone() };
	merge(p, 2, kernelI);
	for (int i = 0; i < 3; i++) {
		//2.使用填充形成hxw大小的
		Mat padded;
		copyMakeBorder(channals[i], padded, 0, h - channals[i].rows, 0, w - channals[i].cols, BORDER_CONSTANT, Scalar::all(0));
		Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
		//3.移到中心
		fftshift(planes[0], planes[0]);
		Mat complexF;
		merge(planes, 2, complexF);
		//4.计算图像的DFT，即F(u,v)
		dft(complexF, complexF);
		Mat complexFH;
		//6.用滤波函数H(u,v)乘以F(u,v)
		multiply(complexF, kernelI, complexFH);
		//7.进行逆 DFT 变换，只输出实部
		Mat ifft;
		idft(complexFH, ifft, DFT_REAL_OUTPUT);
		//8.用(-1)x+y乘以7中的结果。
		fftshift(ifft, ifft);
		//将所有小于 0 的像素值置为 0
		for (int r = 0; r < ifft.rows; ++r)
		{
			for (int c = 0; c < ifft.cols; ++c)
			{
				if (ifft.at<float>(r, c) < 0)
					ifft.at<float>(r, c) = 0.0;
			}
		}
		//对图像进行归一化处理，将像素值范围限定在 0 到 1 之间
		normalize(ifft, ifft, 0, 1, NORM_MINMAX);
		ifft.convertTo(ifft, CV_8UC1, 255);
		//将处理后的图像裁剪为原始图像的大小
		ifft(Rect(0, 0, channals[i].cols, channals[i].rows)).copyTo(outimgI[i]);
	}
	Mat res;
	merge(outimgI, 3, res);
	return res;
}
