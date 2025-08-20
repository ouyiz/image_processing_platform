#pragma once
#include "ImageProcess.h"
class Filter {
public:
	//毛玻璃
	Mat glass(Mat src,int n);
	//素描
	Mat sketch(Mat src, int n1, int n2);
	//浮雕
	Mat relief(Mat src, int n);
	//雕刻
	Mat scuplture(Mat src, int n);
	//油画
	Mat oil(Mat image, int level, int radius);
	//马赛克
	Mat myMask(Mat src,  int n);
	//卡通
	Mat cartoon(Mat src, int res);
	//怀旧
	Mat old(Mat src, int h, int w);
	//流年
	Mat fleet(Mat src, int h, int w, int n);
	//光照
	Mat illumination(Mat src, int h, int w, int n);
	//模糊
	Mat dim(Mat src, int h, int w, int n);
	//熔铸
	Mat casting(Mat src, int h, int w);
	//冰冻
	Mat frozen(Mat src, int h, int w);
	//连环画
	Mat comic(Mat src, int h, int w);
	//羽化
	Mat feather(Mat src, int h, int w, double n);
	//水彩
	Mat watercolor(Mat src, int n, float m);
	//灰度
	Mat grey(Mat src);
	//黑白
	Mat whiteAndBlack(Mat src, int n);
	//单色
	Mat homochromy(Mat src, int n);
	//描线
	Mat linedraw(Mat src);
	//凸透镜
	Mat convex(Mat src, int n);
	//凹透镜
	Mat concave(Mat src, int n);
	//霓虹
	Mat neon(Mat src, int n);
	//重影
	Mat ghost(Mat src, int n);
};