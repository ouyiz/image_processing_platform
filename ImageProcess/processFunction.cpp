#include"processFunction.h"
//const double pi = 3.141592653;
/*----------------------------------------------滤镜--------------------------------------------*/
//毛玻璃效果
//毛玻璃特效，是利用图像邻域内随机一个像素点颜色代替当前像素
Mat glass(Mat src, int h, int w, int n) {
    n = (n / 2) * 2;
    Mat glassImg(h, w, CV_8UC3, Scalar(0, 0, 0));
    int i, j;
    if (n == 0) {
        return src;
    }
    //中
    for (i = n / 2; i < h - n / 2; ++i) {
        for (j = n / 2; j < w - n / 2; ++j) {
            int index = n / 2 - rand() % n;
            glassImg.at<Vec3b>(i, j) = src.at<Vec3b>(i + index, j + index);
        }
    }
    //上
    for (i = 0; i < n / 2; ++i) {
        for (j = n / 2; j < w - n / 2; ++j) {
            int indexi = n / 2 - rand() % (n / 2 + 1 + i);
            int indexj = n / 2 - rand() % n;
            glassImg.at<Vec3b>(i, j) = src.at<Vec3b>(i + indexi, j + indexj);
        }
    }

    //下
    for (i = h - n / 2; i < h; ++i) {
        for (j = n / 2; j < w - n / 2; ++j) {
            int indexi = rand() % (n / 2 - 1 - i + h) - n / 2;
            int indexj = n / 2 - rand() % n;
            glassImg.at<Vec3b>(i, j) = src.at<Vec3b>(i + indexi, j + indexj);
        }
    }
    //左
    for (i = n / 2; i < h - n / 2; ++i) {
        for (j = 0; j < n / 2; ++j) {
            int indexj = n / 2 - rand() % (n / 2 + 1 + j);
            int indexi = n / 2 - rand() % n;
            glassImg.at<Vec3b>(i, j) = src.at<Vec3b>(i + indexi, j + indexj);
        }
    }
    //右
    for (i = n / 2; i < h - n / 2; ++i) {
        for (j = w - n / 2; j < w; ++j) {
            int indexj = rand() % (n / 2 - 1 - j + w) - n / 2;
            int indexi = n / 2 - rand() % n;
            glassImg.at<Vec3b>(i, j) = src.at<Vec3b>(i + indexi, j + indexj);
        }
    }
    //左上
    for (i = 0; i < n / 2; ++i) {
        for (j = 0; j < n / 2; ++j) {
            int indexi = n / 2 - rand() % (n / 2 + 1 + i);
            int indexj = n / 2 - rand() % (n / 2 + 1 + j);
            glassImg.at<Vec3b>(i, j) = src.at<Vec3b>(i + indexi, j + indexj);
        }
    }
    //右上
    for (i = 0; i < n / 2; ++i) {
        for (j = w - n / 2; j < w; ++j) {
            int indexj = rand() % (n / 2 - 1 - j + w) - n / 2;
            int indexi = n / 2 - rand() % (n / 2 + 1 + i);
            glassImg.at<Vec3b>(i, j) = src.at<Vec3b>(i + indexi, j + indexj);
        }
    }
    //左下
    for (i = h - n / 2; i < h; ++i) {
        for (j = 0; j < n / 2; ++j) {
            int indexi = rand() % (n / 2 - 1 - i + h) - n / 2;
            int indexj = n / 2 - rand() % (n / 2 + 1 + j);
            glassImg.at<Vec3b>(i, j) = src.at<Vec3b>(i + indexi, j + indexj);
        }
    }
    //右下
    for (i = h - n / 2; i < h; ++i) {
        for (j = w - n / 2; j < w; ++j) {
            int indexi = rand() % (n / 2 - 1 - i + h) - n / 2;
            int indexj = rand() % (n / 2 - 1 - j + w) - n / 2;
            glassImg.at<Vec3b>(i, j) = src.at<Vec3b>(i + indexi, j + indexj);
        }
    }
    return glassImg;
}

//浮雕效果
Mat relief(Mat src, Mat gray, int h, int w, int n) {
    Mat reliefImg(h, w, CV_8UC1, Scalar(0));
    for (int i = 1; i < h - 1; ++i) {
        for (int j = 1; j < w - 1; ++j) {
            int edge = (int)(gray.at<uchar>(i - 1, j - 1)) - (int)(gray.at<uchar>(i + 1, j + 1));
            int val = edge + n;
            val = min(max(val, 0), 255);
            reliefImg.at<uchar>(i, j) = static_cast<uchar>(val);
        }
    }
    return reliefImg;
}

