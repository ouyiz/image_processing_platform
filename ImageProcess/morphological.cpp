#include "morphological.h"

//膨胀
Mat Morphological::expansion(Mat src, int n) {
    if (n != 0) {
        Mat kernel;
        kernel = getStructuringElement(MORPH_RECT, Size(n, n));
        Mat dst;
        dilate(src, dst, kernel);
        return dst;
    }
    else return src;
}

//腐蚀
Mat Morphological::erosion(Mat src, int n) {
    if (n != 0) {
        Mat kernel;
        kernel = getStructuringElement(MORPH_RECT, Size(n, n));
        Mat dst;
        erode(src, dst, kernel);
        return dst;
    }
    else return src;
}

//开函数
Mat Morphological::openOperation(Mat src, int n) {
    if (n != 0) {
        Mat kernel;
        kernel = getStructuringElement(MORPH_RECT, Size(n, n));
        Mat dst;
        erode(src, dst, kernel);
        dilate(dst, dst, kernel);
        return dst;
    }
    else return src;
}

//闭函数
Mat Morphological::closeOperation(Mat src, int n) {
    if (n != 0) {
        Mat kernel;
        kernel = getStructuringElement(MORPH_RECT, Size(n, n));
        Mat dst;
        dilate(src, dst, kernel);
        erode(dst, dst, kernel);
        return dst;
    }
    else return src;
}

//高帽
Mat Morphological::topHat(Mat src, int n) {
    if (n != 0) {
        Mat kernel;
        kernel = getStructuringElement(MORPH_RECT, Size(n, n));
        Mat dst;
        morphologyEx(src, dst, MORPH_TOPHAT, kernel);
        return dst;
    }
    else return src;
}

//低帽
Mat Morphological::lowHat(Mat src, int n) {
    if (n != 0) {
        Mat kernel;
        kernel = getStructuringElement(MORPH_RECT, Size(n, n));
        Mat dst;
        morphologyEx(src, dst, MORPH_BLACKHAT, kernel);
        return dst;
    }
    else return src;
}

//击中/击不中变换
Mat Morphological::hitMiss(Mat src, int n) {
    if (n != 0) {
        Mat kernel;
        kernel = getStructuringElement(MORPH_RECT, Size(n, n));
        Mat dst;
        morphologyEx(src, dst, MORPH_HITMISS, kernel);
        return dst;
    }
    else return src;
}

//边界提取
Mat Morphological::boundaryExtraction(Mat src, int n) {
    if (n != 0) {
        Mat kernel;
        kernel = getStructuringElement(MORPH_RECT, Size(n, n));
        Mat dst;
        erode(src, dst, kernel);
        Mat subtracted;
        subtract(src, dst,subtracted);
        return subtracted;
    }
    else return src;
}

//连通分量提取
Mat Morphological::connectedComponentExtraction(Mat src, int n) {
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    Mat thresh;
    if (n == 0) {
        threshold(gray, thresh, 0, 1, THRESH_BINARY_INV | THRESH_OTSU);
    }
    else if (n == 1) {
        threshold(gray, thresh, 0, 1, THRESH_BINARY | THRESH_OTSU);
    }
    Mat thresh2;
    int number = connectedComponents(thresh, thresh2, 8, CV_16U);
    RNG rng(100);
    vector<Vec3b>colors;
    for (int i = 0; i < number; ++i) {

        Vec3b vec3 = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        colors.push_back(vec3);
    }
    Mat result = Mat::zeros(thresh.size(), CV_8UC3);
    int w = result.cols;
    int h = result.rows;
    for (int row = 0; row < h; ++row) {
        for (int col = 0; col < w; ++col) {
            int label = thresh2.at<uint16_t>(row, col);
            if (label == 0) {
                continue;
            }
            result.at<Vec3b>(row, col) = colors[label];
        }
    }
    return result;
}

