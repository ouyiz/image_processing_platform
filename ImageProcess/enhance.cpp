#include"enhance.h"

//晕影
//Lab颜色空间与人类感知更加一致
Mat Enhance::vignetting(Mat src, int h, int w, double r, double p) {
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
        cvtColor(labImg, output, COLOR_Lab2BGR);
        return output;
    }
    else {
        Mat dst(h, w, CV_8UC3, Scalar(0, 0, 0));
        return dst;
    }

}

//亮度
//三通道值增大
Mat Enhance::luminance(Mat src, double n) {
    Mat dst = src.clone();
    Mat lookupTable(1, 256, CV_8U);
    uchar* p = lookupTable.data;
    for (int i = 0; i < 256; i++)
        p[i] = max(0.0, min(255.0, (i + 127.5 * n)));
    LUT(src, lookupTable, dst);
    return dst;
}

//对比度
//线性变换
Mat Enhance::contrast(Mat src, double n) {
    Mat dst = src.clone();
    Mat lookupTable(1, 256, CV_8U);
    uchar* p = lookupTable.data;
    double k = tan((45 + 44 * n) / 180 * pi);
    for (int i = 0; i < 256; i++)
        p[i] = max(0.0, min(255.0, ((i - 127.5) * k + 127.5)));
    LUT(src, lookupTable, dst);
    return dst;
}

//色温
//在提高色温的时候，对红色和绿色通道进行增强，对蓝色通道进行减弱
Mat Enhance::colorTemperature(Mat src, int n) {
    Mat dst = src.clone();
    Mat lookupTable(1, 256, CV_8UC3);
    uchar* p = lookupTable.data;
    for (int i = 0; i < 256; i++) {
        int R, G, B;
        R = i + n;
        R = min(255, max(0, R));
        p[i * 3 + 2] = R;
        G = i + n;
        G = min(255, max(0, G));
        p[i * 3 + 1] = G;
        B = i - n;
        B = min(255, max(0, B));
        p[i * 3] = B;
    }
    LUT(src, lookupTable, dst);
    return dst;
}

//高光
Mat Enhance::HighLight(Mat src, int n)
{
    Mat gray = Mat::zeros(src.size(), CV_32FC1);
    Mat f = src.clone();
    f.convertTo(f, CV_32FC3);
    vector<Mat> pics;
    split(f, pics);
    gray = 0.299f * pics[2] + 0.587 * pics[1] + 0.114 * pics[0];
    //cvtColor(src, gray, COLOR_BGR2GRAY);
    gray = gray / 255.f;
    Mat mask = Mat::zeros(gray.size(), gray.type());
    mask = gray.mul(gray);//使亮的更亮
    Scalar t = mean(mask);
    Mat thresh = Mat::zeros(gray.size(), CV_8UC1);
    threshold(mask, thresh, t[0], 255, THRESH_BINARY);//高于为白
    int max = 4;
    float bright = n / 100.0f / max;
    float mid = 1.0f + max * bright;
    //边缘平滑过渡
    Mat midrate = Mat::zeros(src.size(), CV_32FC1);
    Mat brightrate = Mat::zeros(src.size(), CV_32FC1);
    for (int i = 0; i < src.rows; ++i)
    {
        uchar* m = thresh.ptr<uchar>(i);
        float* th = mask.ptr<float>(i);
        float* mi = midrate.ptr<float>(i);
        float* br = brightrate.ptr<float>(i);
        for (int j = 0; j < src.cols; ++j)
        {
            if (m[j] == 255)
            {
                mi[j] = mid;
                br[j] = bright;
            }
            else {
                mi[j] = (mid - 1.0f) / t[0] * th[j] + 1.0f;//亮度平滑过渡
                br[j] = (1.0f / t[0] * th[j]) * bright;
            }
        }
    }
    Mat dst = Mat::zeros(src.size(), src.type());
    for (int i = 0; i < src.rows; ++i)
    {
        float* mi = midrate.ptr<float>(i);
        float* br = brightrate.ptr<float>(i);
        uchar* in = src.ptr<uchar>(i);
        uchar* r = dst.ptr<uchar>(i);
        for (int j = 0; j < src.cols; ++j)
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
    return dst;
}

//饱和度
Mat Enhance::saturability(Mat src, double n) {
    Mat dst = src.clone();
    int h = src.rows;
    int w = src.cols;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int R = src.at<Vec3b>(i, j)[2];
            int G = src.at<Vec3b>(i, j)[1];
            int B = src.at<Vec3b>(i, j)[0];
            //计算RGB三通道的最大值最小值
            int Max = max(R, max(G, B));
            int Min = min(R, min(G, B));
            double delta, value;
            double L, S, alpha;
            delta = (Max - Min) / 255.0;
            if (delta == 0) {//灰点不需要继续操作
                continue;
            }
            value = (Max + Min) / 255.0;
            L = value / 2.0;//HSL的L值
            if (L < 0.5) {//计算HSL的S值
                S = delta / (value * 1.0);
            }
            else {
                S = (delta * 1.0) / (2 - value);
            }
            if (n >= 0) {//提供饱和度
                if ((n + S) >= 1)alpha = S;
                else alpha = 1 - n;
                alpha = 1 / alpha - 1;
                dst.at<Vec3b>(i, j)[2] = R + (R - L * 255) * alpha;
                dst.at<Vec3b>(i, j)[1] = G + (G - L * 255) * alpha;
                dst.at<Vec3b>(i, j)[0] = B + (B - L * 255) * alpha;
            }
            else {//降低饱和度
                alpha = n;
                dst.at<Vec3b>(i, j)[2] = L * 255 + (R - L * 255) * (1 + alpha);
                dst.at<Vec3b>(i, j)[1] = L * 255 + (G - L * 255) * (1 + alpha);
                dst.at<Vec3b>(i, j)[0] = L * 255 + (B - L * 255) * (1 + alpha);
            }
        }
    }
    return dst;
}
/*
Mat Enhance::saturability(Mat src, double n) {
    Mat hlsImg;
    cvtColor(src, hlsImg, COLOR_BGR2HLS);
    int h = src.rows;
    int w = w = src.cols;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            double hue = hlsImg.at<Vec3b>(i, j)[2]*n;
            hlsImg.at<Vec3b>(i, j)[2] = hue;
        }
    }
    Mat dst;
    cvtColor(hlsImg, dst, COLOR_HLS2BGR);
    return dst;
}
*/