//雕刻效果
Mat scuplture(Mat src, Mat gray, int h, int w, int n) {
    Mat reliefImg(h, w, CV_8UC1, Scalar(0));
    for (int i = 1; i < h - 1; ++i) {
        for (int j = 1; j < w - 1; ++j) {
            int edge = (int)(gray.at<uchar>(i + 1, j + 1)) - (int)(gray.at<uchar>(i + 1, j + 1));
            int val = edge + n;
            val = min(max(val, 0), 255);
            reliefImg.at<uchar>(i, j) = static_cast<uchar>(val);
        }
    }
    return reliefImg;
}

//油画效果
Mat oil(Mat src, Mat gray, int h, int w) {
    Mat oilImg(h, w, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 2; i < h - 2; ++i) {
        for (int j = 2; j < w - 2; ++j) {
            int quant[8] = { 0 };
            for (int k = -2; k < 2; ++k) {
                for (int t = -2; t < 2; ++t) {
                    int level = gray.at<uchar>(i + k, j + t) / 32;
                    quant[level]++;
                }
            }
            int valMax = *max_element(begin(quant), end(quant));
            int valIndex = std::distance(std::begin(quant), std::find(std::begin(quant), std::end(quant), valMax));
            uchar b, g, r;
            for (int k = -2; k < 2; ++k) {
                for (int t = -2; t < 2; ++t) {
                    if (gray.at<uchar>(i + k, j + t) >= valIndex * 32 && gray.at<uchar>(i + k, j + t) < (valIndex + 1) * 32) {
                        Vec3b intensity = src.at<Vec3b>(i + k, j + t);
                        b = intensity.val[0];
                        g = intensity.val[1];
                        r = intensity.val[2];
                    }
                }
            }
            oilImg.at<Vec3b>(i, j) = Vec3b(b, g, r);
        }
    }
    return oilImg;
}

//马赛克
Mat myMask(Mat src, int h, int w,int n) {
    if (n != 0) {
        Mat maskImg(h, w, CV_8UC3, Scalar(0, 0, 0));
        int mh = h / n;
        int mw = w / n;
        for (int i = 0; i <= mh*n; i += n) {
            for (int j = 0; j <= mw* n; j += n) {
                if (i < (h - n) && j < (w - n)) {
                    for (int k = 0; k < n; ++k) {
                        for (int t = 0; t < n; ++t) {
                            Vec3b intensity = src.at<Vec3b>(i, j);
                            maskImg.at<Vec3b>(i + k, j + t) = intensity;
                        }
                    }
                }
                if (i == mh * n && j < mw * n) {
                    for (int k = mh * n; k < h; ++k) {
                        for (int t = 0; t < n; ++t) {
                            Vec3b intensity = src.at<Vec3b>(i, j);
                            maskImg.at<Vec3b>(k, j + t) = intensity;
                        }
                    }
                }
                if (j == mw * n && i < mh * n) {
                    for (int k = 0; k < n; ++k) {
                        for (int t = mw * n; t < w; ++t) {
                            Vec3b intensity = src.at<Vec3b>(i, j);
                            maskImg.at<Vec3b>(i+k, t) = intensity;
                        }
                    }
                }
                if (i == mh * n && j == mw * n) {
                    for (int k = mh * n; k < h; ++k) {
                        for (int t = mw * n; t < w; ++t) {
                            Vec3b intensity = src.at<Vec3b>(i, j);
                            maskImg.at<Vec3b>( k, t) = intensity;
                        }
                    }
                }
            }
        }
        
        return maskImg;
    }
    else {
        return src;
    }
   
}

//素描效果
Mat sketch(Mat src, Mat gray, int h, int w,int n1,int n2) {
    if (n1 == 0 || n2 == 0) {
        return src;
    }
    else {
        n1 = (n1 / 2) * 2 + 1;
        Mat gauss;
        GaussianBlur(gray, gauss, Size(n1, n1), 0);
        Mat inverGauss = 255 - gauss;
        Mat sketchImg;
        divide(gray, inverGauss, sketchImg, n2);
        return sketchImg;
    }
}

