#include "imageSegmentation.h"
//获得直方图
Mat getHistogram(Mat image)
{
    Mat histogram = Mat::zeros(Size(256, 1), CV_32SC1);
    int rows = image.rows;
    int cols = image.cols;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            int index = int(image.at<uchar>(r, c));
            histogram.at<int>(0, index) += 1;
        }
    }
    return histogram;
}

//单通道扩展三通道
Mat oneCopyToThree(Mat singleChannel, Mat src) {
    singleChannel = singleChannel / 255;
    int rows = singleChannel.rows;
    int cols = singleChannel.cols;
    Mat threeChannel(rows, cols, CV_8UC3, Scalar(0, 0, 0));
    vector<Mat> channels(3);
    //split(threeChannel, channels);
    for (int i = 0; i < 3; i++) {
        singleChannel.copyTo(channels[i]);
    }
    merge(channels, threeChannel);
    Mat src3;
    src.convertTo(src3, CV_8UC3);
    Mat result;
    multiply(threeChannel, src3, result);
    return result;
}

//简单直方图分割
Mat ImageSegmentation::histogramSegmentation(Mat src,int type)
{
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    Mat dst = gray.clone();
    Mat histogram = getHistogram(gray);
    Point Peak1;
    //计算第一个峰值
    minMaxLoc(histogram, NULL, NULL, NULL, &Peak1);
    int Peakx1 = Peak1.x;
    /*
    Mat h = histogram.clone();
    h.at<int>(0, Peakx1) = 0;
    Point Peak2;
    minMaxLoc(h, NULL, NULL, NULL, &Peak2);
    */
    //计算第二个峰值(近似)
    Mat measureDists = Mat::zeros(Size(256, 1), CV_32FC1);
    for (int k = 0; k < 256; k++)
    {
        int hist_k = histogram.at<int>(0, k);
        measureDists.at<float>(0, k) = pow(float(k - Peakx1), 2) * hist_k;
    }
    Point Peak2;
    minMaxLoc(measureDists, NULL, NULL, NULL, &Peak2);
    
    int Peakx2 = Peak2.x;
    //计算阈值
    Point thresh;
    int threshx = 0;
    if (Peakx1 < Peakx2) {
        minMaxLoc(histogram.colRange(Peakx1, Peakx2), NULL, NULL, &thresh);
        threshx = Peakx1 + thresh.x + 1;
    }
    else {
        minMaxLoc(histogram.colRange(Peakx2, Peakx1), NULL, NULL, &thresh);
        threshx = Peakx2 + thresh.x + 1;
    }
    Mat dst1;
    if (type == 0) {
        threshold(gray, dst, threshx, 255, THRESH_BINARY);
        cvtColor(dst, dst1, COLOR_GRAY2BGR);
    }
    else if(type==1)
    {
        threshold(gray, dst, threshx, 255, THRESH_BINARY_INV);
        cvtColor(dst, dst1, COLOR_GRAY2BGR);
    }
    else if (type == 3) {
        threshold(gray, dst, threshx, 255, THRESH_BINARY);
        dst1 = oneCopyToThree(dst, src);
    }
    return dst1;
}

//迭代阈值分割
Mat ImageSegmentation::iterativeThresholdSegmentation(Mat src,int n,int type) {
    if (n != 0) {
        Mat gray;
        cvtColor(src, gray, COLOR_BGR2GRAY);
        Mat dst;
        Scalar meanImg = mean(gray);
        double T = meanImg[0];
        while (true) {
            Mat mask1, mask2;
            threshold(gray, mask1, T, 255, THRESH_BINARY_INV);
            threshold(gray, mask2, T, 255, THRESH_BINARY);

            Scalar T1 = mean(gray, mask1);
            Scalar T2 = mean(gray, mask2);

            double t = (T1[0] + T2[0]) / 2;
            if (abs(T - t) < n) {
                break;
            }
            T = t;
        }
        int thresh = T;
        Mat dst1;
        if (type == 0) {
            threshold(gray, dst, thresh, 255, THRESH_BINARY);
            cvtColor(dst, dst1, COLOR_GRAY2BGR);
        }
        else if (type == 1)
        {
            threshold(gray, dst, thresh, 255, THRESH_BINARY_INV);
            cvtColor(dst, dst1, COLOR_GRAY2BGR);
        }
        else if (type == 3) {
            threshold(gray, dst, thresh, 255, THRESH_BINARY);
            dst1 = oneCopyToThree(dst, src);
        }

        return dst1;
    }
    else {
        return src;
    }
}

