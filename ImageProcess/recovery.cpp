#include "recovery.h"
#include<cmath>
//几何均值滤波器
Mat Recovery::geometricMean(Mat src,int n){
	Mat dst;
	dst = src.clone();
	Mat dealImg= src.clone();
	if (n != 0) {
		n = (n / 2)*2 + 1;
		copyMakeBorder(src, dealImg, n/ 2, n / 2, n / 2, n / 2, BORDER_REFLECT);
		double k = n * n;
		for (int i = n / 2; i < dealImg.rows - n / 2; i++)
		{
			for (int j = n / 2; j < dealImg.cols - n / 2; j++)
			{
				double Sum1 = 0;
				double Sum2 = 0;
				double Sum3 = 0;
				for (int x = -n / 2; x <= n / 2; x++)
				{
					for (int y = -n / 2; y <= n / 2; y++)
					{
						Sum1 = Sum1 + log10(dealImg.at<Vec3b>(i + x, j + y)[0] + 0.1);
						Sum2 = Sum2 + log10(dealImg.at<Vec3b>(i + x, j + y)[1] + 0.1);
						Sum3 = Sum3 + log10(dealImg.at<Vec3b>(i + x, j + y)[2] + 0.1);
					}
				}
				Sum1 = Sum1 / k;
				dst.at<Vec3b>(i - n / 2, j - n / 2)[0] = round(pow(10, Sum1));
				Sum2 = Sum2 / k;
				dst.at<Vec3b>(i - n / 2, j - n / 2)[1] = round(pow(10, Sum2));
				Sum3 = Sum3 / k;
				dst.at<Vec3b>(i - n / 2, j - n / 2)[2] = round(pow(10, Sum3));
			}
		}
	}
	return dst;
}

//谐波均值滤波器
Mat Recovery::harmonicMean(Mat src, int n) {
	Mat dst;
	dst = src.clone();
	Mat dealImg = src.clone();
	if (n != 0) {
		n = (n / 2) * 2 + 1;
		copyMakeBorder(src, dealImg, n / 2, n / 2, n / 2, n / 2, BORDER_REFLECT);
		double k = n * n;
		for (int i = n / 2; i < dealImg.rows - n / 2; i++)
		{
			for (int j = n / 2; j < dealImg.cols - n / 2; j++)
			{
				double Sum1 = 0;
				double Sum2 = 0;
				double Sum3 = 0;
				for (int x = -n / 2; x <= n / 2; x++)
				{
					for (int y = -n / 2; y <= n / 2; y++)
					{
						Sum1 = Sum1 + 1/(dealImg.at<Vec3b>(i + x, j + y)[0] + 0.1);
						Sum2 = Sum2 + 1/(dealImg.at<Vec3b>(i + x, j + y)[1] + 0.1);
						Sum3 = Sum3 + 1/(dealImg.at<Vec3b>(i + x, j + y)[2] + 0.1);
					}
				}
				Sum1 = k / Sum1;
				dst.at<Vec3b>(i - n / 2, j - n / 2)[0] = Sum1;
				Sum2 = k / Sum2;
				dst.at<Vec3b>(i - n / 2, j - n / 2)[1] = Sum2;
				Sum3 = k / Sum3;
				dst.at<Vec3b>(i - n / 2, j - n / 2)[2] = Sum3;
			}
		}
	}
	return dst;
}