//怀旧效果
Mat old(Mat src, int h, int w) {
    Mat oldImg(h, w, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            double b = 0.272 * src.at<Vec3b>(i, j)[2] + 0.534 * src.at<Vec3b>(i, j)[1] + 0.131 * src.at<Vec3b>(i, j)[0];
            double g = 0.349 * src.at<Vec3b>(i, j)[2] + 0.686 * src.at<Vec3b>(i, j)[1] + 0.168 * src.at<Vec3b>(i, j)[0];
            double r = 0.393 * src.at<Vec3b>(i, j)[2] + 0.769 * src.at<Vec3b>(i, j)[1] + 0.189 * src.at<Vec3b>(i, j)[0];
            b = min(b, 255.0);
            g = min(g, 255.0);
            r = min(r, 255.0);
            oldImg.at<Vec3b>(i, j) = Vec3b((uchar)(b), (uchar)(g), (uchar)(r));
        }
    }
    return oldImg;
}

//流年效果
Mat fleet(Mat src, int h, int w,int n) {
    Mat fleetImg(h, w, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            double b = sqrt(src.at<Vec3b>(i, j)[0]) * n;
            double g = src.at<Vec3b>(i, j)[1];
            double r = src.at<Vec3b>(i, j)[2];
            b = min(b, 255.0);
            fleetImg.at<Vec3b>(i, j) = Vec3b((uchar)(b), (uchar)(g), (uchar)(r));
        }
    }
    return fleetImg;
}

//卡通效果
Mat cartoon(Mat src, Mat gray, int h, int w,int res) {

    int n = (res / 2) * 2 + 1;
    int num_bilateral = n;
    Mat img_color = src;
    for (int i = 0; i < num_bilateral; i++) {
        Mat temp;
        bilateralFilter(img_color, temp, 9, 9, n);
        img_color = temp;
    }
    medianBlur(gray, gray, n);
    Mat img_edge;
    adaptiveThreshold(gray, img_edge, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 9, 2);
    cvtColor(img_edge, img_edge, COLOR_GRAY2BGR);
    Mat img_cartoon;
    bitwise_and(img_color, img_edge, img_cartoon);
    return img_cartoon;
}

//直方图均衡化
Mat histogramEqualization(Mat src, Mat gray, int h, int w) {
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

//光照
Mat illumination(Mat src, int h, int w,int n) {
    if (n != 0) {
        double centerX = h / 2.0;
        double centerY = w / 2.0;
        double radius = min(centerX, centerY);
        int strength = n;
        Mat dst(h, w, CV_8UC3, Scalar(0, 0, 0));
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                double distance = pow((centerY - j), 2) + pow((centerX - i), 2);
                int B = src.at<Vec3b>(i, j)[0];
                int G = src.at<Vec3b>(i, j)[1];
                int R = src.at<Vec3b>(i, j)[2];
                if (distance < radius * radius) {
                    int result = static_cast<int>(strength * (1.0 - sqrt(distance) / radius));
                    B = min(255, max(0, B + result));
                    G = min(255, max(0, G + result));
                    R = min(255, max(0, R + result));
                }
                dst.at<Vec3b>(i, j) = Vec3b(B, G, R);
            }
        }
        return dst;
    }
    else {
        return src;
    }
}

//模糊
Mat dim(Mat src, int h, int w,int res) {
    int n = (res / 2) * 2 + 1;
    Mat source;
    cvtColor(src, source, COLOR_BGR2RGB);
    Mat result;
    GaussianBlur(source, result, Size(n, n), 0);
    cvtColor(result, result, cv::COLOR_RGB2BGR);
    return result;
}



//熔铸
Mat casting(Mat src, int h, int w) {
    Mat  dst(h, w, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            dst.at<Vec3b>(i, j)[0] = min(255, max(0, (128 * src.at<Vec3b>(i, j)[0] / (src.at<Vec3b>(i, j)[1] + src.at<Vec3b>(i, j)[2] + 1))));// blue
            dst.at<Vec3b>(i, j)[1] = min(255, max(0, (128 * src.at<Vec3b>(i, j)[1] / (src.at<Vec3b>(i, j)[0] + src.at<Vec3b>(i, j)[2] + 1))));// green
            dst.at<Vec3b>(i, j)[2] = min(255, max(0, (128 * src.at<Vec3b>(i, j)[2] / (src.at<Vec3b>(i, j)[0] + src.at<Vec3b>(i, j)[1] + 1))));// red
        }
    }
    return dst;
}