//色相
//色相（H）、亮度（L）、饱和度（S）
Mat Enhance::hue(Mat src, int n) {
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
//对输入图像的每个像素值添加随机增量来模拟颗粒感
Mat Enhance::granular(Mat src, int n) {
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
Mat Enhance::sharpen(Mat src, double n) {
    Mat dst;
    Mat s = src.clone();
    Mat kernel;
    kernel = (Mat_<int>(3, 3) <<
        0, -1, 0,
        -1, 4, -1,
        0, -1, 0
        );
    filter2D(s, s, s.depth(), kernel);
    dst = src + s * n;
    return dst;
}


//阴影
Mat Enhance::Shadow(cv::Mat src, int light)
{
    // 生成灰度图
    Mat gray = Mat::zeros(src.size(), CV_32FC1);
    Mat f = src.clone();
    f.convertTo(f, CV_32FC3);
    vector<Mat> pics;
    split(f, pics);
    gray = 0.299f * pics[2] + 0.587 * pics[1] + 0.114 * pics[0];
    //cvtColor(src, gray, COLOR_BGR2GRAY);
    gray = gray / 255.f;
    // 确定阴影区
    Mat thresh = cv::Mat::zeros(gray.size(), gray.type());
    thresh = (1.0f - gray).mul(1.0f - gray);
    // 取平均值作为阈值
    Scalar t = mean(thresh);
    Mat mask = Mat::zeros(gray.size(), CV_8UC1);
    threshold(thresh, mask, t[0], 255, THRESH_BINARY);
    // 参数设置
    int max = 4;
    float bright = light / 100.0f / max;
    float mid = 1.0f + max * bright;
    // 边缘平滑过渡
    Mat midrate = Mat::zeros(src.size(), CV_32FC1);
    Mat brightrate = Mat::zeros(src.size(), CV_32FC1);
    for (int i = 0; i < src.rows; ++i)
    {
        uchar* m = mask.ptr<uchar>(i);
        float* th = thresh.ptr<float>(i);
        float* mi = midrate.ptr<float>(i);
        float* br = brightrate.ptr<float>(i);
        for (int j = 0; j < src.cols; ++j)
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
    Mat dst = Mat::zeros(src.size(), src.type());
    for (int i = 0; i < src.rows; ++i)
    {
        float* mi = midrate.ptr<float>(i);
        float* br = brightrate.ptr<float>(i);
        uchar* in = src.ptr<uchar>(i);
        uchar* r = dst.ptr<uchar>(i);
        for (int j = 0; j < src.cols; ++j)
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
    return dst;
}
