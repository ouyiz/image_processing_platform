#include"spatialFilter.h"

//均值滤波
Mat SpatialFilter::averageFiltering(Mat src, int n) {
    if (n != 0) {
        Mat dst;
        blur(src, dst, Size(n, n));
        return dst;
    }
    else {
        return src;
    }
}

//高斯滤波
Mat SpatialFilter::gaussianFilter(Mat src, int n) {
    if (n != 0) {
        Mat dst;
        n = (n / 2) * 2 + 1;
        GaussianBlur(src, dst, Size(n, n), 10, 10);
        return dst;
    }
    else {
        return src;
    }
}

//中值滤波
Mat  SpatialFilter::medianFilter(Mat src, int n) {
	if (n != 0) {
		n = (n / 2) * 2 + 1;
		Mat dst;
		medianBlur(src, dst, n);
		return dst;
	}
	else return src;
}



//最小值滤波
Mat SpatialFilter::minFilter(Mat src, int n) {
    Mat dst;
    dst = src.clone();
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
                for (int x = -n / 2; x <= n / 2; x++)
                {
                    for (int y = -n / 2; y <= n / 2; y++)
                    {
                        min1 = min(min1, (int)dealImg.at<Vec3b>(i + x, j + y)[0]);
                        min2 = min(min2, (int)dealImg.at<Vec3b>(i + x, j + y)[1]);
                        min3 = min(min3, (int)dealImg.at<Vec3b>(i + x, j + y)[2]);

                       
                    }
                }
                dst.at<Vec3b>(i - n / 2, j - n / 2)[0] = min1;
                dst.at<Vec3b>(i - n / 2, j - n / 2)[1] = min2;
                dst.at<Vec3b>(i - n / 2, j - n / 2)[2] = min3;
            }
        }
    }
    return dst;
}

//最大值滤波
Mat SpatialFilter::maxFilter(Mat src, int n) {
    Mat dst;
    dst = src.clone();
    Mat dealImg = src.clone();
    if (n != 0) {
        n = (n / 2) * 2 + 1;
        copyMakeBorder(src, dealImg, n / 2, n / 2, n / 2, n / 2, BORDER_REFLECT);
        for (int i = n / 2; i < dealImg.rows - n / 2; i++)
        {
            for (int j = n / 2; j < dealImg.cols - n / 2; j++)
            {
                int max1 = 0;
                int max2 = 0;
                int max3 = 0;
                for (int x = -n / 2; x <= n / 2; x++)
                {
                    for (int y = -n / 2; y <= n / 2; y++)
                    {
                        

                        max1 = max(max1, (int)dealImg.at<Vec3b>(i + x, j + y)[0]);
                        max2 = max(max2, (int)dealImg.at<Vec3b>(i + x, j + y)[1]);
                        max3 = max(max3, (int)dealImg.at<Vec3b>(i + x, j + y)[2]);
                    }
                }
                dst.at<Vec3b>(i - n / 2, j - n / 2)[0] = max1;
                dst.at<Vec3b>(i - n / 2, j - n / 2)[1] = max2;
                dst.at<Vec3b>(i - n / 2, j - n / 2)[2] = max3;
            }
        }
    }
    return dst;
}

//Roberts滤波
Mat SpatialFilter::robertsFilter(Mat src, int n) {
    Mat dst = src.clone();
    if (n == 1) {
        Mat roberts_x = (Mat_<int>(2, 2) << 1, 0, 0, -1);
        filter2D(src, dst, -1, roberts_x, Point(-1, -1), 0.0);
    }
    if (n == 2) {
        Mat roberts_y = (Mat_<int>(2, 2) << 0, 1, -1, 0);
        filter2D(src, dst, -1, roberts_y, Point(-1, -1), 0.0);
    }
    return dst;
}

//Prewitt滤波
Mat SpatialFilter::prewittFilter(Mat src, int n) {
    Mat dst = src.clone();
    if (n == 1) {
        Mat prewitt_x = (Mat_<int>(3, 3) << 1, 0, -1, 1, 0, -1, 1, 0, -1);
        filter2D(src, dst, -1, prewitt_x, Point(-1, -1), 0.0);
    }
    if (n == 2) {
        Mat prewitt_y = (Mat_<int>(3, 3) << -1, -1, -1, 0, 0, 0, 1, 1, 1);
        filter2D(src, dst, -1, prewitt_y, Point(-1, -1), 0.0);
    }
    return dst;
}

//Soble滤波
Mat SpatialFilter::sobelFilter(Mat src, int n) {
    Mat dst = src.clone();
    if (n == 1) {
        Mat Sobel_x = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
        filter2D(src, dst, -1, Sobel_x, Point(-1, -1), 0.0);
    }
    if (n == 2) {
        Mat Sobel_y = (Mat_<int>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
        filter2D(src, dst, -1, Sobel_y, Point(-1, -1), 0.0);
    }
    return dst;
}

//Laplacian滤波
Mat SpatialFilter::laplacianFilter(Mat src, int n) {
    Mat dst = src.clone();
    if (n == 1) {
        Mat Laplacian_x = (Mat_<int>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
        filter2D(src, dst, -1, Laplacian_x, Point(-1, -1), 0.0);
    }
    if (n == 2) {
        Mat Laplacian_y = (Mat_<int>(3, 3) << -1, -1, -1, -1, 8, -1, -1, -1, -1);
        filter2D(src, dst, -1, Laplacian_y, Point(-1, -1), 0.0);
    }
    if (n == 3) {
        Mat Laplacian_x = (Mat_<int>(3, 3) << 0, 1, 0, 1, -4, 1, 0, 1, 0);
        filter2D(src, dst, -1, Laplacian_x, Point(-1, -1), 0.0);
    }
    if (n == 4) {
        Mat Laplacian_y = (Mat_<int>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
        filter2D(src, dst, -1, Laplacian_y, Point(-1, -1), 0.0);
    }
    return dst;
}