//冰冻
Mat frozen(Mat src, int h, int w) {
    Mat  dst(h, w, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            dst.at<Vec3b>(i, j)[0] = (min(255, max(0, abs(src.at<cv::Vec3b>(i, j)[0] - src.at<Vec3b>(i, j)[1] - src.at<Vec3b>(i, j)[2]) * 3 >>2)));// blue
            dst.at<Vec3b>(i, j)[1] = (min(255, max(0, abs(src.at<cv::Vec3b>(i, j)[1] - src.at<Vec3b>(i, j)[0] - src.at<Vec3b>(i, j)[2]) * 3 >>2)));// green
            dst.at<Vec3b>(i, j)[2] = (min(255, max(0, abs(src.at<cv::Vec3b>(i, j)[2] - src.at<Vec3b>(i, j)[0] - src.at<Vec3b>(i, j)[1]) * 3 >>2)));// red
        }
    }
    return dst;
}

//连环画
Mat comic(Mat src, int h, int w) {
    Mat  dst(h, w, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int r = src.at<cv::Vec3b>(i, j)[2];
            int g = src.at<cv::Vec3b>(i, j)[1];
            int b = src.at<cv::Vec3b>(i, j)[0];

            int R = abs(g - b + g + r) * r / 256;
            int G = abs(b - g + b + r) * r / 256;
            int B = abs(b - g + b + r) * g / 256;

            dst.at<cv::Vec3b>(i, j)[0] = (min(255, max(0, B)));
            dst.at<cv::Vec3b>(i, j)[1] = (min(255, max(0, G)));
            dst.at<cv::Vec3b>(i, j)[2] = (min(255, max(0, R)));
        }
    }
    return dst;
}

//羽化
Mat feather(Mat src, int h, int w, double n) {
    Mat  dst(h, w, CV_8UC3, Scalar(0, 0, 0));
    int center_x = w / 2;
    int center_y = h / 2;
    int s1 = center_x * center_x + center_y * center_y;
    double ratio = w > h ? static_cast<double>(h) / w : static_cast<double>(w) / h;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++)
        {
            double dx = (double)(abs(center_x - j));
            double dy = (double)(abs(center_y - i));
            if (center_x > center_y)
                dx = dx * ratio;
            else
                dy = dx * ratio;
            double s2 = dx * dx + dy * dy;
            double v = 255 * s2 / (s1 * n);
            int b = src.at<Vec3b>(i, j)[0];
            int g = src.at<Vec3b>(i, j)[1];
            int r = src.at<Vec3b>(i, j)[2];

            dst.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(b + v);
            dst.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(g + v);
            dst.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(r + v);

        }
    }
    return dst;
}

/*----------------------------------------------增强--------------------------------------------*/
//色温
Mat colorTemperature(Mat src, int n) {
    Mat dst = src.clone();
    Mat lookupTable(1, 256, CV_8UC3);
    uchar* p = lookupTable.data;
    for (int i = 0; i < 256; i++) {
        int R, G, B;
        // R通道
        R = i + n;
        R = min(255, max(0, R));
        p[i * 3 + 2] = R;
        // G通道
        G = i + n;
        G = min(255, max(0, G));
        p[i * 3 + 1] = G;
        // B通道
        B = i - n;
        B = min(255, max(0, B));
        p[i * 3] = B;
    }
    LUT(src, lookupTable, dst);
    return dst;
}

//晕影
Mat vignetting(Mat src, int h, int w, double r, double p) {
    Mat maskImg(h, w, CV_64F, Scalar(1));
    double maxDis = sqrt(pow((double)(w - w / 2.0), 2) + pow((double)(h - h / 2.0), 2));
    double rad = r * maxDis;
    if (r != 0) {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                double temp = sqrt(pow((double)(h / 2.0 - i), 2) + pow((double)(w / 2.0 - j), 2)) / rad;
                double temp_s;
                if (temp >= (pi / 2)) {
                    temp_s = 0;
                }
                else {
                    temp = temp * p;
                    temp_s = pow(cos(temp), 4);
                }

                maskImg.at<double>(i, j) = temp_s;
            }
        }

        Mat labImg;
        cvtColor(src, labImg, COLOR_BGR2Lab);

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                Vec3b value = labImg.at<Vec3b>(i, j);
                value.val[0] *= maskImg.at<double>(i, j);
                labImg.at<Vec3b>(i, j) = value;
            }
        }
        Mat output;
        cvtColor(labImg, output, cv::COLOR_Lab2BGR);
        return output;
    }
    else {
        Mat dst(h, w, CV_8UC3, Scalar(0, 0, 0));
        return dst;
    }

}

