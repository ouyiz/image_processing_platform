#include"addNoise.h"
#include <random>

//高斯噪声
Mat AddNoise::gaussNoise(Mat src, double sigma, double mean) {
	if (sigma != 0) {
		Mat img_noise = Mat::zeros(src.size(), src.type());
		Mat dst;
		RNG rng;
		rng.fill(img_noise, RNG::NORMAL, mean, sigma);
		dst = src + img_noise;
		return dst;
	}
	else return src;
}

//瑞利噪声
Mat AddNoise::rayleighNoise(Mat src, double sigma, double mean) {
	default_random_engine generator;
	uniform_real_distribution<double> uniform_dist(0.0, 1.0);
	Mat noiseImg(src.size(), src.type());
	int h = src.rows;
	int w = src.cols;
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			double u = uniform_dist(generator);
			noiseImg.at<Vec3b>(i, j)[0] = sigma * sqrt(-2.0 * log(u)) + mean;
			noiseImg.at<Vec3b>(i, j)[1] = sigma * sqrt(-2.0 * log(u)) + mean;
			noiseImg.at<Vec3b>(i, j)[2] = sigma * sqrt(-2.0 * log(u)) + mean;
		}
	}
	Mat dst = src + noiseImg;
	normalize(dst, dst, 0, 255, NORM_MINMAX);
	dst.convertTo(dst, CV_8UC3);
	return dst;
}

//伽马噪声
Mat AddNoise::gammaNoise(Mat src, float alpha, float beta) {
	if (alpha != 0 && beta != 0) {
		Mat noiseImg(src.size(), src.type());
		int h = src.rows;
		int w = src.cols;
		mt19937 gen(random_device{}());
		gamma_distribution<> d(alpha, beta);
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				for (int k = 0; k < src.channels(); ++k) {
					float noise = static_cast<float>(d(gen));
					noiseImg.at<Vec3b>(i, j)[k] = saturate_cast<uchar>(noise);
				}
			}
		}
		Mat dst = src + noiseImg;
		normalize(dst, dst, 0, 255, NORM_MINMAX);
		dst.convertTo(dst, CV_8UC3);
		return dst;
	}
	else return src;	
}

//指数分布噪声
Mat AddNoise::exponentialNoise(Mat src, double lambda) {
	if (lambda != 0) {
		Mat noiseImg(src.size(), src.type());
		default_random_engine generator;
		exponential_distribution<double> distribution(1.0 / lambda);

		for (int i = 0; i < src.rows; ++i) {
			for (int j = 0; j < src.cols; ++j) {
				for (int k = 0; k < src.channels(); ++k) {
					double noise = distribution(generator);
					noiseImg.at<cv::Vec3b>(i, j)[k] = cv::saturate_cast<uchar>(noise);
				}
			}
		}
		Mat dst = src + noiseImg;
		normalize(dst, dst, 0, 255, NORM_MINMAX);
		dst.convertTo(dst, CV_8UC3);
		return dst;
	}
	else return src;
}

//均匀分布噪声
Mat AddNoise::uniformNoise(Mat src, double maxVal) {
	Mat noiseImg = src.clone();
	if (maxVal != 0) {
		mt19937 gen(random_device{}());
		uniform_int_distribution<> dis(0, maxVal);

		for (int i = 0; i < noiseImg.rows; ++i) {
			for (int j = 0; j < noiseImg.cols; ++j) {
				for (int k = 0; k < noiseImg.channels(); ++k) {
					double noise = dis(gen);
					noiseImg.at<Vec3b>(i, j)[k] = saturate_cast<uchar>(noise);
				}
			}
		}
		Mat dst = src + noiseImg;
		normalize(dst, dst, 0, 255, NORM_MINMAX);
		dst.convertTo(dst, CV_8UC3);
		return dst;
	}
	else return noiseImg;
}

//椒盐噪声
Mat AddNoise::saltandPepperNoise(Mat src, double n) {
	Mat dst = src.clone();
	mt19937 gen(random_device{}());
	int h = src.rows;
	int w = src.cols;
	uniform_real_distribution<> dis(0, 1);
	int noise_points = (int)(h * w * n);
	for (int i = 0; i < noise_points; ++i) {
		int row = dis(gen) * h;
		int col = dis(gen) * w;
		double salt_or_pepper = dis(gen);
		if (salt_or_pepper < 0.5) {
			dst.at<Vec3b>(row, col) = Vec3b(255, 255, 255);
		}
		else {
			dst.at<Vec3b>(row, col) = Vec3b(0, 0, 0);
		}
	}
	return dst;
}

//周期噪声
Mat AddNoise::periodicNoise(Mat src,double amplitude,double nx,double ny) {
	Mat noiseImg = src.clone();
	int h = src.rows;
	int w = src.cols;
	int frequencyX = h * nx;
	int frequencyY = w * ny;

	for (int y = 0; y < noiseImg.rows; ++y) {
		for (int x = 0; x < noiseImg.cols; ++x) {
			float noise = amplitude * sin(2 * CV_PI * frequencyX * x / noiseImg.cols) *
				sin(2 * CV_PI * frequencyY * y / noiseImg.rows);
			noiseImg.at<Vec3b>(y, x)[0] = saturate_cast<uchar>(noise);
			noiseImg.at<Vec3b>(y, x)[1] = saturate_cast<uchar>(noise);
			noiseImg.at<Vec3b>(y, x)[2] = saturate_cast<uchar>(noise);
		}
	}
	Mat dst = src + noiseImg;
	normalize(dst, dst, 0, 255, NORM_MINMAX);
	dst.convertTo(dst, CV_8UC3);
	return dst;
}