//反谐波均值滤波器
Mat Recovery::antiharmonicMean(Mat src, int n,int q) {
	Mat dst;
	dst = src.clone();
	Mat dealImg = src.clone();
	if (n != 0) {
		n = (n / 2) * 2 + 1;
		copyMakeBorder(src, dealImg, n / 2, n / 2, n / 2, n / 2, BORDER_REFLECT);
		double k = n * n;
		for (int i = n / 2; i < dealImg.rows - n / 2; i++)
		{
			for (int j = n / 2; j < dealImg.cols - n / 2; j++)
			{
				double Sum10 = 0;
				double Sum20 = 0;
				double Sum30 = 0;
				double Sum11 = 0;
				double Sum21 = 0;
				double Sum31 = 0;
				double Sum1 = 0;
				double Sum2 = 0;
				double Sum3 = 0;
				for (int x = -n / 2; x <= n / 2; x++)
				{
					for (int y = -n / 2; y <= n / 2; y++)
					{
						Sum10 = Sum10 + pow(dealImg.at<Vec3b>(i + x, j + y)[0] + 0.1, q + 1);
						Sum11 = Sum11 + pow(dealImg.at<Vec3b>(i + x, j + y)[0] + 0.1, q );
						Sum20 = Sum20 + pow(dealImg.at<Vec3b>(i + x, j + y)[1] + 0.1, q + 1);
						Sum21 = Sum21 + pow(dealImg.at<Vec3b>(i + x, j + y)[1] + 0.1, q);
						Sum30 = Sum30 + pow(dealImg.at<Vec3b>(i + x, j + y)[2] + 0.1, q + 1);
						Sum31 = Sum31 + pow(dealImg.at<Vec3b>(i + x, j + y)[2] + 0.1, q);
						
					}
				}
				Sum1 = Sum10 / Sum11;
				dst.at<Vec3b>(i - n / 2, j - n / 2)[0] = Sum1;
				Sum2 = Sum20 / Sum21;
				dst.at<Vec3b>(i - n / 2, j - n / 2)[1] = Sum2;
				Sum3 = Sum30 / Sum31;
				dst.at<Vec3b>(i - n / 2, j - n / 2)[2] = Sum3;
			}
		}
	}
	return dst;
}

//中点滤波器
Mat Recovery::midpoint(Mat src, int n) {
	Mat dst=src.clone();
	Mat dealImg = src.clone();
	if (n != 0) {
		n = (n / 2) * 2 + 1;
		copyMakeBorder(src, dealImg, n / 2, n / 2, n / 2, n / 2, BORDER_REFLECT);
		for (int i = n / 2; i < dealImg.rows - n / 2; i++)
		{
			for (int j = n / 2; j < dealImg.cols - n / 2; j++)
			{
				int min1 = 255;
				int min2 = 255;
				int min3 = 255;
				int max1 = 0;
				int max2 = 0;
				int max3 = 0;
				for (int x = -n / 2; x <= n / 2; x++)
				{
					for (int y = -n / 2; y <= n / 2; y++)
					{
						min1 = min(min1, (int)dealImg.at<Vec3b>(i + x, j + y)[0]);
						min2 = min(min2, (int)dealImg.at<Vec3b>(i + x, j + y)[1]);
						min3 = min(min3, (int)dealImg.at<Vec3b>(i + x, j + y)[2]);

						max1 = max(max1, (int)dealImg.at<Vec3b>(i + x, j + y)[0]);
						max2 = max(max2, (int)dealImg.at<Vec3b>(i + x, j + y)[1]);
						max3 = max(max3, (int)dealImg.at<Vec3b>(i + x, j + y)[2]);
					}
				}
				dst.at<Vec3b>(i - n / 2, j - n / 2)[0] = (max1 + min1) / 2;
				dst.at<Vec3b>(i - n / 2, j - n / 2)[1] = (max2 + min2) / 2;
				dst.at<Vec3b>(i - n / 2, j - n / 2)[2] = (max3 + min3) / 2;
			}
		}
	}
	return dst;
}