//饱和度
Mat saturability(Mat src, double n) {
	Mat dst = src.clone();
	int h = src.rows;
	int w = src.cols;
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			int R = src.at<Vec3b>(i, j)[2];
			int G = src.at<Vec3b>(i, j)[1];
			int B = src.at<Vec3b>(i, j)[0];
			int Max = max(R, max(G, B));
			int Min = min(R, min(G, B));
			double delta, value;
			double L, S, alpha;
			delta = (Max - Min) / 255.0;
			//灰点不做处理
			if (delta == 0) {
				continue;
			}
			value = (Max + Min) / 255.0;
			L = value / 2.0;
			if (L < 0.5) {
				S = delta / (value*1.0);
			}
			else {
				S = (delta*1.0) / (2 - value);
			}
			if (n >= 0){
				if ((n + S) >= 1)alpha = S;
				else alpha = 1 - n;
				alpha = 1 / alpha - 1;
				dst.at<Vec3b>(i, j)[2] = R + (R - L * 255) * alpha;
				dst.at<Vec3b>(i, j)[1] = G + (G - L * 255) * alpha;
				dst.at<Vec3b>(i, j)[0] = B + (B - L * 255) * alpha;
			}
			else{
				alpha = n;
				dst.at<Vec3b>(i, j)[2] = L * 255 + (R - L * 255) * (1 + alpha);
				dst.at<Vec3b>(i, j)[1] = L * 255 + (G - L * 255) * (1 + alpha);
				dst.at<Vec3b>(i, j)[0] = L * 255 + (B - L * 255) * (1 + alpha);
			}
		}
	}
			return dst;
}

//亮度
Mat luminance(Mat src, double n) {
    Mat dst = src.clone();
    Mat lookupTable(1, 256, CV_8U);
    uchar* p = lookupTable.data;
    for (int i = 0; i < 256; i++)
        p[i] = max(0.0, min(255.0, ((i - 127.5 * (1 - n)) + 127.5 * (1 + n))));
    LUT(src, lookupTable, dst);
    return dst;
}

//对比度
Mat contrast(Mat src, double n) {
    Mat dst = src.clone();
    Mat lookupTable(1, 256, CV_8U);
    uchar* p = lookupTable.data;
    double k = tan((45 + 44 * n) / 180 * pi);
    for (int i = 0; i < 256; i++)
        p[i] = max(0.0, min(255.0, ((i - 127.5) * k + 127.5)));
    LUT(src, lookupTable, dst);
    return dst;
}

//色相
Mat hue(Mat src, int n) {
    Mat hlsImg;
    cvtColor(src, hlsImg, COLOR_BGR2HLS);
    int h = src.rows;
    int w = w = src.cols;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int hue = hlsImg.at<Vec3b>(i, j)[0] + n;
            if (hue < 0) {
                hue = hue + 360;
            }
            else if (hue > 360) {
                hue = hue - 360;
            }
            hlsImg.at<Vec3b>(i, j)[0] = hue;
        }
    }
    Mat dst;
    cvtColor(hlsImg, dst, COLOR_HLS2BGR);
    return dst;
}

//颗粒感
Mat granular(Mat src, int n) {
    int h = src.rows;
    int w = src.cols;
    Mat dst = src.clone();
    if (n != 0) {
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                dst.at<Vec3b>(i, j)[0] = max(0, min(255, src.at<Vec3b>(i, j)[0] + ((rand() % (2 * n)) - n)));
                dst.at<Vec3b>(i, j)[1] = max(0, min(255, src.at<Vec3b>(i, j)[1] + ((rand() % (2 * n)) - n)));
                dst.at<Vec3b>(i, j)[2] = max(0, min(255, src.at<Vec3b>(i, j)[2] + ((rand() % (2 * n)) - n)));
            }
        }
    }
    return dst;
}

