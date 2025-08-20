#include"filter.h"

//毛玻璃效果
//在输入图像的每个像素周围添加随机偏移量来模拟图像被玻璃片扭曲的效果
Mat Filter::glass(Mat src,int n) {
    int h = src.rows;
    int w = src.cols;
    int m = min(h, w);
    n = n * m / 100;
    n = (n / 2) * 2 + 1;
    Mat dst(h, w, CV_8UC3, Scalar(0, 0, 0));
    int i, j;
    if (n == 0) {
        return src;
    }
    Mat src1;
    copyMakeBorder(src, src1, n / 2, n / 2, n / 2, n / 2, BORDER_REFLECT);
    for (i = 0; i < h ; ++i) {
        for (j = 0; j < w ; ++j) {
            int index = n / 2 - rand() % n;
            dst.at<Vec3b>(i, j) = src1.at<Vec3b>(i + index+n/2, j + index+n/2);
        }
    }
    
    return dst;
}
//素描效果
//对灰度图像进行高斯模糊和反转操作，并与原始灰度图像相除，最后将结果转换回彩色图像以产生素描效果
Mat Filter::sketch(Mat src, int n1, int n2) {
    if (n1 == 0 || n2 == 0) {
        return src;
    }
    else {
        Mat gray;
        cvtColor(src, gray, COLOR_BGR2GRAY);
        int h = src.rows;
        int w = src.cols;
        n1 = (n1 / 2) * 2 + 1;
        Mat gauss;
        GaussianBlur(gray, gauss, Size(n1, n1), 0);
        Mat inverGauss = 255 - gauss;
        Mat dst;
        divide(gray, inverGauss, dst, n2);
        Mat dst1;
        cvtColor(dst, dst1, cv::COLOR_GRAY2BGR);
        return dst1;
    }
}

//浮雕效果
Mat Filter::relief(Mat src, int n) {
    int h = src.rows;
    int w = src.cols;
    Mat gray;
    cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    Mat dst(h, w, CV_8UC1, Scalar(0));
    for (int i = 1; i < h - 1; ++i) {
        for (int j = 1; j < w - 1; ++j) {
            int edge = (int)(gray.at<uchar>(i - 1, j - 1)) - (int)(gray.at<uchar>(i + 1, j + 1));
            int val = edge + n;
            val = min(max(val, 0), 255);
            dst.at<uchar>(i, j) = static_cast<uchar>(val);
        }
    }
    Mat dst1;
    cvtColor(dst, dst1, cv::COLOR_GRAY2BGR);
    return dst1;
}

//雕刻效果
Mat Filter::scuplture(Mat src, int n) {
    int h = src.rows;
    int w = src.cols;
    Mat gray;
    cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    Mat dst(h, w, CV_8UC1, Scalar(0));
    for (int i = 1; i < h - 1; ++i) {
        for (int j = 1; j < w - 1; ++j) {
            int edge = (int)(gray.at<uchar>(i + 1, j + 1)) - (int)(gray.at<uchar>(i - 1, j - 1));
            int val = edge + n;
            val = min(max(val, 0), 255);
            dst.at<uchar>(i, j) = static_cast<uchar>(val);
        }
    }
    Mat dst1;
    cvtColor(dst, dst1, cv::COLOR_GRAY2BGR);
    return dst1;
}