//最佳阈值分割
Mat ImageSegmentation::otsuSegmentation(Mat src,int type) {
    Mat dst;
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    Mat dst1;
    if (type == 0) {
        threshold(gray, dst, 0, 255, THRESH_BINARY + THRESH_OTSU);
        cvtColor(dst, dst1, COLOR_GRAY2BGR);
    }
    else if (type == 1)
    {
        threshold(gray, dst, 0, 255, THRESH_BINARY_INV + THRESH_OTSU);
        cvtColor(dst, dst1, COLOR_GRAY2BGR);
    }
    else if (type == 3) {
        threshold(gray, dst, 0, 255, THRESH_BINARY + THRESH_OTSU);
        dst1 = oneCopyToThree(dst, src);
    }
    return dst1;
}

//Kmeans聚类
Mat ImageSegmentation::KmeansSegmentation(Mat src, int n) {
    if (n != 0) {
        int w = src.cols;
        int h = src.rows;
        int channels = src.channels();

        int sum = w * h;
        Mat points(sum, channels, CV_32F, Scalar(10));
        Mat labels;
        Mat centers(n, 1, points.type());

        int index = 0;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                index = i * w + j;
                points.at<float>(index, 0) = static_cast<int>(src.at<Vec3b>(i, j)[0]);
                points.at<float>(index, 1) = static_cast<int>(src.at<Vec3b>(i, j)[1]);
                points.at<float>(index, 2) = static_cast<int>(src.at<Vec3b>(i, j)[2]);
            }
        }

        TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);//最大迭代次数达到10次或者聚类中心的移动距离小于0.1
        kmeans(points, n, labels, criteria, 10, KMEANS_PP_CENTERS, centers);//10为重复此时，KMEANS_PP_CENTERS表示使用kmeans++算法来初始化聚类中心

        Mat dst = Mat::zeros(src.size(), src.type());
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                index = i * w + j;
                int label = labels.at<int>(index, 0);
                dst.at<Vec3b>(i, j)[0] = centers.at<float>(label, 0);
                dst.at<Vec3b>(i, j)[1] = centers.at<float>(label, 1);
                dst.at<Vec3b>(i, j)[2] = centers.at<float>(label, 2);
            }
        }
        return dst;
    }
    else {
        return src;
    }
}

//meanShift
Mat ImageSegmentation::meanShiftSegmentation(Mat src, int sp, int sr) {
    Mat dst=src.clone();
    if (sp != 0 && sr != 0) {
        pyrMeanShiftFiltering(src, dst, sp, sr, 2);
    }
    return dst;
}