//锐化
Mat sharpen(Mat src, double n) {
    Mat dst;
    Mat s = src.clone();
    Mat kernel;
    kernel = (Mat_<int>(3, 3) <<
        0, -1, 0,
        -1, 4, -1,
        0, -1, 0
        );
    cv::filter2D(s, s, s.depth(), kernel);
    dst = src + s * n;
    return dst;
}

//高光
// 图像高光选取
Mat HighLight(Mat input, int light)
{
    
    // 生成灰度图
    Mat gray = Mat::zeros(input.size(), CV_32FC1);
    Mat f = input.clone();
    f.convertTo(f, CV_32FC3);
    vector<Mat> pics;
    split(f, pics);
    gray = 0.299f * pics[2] + 0.587 * pics[1] + 0.114 * pics[0];
    gray = gray / 255.f;

    // 确定高光区
    Mat thresh = Mat::zeros(gray.size(), gray.type());
    thresh = gray.mul(gray);
    // 取平均值作为阈值
    Scalar t = mean(thresh);
    Mat mask = Mat::zeros(gray.size(), CV_8UC1);
    mask.setTo(255, thresh >= t[0]);

    // 参数设置
    int max = 4;
    float bright = light/ 100.0f/max;
    float mid = 1.0f + max * bright;

    // 边缘平滑过渡
    Mat midrate = Mat::zeros(input.size(), CV_32FC1);
    Mat brightrate = Mat::zeros(input.size(), CV_32FC1);
    for (int i = 0; i < input.rows; ++i)
    {
        uchar* m = mask.ptr<uchar>(i);
        float* th = thresh.ptr<float>(i);
        float* mi = midrate.ptr<float>(i);
        float* br = brightrate.ptr<float>(i);
        for (int j = 0; j < input.cols; ++j)
        {
            if (m[j] == 255)
            {
                mi[j] = mid;
                br[j] = bright;
            }
            else {
                mi[j] = (mid - 1.0f) / t[0] * th[j] + 1.0f;
                br[j] = (1.0f / t[0] * th[j]) * bright;
            }
        }
    }

    // 高光提亮，获取结果图
    Mat result = Mat::zeros(input.size(), input.type());
    for (int i = 0; i < input.rows; ++i)
    {
        float* mi = midrate.ptr<float>(i);
        float* br = brightrate.ptr<float>(i);
        uchar* in = input.ptr<uchar>(i);
        uchar* r = result.ptr<uchar>(i);
        for (int j = 0; j < input.cols; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                float temp = pow(float(in[3 * j + k]) / 255.f, 1.0f / mi[j]) * (1.0 / (1 - br[j]));
                if (temp > 1.0f)
                    temp = 1.0f;
                if (temp < 0.0f)
                    temp = 0.0f;
                uchar utemp = uchar(255 * temp);
                r[3 * j + k] = utemp;
            }

        }
    }
    return result;
    
}

//阴影
Mat Shadow(cv::Mat input, int light)
{
    // 生成灰度图
    cv::Mat gray = cv::Mat::zeros(input.size(), CV_32FC1);
    cv::Mat f = input.clone();
    f.convertTo(f, CV_32FC3);
    vector<cv::Mat> pics;
    split(f, pics);
    gray = 0.299f * pics[2] + 0.587 * pics[1] + 0.114 * pics[0];
    gray = gray / 255.f;

    // 确定阴影区
    cv::Mat thresh = cv::Mat::zeros(gray.size(), gray.type());
    thresh = (1.0f - gray).mul(1.0f - gray);
    // 取平均值作为阈值
    Scalar t = mean(thresh);
    cv::Mat mask = cv::Mat::zeros(gray.size(), CV_8UC1);
    mask.setTo(255, thresh >= t[0]);

    // 参数设置
    int max = 4;
    float bright = light / 100.0f / max;
    float mid = 1.0f + max * bright;

    // 边缘平滑过渡
    cv::Mat midrate = cv::Mat::zeros(input.size(), CV_32FC1);
    cv::Mat brightrate = cv::Mat::zeros(input.size(), CV_32FC1);
    for (int i = 0; i < input.rows; ++i)
    {
        uchar* m = mask.ptr<uchar>(i);
        float* th = thresh.ptr<float>(i);
        float* mi = midrate.ptr<float>(i);
        float* br = brightrate.ptr<float>(i);
        for (int j = 0; j < input.cols; ++j)
        {
            if (m[j] == 255)
            {
                mi[j] = mid;
                br[j] = bright;
            }
            else {
                mi[j] = (mid - 1.0f) / t[0] * th[j] + 1.0f;
                br[j] = (1.0f / t[0] * th[j]) * bright;
            }
        }
    }

    // 阴影提亮，获取结果图
    cv::Mat result = cv::Mat::zeros(input.size(), input.type());
    for (int i = 0; i < input.rows; ++i)
    {
        float* mi = midrate.ptr<float>(i);
        float* br = brightrate.ptr<float>(i);
        uchar* in = input.ptr<uchar>(i);
        uchar* r = result.ptr<uchar>(i);
        for (int j = 0; j < input.cols; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                float temp = pow(float(in[3 * j + k]) / 255.f, 1.0f / mi[j]) * (1.0 / (1 - br[j]));
                if (temp > 1.0f)
                    temp = 1.0f;
                if (temp < 0.0f)
                    temp = 0.0f;
                uchar utemp = uchar(255 * temp);
                r[3 * j + k] = utemp;
            }

        }
    }
    return result;
}