//凸壳
Mat Morphological::convexShell(Mat src) {
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    Mat thresh;
    threshold(gray, thresh, 0, 255, THRESH_BINARY | THRESH_OTSU);
    vector<vector<Point>> contours;
    findContours(thresh, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
    vector<vector<Point>> hullAll(contours.size());
    for (size_t i = 0; i < contours.size(); i++) {
        convexHull(contours[i], hullAll[i], false);
    }
    Scalar colorConvexHull = Scalar(0, 255, 0);
    Mat imgDrawing;
    cvtColor(thresh, imgDrawing, COLOR_GRAY2BGR);

    for (size_t i = 0; i < hullAll.size(); i++) {
        drawContours(imgDrawing, hullAll, static_cast<int>(i), colorConvexHull, 2, 8);
    }
    return imgDrawing;
}

//细化
Mat Morphological::refinement(Mat src, int n, int type) {
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    Mat thresh;
    if (type == 0) {
        threshold(gray, thresh, 0, 1, THRESH_BINARY | THRESH_OTSU);
    }
    else if (type == 1) {
        threshold(gray, thresh, 0, 1, THRESH_BINARY_INV | THRESH_OTSU);
    }
    Mat dst = thresh.clone();
    int w = dst.cols;
    int h = dst.rows;
    int count = 0;
    while (true)
    {
        if (count > n)
            break;
        count++;
        vector<uchar*> mFlag;
        for (int i = 1; i < h-1; ++i)
        {
            uchar* p = dst.ptr<uchar>(i);
            for (int j = 1; j < w-1; ++j)
            {
                //  p9 p2 p3
                //  p8 p1 p4
                //  p7 p6 p5
                uchar p1 = p[j];
                if (p1 != 1) continue;
                uchar p4 = (j == w - 1) ? 0 : dst.at<uchar>(i, j + 1);
                uchar p8 = (j == 0) ? 0 : dst.at<uchar>(i, j - 1);
                uchar p2 = (i == 0) ? 0 : dst.at<uchar>(i - 1, j);
                uchar p3 = (i == 0 || j == w - 1) ? 0 : dst.at<uchar>(i - 1, j + 1);
                uchar p9 = (i == 0 || j == 0) ? 0 : dst.at<uchar>(i - 1, j - 1);
                uchar p6 = (i == h - 1) ? 0 : dst.at<uchar>(i + 1, j );
                uchar p5 = (i == h - 1 || j == w - 1) ? 0 : dst.at<uchar>(i + 1, j + 1);
                uchar p7 = (i == h - 1 || j == 0) ? 0 : dst.at<uchar>(i + 1, j - 1);
                if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)
                {
                    int ap = 0;
                    if (p2 == 0 && p3 == 1) ++ap;
                    if (p3 == 0 && p4 == 1) ++ap;
                    if (p4 == 0 && p5 == 1) ++ap;
                    if (p5 == 0 && p6 == 1) ++ap;
                    if (p6 == 0 && p7 == 1) ++ap;
                    if (p7 == 0 && p8 == 1) ++ap;
                    if (p8 == 0 && p9 == 1) ++ap;
                    if (p9 == 0 && p2 == 1) ++ap;

                    if (ap == 1 && p2 * p4 * p6 == 0 && p4 * p6 * p8 == 0)
                    {

                        mFlag.push_back(p + j);
                    }
                }
            }
        }

        for (std::vector<uchar*>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
        {
            **i = 0;
        }

        if (mFlag.empty())
        {
            break;
        }
        else
        {
            mFlag.clear();
        }
        for (int i = 1; i < h-1; ++i)
        {
            uchar* p = dst.ptr<uchar>(i);
            for (int j = 1; j < w-1; ++j)
            {
                //  p9 p2 p3
                //  p8 p1 p4
                //  p7 p6 p5
                uchar p1 = p[j];
                if (p1 != 1) continue;
                uchar p4 = (j == w - 1) ? 0 : *(p + j + 1);
                uchar p8 = (j == 0) ? 0 : *(p + j - 1);
                uchar p2 = (i == 0) ? 0 : *(p - dst.step + j);
                uchar p3 = (i == 0 || j == w - 1) ? 0 : *(p - dst.step + j + 1);
                uchar p9 = (i == 0 || j == 0) ? 0 : *(p - dst.step + j - 1);
                uchar p6 = (i == h - 1) ? 0 : *(p + dst.step + j);
                uchar p5 = (i == h - 1 || j == w - 1) ? 0 : *(p + dst.step + j + 1);
                uchar p7 = (i == h - 1 || j == 0) ? 0 : *(p + dst.step + j - 1);
                if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)
                {
                    int ap = 0;
                    if (p2 == 0 && p3 == 1) ++ap;
                    if (p3 == 0 && p4 == 1) ++ap;
                    if (p4 == 0 && p5 == 1) ++ap;
                    if (p5 == 0 && p6 == 1) ++ap;
                    if (p6 == 0 && p7 == 1) ++ap;
                    if (p7 == 0 && p8 == 1) ++ap;
                    if (p8 == 0 && p9 == 1) ++ap;
                    if (p9 == 0 && p2 == 1) ++ap;

                    if (ap == 1 && p2 * p4 * p8 == 0 && p2 * p6 * p8 == 0)
                    {
                        mFlag.push_back(p + j);
                    }
                }
            }
        }
        for (std::vector<uchar*>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
        {
            **i = 0;
        }
        if (mFlag.empty())
        {
            break;
        }
        else
        {
            mFlag.clear();
        }
    }
    dst = dst * 255;
    if (type == 1) {
        Mat res1 = dst.clone();
        bitwise_not(res1, dst);
    }
    Mat dst1;
    cvtColor(dst, dst1, COLOR_GRAY2BGR);
    return dst1;
}

//粗化
Mat Morphological::coarsening(Mat src, int n, int type) {
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    Mat thresh;
    if (type == 1) {
        threshold(gray, thresh, 0, 1, THRESH_BINARY | THRESH_OTSU);
    }
    else if (type == 0) {
        threshold(gray, thresh, 0, 1, THRESH_BINARY_INV | THRESH_OTSU);
    }
    Mat dst = thresh.clone();
    int w = dst.cols;
    int h = dst.rows;
    int count = 0;

    while (true)
    {
        if (count > n)
            break;
        count++;
        vector<uchar*> mFlag;

        for (int i = 1; i < h - 1; ++i)
        {
            uchar* p = dst.ptr<uchar>(i);
            for (int j = 1; j < w - 1; ++j)
            {

                //  p9 p2 p3
                //  p8 p1 p4
                //  p7 p6 p5
                uchar p1 = p[j];
                if (p1 != 1) continue;
                uchar p4 = (j == w - 1) ? 0 : *(p + j + 1);
                uchar p8 = (j == 0) ? 0 : *(p + j - 1);
                uchar p2 = (i == 0) ? 0 : *(p - dst.step + j);
                uchar p3 = (i == 0 || j == w - 1) ? 0 : *(p - dst.step + j + 1);
                uchar p9 = (i == 0 || j == 0) ? 0 : *(p - dst.step + j - 1);
                uchar p6 = (i == h - 1) ? 0 : *(p + dst.step + j);
                uchar p5 = (i == h - 1 || j == w - 1) ? 0 : *(p + dst.step + j + 1);
                uchar p7 = (i == h - 1 || j == 0) ? 0 : *(p + dst.step + j - 1);
                if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)
                {
                    int ap = 0;
                    if (p2 == 0 && p3 == 1) ++ap;
                    if (p3 == 0 && p4 == 1) ++ap;
                    if (p4 == 0 && p5 == 1) ++ap;
                    if (p5 == 0 && p6 == 1) ++ap;
                    if (p6 == 0 && p7 == 1) ++ap;
                    if (p7 == 0 && p8 == 1) ++ap;
                    if (p8 == 0 && p9 == 1) ++ap;
                    if (p9 == 0 && p2 == 1) ++ap;

                    if (ap == 1 && p2 * p4 * p6 == 0 && p4 * p6 * p8 == 0)
                    {

                        mFlag.push_back(p + j);
                    }
                }
            }
        }


        for (std::vector<uchar*>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
        {
            **i = 0;
        }
        if (mFlag.empty())
        {
            break;
        }
        else
        {
            mFlag.clear();
        }
        for (int i = 1; i < h - 1; ++i)
        {
            uchar* p = dst.ptr<uchar>(i);
            for (int j = 1; j < w - 1; ++j)
            {

                //  p9 p2 p3
                //  p8 p1 p4
                //  p7 p6 p5
                uchar p1 = p[j];
                if (p1 != 1) continue;
                uchar p4 = (j == w - 1) ? 0 : *(p + j + 1);
                uchar p8 = (j == 0) ? 0 : *(p + j - 1);
                uchar p2 = (i == 0) ? 0 : *(p - dst.step + j);
                uchar p3 = (i == 0 || j == w - 1) ? 0 : *(p - dst.step + j + 1);
                uchar p9 = (i == 0 || j == 0) ? 0 : *(p - dst.step + j - 1);
                uchar p6 = (i == h - 1) ? 0 : *(p + dst.step + j);
                uchar p5 = (i == h - 1 || j == w - 1) ? 0 : *(p + dst.step + j + 1);
                uchar p7 = (i == h - 1 || j == 0) ? 0 : *(p + dst.step + j - 1);

                if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)
                {
                    int ap = 0;
                    if (p2 == 0 && p3 == 1) ++ap;
                    if (p3 == 0 && p4 == 1) ++ap;
                    if (p4 == 0 && p5 == 1) ++ap;
                    if (p5 == 0 && p6 == 1) ++ap;
                    if (p6 == 0 && p7 == 1) ++ap;
                    if (p7 == 0 && p8 == 1) ++ap;
                    if (p8 == 0 && p9 == 1) ++ap;
                    if (p9 == 0 && p2 == 1) ++ap;

                    if (ap == 1 && p2 * p4 * p8 == 0 && p2 * p6 * p8 == 0)
                    {
                        mFlag.push_back(p + j);
                    }
                }
            }
        }

        for (std::vector<uchar*>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
        {
            **i = 0;
        }

        if (mFlag.empty())
        {
            break;
        }
        else
        {
            mFlag.clear();
        }
    }
    dst = dst * 255;
    Mat dst1;
    Mat inverted_img=dst.clone();
    if (type == 0) {
        Mat res1 = inverted_img.clone();
        bitwise_not(res1, inverted_img);
    }
    cvtColor(inverted_img, dst1, COLOR_GRAY2BGR);
    return dst1;
}


bool isEqual(Mat a, Mat b)
{
    Mat temp;
    bitwise_xor(a, b, temp);
    return !(cv::countNonZero(temp.reshape(1)));
}
void myDilate(const Mat _src, Mat& dst, int se[3][3])
{
    Mat src;
    _src.copyTo(src);
    if (src.empty())
    {
        cout << "error" << endl;
        return;
    }
    _src.copyTo(dst);

    int nTemp;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3 - i; j++)
        {
            nTemp = se[i][j];
            se[i][j] = se[2 - i][2 - j];
            se[2 - i][2 - j] = nTemp;
        }
    }

    for (int i = 1; i < src.rows - 1; i++)
    {
        uchar* data = src.ptr<uchar>(i);
        for (int j = 1; j < src.cols - 1; j++)
        {
            if (data[j] != 0)
            {
                for (int k = 0; k < 3; k++)
                {
                    for (int l = 0; l < 3; l++)
                    {
                        if (se[k][l] == 0)
                            continue;
                        if (se[k][l] == 1)
                        {
                            dst.at<uchar>(i - 1 + k, j - 1 + l) = 255;
                        }
                        else
                        {
                            cout << "error" << endl;
                            return;
                        }
                    }
                }
            }
        }
    }
}
//区域填充
Mat Morphological::areaFill(Mat src, Point ptStart, int n)
{
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    Mat thresh;
    Mat revImg;
    if (n == 0) {
        threshold(gray, thresh, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
        bitwise_not(thresh, revImg);
        //imshow("thresh", thresh);
    }
    
    else if (n == 1) {
        threshold(gray, thresh, 0, 255, THRESH_BINARY | THRESH_OTSU);//revImg为点的变白
        bitwise_not(thresh, revImg);
    }
    Mat dst = Mat::zeros(revImg.size(), revImg.type());
    int se[3][3] = { { 0, 1, 0 }, { 1, 1, 1 }, { 0, 1, 0 } };
    Mat kernel = Mat(3, 3, CV_8U, se);
    dst.at<uchar>(ptStart.y, ptStart.x) = 255;
    while (true)
    {
        Mat temp;
        dst.copyTo(temp);
        myDilate(dst, dst, se);
        dst = dst & revImg;
        if (isEqual(dst, temp))
        {
            break;
        }
    }
    Mat result=dst;
    
    Mat dst1;
    cvtColor(result, dst1, COLOR_GRAY2BGR);
    return dst1;
}