//分水岭算法
Mat ImageSegmentation::watershedSegmentation(Mat src) {
    Mat dst = src.clone();
    Mat gray;
    cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    Mat thresh;
    threshold(gray, thresh, 0, 255, THRESH_BINARY_INV + THRESH_OTSU);
    Mat kernel = Mat::ones(3, 3, CV_8U);
    //去除图像中的噪点和孤立的小块
    Mat openimg;
    morphologyEx(thresh, openimg, MORPH_OPEN, kernel, Point(-1, -1), 2);
    //膨胀操作，结束后确定的背景为黑色，得到确认的背景
    Mat sure_bg;
    dilate(openimg, sure_bg, kernel, cv::Point(-1, -1), 3);
    //计算开运算后的图像到其最近背景像素的距离，使用欧氏距离作为度量
    Mat dist_transform;
    distanceTransform(openimg, dist_transform, cv::DIST_L2, 5);
    //基于距离变换结果，得到确定的前景，前景为白色
    Mat sure_fg;
    double minVal, maxVal;
    minMaxLoc(dist_transform, &minVal, &maxVal);
    threshold(dist_transform, sure_fg, 0.7 * maxVal, 255, 0);
    sure_fg.convertTo(sure_fg, CV_8U);
    //得到不确定区域
    Mat unknown = sure_bg - sure_fg;
    //区域标记
    Mat markers;
    connectedComponents(sure_fg, markers);
    markers = markers + 1;//2表示前景，1表示背景
    markers.setTo(0, unknown == 255);//最后用0表示我们无法确定的区域
    //执行分水岭
    watershed(dst, markers);
    for (int i = 0; i < markers.rows; i++) {
        for (int j = 0; j < markers.cols; j++) {
            if (markers.at<int>(i, j) == -1) {
                dst.at<Vec3b>(i, j) = Vec3b(0, 0, 255);
            }
        }
    }
    return dst;
}

//grabCut
Mat ImageSegmentation::grabCutSegmentation(Mat src, Rect rect) {
    if (rect.x < 0)
        rect.x = 0;
    if (rect.y < 0)
        rect.y = 0;
    if (rect.x + rect.width > src.cols)
        rect.width = src.cols - rect.x;
    if (rect.y + rect.height > src.rows)
        rect.height = src.rows - rect.y;

    Mat mask;
    mask.create(src.size(), CV_8UC1);
    mask.setTo(GC_BGD);
    (mask(rect)).setTo(Scalar(GC_PR_FGD));
    Mat bgdModel, fgdModel;

    grabCut(src, mask, rect, bgdModel, fgdModel, 10, GC_INIT_WITH_RECT);
    Mat binMask;
    binMask.create(mask.size(), CV_8UC1);
    binMask = mask & 1;
    Mat res;
    src.copyTo(res, binMask);
    return res;
}

//区域生长
Mat ImageSegmentation::regionalGrowth(Mat src, Point pbegin, int thresh1, int thresh2, int thresh3,int n)
{
    Point pNow;                       
    Scalar pLastValue = 0;                               
    Scalar pNowValue = 0;                              
    Mat growImage = Mat::zeros(src.size(), CV_8UC1);   
    int GROW[8][2] = { {-1,-1}, {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0} };
    vector<Point> growPtVector;                     
    growPtVector.push_back(pbegin);                         
    growImage.at<uchar>(pbegin.y, pbegin.x) = 255;              
    pLastValue = src.at<Vec3b>(pbegin.y, pbegin.x);        
    while (!growPtVector.empty())                       
    {
        pbegin = growPtVector.back();                       
        growPtVector.pop_back();
        for (int i = 0; i < 8; ++i)
        {
            pNow.x = pbegin.x + GROW[i][0];
            pNow.y = pbegin.y + GROW[i][1];
            if (pNow.x < 0 || pNow.y < 0 ||
                pNow.x >(src.cols - 1) || (pNow.y > src.rows - 1))
                continue;
            pLastValue = src.at<Vec3b>(pbegin.y, pbegin.x);
            if (growImage.at<uchar>(pNow.y, pNow.x) == 0)                    
            {
                pNowValue = src.at<Vec3b>(pNow.y, pNow.x);

                if (abs(pLastValue[0] - pNowValue[0]) < thresh1 &&
                    abs(pLastValue[1] - pNowValue[1]) < thresh2 &&
                    abs(pLastValue[2] - pNowValue[2]) < thresh3)                    
                {
                    growImage.at<uchar>(pNow.y, pNow.x) = 255;     
                    growPtVector.push_back(pNow);                
                }

            }
        }
    }
    Mat dst = growImage.clone();
    if (n == 1) {
        bitwise_not(growImage, dst);
    }
    Mat dst1;
    cvtColor(dst, dst1, COLOR_GRAY2BGR);
    return dst1;
}