Mat reversal(Mat src) {
    Mat dst = src.clone();
    Mat lookupTable(1, 256, CV_8U);
    uchar* p = lookupTable.data;
    for (int i = 0; i < 256; i++)
        p[i] = 255 - i;
    LUT(src, lookupTable, dst);
    return dst;
}
Mat grey(Mat src) {
    Mat grey;
    cvtColor(src, grey, cv::COLOR_BGR2GRAY);
    return grey;
}

Mat whiteAndBlack(Mat src, int n) {
    
    Mat grey;
    cvtColor(src, grey, cv::COLOR_BGR2GRAY);
    Mat dst = grey.clone();
    Mat lookupTable(1, 256, CV_8U);
    uchar* p = lookupTable.data;
    for (int i = 0; i < 256; i++) {
        if (i > n)p[i] = 255;
        else p[i] = 0;
    }
    LUT(grey, lookupTable, dst);
    return dst;
}

Mat homochromy(Mat src, int n) {
    int h = src.rows;
    int w = src.cols;
    Mat dst = src.clone();
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            for (int k = 0; k < 3; k++) {
                if (k != n) {
                    dst.at<Vec3b>(i, j)[k] = 0;
                }
            }
        }
    }
    return dst;
}

//水彩
Mat watercolor(Mat src, int n, float m) {
    Mat res;
    stylization(src, res, n, m);
    return res;
}

//描线
Mat linedraw(Mat src) {
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    Mat gaussian;
    GaussianBlur(gray, gaussian, Size(3, 3), 0);
    Mat canny;
    Canny(gaussian, canny, 50, 140);
    Mat result;
    threshold(canny, result, 90, 255, THRESH_BINARY_INV);
    return result;
}

//凸透镜
Mat convex(Mat src, int n) {
    int h = src.rows;
    int w = src.cols;
    int channel = src.channels();

    Mat canvas(h, w, src.type(), Scalar(0, 0, 0));

    double center_x = h / 2.0;
    double center_y = w / 2.0;
    double radius = n;
    if (n != 0) {
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                double distance = (i - center_x) * (i - center_x) + (j - center_y) * (j - center_y);
                double new_dist = sqrt(distance);

                // Copy original pixel value to canvas
                for (int c = 0; c < channel; ++c) {
                    canvas.at<Vec3b>(i, j)[c] = src.at<Vec3b>(i, j)[c];
                }

                // Apply distortion if within circle
                if (distance <= radius * radius) {
                    int new_i = floor(new_dist * (i - center_x) / radius + center_x);
                    int new_j = floor(new_dist * (j - center_y) / radius + center_y);

                    // Copy distorted pixel value to canvas
                    for (int c = 0; c < channel; ++c) {
                        canvas.at<Vec3b>(i, j)[c] = src.at<Vec3b>(new_i, new_j)[c];
                    }
                }
            }
        }
        return canvas;
    }
    else return src;
}