//油画
Mat oil1(Mat src,int level, int radius) {
    int h = src.rows;
    int w=src.cols;
    Mat oilImg(h, w, CV_8UC3, Scalar(0, 0, 0));
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
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

//对每个元素执行，S性运行，节约时间
//hor为1代窗向右移动， -1代表向左移动， 0代表向下移动
void load_in(bool isFirst, int hor, int x, int y, int radius, int bucket[], Mat& image, Mat& gray) {
    if (isFirst) {
        //第一次进行窗口元素统计的方法，此时窗中的每一个元素都要被统计到
        int current_y = 0;
        int current_x = 0;
        for (int i = -radius; i < radius + 1; i++)
        {
            for (int j = -radius; j < radius + 1; j++)
            {
                current_y = y + i;
                current_x = x + j;
                int current_level = gray.at<uchar>(current_y + radius, current_x + radius);
                Vec3b color = image.at<Vec3b>(current_y+radius, current_x + radius);
                bucket[current_level * 4] += 1;
                bucket[current_level * 4 + 1] += color[2];  
                bucket[current_level * 4 + 2] += color[1]; 
                bucket[current_level * 4 + 3] += color[0];
            }
        }
    }
    else
    {
        if (hor != 0)
        {
            //只需要增加列与删除列
            int current_in_x = x + (radius + 1) * hor;//增加的列
            int current_out_x = x - radius * hor;//删除的列
            for (int i = -radius; i < radius + 1; i++)
            {

                int current_y = i + y;
                int current_level = gray.at<uchar>(current_y + radius, current_in_x + radius);
                Vec3b color = image.at<Vec3b>(current_y + radius, current_in_x + radius);
                bucket[current_level * 4] += 1;
                bucket[current_level * 4 + 1] += color[2];
                bucket[current_level * 4 + 2] += color[1];
                bucket[current_level * 4 + 3] += color[0];
                current_level = gray.at<uchar>(current_y + radius, current_out_x + radius);
                color = image.at<Vec3b>(current_y + radius, current_out_x + radius);
                bucket[current_level * 4] -= 1;
                bucket[current_level * 4 + 1] -= color[2];  
                bucket[current_level * 4 + 2] -= color[1];  
                bucket[current_level * 4 + 3] -= color[0];  
            }
        }
        else
        {
            //增加行与删除行
            int current_in_y = y + radius + 1;
            int current_out_y = y - radius;
            for (int i = -radius; i < radius + 1; i++)
            {
                int current_x = i + x;
                int current_level = gray.at<uchar>(current_in_y + radius, current_x + radius);
                Vec3b color = image.at<Vec3b>(current_in_y + radius, current_x + radius);
                bucket[current_level * 4] += 1;
                bucket[current_level * 4 + 1] += color[2];
                bucket[current_level * 4 + 2] += color[1];
                bucket[current_level * 4 + 3] += color[0];
               
                current_level = gray.at<uchar>(current_out_y + radius, current_x + radius);
                color = image.at<Vec3b>(current_out_y + radius, current_x + radius);
                bucket[current_level * 4] -= 1;
                bucket[current_level * 4 + 1] -= color[2];  
                bucket[current_level * 4 + 2] -= color[1];  
                bucket[current_level * 4 + 3] -= color[0];  
            }
        }
    }
}

Vec3b update_RGB(int level, int bucket[])
{
    int most_level = 0;
    int most_times = 0;
    //找出最多的
    for (int i = 0; i < level; i++)
    {
        int times = bucket[i * 4];
        if (times > most_times)
        {
            most_times = times;
            most_level = i;
        }
    }
    //更新值
    int r_sum = bucket[most_level * 4 + 1];
    int g_sum = bucket[most_level * 4 + 2];
    int b_sum = bucket[most_level * 4 + 3];
    int current_r = r_sum / most_times;
    int current_g = g_sum / most_times;
    int current_b = b_sum / most_times;
    return Vec3b(current_b, current_g, current_r);
    //cout << "r, g, b" << current_r << ", " << current_g << ", " << current_b << endl;
}
//油画
Mat Filter::oil(Mat src, int level, int radius) {
    if (radius != 0 && level != 0) {
        int* bucket;
        int h = src.rows;
        int w = src.cols;
        int len;
        Mat oil_image;
        oil_image = src.clone();
        double scale;
        scale = level / 256.0;
        Mat srcadd;
        copyMakeBorder(src, srcadd, radius, radius, radius, radius, BORDER_REFLECT);
        Mat gray;
        cvtColor(srcadd, gray, COLOR_BGR2GRAY);
        //得到每个像素的灰度级
        for (int i = 0; i < gray.rows; i++)
        {
            for (int j = 0; j < gray.cols; j++)
            {
                gray.at<uchar>(i, j) = gray.at<uchar>(i, j) * scale;
            }
        }
        len = radius * 2 + 1;
        bucket = new int[level * 4];
        memset(bucket, 0, level * 4 * 4);//数组初始化为0
        bool isFirst = true;
        //首次计算窗口
        load_in(isFirst, 0, 0, 0, radius, bucket, srcadd, gray);
        oil_image.at<Vec3b>(radius, radius) = update_RGB(level, bucket);
        int hor = 1;
        isFirst = false;
        int k = 0;
        //按行循环
        for (int i = 0; i < h; i++)
        {
            if (hor == 1) 
            {
                //窗口向右移动
                for (int j = 0; j < w - 1; j++)
                {
                    load_in(isFirst, hor, j, i, radius, bucket, srcadd, gray);
                    oil_image.at<Vec3b>(i, j + 1) = update_RGB(level, bucket);

                    k = j;
                }
            }
            else
            {
                //窗口向左移动
                for (int j = w - 1; j > 0; j--)

                {
                    load_in(isFirst, hor, j, i, radius, bucket, srcadd, gray);

                    oil_image.at<Vec3b>(i, j - 1) = update_RGB(level, bucket);
                    k = j;
                }

            }
            //全部遍历完
            if (i == h  - 1)
                return oil_image;
            if (hor == 1)
            {
                //窗口向下移动
                load_in(isFirst, 0, w - 1, i, radius, bucket, srcadd, gray);
                oil_image.at<Vec3b>(i + 1, w- 1) = update_RGB(level, bucket);
            }
            else
            {
                // 窗口向下移动
                load_in(isFirst, 0, 0, i, radius, bucket, srcadd, gray);
                oil_image.at<Vec3b>(i + 1, 0) = update_RGB(level, bucket);
            }
            //反向
            hor = -hor;

        }
        return oil_image;
    }
    else return src;
}

//马赛克
//通过将图像分割成多个小块，然后对每个小块内的像素进行像素化处理，即用块内的某个颜色代替所有像素的颜色，从而实现图像的模糊和抽象化效果。
Mat Filter::myMask(Mat src, int n) {
    if (n <= 1) {
        return src; 
    }
    Mat dst = src.clone();
    int h = src.rows;
    int w = src.cols;
    for (int i = 0; i < h; i += n) {
        for (int j = 0; j < w; j += n) {
           
            Rect roi(j, i, min(n, w - j), min(n, h - i));
            Mat roiImg = dst(roi);
            Vec3b avgColor = src.at<Vec3b>(i, j);
            rectangle(dst, roi, avgColor, CV_FILLED);
        }
    }

    return dst;

}

//卡通效果
//卡通效果的原理是通过减少图像的细节和边缘信息，从而使图像看起来更加平滑和简化，就像是手绘的卡通画一样
Mat Filter::cartoon(Mat src,  int res) {
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    int h = src.rows;
    int w = src.cols;
    int n = (res / 2) * 2 + 1;
    int num_bilateral = n;
    Mat img_color = src;
    for (int i = 0; i < num_bilateral; i++) {
        Mat temp;
        bilateralFilter(img_color, temp, 9, n, 7);
        img_color = temp;
    }
    medianBlur(gray, gray, 9);
    Mat img_edge;
    adaptiveThreshold(gray, img_edge, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 9, 2);
    cvtColor(img_edge, img_edge, COLOR_GRAY2BGR);
    Mat img_cartoon;
    bitwise_and(img_color, img_edge, img_cartoon);
    return img_cartoon;
}

//光照
//通过计算像素与光源之间的距离，根据距离和光照强度调整像素的颜色，从而实现了基于距离的光照效果
Mat Filter::illumination(Mat src, int h, int w, int n) {
    if (n != 0) {
        double centerX = h / 2.0;
        double centerY = w / 2.0;
        double radius = min(centerX, centerY);
        Mat dst(h, w, CV_8UC3, Scalar(0, 0, 0));
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                double distance = pow((centerY - j), 2) + pow((centerX - i), 2);
                int B = src.at<Vec3b>(i, j)[0];
                int G = src.at<Vec3b>(i, j)[1];
                int R = src.at<Vec3b>(i, j)[2];
                if (distance < radius * radius) {
                    int result = static_cast<int>(n * (1.0 - sqrt(distance) / radius));
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
//高斯滤波
Mat Filter::dim(Mat src, int h, int w, int res) {
    int n = (res / 2) * 2 + 1;
    Mat source;
    Mat result;
    GaussianBlur(src, result, Size(n, n), 0);
    return result;
}

//怀旧效果
//公式
Mat Filter::old(Mat src, int h, int w) {
   
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

//单色
//只保留输入图像中指定通道（R、G 或 B）的颜色，将其他通道的颜色置为0。
Mat Filter::homochromy(Mat src, int n) {
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

//熔铸
Mat Filter::casting(Mat src, int h, int w) {
    Mat  dst(h, w, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            dst.at<Vec3b>(i, j)[0] = min(255, max(0, (128 * src.at<Vec3b>(i, j)[0] / (src.at<Vec3b>(i, j)[1] + src.at<Vec3b>(i, j)[2] + 1))));
            dst.at<Vec3b>(i, j)[1] = min(255, max(0, (128 * src.at<Vec3b>(i, j)[1] / (src.at<Vec3b>(i, j)[0] + src.at<Vec3b>(i, j)[2] + 1))));
            dst.at<Vec3b>(i, j)[2] = min(255, max(0, (128 * src.at<Vec3b>(i, j)[2] / (src.at<Vec3b>(i, j)[0] + src.at<Vec3b>(i, j)[1] + 1))));
        }
    }
    return dst;
}

//冰冻
Mat Filter::frozen(Mat src, int h, int w) {
    Mat  dst(h, w, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            dst.at<Vec3b>(i, j)[0] = (min(255, max(0, abs(src.at<cv::Vec3b>(i, j)[0] - src.at<Vec3b>(i, j)[1] - src.at<Vec3b>(i, j)[2]) * 3 >> 2)));
            dst.at<Vec3b>(i, j)[1] = (min(255, max(0, abs(src.at<cv::Vec3b>(i, j)[1] - src.at<Vec3b>(i, j)[0] - src.at<Vec3b>(i, j)[2]) * 3 >> 2)));
            dst.at<Vec3b>(i, j)[2] = (min(255, max(0, abs(src.at<cv::Vec3b>(i, j)[2] - src.at<Vec3b>(i, j)[0] - src.at<Vec3b>(i, j)[1]) * 3 >> 2)));
        }
    }
    return dst;
}

//连环画
Mat Filter::comic(Mat src, int h, int w) {
    Mat  dst(h, w, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int r = src.at<Vec3b>(i, j)[2];
            int g = src.at<Vec3b>(i, j)[1];
            int b = src.at<Vec3b>(i, j)[0];

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
//在图像中心以外的像素上，通过对rgb值增加额外的V值实现朦胧效果。
Mat Filter::feather(Mat src, int h, int w, double n) {
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

//灰度
Mat Filter::grey(Mat src) {
    Mat dst;
    cvtColor(src, dst, COLOR_BGR2GRAY);
    Mat dst1;
    cvtColor(dst, dst1, COLOR_GRAY2BGR);
    return dst1;
}

//黑白
Mat Filter::whiteAndBlack(Mat src, int n) {
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
    Mat dst1;
    cvtColor(dst, dst1, COLOR_GRAY2BGR);
    return dst1;
}

//流年效果
//根据像素的蓝色通道强度来调整像素的亮度
Mat Filter::fleet(Mat src, int h, int w, int n) {
    Mat dst(h, w, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            double b = sqrt(src.at<Vec3b>(i, j)[0]) * n;
            double g = src.at<Vec3b>(i, j)[1];
            double r = src.at<Vec3b>(i, j)[2];
            b = min(b, 255.0);
            dst.at<Vec3b>(i, j) = Vec3b((uchar)(b), (uchar)(g), (uchar)(r));
        }
    }
    return dst;
}

//水彩
//使用stylization函数（双边滤波器，计算原始图像与风格化后的图像之间的细节差异，将细节图像增强到原始图像上）
Mat Filter::watercolor(Mat src, int n, float m) {
    Mat res;
    stylization(src, res, n, m);
    return res;
}

//描线
//canny边缘检测
Mat Filter::linedraw(Mat src) {
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    Mat gaussian;
    GaussianBlur(gray, gaussian, Size(3, 3), 0);
    Mat canny;
    Canny(gaussian, canny, 50, 140);
    Mat result;
    threshold(canny, result, 90, 255, THRESH_BINARY_INV);
    Mat dst1;
    cvtColor(result, dst1, COLOR_GRAY2BGR);
    return dst1;
}

//凸透镜
Mat Filter::convex(Mat src, int n) {
    int h = src.rows;
    int w = src.cols;
    int channel = src.channels();
    Mat dst(h, w, src.type(), Scalar(0, 0, 0));
    double center_x = h / 2.0;
    double center_y = w / 2.0;
    double radius = n;
    if (n != 0) {
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                double distance = (i - center_x) * (i - center_x) + (j - center_y) * (j - center_y);
                double new_dist = sqrt(distance);
                for (int c = 0; c < channel; ++c) {
                    dst.at<Vec3b>(i, j)[c] = src.at<Vec3b>(i, j)[c];
                }
                if (distance <= radius * radius) {
                    int new_i = floor(new_dist * (i - center_x) / radius + center_x);
                    int new_j = floor(new_dist * (j - center_y) / radius + center_y);
                    if (new_i < 0 || new_i >= w) new_i = 0;
                    if (new_j < 0 || new_j >= h) new_j = 0;
                    for (int c = 0; c < channel; ++c) {
                        dst.at<Vec3b>(i, j)[c] = src.at<Vec3b>(new_i, new_j)[c];
                    }
                }
            }
        }
        return dst;
    }
    else return src;
}

//凹透镜
Mat Filter::concave(Mat img, int n) {
    if (n != 0) {
        int h = img.rows;
        int w = img.cols;
        int num = img.channels();
        int cx = w / 2;
        int cy = h / 2;
        Mat new_img = img.clone();
        for (int i = 0; i < w; ++i) {
            for (int j = 0; j < h; ++j) {
                int dx = i - cx;
                int dy = j - cy;
                int x = cx + sqrt(sqrt(dx * dx + dy * dy)) * n * cos(atan2(dy, dx));
                int y = cy + sqrt(sqrt(dx * dx + dy * dy)) * n * sin(atan2(dy, dx));

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

//霓虹
//将当前像素与其同列正下方和右方的像素的RGB分量分别做梯度运算
Mat Filter::neon(Mat src, int n) {
    int h = src.rows;
    int w = src.cols;
    Mat dst = src.clone();
    if (n != 0) {
        for (int i = 0; i < h - 1; i++) {
            for (int j = 0; j < w - 1; j++) {
                int b1 = dst.at<Vec3b>(i, j)[0];
                int g1 = dst.at<Vec3b>(i, j)[1];
                int r1 = dst.at<Vec3b>(i, j)[2];

                int b2 = dst.at<Vec3b>(i, j + 1)[0];
                int g2 = dst.at<Vec3b>(i, j + 1)[1];
                int r2 = dst.at<Vec3b>(i, j + 1)[2];

                int b3 = dst.at<Vec3b>(i + 1, j)[0];
                int g3 = dst.at<Vec3b>(i + 1, j)[1];
                int r3 = dst.at<Vec3b>(i + 1, j)[2];
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

//重影
//创建四个相互偏移的副本，叠加之后产生类似重影的效果。偏移方向为左上，左下，右上，右下，偏移角度为45度
Mat Filter::ghost(Mat src, int n) {
    int OffsetJ[4] = { n, -n, -n, n };
    int OffsetI[4] = { -n, -n, n, n };
    Mat dst = src.clone();
    int sumB, sumG, sumR;
    for (int j = 0; j < dst.rows; j++) {
        for (int i = 0; i < dst.cols; i++) {
            sumB = 0; sumG = 0; sumR = 0;
            for (int k = 0; k < 4; k++) {
                int jj = j + OffsetJ[k];
                int ii = i + OffsetI[k];
                jj = max(0, min(dst.rows - 1, jj));
                ii = max(0, min(dst.cols - 1, ii));
                sumB += dst.at<Vec3b>(jj, ii)[0];
                sumG += dst.at<Vec3b>(jj, ii)[1];
                sumR += dst.at<Vec3b>(jj, ii)[2];
            }
            dst.at<Vec3b>(j, i)[2] = sumR / 4;
            dst.at<Vec3b>(j, i)[1] = sumG / 4;
            dst.at<Vec3b>(j, i)[0] = sumB / 4;
        }
    }
    return dst;
}