//修正后的alpha均值滤波器
Mat Recovery::alphaTrimmedMean(Mat src, int n, double dd) {
	Mat dst = src.clone();
	Mat dealImg = src.clone();
	if (n != 0) {
		n = (n / 2) * 2 + 1;
		int n2 = n * n;
		int d = n2 * dd;
		if (n2 - d * 2 == 0) {
			d = d - 1;
		}
		copyMakeBorder(src, dealImg, n /2, n/ 2, n / 2, n / 2, BORDER_REFLECT);
		vector<uchar> a1(n2);
		vector<uchar> a2(n2);
		vector<uchar> a3(n2);
		for (int i = n / 2; i < dealImg.rows - n / 2; i++)
		{
			for (int j = n / 2; j < dealImg.cols - n / 2; j++)
			{
				int k = 0;
				for (int x = -n / 2; x <= n / 2; x++)
				{
					for (int y = -n / 2; y <= n / 2; y++)
					{
						a1[k] = dealImg.at<Vec3b>(i + x, j + y)[0];
						a2[k] = dealImg.at<Vec3b>(i + x, j + y)[1];
						a3[k] = dealImg.at<Vec3b>(i + x, j + y)[2];
						k++;
					}
				}
				sort(a1.begin(), a1.end());
				sort(a2.begin(), a2.end());
				sort(a3.begin(), a3.end());
				int sum1 = 0;
				int sum2 = 0;
				int sum3 = 0;
				for (int m = d; m < n2 - d; m++)
				{
					sum1 = sum1 + a1[m];
					sum2 = sum2 + a2[m];
					sum3 = sum3 + a3[m];
				}
				dst.at<Vec3b>(i - n / 2, j - n / 2)[0] = round(sum1 / (n2 - 2 * d));
				dst.at<Vec3b>(i - n / 2, j - n / 2)[1] = round(sum2 / (n2 - 2 * d));
				dst.at<Vec3b>(i - n / 2, j - n / 2)[2] = round(sum3 / (n2 - 2 * d));
				
			}
		}
	}
	return dst;
}
//自适应噪声消除滤波器
Mat Recovery::adaptiveNoiseCancel(Mat src,int n)
{
	Mat dst = src.clone();
	if (n != 0) {
		n = (n / 2) * 2 + 1;
		Mat dealImg = src.clone();
		vector<Mat> a;
		a.resize(3);
		for (int i = 0; i < 3; i++) {
			a[i] = Mat(1, n * n, CV_8U);
		}
		copyMakeBorder(src, dealImg, n / 2, n / 2, n / 2, n / 2, BORDER_REFLECT);
		vector<Mat> channels;
		split(dealImg, channels);
		for (int k = 0; k < 3; k++) {
			Mat mat_mean1, mat_stddev1, mat_mean2, mat_stddev2;
			meanStdDev(channels[k], mat_mean1, mat_stddev1);
			double stddev1, mean2, stddev2;
			stddev1 = mat_stddev1.at<double>(0, 0);
			for (int i = n / 2; i < dealImg.rows - n / 2; i++)
			{
				for (int j = n / 2; j < dealImg.cols - n / 2; j++)
				{
					int h = 0;
					for (int x = -n / 2; x <= n / 2; x++)
					{
						for (int y = -n / 2; y <= n / 2; y++)
						{
		
							a[k].at<uchar>(h) = dealImg.at<Vec3b>(i + x, j + y)[k];
							h++;
						}
					}
					meanStdDev(a[k], mat_mean2, mat_stddev2);
					stddev2 = mat_stddev2.at<double>(0, 0); 
					mean2 = mat_mean2.at<double>(0, 0); 
					double m= (stddev1 * stddev1) / (stddev2 * stddev2 + 0.00001);
					if (m <= 1) {
						dst.at<Vec3b>(i - n / 2, j - n / 2)[k] = dealImg.at<Vec3b>(i, j)[k] - m * (dealImg.at<Vec3b>(i, j)[k] - mean2);
					}
					else {
						dst.at<Vec3b>(i - n / 2, j - n / 2)[k] = mean2;
					}
				}
			}
		}
	}
	return dst;
}

//自适应中值滤波器
Mat Recovery::adaptiveMedian(Mat src, int n,int Smax) {
	Mat dst = src.clone();
	if (n != 0) {
		n = (n / 2) * 2 + 1;
		Mat dealImg = src.clone();
		copyMakeBorder(src, dealImg, Smax / 2, Smax / 2, Smax / 2, Smax / 2, BORDER_REFLECT);
		for (int i = Smax / 2; i < dealImg.rows -  Smax/ 2; i++)
		{
			for (int j = Smax / 2; j < dealImg.cols - Smax / 2; j++)
			{
				for (int k = 0; k < 3; k++) {
					dst.at<Vec3b>(i - Smax / 2, j - Smax / 2)[k] = adaptiveMedianSmall(dealImg, k,i, j, n, Smax);
					
				}
			}
		}
	}
	return dst;
}
uchar Recovery::adaptiveMedianSmall(Mat src, int k,int i,int j,int n, int Smax) {
	int n2 = n * n;
	vector<uchar> a(n2);
	int h = 0;
	for (int x = -n / 2; x <= n / 2; x++)
	{
		for (int y = -n / 2; y <= n / 2; y++)
		{
			a[h] = src.at<Vec3b>(i + x, j + y)[k];
			
			h++;
		}
	}
	sort(a.begin(), a.end());
	
	int z_min = a[0];
	int z_med = a[(n2 - 1) / 2];
	
	int z_max = a[n2 - 1];
	int z_xy = src.at<Vec3b>(i, j)[k];
	if (z_med > z_min && z_med < z_max)
	{
		if (z_xy > z_min && z_xy < z_max)
			return z_xy;
		else
			return z_med;
	}
	else
	{
		n += 2;
		if (n <= Smax)
			return adaptiveMedianSmall(src, k,i, j, n, Smax);
		else {
			
			return z_med;
		}
			
	}
}