Mat concave(Mat img, int nn) {
    if (nn != 0) {
        int h = img.rows;
        int w = img.cols;
        int n = img.channels();
        int cx = w / 2;
        int cy = h / 2;
        int compress = nn;
        Mat new_img = img.clone();
        for (int i = 0; i < w; ++i) {
            for (int j = 0; j < h; ++j) {
                int tx = i - cx;
                int ty = j - cy;
                int x = cx + std::sqrt(std::sqrt(tx * tx + ty * ty)) * compress * std::cos(std::atan2(ty, tx));
                int y = cy + std::sqrt(std::sqrt(tx * tx + ty * ty)) * compress * std::sin(std::atan2(ty, tx));

                if (x < 0 || x >= w) x = 0;
                if (y < 0 || y >= h) y = 0;

                if (x < w && y < h) {
                    new_img.at<cv::Vec3b>(j, i)[0] = img.at<cv::Vec3b>(y, x)[0];
                    new_img.at<cv::Vec3b>(j, i)[1] = img.at<cv::Vec3b>(y, x)[1];
                    new_img.at<cv::Vec3b>(j, i)[2] = img.at<cv::Vec3b>(y, x)[2];
                }
            }
        }
        return new_img;
    }
    else return img;
}
Mat neon(Mat src, int n) {
    int h = src.rows;
    int w = src.cols;
    Mat dst = src.clone();
    if (n != 0) {
        for (int i = 0; i < h - 1; i++) {
            
            for (int j = 0; j < w - 1; j++) {

                //当前像素的RGB分量
                int b1 = dst.at<Vec3b>(i, j)[0];
                int g1 = dst.at<Vec3b>(i, j)[1];
                int r1 = dst.at<Vec3b>(i, j)[2];

                //同行下一个像素的RGB分量
                int b2 = dst.at<Vec3b>(i, j + 1)[0];
                int g2 = dst.at<Vec3b>(i, j + 1)[1];
                int r2 = dst.at<Vec3b>(i, j + 1)[2];

             

                //同列正下方的像素的RGB分量
                int b3 = dst.at<Vec3b>(i + 1, j)[0];
                int g3 = dst.at<Vec3b>(i + 1, j)[1];
                int r3 = dst.at<Vec3b>(i + 1, j)[2];

                

                //计算新的RGB分量的值
                int R = n * sqrt((r1 - r2) * (r1 - r2) + (r1 - r3) * (r1 - r3));
                int G = n * sqrt((g1 - g2) * (g1 - g2) + (g1 - g3) * (g1 - g3));
                int B = n * sqrt((b1 - b2) * (b1 - b2) + (b1 - b3) * (b1 - b3));

                dst.at<Vec3b>(i, j)[0] = max(0, min(B, 255));;
                dst.at<Vec3b>(i, j)[1] = max(0, min(G, 255));;
                dst.at<Vec3b>(i, j)[2] = max(0, min(R, 255));;
            }
        }
    }
    return dst;
}
Mat ghost(Mat src, int n) {
    int OffsetJ[4] = { n, -n, -n, n };
    int OffsetI[4] = { -n, -n, n, n };
    Mat dst = src.clone();
    int sumB, sumG, sumR;
    for (int j = 0; j < dst.rows; j++) {
        for (int i = 0; i < dst.cols; i++) {
            sumB = 0; sumG = 0; sumR = 0;
            for (int k = 0; k < 4; k++) {
                int JJ = j + OffsetJ[k];
                int II = i + OffsetI[k];

                //防止越界
                if (JJ < 0) {
                    JJ = 0;
                }
                else if (JJ >= dst.rows) {
                    JJ = dst.rows - 1;
                }
                if (II < 0) {
                    II = 0;
                }
                else if (II >= dst.cols) {
                    II = dst.cols - 1;
                }

                //累加，求当前像素点的左下，左上，右上，右下四个偏移量的和
                sumB += dst.at<Vec3b>(JJ, II)[0];
                sumG += dst.at<Vec3b>(JJ, II)[1];
                sumR += dst.at<Vec3b>(JJ, II)[2];
            }
            //求平均值，求平均值(sum+2)/4,
            //为什么要+2，就为了四舍五入。比如如果计算结果为108.6，则取像素109更为合理     
            dst.at<Vec3b>(j, i)[2] = (sumR + 2) >> 2;
            dst.at<Vec3b>(j, i)[1] = (sumG + 2) >> 2;
            dst.at<Vec3b>(j, i)[0] = (sumB + 2) >> 2;
        }
    }
    return dst;
}