#pragma execution_character_set("utf-8")
#include "ImageProcess.h"
#include "filter.h"
#include "enhance.h"
#include "greyTransform.h"
#include "spatialFilter.h"
#include "frequencyFilter.h"
#include"spatialTransformation.h"
#include "addNoise.h"
#include "recovery.h"
#include "morphological.h"
#include "imageSegmentation.h"
#include "other.h"
ImageProcess::ImageProcess(QWidget* parent)
	: QMainWindow(parent),
	ui(new Ui::ImageProcessClass)
{
	flagFile = false;
	ui->setupUi(this);
	ui->labelCrop->installEventFilter(this);
	//ui->labelNowImage->setStyleSheet("QLabel {"
	//	"border: 2px solid #D3D3D3;" // 设置边框颜色为浅灰色，宽度为2像素
	//	"}");
	//ui->labelOriginImage->setStyleSheet("QLabel {"
	//	"border: 2px solid #D3D3D3;" // 设置边框颜色为浅灰色，宽度为2像素
	//	"}");
	//
	//ui->labelShow->setStyleSheet("QLabel {"
	//	"border: 1px solid #D3D3D3;" // 设置边框颜色为浅灰色，宽度为2像素
	//	"}");
	//	
	/*
	ui->labelCrop->setStyleSheet("QLabel {"
		"border: 2px solid #FF0000;" // 设置边框颜色为红色，宽度为2像素
		"}");
	*/
	flaginitial();
	back1 = QIcon("back1.ico");
	back2 = QIcon("back2.ico");
	next1 = QIcon("next1.ico");
	next2 = QIcon("next2.ico");

	ui->pushButton_back->hide();
	ui->pushButton_back->setIcon(back2);
	ui->pushButton_next->hide();
	ui->pushButton_next->setIcon(next2);
	ui->labelShow->show();
	ui->labelShow->setText("处理详情");
	
}

ImageProcess::~ImageProcess() {
	delete ui;
}

Filter filter;
Enhance enhance;
GreyTransform greyTransform;
SpatialFilter spatialFilter;
FrequencyFilter frequencyFilter;
SpatialTransformation spatialTransformation;
AddNoise addNoise;
Recovery recovery;
Morphological morphological;
ImageSegmentation imageSegmentation;
Other other;

//参数的初始化
void ImageProcess::flaginitial() {
	ui->horizontalSlider->hide();
	ui->horizontalSlider_2->hide();
	ui->horizontalSlider_3->hide();

	ui->labelShow->hide();
	ui->pushButtonNo->hide();
	ui->pushButtonYes->hide();

	ui->pushButtonRed->hide();
	ui->pushButtonRed_2->hide();
	ui->pushButtonGreen->hide();
	ui->pushButtonGreen_2->hide();
	ui->pushButtonBlue->hide();
	ui->pushButtonBlue_2->hide();

	ui->labelSliderMax->hide();
	ui->labelSliderMin->hide();
	ui->labelSliderMin_2->hide();
	ui->labelSliderMax_2->hide();
	ui->labelSliderMin_3->hide();
	ui->labelSliderMax_3->hide();

	ui->lineEdit->hide();
	ui->lineEdit_2->hide();
	ui->lineEdit_3->hide();

	ui->pushButton_back->hide();
	ui->pushButton_next->hide();

	ui->labelCrop->clear();
	ui->labelCrop->hide();
	ui->label_11->hide();
	tempImage = nowImage.clone();
	display_MatInQT(ui->labelNowImage, nowImage);
	
	flagGlass = false;
	flagSketch = false;
	flagRelief = false;
	flagScuplture = false;
	flagOil = false;
	flagMask = false;
	flagOld = false;
	flagFleet = false;
	flagCartoon = false;
	flagIllumination = false;
	flagDim = false;
	flagVignetting = false;
	flagCasting = false;
	flagComic = false;
	flagFeather = false;
	flagTemperature = false;
	flagSaturability = false;
	flagLuminance = false;
	flagHue = false;
	flagSharpen = false;
	flagHighlight = false;
	flagShadow = false;
	flagReversal = false;
	flagGrey = false;
	flagWhiteAndBlack = false;
	flagHomochromy = false;
	flagWatercolor = false;
	flagLinedraw = false;
	flagConcave = false;
	flagConvex = false;
	flagNeon = false;
	flagGhost = false;
	flagFrozen=false;
	flagContrast = false;
	flagGranular = false;
	flagLog = false;
	flagGamma = false;
	flagAverageFilter = false;
	flagGaussianFilter = false;
	flagMedianFilter = false;
	flagMinFilter = false;
	flagMaxFilter = false;
	flagLaplacianFilter = false;
	flagPrewittFilter = false;
	flagRobertsFilter = false;
	flagSobelFilter = false;
	flagButterworthHighFilter=false;
	flagButterworthLowFilter=false;
	flagIdealHighFilter=false;
	flagIdealLowFilter=false;
	flagGaussHighFilter=false;
	flagGaussLowFilter=false;

	flagZoom = false;
	flagRotation = false;
	flagMirror = false;
	flagCropping = false;

	flagGaussNoise = false;
	flagRayleighNoise = false;
	flagGammaNoise = false;
	flagExponentialNoise = false;
	flagUniformNoise = false;
	flagSaltandPepperNoise = false;
	flagPeriodicNoise = false;

	flagArithmeticMean = false;
	flagGeometricMean = false;
	flagHarmonicMean = false;
	flagAntiharmonicMean = false;
	flagMidpoint = false;
	flagAlphaTrimmedMean = false;
	flagAdaptiveNoiseCancel = false;
	flagAdaptiveMedian = false;

	flagExpansion = false;
	flagErosion = false;
	flagOpenOperation = false;
	flagCloseOperation = false;
	flagTopHat = false;
	flagLowHat = false;
	flagHitMiss = false;

	flagBoundaryExtraction = false;
	flagAreaFill = false;
	flagConnectedComponentExtraction = false;
	flagConvexShell = false;
	flagCoarsening = false;
	flagRefinement = false;

	

	flagHistogramSegmentation = false;
	flagIterativeThresholdSegmentation = false;
	flagOtsu = false;
	flagKmeans = false;
	flagMeanShift = false;
	flagWaterShed = false;
	flagGrabCut = false;
	flagRegionalGrowth = false;

	flagShowHistogram = false;
	flagShowSpectrogram = false;
	isModify = false;
	isGetPoint = false;
	isRegionalGrowth=false;
}


//打开文件
void ImageProcess::menu_file_open_clicked() {
	flaginitial();
	ui->labelShow->show();
	ui->pushButton_back->show();
	ui->pushButton_next->show();
	ui->labelOriginImage->clear();
	ui->labelNowImage->clear();
	QString filename =
		QFileDialog::getOpenFileName(this, "打开图像",
			".",
			tr("Image file(*.png *.jpg *.bmp)"));
	originImage = imread(filename.toLocal8Bit().data());
	nowImage = originImage.clone();
	tempImage = originImage.clone();
	if (originImage.data){
		flagFile = true;
		display_MatInQT(ui->labelOriginImage, originImage);
		display_MatInQT(ui->labelNowImage, nowImage);
		string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
		QString qstr = QString::fromStdString(s);
		ui->label_5->show();
		ui->label_5->setText(qstr);
	}
	
}

//保存文件
void ImageProcess::menu_file_save_clicked() {
	flaginitial();
	ui->labelShow->show();
	ui->pushButton_back->show();
	ui->pushButton_next->show();
	if (flagFile == true) {
		if (nowImage.data)
		{
			string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
			QString qstr = QString::fromStdString(s);
			ui->label_5->show();
			ui->label_5->setText(qstr);
			QString savePath;
			savePath = QFileDialog::getSaveFileName(0, "请选择图片保存路径",
				".\\Image Files", "jpg(*.jpg);;png(*.png);;bmp(*.bmp);;所有文件(*.*)");

			if ((!savePath.isNull()) || (!savePath.isEmpty()))
			{
				//const QPixmap saveImgage = ui->labelNowImage->pixmap();
				QImage saveImgage = MatToQImage(nowImage);
				saveImgage.save(savePath);
				QMessageBox::information(this, "保存图片", "保存图片成功！");

			}
		}
		else
		{
			QMessageBox::warning(this, "保存图片", "保存图片失败！");

		}
	}
	else {
		QMessageBox::warning(this, "保存图片", "保存图片失败！");

	}
}

//毛玻璃
void ImageProcess::menu_filter_glass_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagGlass = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->labelShow->setText("毛玻璃");
		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(0); 
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//素描
void ImageProcess::menu_filter_sketch_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagSketch = true;
		ui->horizontalSlider->show();
		ui->horizontalSlider_2->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->labelSliderMin_2->show();
		ui->labelSliderMax_2->show();
		

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->lineEdit_2->show();
		QIntValidator* validator_2 = new QIntValidator(0, 255, this);
		ui->lineEdit_2->setValidator(validator_2);
		ui->lineEdit_2->setText("0");

		ui->labelShow->setText("素描");
		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(0); 
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(100));
		ui->horizontalSlider_2->setRange(0, 255);
		ui->horizontalSlider_2->setValue(0); 
		ui->labelSliderMin_2->setText("0");
		ui->labelSliderMax_2->setText(QString::number(255));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//浮雕
void ImageProcess::menu_filter_relief_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagRelief = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 255, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->labelShow->setText(("浮雕"));
		ui->horizontalSlider->setRange(0, 255);
		ui->horizontalSlider->setValue(128);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(255));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//雕刻
void ImageProcess::menu_filter_sculpture_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagRelief = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 255, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("128");
		ui->labelShow->setText("雕刻");
		ui->horizontalSlider->setRange(0, 255);
		ui->horizontalSlider->setValue(128);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText("255");

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//油画
void ImageProcess::menu_filter_oil_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagOil = true;
		ui->horizontalSlider->show();
		ui->horizontalSlider_2->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->labelSliderMin_2->show();
		ui->labelSliderMax_2->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 256, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->lineEdit_2->show();
		QIntValidator* validator_2 = new QIntValidator(0, 20, this);
		ui->lineEdit_2->setValidator(validator_2);
		ui->lineEdit_2->setText("0");
		ui->labelShow->setText("油画");
		ui->horizontalSlider->setRange(0, 256);//设置范围
		ui->horizontalSlider->setValue(0); //设置当前值
		ui->labelSliderMin->setText("0");
		

		ui->lineEdit->setText(QString::number(0));
		ui->labelSliderMax->setText(QString::number(256));
		ui->horizontalSlider_2->setRange(0, 20);//设置范围
		ui->horizontalSlider_2->setValue(0); //设置当前值
		ui->labelSliderMin_2->setText("0");
		

		ui->labelSliderMax_2->setText(QString::number(20));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//马赛克
void ImageProcess::menu_filter_mask_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagMask = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, min(tempImage.rows, tempImage.cols), this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->labelShow->setText("马赛克");
		ui->horizontalSlider->setRange(0, min(tempImage.rows, tempImage.cols));
		ui->horizontalSlider->setValue(0); 
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(min(tempImage.rows, tempImage.cols)));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}
//卡通
void ImageProcess::menu_filter_cartoon_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagCartoon = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 200, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->labelShow->setText("卡通");
		ui->horizontalSlider->setRange(0, 200);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(200));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}




//光照
void ImageProcess::menu_filter_illumination_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagIllumination = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 1000, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->labelShow->setText("光照");
		ui->horizontalSlider->setRange(0, 1000);
		ui->horizontalSlider->setValue(0); 
		ui->labelSliderMin->setText("0");
		
		ui->labelSliderMax->setText(QString::number(1000));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//模糊
void ImageProcess::menu_filter_dim_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagDim = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, min(tempImage.rows, tempImage.cols), this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		
		ui->labelShow->setText("模糊");
		ui->horizontalSlider->setRange(0, min(tempImage.rows, tempImage.cols));
		ui->horizontalSlider->setValue(100); 
		ui->labelSliderMin->setText("0");
		
		ui->labelSliderMax->setText(QString::number(min(tempImage.rows, tempImage.cols)));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}
//怀旧
void ImageProcess::menu_filter_old_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagOld = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelShow->setText("怀旧");
		OldChange();
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//流年
void ImageProcess::menu_filter_fleet_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagFleet = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->labelShow->setText("流年");
		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}


//晕影
void ImageProcess::menu_enhance_vignetting_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagVignetting = true;
		ui->horizontalSlider->show();
		ui->horizontalSlider_2->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		
		ui->labelSliderMin_2->show();
		ui->labelSliderMax_2->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("50");
		ui->lineEdit_2->show();
		QIntValidator* validator1 = new QIntValidator(0, 100, this);
		ui->lineEdit_2->setValidator(validator1);
		ui->lineEdit_2->setText("50");
		ui->labelShow->setText("晕影");
		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(50);
		ui->labelSliderMin->setText("0");
		
		ui->labelSliderMax->setText(QString::number(100));
		ui->horizontalSlider_2->setRange(0, 100);
		ui->horizontalSlider_2->setValue(50); 
		ui->labelSliderMin_2->setText("0");
		
		ui->labelSliderMax_2->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//熔铸
void ImageProcess::menu_filter_casting_clicked(){
	flaginitial();
	if (flagFile == true) {
		flagCasting = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelShow->setText("熔铸");
		CastingChange();
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//冰冻
void ImageProcess::menu_filter_frozen_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagFrozen = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelShow->setText("冰冻");
		FrozenChange();
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//连环画
void ImageProcess::menu_filter_comic_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagComic = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelShow->setText("连环画");
		ComicChange();
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//羽化
void ImageProcess::menu_filter_feather_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagFeather = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("50");
		ui->labelShow->setText("羽化");
		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(50); 
		ui->labelSliderMin->setText("0");
		
		ui->labelSliderMax->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//色温
void ImageProcess::menu_enhance_colorTemperature_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagTemperature = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(-100, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("50");
		ui->labelShow->setText("色温");
		ui->horizontalSlider->setRange(-100, 100);
		ui->horizontalSlider->setValue(50); 
		ui->labelSliderMin->setText("-100");
		
		ui->labelSliderMax->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//饱和度
void ImageProcess::menu_enhance_saturability_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagSaturability = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(-100, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("50");
		ui->labelShow->setText("饱和度");
		ui->horizontalSlider->setRange(-100, 100);
		ui->horizontalSlider->setValue(50); 
		ui->labelSliderMin->setText("-100");
		
		ui->labelSliderMax->setText(QString::number(100));
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//亮度
void ImageProcess::menu_enhance_luminance_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagLuminance = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(-100, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("50");
		ui->labelShow->setText("亮度");
		ui->horizontalSlider->setRange(-100, 100);
		ui->horizontalSlider->setValue(50); 
		ui->labelSliderMin->setText("-100");
		
		ui->labelSliderMax->setText(QString::number(100));
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//对比度
void ImageProcess::menu_enhance_contrast_clicked() {
	flaginitial();
	if(flagFile == true) {
		flagContrast = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(-100, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("50");
		ui->labelShow->setText("对比度");
		ui->horizontalSlider->setRange(-100, 100);
		ui->horizontalSlider->setValue(50); 
		ui->labelSliderMin->setText("-100");
		
		ui->labelSliderMax->setText(QString::number(100));
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
		}
}

//色相
void ImageProcess::menu_enhance_hue_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagHue = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(-360, 360, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->labelShow->setText("色相");
		ui->horizontalSlider->setRange(-360, 360);//设置范围
		ui->horizontalSlider->setValue(0); //设置当前值
		ui->labelSliderMin->setText("-360");
		
		ui->labelSliderMax->setText(QString::number(360));
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//颗粒感
void ImageProcess::menu_enhance_granular_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagGranular = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->labelShow->setText("颗粒感");
		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(0); 
		ui->labelSliderMin->setText("0");
		
		ui->labelSliderMax->setText(QString::number(100));
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//锐化
void ImageProcess::menu_enhance_sharpen_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagSharpen = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 200, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->labelShow->setText("锐化");
		ui->horizontalSlider->setRange(0, 200);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");
		
		ui->labelSliderMax->setText(QString::number(200));
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//高光
void ImageProcess::menu_enhance_highlight_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagHighlight = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(-100, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->labelShow->setText("高光");
		ui->horizontalSlider->setRange(-100, 100);
		ui->horizontalSlider->setValue(0); 
		ui->labelSliderMin->setText("-100");
		
		ui->labelSliderMax->setText(QString::number(100));
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//阴影
void ImageProcess::menu_enhance_shadow_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagShadow = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(-100, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->labelShow->setText("阴影");
		ui->horizontalSlider->setRange(-100, 100);
		ui->horizontalSlider->setValue(0); 		
		ui->labelSliderMin->setText("-100");
		ui->labelSliderMax->setText(QString::number(100));
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//灰度反转
void ImageProcess::menu_greyTransform_reversal_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagReversal = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelShow->setText("灰度反转");
		ReversalChange();
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//灰度
void ImageProcess::menu_filter_grey_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagGrey = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelShow->setText("灰度");
		GreyChange();
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//黑白
void ImageProcess::menu_filter_whiteAndBlack_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagWhiteAndBlack = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 255, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("128");
		ui->labelShow->setText("黑白");
		ui->horizontalSlider->setRange(0, 255);//设置范围
		ui->horizontalSlider->setValue(128); //设置当前值
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText("255");
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//单色
void ImageProcess:: menu_filter_homochromy_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagHomochromy = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->pushButtonRed->show();
		ui->pushButtonGreen->show();
		ui->pushButtonBlue->show();
		ui->pushButtonYes->show();
		ui->pushButtonRed->setText("红色");
		ui->pushButtonGreen->setText("绿色");
		ui->pushButtonBlue->setText("蓝色");
		ui->labelShow->setText("单色");
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//水彩
void ImageProcess::menu_filter_watercolor_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagWatercolor = true;
		ui->horizontalSlider->show();
		ui->horizontalSlider_2->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		
		ui->labelSliderMin_2->show();
		ui->labelSliderMax_2->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("50");
		ui->lineEdit_2->show();
		QIntValidator* validator_2 = new QIntValidator(0, 100, this);
		ui->lineEdit_2->setValidator(validator_2);
		ui->lineEdit_2->setText("50");
		ui->labelShow->setText("水彩");
		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(50); 
		ui->labelSliderMin->setText("0");
		
		ui->labelSliderMax->setText("100");
		ui->horizontalSlider_2->setRange(0, 100);
		ui->horizontalSlider_2->setValue(50); 
		ui->labelSliderMin_2->setText("0");
		
		ui->labelSliderMax_2->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//描线
void ImageProcess::menu_filter_linedraw_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagLinedraw = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelShow->setText("描线");
		LinedrawChange();
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//凸透镜
void ImageProcess::menu_filter_convex_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagConvex = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, min(tempImage.rows, tempImage.cols), this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		
		ui->labelShow->setText("凸透镜");
		ui->horizontalSlider->setRange(0, min(tempImage.rows, tempImage.cols));
		ui->horizontalSlider->setValue(0); 
		ui->labelSliderMin->setText("0");
		
		ui->labelSliderMax->setText(QString::number(min(tempImage.rows, tempImage.cols)));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

// 凹透镜
void ImageProcess::menu_filter_concave_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagConcave = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0,100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->labelShow->setText("凹透镜");
		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(0); 
		ui->labelSliderMin->setText("0");
		
		ui->labelSliderMax->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//霓虹
void ImageProcess::menu_filter_neon_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagNeon = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->labelShow->setText("霓虹");
		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(0); 
		ui->labelSliderMin->setText(QString::fromLocal8Bit("0"));
		
		ui->labelSliderMax->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//重影
void ImageProcess::menu_filter_ghost_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagGhost = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->labelShow->setText("重影");
		ui->horizontalSlider->setRange(0, 100);//设置范围
		ui->horizontalSlider->setValue(0); //设置当前值
		ui->labelSliderMin->setText("0");
		
		ui->labelSliderMax->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//对数变换
void ImageProcess::menu_greyTransform_log_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagLog = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->labelShow->setText("对数变换");
		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//伽马变换
void ImageProcess::menu_greyTransform_gamma_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagGamma= true;
		ui->horizontalSlider->show();
		ui->horizontalSlider_2->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->labelSliderMin_2->show();
		ui->labelSliderMax_2->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->lineEdit_2->show();
		QIntValidator* validator_2 = new QIntValidator(-100, 100, this);
		ui->lineEdit_2->setValidator(validator_2);
		ui->lineEdit_2->setText("0");
		ui->labelShow->setText("伽马变换");
		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(100));
		ui->horizontalSlider_2->setRange(-100, 100);
		ui->horizontalSlider_2->setValue(0);
		ui->labelSliderMin_2->setText("-100");

		ui->labelSliderMax_2->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//直方图均衡化
void ImageProcess::menu_greyTransform_histogramEqualization_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagHistogramEqualization = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelShow->setText("直方图均衡化");
		HistogramEqualizationChange();
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//均值滤波
void ImageProcess::menu_spatialFilter_averageFilter_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagAverageFilter = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->labelShow->setText("均值滤波");
		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//高斯滤波
void ImageProcess::menu_spatialFilter_gaussianFilter_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagGaussianFilter = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->labelShow->setText("高斯滤波");
		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//中值滤波
void ImageProcess::menu_spatialFilter_medianFilter_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagMedianFilter = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->labelShow->setText("中值滤波");
		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//最小值滤波
void ImageProcess::menu_spatialFilter_minFilter_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagMinFilter = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 10, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("5");
		ui->labelShow->setText("最小值滤波");
		ui->horizontalSlider->setRange(0, 10);
		ui->horizontalSlider->setValue(5);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(10));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//最大值滤波
void ImageProcess::menu_spatialFilter_maxFilter_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagMaxFilter = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 10, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("5");
		ui->labelShow->setText("最大值滤波");
		ui->horizontalSlider->setRange(0, 10);
		ui->horizontalSlider->setValue(5);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(10));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//LaplacianFilter
void ImageProcess::menu_spatialFilter_LaplacianFilter_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagLaplacianFilter = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->pushButtonRed->show();
		ui->pushButtonRed->setText("4邻域1");
		ui->pushButtonBlue->setText("8邻域1");
		ui->pushButtonBlue->show();
		ui->pushButtonRed_2->show();
		ui->pushButtonRed_2->setText("4邻域2");
		ui->pushButtonBlue_2->setText("8邻域2");
		ui->pushButtonBlue_2->show();
		ui->pushButtonYes->show();
		ui->labelShow->setText("Laplacian Filter");
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//PrewittFilter
void ImageProcess::menu_spatialFilter_PrewittFilter_clicked(){
	flaginitial();
	if (flagFile == true) {
		flagPrewittFilter = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->pushButtonRed->show();
		ui->pushButtonRed->setText("x方向");
		ui->pushButtonBlue->setText("y方向");
		ui->pushButtonBlue->show();
		ui->pushButtonYes->show();
		ui->labelShow->setText("Prewitt Filter");
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//RobertsFilter
void ImageProcess::menu_spatialFilter_RobertsFilter_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagRobertsFilter = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->pushButtonRed->show();
		ui->pushButtonRed->setText("x方向");
		ui->pushButtonBlue->setText("y方向");
		ui->pushButtonBlue->show();
		ui->pushButtonYes->show();
		ui->labelShow->setText("Roberts Filter");
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//SobleFilter
void ImageProcess::menu_spatialFilter_SobelFilter_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagSobelFilter = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->pushButtonRed->show();
		ui->pushButtonRed->setText("x方向");
		ui->pushButtonBlue->setText("y方向");
		ui->pushButtonBlue->show();
		ui->pushButtonYes->show();
		ui->labelShow->setText("Soble Filter");
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//Butterworth低通滤波器
void ImageProcess::menu_frequency_ButterworthLowPass_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagButterworthLowFilter = true;
		ui->horizontalSlider->show();
		ui->horizontalSlider_2->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->labelSliderMin_2->show();
		ui->labelSliderMax_2->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("10");

		ui->lineEdit_2->show();
		QIntValidator* validator_2 = new QIntValidator(0, 100, this);
		ui->lineEdit_2->setValidator(validator_2);
		ui->lineEdit_2->setText("2");

		ui->labelShow->setText("butterworth 低通滤波");

		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(10);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(100));

		ui->horizontalSlider_2->setRange(0, 100);
		ui->horizontalSlider_2->setValue(2);
		ui->labelSliderMin_2->setText("0");
		ui->labelSliderMax_2->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//Butterworth高通滤波器
void ImageProcess::menu_frequency_ButterworthHighPass_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagButterworthHighFilter = true;
		ui->horizontalSlider->show();
		ui->horizontalSlider_2->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->labelSliderMin_2->show();
		ui->labelSliderMax_2->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("10");

		ui->lineEdit_2->show();
		QIntValidator* validator_2 = new QIntValidator(0, 100, this);
		ui->lineEdit_2->setValidator(validator_2);
		ui->lineEdit_2->setText("2");

		ui->labelShow->setText("butterworth 高通滤波");

		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(10);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(100));

		ui->horizontalSlider_2->setRange(0, 100);
		ui->horizontalSlider_2->setValue(2);
		ui->labelSliderMin_2->setText("0");
		ui->labelSliderMax_2->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//高斯低通滤波器
void ImageProcess::menu_frequency_GaussLowPass_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagGaussLowFilter = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("10");

		ui->labelShow->setText("高斯低通滤波");

		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(10);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//高斯高通滤波器
void ImageProcess::menu_frequency_GaussHighPass_clicked(){
	flaginitial();
	if (flagFile == true) {
		flagGaussHighFilter = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("10");

		ui->labelShow->setText("高斯高通滤波");

		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(10);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//理想低通滤波器
void ImageProcess::menu_frequency_idealLowPass_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagIdealLowFilter = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("10");

		ui->labelShow->setText("理想低通滤波");

		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(10);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//理想高通滤波
void ImageProcess::menu_frequency_idealHighPass_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagIdealHighFilter = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("10");

		ui->labelShow->setText("理想高通滤波");

		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(10);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//旋转
void ImageProcess::menu_spatialtransformation_rotation_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagRotation = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 360, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");
		ui->labelShow->setText("旋转");
		ui->horizontalSlider->setRange(0, 360);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText("360");

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//缩放
void ImageProcess::menu_spatialtransformation_zoom_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagZoom = true;
		ui->horizontalSlider->show();
		ui->horizontalSlider_2->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->labelSliderMin_2->show();
		ui->labelSliderMax_2->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 200, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->lineEdit_2->show();
		QIntValidator* validator_2 = new QIntValidator(0, 200, this);
		ui->lineEdit_2->setValidator(validator_2);
		ui->lineEdit_2->setText("0");

		ui->labelShow->setText("缩放");

		ui->horizontalSlider->setRange(0, 200);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(200));

		ui->horizontalSlider_2->setRange(0, 200);
		ui->horizontalSlider_2->setValue(0);
		ui->labelSliderMin_2->setText("0");
		ui->labelSliderMax_2->setText(QString::number(200));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//镜像
void ImageProcess::menu_spatialtransformation_mirror_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagMirror = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->pushButtonRed->show();
		ui->pushButtonRed->setText("水平");
		ui->pushButtonBlue->setText("垂直");
		ui->pushButtonBlue->show();
		ui->pushButtonYes->show();
		ui->labelShow->setText("镜像");
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

bool ImageProcess::eventFilter(QObject* obj, QEvent* event)
{
	if (flagCropping == true) {
		if (obj == ui->labelCrop) {
			if (event->type() == QEvent::MouseButtonPress && isModify == false) {
				//cout << "start" << endl;
				QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
				if (mouseEvent->button() == Qt::LeftButton) {
					isModify = true;
					QPoint pos = QCursor::pos();
					QPoint pos2 = ui->labelCrop->mapFromGlobal(pos);
					xcrop1 = pos2.x();
					ycrop1 = pos2.y();
					return  true;
				}
				else {
					return false;
				}
			}
			if (event->type() == QEvent::MouseMove && isModify == true) {
				QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
				if (mouseEvent->buttons() == Qt::LeftButton) {
					QPoint pos = QCursor::pos();
					QPoint pos2 = ui->labelCrop->mapFromGlobal(pos);
					xcrop2 = pos2.x();
					ycrop2 = pos2.y();
					QSize labelCropSize = ui->labelCrop->size();
					if (xcrop2 > labelCropSize.width() && ycrop2 > labelCropSize.height()) {
						xcrop2 = labelCropSize.width() - 1;
						ycrop2 = labelCropSize.height() - 1;
					}
					QImage tmpImg = MatToQImage(tempImage);
					QSize tmpImageSize = tmpImg.size();
					double scaleX = double(tmpImageSize.width()) / double(labelCropSize.width());
					double scaleY = double(tmpImageSize.height()) / double(labelCropSize.height());
					int adjustedX1 = int(xcrop1 * scaleX);
					int adjustedY1 = int(ycrop1 * scaleY);
					int adjustedX2 = int(xcrop2 * scaleX);
					int adjustedY2 = int(ycrop2 * scaleY);
					QPainter painter(&tmpImg);
					painter.setPen(QPen(Qt::red, 2, Qt::DashDotLine, Qt::RoundCap));
					painter.drawRect(adjustedX1, adjustedY1, adjustedX2 - adjustedX1, adjustedY2 - adjustedY1);
					painter.end();
					display_QImageInQT(ui->labelNowImage, tmpImg);

				}
				else {
					return false;
				}
			}
			if (event->type() == QEvent::MouseButtonRelease && isModify == true) {
				//cout << "end" << endl;
				isModify = false;
				QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
				if (mouseEvent->button() == Qt::LeftButton) {
					QPoint pos = QCursor::pos();
					QPoint pos2 = ui->labelCrop->mapFromGlobal(pos);
					xcrop2 = pos2.x();
					ycrop2 = pos2.y();
					QSize labelCropSize = ui->labelCrop->size();

					if (xcrop2 > labelCropSize.width() && ycrop2 > labelCropSize.height()) {
						xcrop2 = labelCropSize.width() - 1;
						ycrop2 = labelCropSize.height() - 1;
					}
					if (xcrop1 == xcrop2)xcrop2 = xcrop1 + 1;
					if (ycrop1 == ycrop2)ycrop2 = ycrop1 + 1;
					if (xcrop1 > xcrop2) {
						int temp = xcrop2;
						xcrop2 = xcrop1;
						xcrop1 = temp;
					}
					if (ycrop1 > ycrop2) {
						int temp = ycrop2;
						ycrop2 = ycrop1;
						ycrop1 = temp;
					}

					QImage tmpImg = MatToQImage(tempImage);
					QSize tmpImageSize = tmpImg.size();

					double scaleX = double(tmpImageSize.width()) / double(labelCropSize.width());
					double scaleY = double(tmpImageSize.height()) / double(labelCropSize.height());
					int adjustedX1 = int(xcrop1 * scaleX);
					int adjustedY1 = int(ycrop1 * scaleY);
					int adjustedX2 = int(xcrop2 * scaleX);
					int adjustedY2 = int(ycrop2 * scaleY);
					QPainter painter(&tmpImg);
					painter.setPen(QPen(Qt::red, 2, Qt::DashDotLine, Qt::RoundCap));
					painter.drawRect(adjustedX1, adjustedY1, adjustedX2 - adjustedX1, adjustedY2 - adjustedY1);
					painter.end();

					int row1 = static_cast<int>(ycrop1 / scale);
					int row2 = min(tmpImageSize.height(), static_cast<int>(ycrop2 / scale));
					int col1 = static_cast<int>(xcrop1 / scale);
					int col2 = min(tmpImageSize.width(), static_cast<int>(xcrop2 / scale));
					Rect rect(col1, row1, col2 - col1, row2 - row1);
					Mat img2 = tempImage(rect);
					tempImage = img2.clone();
					display_MatInQT(ui->labelNowImage, tempImage);
					string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
					QString qstr = QString::fromStdString(s);
					ui->label_5->show();
					ui->label_5->setText(qstr);

					QSize tempImageSize(tempImage.cols, tempImage.rows);
					QSize labelNowImageSize = ui->labelNowImage->size();

					double scaleXx = double(labelNowImageSize.width()) / double(tempImageSize.width());
					double scaleYy = double(labelNowImageSize.height()) / double(tempImageSize.height());
					scale = qMin(scaleXx, scaleYy);
					QSize scaledImageSize = QSize(tempImageSize.width() * scale, tempImageSize.height() * scale);
					QPoint centerPosition = ui->labelNowImage->geometry().center() - QPoint(scaledImageSize.width() / 2, scaledImageSize.height() / 2);

					ui->labelCrop->setGeometry(QRect(centerPosition, scaledImageSize));

				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			isModify = false;
			return  false;
		}
	}
	if (flagAreaFill == true) {
		if (obj == ui->labelCrop) {
			if (event->type() == QEvent::MouseButtonRelease && isGetPoint == false) {
				QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
				if (mouseEvent->button() == Qt::LeftButton) {
					isGetPoint = true;
					QPoint pos = QCursor::pos();
					QPoint pos2 = ui->labelCrop->mapFromGlobal(pos);
					double x3 = pos2.x();
					double y3 = pos2.y();
					QSize labelCropSize = ui->labelCrop->size();

					if (x3 > labelCropSize.width() && y3 > labelCropSize.height()) {
						x3 = labelCropSize.width() - 1;
						y3 = labelCropSize.height() - 1;
					}
					
					QImage tempImg = MatToQImage(tempImage);
					QSize tmpImageSize = tempImg.size();

					
					double scaleX = double(tmpImageSize.width()) / double(labelCropSize.width());
					double scaleY = double(tmpImageSize.height()) / double(labelCropSize.height());
					int adjustedX1 = int(x3 * scaleX);
					int adjustedY1 = int(y3 * scaleY);
					pStart = Point(adjustedY1, adjustedX1);

					QPainter painter(&tempImg);
					painter.setPen(QPen(Qt::red, 5, Qt::DashDotLine, Qt::RoundCap));
					painter.drawPoint(adjustedX1, adjustedY1);
					display_QImageInQT(ui->labelCrop, tempImg);
					
					cout << "pStart" << pStart.x << " " << pStart.y << endl;
					//circle(tempImage, Point(adjustedY1, adjustedX1), 1, Scalar(0, 0, 255), 3, LINE_AA);
					//display_MatInQT(ui->labelNowImage, tempImage);

					ui->pushButtonBlue->show();
					ui->pushButtonRed->show();
					ui->pushButtonGreen->hide();

				}
				else {
					return false;
				}
			}
		}
	}
	if (flagGrabCut == true) {
		if (obj == ui->labelCrop) {
			if (event->type() == QEvent::MouseButtonPress && isGrabCut == false) {
				QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
				if (mouseEvent->button() == Qt::LeftButton) {
					cout << "start" << endl;
					isGrabCut = true;
					QPoint pos = QCursor::pos();
					QPoint pos2 = ui->labelCrop->mapFromGlobal(pos);
					xgrab1 = pos2.x();
					ygrab1 = pos2.y();
					return  true;
				}
				else {
					return false;
				}
			}
			if (event->type() == QEvent::MouseMove && isGrabCut == true) {
				QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
				if (mouseEvent->buttons() == Qt::LeftButton) {
					cout << "mid" << endl;
					QPoint pos = QCursor::pos();
					QPoint pos2 = ui->labelCrop->mapFromGlobal(pos);
					xgrab2 = pos2.x();
					ygrab2 = pos2.y();
					QSize labelCropSize = ui->labelCrop->size();
					if (xgrab2 > labelCropSize.width() && ygrab2 > labelCropSize.height()) {
						xgrab2 = labelCropSize.width() - 1;
						ygrab2 = labelCropSize.height() - 1;
					}
					QImage tmpImg = MatToQImage(tempImage);
					QSize tmpImageSize = tmpImg.size();
					double scaleX = double(tmpImageSize.width()) / double(labelCropSize.width());
					double scaleY = double(tmpImageSize.height()) / double(labelCropSize.height());
					int adjustedX1 = int(xgrab1 * scaleX);
					int adjustedY1 = int(ygrab1 * scaleY);
					int adjustedX2 = int(xgrab2 * scaleX);
					int adjustedY2 = int(ygrab2 * scaleY);
					QPainter painter(&tmpImg);
					painter.setPen(QPen(Qt::red, 2, Qt::DashDotLine, Qt::RoundCap));
					painter.drawRect(adjustedX1, adjustedY1, adjustedX2 - adjustedX1, adjustedY2 - adjustedY1);
					painter.end();
					display_QImageInQT(ui->labelNowImage, tmpImg);

				}
				else {
					return false;
				}
			}
			if (event->type() == QEvent::MouseButtonRelease && isGrabCut == true) {
				QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
				if (mouseEvent->button() == Qt::LeftButton) {
					cout << "end"<<endl;
					QPoint pos = QCursor::pos();
					QPoint pos2 = ui->labelCrop->mapFromGlobal(pos);
					xgrab2 = pos2.x();
					ygrab2 = pos2.y();
					QSize labelCropSize = ui->labelCrop->size();

					if (xgrab2 > labelCropSize.width() && ygrab2 > labelCropSize.height()) {
						xgrab2 = labelCropSize.width() - 1;
						ygrab2 = labelCropSize.height() - 1;
					}
					if (xgrab1 == xgrab2)xgrab2 = xgrab1 + 1;
					if (ygrab1 == ygrab2)ygrab2 = ygrab1 + 1;
					if (xgrab1 > xgrab2) {
						int temp = xgrab2;
						xgrab2 = xgrab1;
						xgrab1 = temp;
					}
					if (ygrab1 > ygrab2) {
						int temp = ygrab2;
						ygrab2 = ygrab1;
						ygrab1 = temp;
					}

					QImage tmpImg = MatToQImage(tempImage);
					QSize tmpImageSize = tmpImg.size();

					double scaleX = double(tmpImageSize.width()) / double(labelCropSize.width());
					double scaleY = double(tmpImageSize.height()) / double(labelCropSize.height());
					int adjustedX1 = int(xgrab1 * scaleX);
					int adjustedY1 = int(ygrab1 * scaleY);
					int adjustedX2 = int(xgrab2 * scaleX);
					int adjustedY2 = int(ygrab2 * scaleY);
					QPainter painter(&tmpImg);
					painter.setPen(QPen(Qt::red, 2, Qt::DashDotLine, Qt::RoundCap));
					Rect rectt(Point(adjustedX1, adjustedY1), Point(adjustedX2,adjustedY2));
					painter.drawRect(adjustedX1, adjustedY1, adjustedX2 - adjustedX1, adjustedY2 - adjustedY1);
					painter.end();
					GrabCutChange(rectt);
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			isModify = false;
			return  false;
		}
	}
	if (flagRegionalGrowth == true) {
		if (obj == ui->labelCrop) {
			if (event->type() == QEvent::MouseButtonRelease && isRegionalGrowth == false) {
				QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
				if (mouseEvent->button() == Qt::LeftButton) {
					isRegionalGrowth = true;
					QPoint pos = QCursor::pos();
					QPoint pos2 = ui->labelCrop->mapFromGlobal(pos);
					double x3 = pos2.x();
					double y3 = pos2.y();
					QSize labelCropSize = ui->labelCrop->size();

					if (x3 > labelCropSize.width() && y3 > labelCropSize.height()) {
						x3 = labelCropSize.width() - 1;
						y3 = labelCropSize.height() - 1;
					}

					QImage temppImg = MatToQImage(tempImage);
					QSize tmpImageSize = temppImg.size();


					double scaleX = double(tmpImageSize.width()) / double(labelCropSize.width());
					double scaleY = double(tmpImageSize.height()) / double(labelCropSize.height());
					int adjustedX1 = int(x3 * scaleX);
					int adjustedY1 = int(y3 * scaleY);
					pBegin = Point(adjustedY1, adjustedX1);

					QPainter painter(&temppImg);
					painter.setPen(QPen(Qt::red, 5, Qt::DashDotLine, Qt::RoundCap));
					painter.drawPoint(adjustedX1, adjustedY1);
					display_QImageInQT(ui->labelCrop, temppImg);
					//display_QImageInQT(ui->labelNowImage, temppImg);
					cout << "pBegin" << pBegin.x << " " << pBegin.y << endl;
					//circle(tempImage, Point(adjustedY1, adjustedX1), 1, Scalar(0, 0, 255), 3, LINE_AA);
					//display_MatInQT(ui->labelNowImage, tempImage);

					ui->pushButtonBlue->show();
					ui->pushButtonRed->show();
					ui->pushButtonGreen->hide();

				}
				else {
					return false;
				}
			}
		}
	}
	
}

//裁剪
void ImageProcess::menu_spatialtransformation_cropping_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagCropping = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelCrop->show();

		QSize nowImageSize(tempImage.cols, tempImage.rows);
		QSize labelNowImageSize = ui->labelNowImage->size();
		double scaleX = double(labelNowImageSize.width()) / double(nowImageSize.width());
		double scaleY = double(labelNowImageSize.height()) / double(nowImageSize.height());
		scale = qMin(scaleX, scaleY); 
		//cout << "scale:" << scale << endl;
		QSize scaledImageSize = QSize(nowImageSize.width() * scale, nowImageSize.height() * scale);
		QPoint centerPosition = ui->labelNowImage->geometry().center() - QPoint(scaledImageSize.width() / 2, scaledImageSize.height() / 2);
		ui->labelCrop->setGeometry(QRect(centerPosition, scaledImageSize));
		//cout << "size" << scaledImageSize.height() << "," << scaledImageSize.width() << endl;

		ui->labelShow->setText("裁剪");
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//添加高斯噪声
void ImageProcess::menu_addNoise_GaussNoise_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagGaussNoise = true;
		ui->horizontalSlider->show();
		ui->horizontalSlider_2->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->labelSliderMin_2->show();
		ui->labelSliderMax_2->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 200, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->lineEdit_2->show();
		QIntValidator* validator_2 = new QIntValidator(0, 200, this);
		ui->lineEdit_2->setValidator(validator_2);
		ui->lineEdit_2->setText("0");

		ui->labelShow->setText("高斯噪声");

		ui->horizontalSlider->setRange(0, 200);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(200));

		ui->horizontalSlider_2->setRange(0, 200);
		ui->horizontalSlider_2->setValue(0);
		ui->labelSliderMin_2->setText("0");
		ui->labelSliderMax_2->setText(QString::number(200));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//添加瑞利噪声
void ImageProcess::menu_addNoise_RayleighNoise_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagRayleighNoise = true;
		ui->horizontalSlider->show();
		ui->horizontalSlider_2->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->labelSliderMin_2->show();
		ui->labelSliderMax_2->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 200, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->lineEdit_2->show();
		QIntValidator* validator_2 = new QIntValidator(0, 200, this);
		ui->lineEdit_2->setValidator(validator_2);
		ui->lineEdit_2->setText("0");

		ui->labelShow->setText("瑞利噪声");

		ui->horizontalSlider->setRange(0, 200);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(200));

		ui->horizontalSlider_2->setRange(0, 200);
		ui->horizontalSlider_2->setValue(0);
		ui->labelSliderMin_2->setText("0");
		ui->labelSliderMax_2->setText(QString::number(200));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//添加伽马噪声
void ImageProcess::menu_addNoise_GammaNoise_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagGammaNoise = true;
		ui->horizontalSlider->show();
		ui->horizontalSlider_2->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->labelSliderMin_2->show();
		ui->labelSliderMax_2->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 200, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->lineEdit_2->show();
		QIntValidator* validator_2 = new QIntValidator(0, 200, this);
		ui->lineEdit_2->setValidator(validator_2);
		ui->lineEdit_2->setText("0");

		ui->labelShow->setText("伽马噪声");

		ui->horizontalSlider->setRange(0, 200);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(200));

		ui->horizontalSlider_2->setRange(0, 200);
		ui->horizontalSlider_2->setValue(0);
		ui->labelSliderMin_2->setText("0");
		ui->labelSliderMax_2->setText(QString::number(200));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//添加指数分布噪声
void ImageProcess::menu_addNoise_ExponentialNoise_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagExponentialNoise = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 200, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->labelShow->setText("指数分布噪声");

		ui->horizontalSlider->setRange(0, 200);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText("200");

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//添加均匀分布噪声
void ImageProcess::menu_addNoise_UniformNoise_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagUniformNoise = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 255, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->labelShow->setText("均匀分布噪声");

		ui->horizontalSlider->setRange(0, 255);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText("255");

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//添加椒盐噪声
void ImageProcess::menu_addNoise_SaltandPepperNoise_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagSaltandPepperNoise = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 200, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->labelShow->setText("椒盐噪声");

		ui->horizontalSlider->setRange(0, 200);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText("200");

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//添加周期噪声
void ImageProcess::menu_addNoise_PeriodicNoise_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagPeriodicNoise = true;
		ui->horizontalSlider->show();
		ui->horizontalSlider_2->show();
		ui->horizontalSlider_3->show();

		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->labelSliderMin_2->show();
		ui->labelSliderMax_2->show();
		ui->labelSliderMin_3->show();
		ui->labelSliderMax_3->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 255, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->lineEdit_2->show();
		QIntValidator* validator_2 = new QIntValidator(0, 200, this);
		ui->lineEdit_2->setValidator(validator_2);
		ui->lineEdit_2->setText("0");

		ui->lineEdit_3->show();
		QIntValidator* validator_3 = new QIntValidator(0, 200, this);
		ui->lineEdit_3->setValidator(validator_3);
		ui->lineEdit_3->setText("0");

		ui->labelShow->setText("周期噪声");

		ui->horizontalSlider->setRange(0, 255);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(255));

		ui->horizontalSlider_2->setRange(0, 200);
		ui->horizontalSlider_2->setValue(0);
		ui->labelSliderMin_2->setText("0");
		ui->labelSliderMax_2->setText(QString::number(200));

		ui->horizontalSlider_3->setRange(0, 200);
		ui->horizontalSlider_3->setValue(0);
		ui->labelSliderMin_3->setText("0");
		ui->labelSliderMax_3->setText(QString::number(200));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//算数均值滤波
void ImageProcess::menu_recovery_arithmeticMean_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagArithmeticMean = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->labelShow->setText("算数均值滤波");
		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//几何均值
void ImageProcess::menu_recovery_geometricMean_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagGeometricMean = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 20, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->labelShow->setText("几何均值滤波");
		ui->horizontalSlider->setRange(0, 20);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(20));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//谐波均值滤波
void ImageProcess::menu_recovery_harmonicMean_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagHarmonicMean = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 20, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->labelShow->setText("谐波均值滤波");
		ui->horizontalSlider->setRange(0, 20);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(20));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//反谐波均值
void ImageProcess::menu_recovery_antiharmonicMean_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagAntiharmonicMean = true;
		ui->horizontalSlider->show();
		ui->horizontalSlider_2->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->labelSliderMin_2->show();
		ui->labelSliderMax_2->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 20, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->lineEdit_2->show();
		QIntValidator* validator_2 = new QIntValidator(0, 10, this);
		ui->lineEdit_2->setValidator(validator_2);
		ui->lineEdit_2->setText("0");

		ui->labelShow->setText("反谐波均值滤波");

		ui->horizontalSlider->setRange(0, 20);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(20));

		ui->horizontalSlider_2->setRange(0, 10);
		ui->horizontalSlider_2->setValue(0);
		ui->labelSliderMin_2->setText("0");
		ui->labelSliderMax_2->setText(QString::number(10));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//中点滤波
void ImageProcess::menu_recovery_midpoint_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagMidpoint = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 20, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->labelShow->setText("中点滤波");
		ui->horizontalSlider->setRange(0, 20);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(20));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//修正后的阿尔法均值滤波
void ImageProcess::menu_recovery_alphaTrimmedMean_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagAlphaTrimmedMean = true;
		ui->horizontalSlider->show();
		ui->horizontalSlider_2->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->labelSliderMin_2->show();
		ui->labelSliderMax_2->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 20, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->lineEdit_2->show();
		QIntValidator* validator_2 = new QIntValidator(0, 10, this);
		ui->lineEdit_2->setValidator(validator_2);
		ui->lineEdit_2->setText("0");

		ui->labelShow->setText("修正后的阿尔法均值滤波");

		ui->horizontalSlider->setRange(0, 20);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(20));

		ui->horizontalSlider_2->setRange(0, 10);
		ui->horizontalSlider_2->setValue(0);
		ui->labelSliderMin_2->setText("0");
		ui->labelSliderMax_2->setText(QString::number(10));
	}
}

//自适应局部降噪滤波
void ImageProcess::menu_recovery_adaptiveNoiseCancel_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagAdaptiveNoiseCancel = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 20, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->labelShow->setText("自适应局部降噪滤波");
		ui->horizontalSlider->setRange(0, 20);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(20));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//自适应中值滤波器
void ImageProcess::menu_recovery_adaptiveMedian_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagAdaptiveMedian = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 20, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->labelShow->setText("自适应中值滤波器");
		ui->horizontalSlider->setRange(0, 20);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(20));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//膨胀
void ImageProcess::menu_morphological_expansion_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagExpansion = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 20, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->labelShow->setText("膨胀");
		ui->horizontalSlider->setRange(0, 20);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(20));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//腐蚀
void ImageProcess::menu_morphological_erosion_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagErosion = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 20, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->labelShow->setText("腐蚀");
		ui->horizontalSlider->setRange(0, 20);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(20));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//开操作
void ImageProcess::menu_morphological_openOperation_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagOpenOperation = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 20, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->labelShow->setText("开操作");
		ui->horizontalSlider->setRange(0, 20);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(20));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//闭操作
void ImageProcess::menu_morphological_closeOperation_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagCloseOperation = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 20, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->labelShow->setText("闭操作");
		ui->horizontalSlider->setRange(0, 20);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(20));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//高帽
void ImageProcess::menu_morphological_topHat_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagTopHat = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 20, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->labelShow->setText("高帽");
		ui->horizontalSlider->setRange(0, 20);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(20));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//低帽
void ImageProcess::menu_morphological_lowHat_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagLowHat = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 20, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->labelShow->setText("低帽");
		ui->horizontalSlider->setRange(0, 20);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(20));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//击中/击不中变换
void ImageProcess::menu_morphological_hitMiss_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagLowHat = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 20, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->labelShow->setText("击中/击不中变换");
		ui->horizontalSlider->setRange(0, 20);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(20));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//边界提取
void ImageProcess::menu_morphological_boundaryExtraction_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagBoundaryExtraction = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 20, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->labelShow->setText("边界提取");
		ui->horizontalSlider->setRange(0, 20);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(20));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//连通分量提取
void ImageProcess::menu_morphological_connectedComponentExtraction_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagConnectedComponentExtraction = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->pushButtonRed->show();
		ui->pushButtonRed->setText("黑白");
		ui->pushButtonBlue->setText("白黑");
		ui->pushButtonBlue->show();
		ui->pushButtonYes->show();
		ui->labelShow->setText("连通分量提取");
		
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//区域填充
void ImageProcess::menu_morphological_areaFill_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagAreaFill = true;
		isGetPoint = false;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();

		ui->pushButtonRed->setText("黑白");
		ui->pushButtonBlue->setText("白黑");
		
		ui->labelShow->setText("区域填充");

		ui->pushButtonGreen->show();
		ui->pushButtonGreen->setText("选点");

		QSize nowImageSize(tempImage.cols, tempImage.rows);
		QSize labelNowImageSize = ui->labelNowImage->size();
		double scaleX = double(labelNowImageSize.width()) / double(nowImageSize.width());
		double scaleY = double(labelNowImageSize.height()) / double(nowImageSize.height());
		scale = qMin(scaleX, scaleY);
		QSize scaledImageSize = QSize(nowImageSize.width() * scale, nowImageSize.height() * scale);
		QPoint centerPosition = ui->labelNowImage->geometry().center() - QPoint(scaledImageSize.width() / 2, scaledImageSize.height() / 2);
		ui->labelCrop->setGeometry(QRect(centerPosition, scaledImageSize));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}
//凸壳
void ImageProcess::menu_morphological_convexShell_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagConvexShell = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelShow->setText("凸壳");
		ConvexShellChange();
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//细化
void ImageProcess::menu_morphological_refinement_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagRefinement = true;
		typeRefinement = 0;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();
		ui->pushButtonBlue->show();
		ui->pushButtonRed->show();
		ui->pushButtonBlue->setText("黑白");
		ui->pushButtonRed->setText("白黑");
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->labelShow->setText("细化");
		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//粗化
void ImageProcess::menu_morphological_coarsening_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagCoarsening = true;
		typeCoarsening = 0;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->pushButtonBlue->show();
		ui->pushButtonRed->show();
		ui->pushButtonBlue->setText("黑白");
		ui->pushButtonRed->setText("白黑");

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("0");

		ui->labelShow->setText("粗化");
		ui->horizontalSlider->setRange(0, 100);
		ui->horizontalSlider->setValue(0);
		ui->labelSliderMin->setText("0");

		ui->labelSliderMax->setText(QString::number(100));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//简单直方图分割
void ImageProcess::menu_imageSegmentation_histogramSegmentation_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagHistogramSegmentation = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		
		ui->pushButtonRed->setText("黑白");
		ui->pushButtonBlue->setText("彩色");
		ui->pushButtonGreen->setText("白黑");
		ui->pushButtonBlue->show();
		ui->pushButtonRed->show();
		ui->pushButtonGreen->show();

		ui->labelShow->setText("简单直方图分割");

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//迭代阈值
void ImageProcess::menu_imageSegmentation_iterativeThresholdSegmentation_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagIterativeThresholdSegmentation = true;
		typeIterativeThresholdSegmentation = 0;

		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->horizontalSlider->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(1, 255, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("1");

		ui->labelShow->setText("迭代阈值分割");

		ui->horizontalSlider->setRange(1, 255);
		ui->horizontalSlider->setValue(1);
		ui->labelSliderMin->setText("1");
		ui->labelSliderMax->setText(QString::number(255));

		ui->pushButtonRed->setText("黑白");
		ui->pushButtonBlue->setText("彩色");
		ui->pushButtonGreen->setText("白黑");
		ui->pushButtonBlue->show();
		ui->pushButtonRed->show();
		ui->pushButtonGreen->show();


	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//最佳阈值分割
void ImageProcess::menu_imageSegmentation_otsu_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagOtsu = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();

		ui->pushButtonRed->setText("黑白");
		ui->pushButtonBlue->setText("彩色");
		ui->pushButtonGreen->setText("白黑");
		ui->pushButtonBlue->show();
		ui->pushButtonRed->show();
		ui->pushButtonGreen->show();

		ui->labelShow->setText("最佳阈值分割");

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//Kmeans聚类
void ImageProcess::menu_imageSegmentation_Kmeans_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagKmeans = true;
		ui->horizontalSlider->show();
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(1, 100, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("1");

		ui->labelShow->setText("Kmeans聚类");

		ui->horizontalSlider->setRange(1, 100);
		ui->horizontalSlider->setValue(1);
		ui->labelSliderMin->setText("1");
		ui->labelSliderMax->setText("100");

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//meanShift算法
void ImageProcess::menu_imageSegmentation_meanShift_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagMeanShift = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();

		ui->horizontalSlider->show();
		ui->labelSliderMin->show();
		ui->labelSliderMax->show();

		ui->horizontalSlider_2->show();
		ui->labelSliderMin_2->show();
		ui->labelSliderMax_2->show();
		
		ui->lineEdit->show();
		QIntValidator* validator = new QIntValidator(0, 50, this);
		ui->lineEdit->setValidator(validator);
		ui->lineEdit->setText("10");

		ui->lineEdit_2->show();
		QIntValidator* validator_2 = new QIntValidator(0, 50, this);
		ui->lineEdit_2->setValidator(validator_2);
		ui->lineEdit_2->setText("10");

		ui->labelShow->setText("meanshift");

		ui->horizontalSlider->setRange(0, 50);
		ui->horizontalSlider->setValue(10);
		ui->labelSliderMin->setText("0");
		ui->labelSliderMax->setText(QString::number(50));

		ui->horizontalSlider_2->setRange(0, 50);
		ui->horizontalSlider_2->setValue(10);
		ui->labelSliderMin_2->setText("0");
		ui->labelSliderMax_2->setText(QString::number(50));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//分水岭算法
void ImageProcess::menu_imageSegmentation_watershed_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagWaterShed = true;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelShow->setText("分水岭");
		WatershedChange();
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//GrabCut算法
void ImageProcess::menu_imageSegmentation_grabCut_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagGrabCut = true;
		xgrab1 = 0;
		xgrab2 = 0;
		ygrab1 = 0;
		ygrab2 = 0;

		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();
		ui->labelShow->setText("GrabCut");

		ui->pushButtonGreen->setText("画区");
		ui->pushButtonGreen->show();

		isGrabCut = false;
		QSize nowImageSize(nowImage.cols, nowImage.rows);
		QSize labelNowImageSize = ui->labelNowImage->size();
		double scaleX = double(labelNowImageSize.width()) / double(nowImageSize.width());
		double scaleY = double(labelNowImageSize.height()) / double(nowImageSize.height());
		scale = qMin(scaleX, scaleY);
		QSize scaledImageSize = QSize(nowImageSize.width() * scale, nowImageSize.height() * scale);
		QPoint centerPosition = ui->labelNowImage->geometry().center() - QPoint(scaledImageSize.width() / 2, scaledImageSize.height() / 2);
		ui->labelCrop->setGeometry(QRect(centerPosition, scaledImageSize));
		
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//区域生长
void ImageProcess::menu_imageSegmentation_regionalGrowth_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagRegionalGrowth = true;
		isRegionalGrowth = false;
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();

		ui->pushButtonRed->setText("黑白");
		ui->pushButtonBlue->setText("白黑");

		ui->labelShow->setText("区域生长");

		ui->pushButtonGreen->show();
		ui->pushButtonGreen->setText("选点");

		QSize nowImageSize(tempImage.cols, tempImage.rows);
		QSize labelNowImageSize = ui->labelNowImage->size();
		double scaleX = double(labelNowImageSize.width()) / double(nowImageSize.width());
		double scaleY = double(labelNowImageSize.height()) / double(nowImageSize.height());
		scale = qMin(scaleX, scaleY);
		QSize scaledImageSize = QSize(nowImageSize.width() * scale, nowImageSize.height() * scale);
		QPoint centerPosition = ui->labelNowImage->geometry().center() - QPoint(scaledImageSize.width() / 2, scaledImageSize.height() / 2);
		ui->labelCrop->setGeometry(QRect(centerPosition, scaledImageSize));

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//直方图显示
void ImageProcess::menu_other_showHistogram_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagShowHistogram = true;
		
		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();

		

		ui->labelShow->setText("直方图");

		ui->pushButtonGreen->show();
		ui->pushButtonGreen->setText("显示");

		

	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//频谱图

void ImageProcess::menu_other_showSpectrogram_clicked() {
	flaginitial();
	if (flagFile == true) {
		flagShowSpectrogram = true;

		ui->labelShow->show();
		ui->pushButtonNo->show();
		ui->pushButtonYes->show();



		ui->labelShow->setText("频谱图");

		ui->pushButtonGreen->show();
		ui->pushButtonGreen->setText("显示");



	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}
//确认按键
void ImageProcess::button_yes_clicked() {
	
		
		ui->menu->close();
		if (mats_back.size() == 10) {
			auto it = mats_back.begin();
			mats_back.erase(it);
		}
		mats_back.push_back(nowImage);
		if (mats_back.size() > 0) {
			ui->pushButton_back->setIcon(back1);
		}
		nowImage = tempImage.clone();
		display_MatInQT(ui->labelNowImage, nowImage);
		flaginitial();
		ui->pushButton_back->show();
		ui->pushButton_next->show();
		ui->labelShow->show();
		ui->labelShow->setText("处理详情");
		return;
	
}

//取消按键
void ImageProcess::button_no_clicked() {
		flaginitial();
		tempImage = nowImage.clone();
		display_MatInQT(ui->labelNowImage, nowImage);
		ui->menu->close();
		ui->pushButton_back->show();
		ui->pushButton_next->show();
		ui->labelShow->show();
		ui->labelShow->setText("处理详情");
		return;
}

//back按键
void ImageProcess::button_back_clicked() {
	if (mats_back.size() != 0) {
		Mat matb = mats_back.back();
		
		if (mats_next.size() == 10) {
			auto it = mats_next.begin();
			mats_next.erase(it);
		}
		mats_next.push_back(nowImage);
		if (mats_next.size() > 0) {
			ui->pushButton_next->setIcon(next1);
		}
		
		nowImage = matb;
		mats_back.pop_back();
		if (mats_back.size() == 0) {
			ui->pushButton_back->setIcon(back2);
		}
		display_MatInQT(ui->labelNowImage, nowImage);
	}
}

//next按键
void ImageProcess::button_next_clicked() {
	if (mats_next.size() != 0) {
		Mat matb = mats_next.back();
		
		if (mats_back.size() == 10) {
			auto it = mats_back.begin();
			mats_back.erase(it);
		}
		mats_back.push_back(nowImage);
		if (mats_back.size() > 0) {
			ui->pushButton_back->setIcon(back1);
		}
		nowImage = matb;
		mats_next.pop_back();
		if (mats_next.size() == 0) {
			ui->pushButton_next->setIcon(next2);
		}
		display_MatInQT(ui->labelNowImage, nowImage);
	}
}

//红色按键
void ImageProcess::button_red_clicked() {
	if (flagHomochromy == true) {
		
		HomochromyChange(2);
	}
	if (flagLaplacianFilter == true) {
		
		LaplacianFilterChange(1);
	}
	if (flagSobelFilter == true) {
		
		SobelFilterChange(1);
	}
	if (flagRobertsFilter == true) {		
		RobertsFilterChange(1);
	}
	if (flagPrewittFilter == true) {
		
		PrewittFilterChange(1);
	}
	if (flagMirror==true) {
		MirrorChange(1);
	}
	if (flagConnectedComponentExtraction == true) {
		ConnectedComponentExtractionChange(0);
	}
	if (flagAreaFill == true) {
		ui->label_11->show();
		ui->label_11->setText("处理中");
		AreaFillChange(0);
	}
	
	if (flagHistogramSegmentation == true) {
		HistogramSegmentationChange(0);
	}
	
	if (flagOtsu == true) {
		OtsuChange(0);
	}
	if (flagRegionalGrowth == true) {
		RegionalGrowthChange(0);
	}
	if (flagRefinement == true) {
		typeRefinement = 0;
		RefinementChange();
	}
	if (flagCoarsening == true) {
		typeCoarsening = 0;
		CoarseningChange();
	}
	if (flagIterativeThresholdSegmentation == true) {
		typeIterativeThresholdSegmentation = 0;
		IterativeThresholdSegmentationChange(typeIterativeThresholdSegmentation);
	}
	
}

//绿色按键
void ImageProcess::button_green_clicked() {
	if (flagHomochromy == true) {
		
		HomochromyChange(1);
	}
	if (flagAreaFill == true) {
		ui->labelCrop->show();
	}
	
	if (flagHistogramSegmentation == true) {
		HistogramSegmentationChange(1);
	}
	
	if (flagOtsu == true) {
		OtsuChange(1);
	}
	if (flagGrabCut == true) {
		ui->labelCrop->show();
		cout << "button" << endl;
		ui->pushButtonGreen->hide();
	}
	if (flagRegionalGrowth == true) {
		ui->labelCrop->show();
	}
	if (flagShowHistogram == true) {
		ShowHistogramChange();
	}
	if (flagShowSpectrogram == true) {
		ShowSpectrogramChange();
	}
	if (flagIterativeThresholdSegmentation == true) {
		typeIterativeThresholdSegmentation = 1;
		IterativeThresholdSegmentationChange(typeIterativeThresholdSegmentation);
	}
}

//蓝色按键
void ImageProcess::button_blue_clicked() {
	if (flagHomochromy == true) {
		
		HomochromyChange(0);
	}
	if (flagLaplacianFilter == true) {
		
		LaplacianFilterChange(2);
	}
	if (flagSobelFilter == true) {
		
		SobelFilterChange(2);
	}
	if (flagRobertsFilter == true) {
		
		RobertsFilterChange(2);
	}
	if (flagPrewittFilter == true) {
		
		PrewittFilterChange(2);
	}
	if (flagMirror == true) {
		MirrorChange(0);
	}
	if (flagConnectedComponentExtraction == true) {
		ConnectedComponentExtractionChange(1);
	}
	if (flagAreaFill == true) {
		ui->label_11->show();
		ui->label_11->setText("处理中");
		AreaFillChange(1);
	}
	
	if (flagHistogramSegmentation == true) {
		HistogramSegmentationChange(3);
	}
	
	if (flagOtsu == true) {
		OtsuChange(3);
	}
	if (flagRegionalGrowth == true) {
		RegionalGrowthChange(1);
	}
	if (flagRefinement == true) {
		typeRefinement = 1;
		RefinementChange();
	}
	if (flagCoarsening == true) {
		typeCoarsening = 1;
		CoarseningChange();
	}
	if (flagIterativeThresholdSegmentation == true) {
		typeIterativeThresholdSegmentation = 3;
		IterativeThresholdSegmentationChange(typeIterativeThresholdSegmentation);
	}

}

//红色2按键
void ImageProcess::button_red2_clicked() {
	if (flagLaplacianFilter == true) {

		LaplacianFilterChange(3);
	}
	
}

//绿色2按键
void ImageProcess::button_green2_clicked() {
	
}

//蓝色2按键
void ImageProcess::button_blue2_clicked() {
	if (flagLaplacianFilter == true) {

		LaplacianFilterChange(4);
	}
	
}

//滑动1
void ImageProcess::slider_change() {
	if (flagFile == true) {
		if (flagGlass == true) {
			glassChange();
		}
		if (flagSketch == true) {
			sketchChange();
		}
		if (flagRelief == true) {
			reliefChange();
		}
		if (flagScuplture == true) {
			ScupltureChange();
		}
		if (flagMask == true) {
			MaskChange();
		}
		if (flagCartoon == true) {
			CartoonChange();
		}
		if (flagIllumination == true) {
			IlluminationChange();
		}
		if (flagDim == true) {
			DimChange();
		}
		if (flagVignetting == true) {
			VignettingChange();
		}
		if (flagFeather == true) {
			FeatherChange();
		}
		if (flagTemperature == true) {
			ColorTemperatrueChange();
		}
		if (flagSaturability == true) {
			SaturabilityChange();
		}
		if (flagLuminance == true) {
			LuminanceChange();
		}
		if (flagContrast == true) {
			ContrastChange();
		}
		if (flagHue == true) {
			HueChange();
		}
		if (flagGranular == true) {
			GranularChange();
		}
		if (flagSharpen == true) {
			SharpenChange();
		}
		if (flagHighlight == true) {
			HighlightChange();
		}
		if (flagShadow == true) {
			ShadowChange();
		}
		if (flagWhiteAndBlack == true) {
			WhiteAndBlackChange();
		}
		if (flagWatercolor == true) {
			WatercolorChange();
		}
		if (flagFleet == true) {
			FleetChange();
		}
		if (flagConvex == true) {
			ConvexChange();
		}
		if (flagConcave == true) {
			ConcaveChange();
		}
		if (flagNeon == true) {
			NeonChange();
		}
		if (flagGhost == true) {
			GhostChange();
		}
		if (flagOil == true) {
			OilChange();
		}
		if (flagLog == true) {
			LogChange();
		}
		if (flagGamma == true) {
			GammaChange();
		}
		if (flagAverageFilter == true) {
			AverageFilterChange();
		}
		if (flagGaussianFilter == true) {
			GaussianFilterChange();
			
		}
		if (flagMedianFilter == true) {
			MedianFilterChange();

		}
		if (flagMinFilter == true) {
			MinFilterChange();

		}
		if (flagMaxFilter == true) {
			MaxFilterChange();
		}
		if (flagIdealLowFilter == true) {
			IdealLowFilterChange();
		}
		if (flagIdealHighFilter == true) {
			IdealHighFilterChange();
		}
		if (flagButterworthHighFilter == true) {
			ButterworthHighFilterChange();
		}
		if (flagButterworthLowFilter == true) {
			ButterworthLowFilterChange();
		}
		if (flagGaussHighFilter == true) {
			GaussHighFilterChange();
		}
		if (flagGaussLowFilter == true) {
			GaussLowFilterChange();
		}
		if (flagRotation == true) {
			RotationChange();
		}
		if (flagZoom == true) {
			ZoomChange();
		}
		if (flagGaussNoise == true) {
			GaussNoiseChange();
		}
		if (flagRayleighNoise == true) {
			RayleighNoiseChange();
		}
		if (flagGammaNoise == true) {
			GammaNoiseChange();
		}
		if (flagExponentialNoise == true) {
			ExponentialNoiseChange();
		}
		if (flagUniformNoise == true) {
			UniformNoiseChange();
		}
		if (flagSaltandPepperNoise == true) {
			SaltandPepperNoiseChange();
		}
		if (flagPeriodicNoise == true) {
			PeriodicNoiseChange();
		}
		if (flagArithmeticMean == true) {
			AverageFilterChange();
		}
		if (flagGeometricMean == true) {
			GeometricMeanChange();
		}
		if (flagHarmonicMean == true) {
			HarmonicMeanChange();
		}
		if (flagAntiharmonicMean == true) {
			AntiharmonicMeanChange();
		}
		if (flagMidpoint == true) {
			MidpointChange();
		}
		if (flagAlphaTrimmedMean == true) {
			AlphaTrimmedMeanChange();
		}
		if (flagAdaptiveNoiseCancel == true) {
			AdaptiveNoiseCancelChange();
		}
		if (flagAdaptiveMedian == true) {
			AdaptiveMedianChange();
		}
		if (flagExpansion == true) {
			ExpansionChange();
		}
		if (flagErosion == true) {
			ErosionChange();
		}
		if (flagOpenOperation == true) {
			OpenOperationChange();
		}
		if (flagCloseOperation == true) {
			CloseOperationChange();
		}
		if (flagTopHat == true) {
			TopHatChange();
		}
		if (flagLowHat == true) {
			LowHatChange();
		}
		if (flagBoundaryExtraction == true) {
			BoundaryExtractionChange();
		}
		if (flagRefinement == true) {
			RefinementChange();
		}
		if (flagCoarsening == true) {
			CoarseningChange();
		}
		if (flagKmeans == true) {
			KmeansChange();
		}
		if (flagMeanShift == true) {
			MeanShiftChange();
		}
		if (flagIterativeThresholdSegmentation == true) {
			IterativeThresholdSegmentationChange(typeIterativeThresholdSegmentation);
		}
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//滑动2
void ImageProcess::slider2_change() {
	if (flagFile == true) {

		if (flagSketch == true) {
			sketchChange();
		}
		if (flagVignetting == true) {
			VignettingChange();
		}
		if (flagWatercolor == true) {
			WatercolorChange();
		}
		if (flagOil == true) {
			OilChange();
		}
		if (flagGamma == true) {
			GammaChange();
		}
		if (flagButterworthHighFilter == true) {
			ButterworthHighFilterChange();
		}
		if (flagButterworthLowFilter == true) {
			ButterworthLowFilterChange();
		}
		if (flagZoom == true) {
			ZoomChange();
		}
		if (flagGaussNoise == true) {
			GaussNoiseChange();
		}
		if (flagRayleighNoise == true) {
			RayleighNoiseChange();
		}
		if (flagGammaNoise == true) {
			GammaNoiseChange();
		}
		if (flagPeriodicNoise == true) {
			PeriodicNoiseChange();
		}
		if (flagAntiharmonicMean == true) {
			AntiharmonicMeanChange();
		}
		if (flagAlphaTrimmedMean == true) {
			AlphaTrimmedMeanChange();
		}
		if (flagHitMiss == true) {
			HitMissChange();
		}
		
		
		if (flagMeanShift == true) {
			MeanShiftChange();
		}
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//滑动3
void ImageProcess::slider3_change() {
	if (flagFile == true) {
		if (flagPeriodicNoise == true) {
			PeriodicNoiseChange();
		}
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//输入1
void ImageProcess::LineEdit_first_clicked() {
	int val = (ui->lineEdit->text()).toInt();
	
	if (flagFile == true) {
		if (flagGlass == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagSketch == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagRelief == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagScuplture == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagMask == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagCartoon == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagIllumination == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagDim == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagVignetting == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagFeather == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagTemperature == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagSaturability == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagLuminance == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagContrast == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagHue == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagGranular == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagSharpen == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagHighlight == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagShadow == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagWhiteAndBlack == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagWatercolor == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagFleet == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagConvex == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagConcave == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagNeon == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagGhost == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagOil == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagLog == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagGamma == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagAverageFilter == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagGaussianFilter == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagMedianFilter == true) {
			ui->horizontalSlider->setValue(val);

		}
		if (flagMinFilter == true) {
			ui->horizontalSlider->setValue(val);

		}
		if (flagMaxFilter == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagIdealLowFilter == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagIdealHighFilter == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagButterworthHighFilter == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagButterworthLowFilter == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagGaussHighFilter == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagGaussLowFilter == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagRotation == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagZoom == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagGaussNoise == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagRayleighNoise == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagGammaNoise == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagExponentialNoise == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagUniformNoise == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagSaltandPepperNoise == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagPeriodicNoise == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagArithmeticMean == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagGeometricMean == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagHarmonicMean == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagAntiharmonicMean == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagMidpoint == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagAlphaTrimmedMean == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagAdaptiveNoiseCancel == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagAdaptiveMedian == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagExpansion == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagErosion == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagOpenOperation == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagCloseOperation == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagTopHat == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagLowHat == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagHitMiss == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagBoundaryExtraction == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagRefinement == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagCoarsening == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagKmeans == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagMeanShift == true) {
			ui->horizontalSlider->setValue(val);
		}
		if (flagIterativeThresholdSegmentation == true) {
			ui->horizontalSlider->setValue(val);
		}
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//输入2
void ImageProcess::LineEdit_second_clicked() {
	int val = (ui->lineEdit_2->text()).toInt();
	if (flagFile == true) {
		if (flagSketch == true) {
			ui->horizontalSlider_2->setValue(val);
			
		}
		if (flagVignetting == true) {
			ui->horizontalSlider_2->setValue(val);
		}
		if (flagWatercolor == true) {
			ui->horizontalSlider_2->setValue(val);
		}
		if (flagOil == true) {
			ui->horizontalSlider_2->setValue(val);
		}
		if (flagGamma == true) {
			ui->horizontalSlider_2->setValue(val);
		}
		if (flagButterworthHighFilter == true) {
			ui->horizontalSlider_2->setValue(val);
		}
		if (flagButterworthLowFilter == true) {
			ui->horizontalSlider_2->setValue(val);
		}
		if (flagZoom == true) {
			ui->horizontalSlider_2->setValue(val);
		}
		if (flagGaussNoise == true) {
			ui->horizontalSlider_2->setValue(val);
		}
		if (flagRayleighNoise == true) {
			ui->horizontalSlider_2->setValue(val);
		}
		if (flagGammaNoise == true) {
			ui->horizontalSlider_2->setValue(val);
		}
		if (flagPeriodicNoise == true) {
			ui->horizontalSlider_2->setValue(val);
		}
		if (flagAntiharmonicMean == true) {
			ui->horizontalSlider_2->setValue(val);
		}
		if (flagAlphaTrimmedMean == true) {
			ui->horizontalSlider_2->setValue(val);
		}
		
		
		if (flagMeanShift == true) {
			ui->horizontalSlider_2->setValue(val);
		}
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//输入3
void ImageProcess::LineEdit_third_clicked() {
	int val = (ui->lineEdit_2->text()).toInt();
	if (flagFile == true) {
		
		if (flagPeriodicNoise == true) {
			ui->horizontalSlider_3->setValue(val);
		}
	}
	else {
		QMessageBox::warning(this, "错误", "未打开图片！");
	}
}

//毛玻璃值改变
void ImageProcess::glassChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = filter.glass(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows)+"px" + " * " + to_string(tempImage.cols)+"px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//素描值改变
void ImageProcess::sketchChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int n1 = ui->horizontalSlider->value(); 
	int n2 = ui->horizontalSlider_2->value(); 
	tempImage = filter.sketch(nowImage, n1, n2);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(n1));
	ui->lineEdit_2->setText(QString::number(n2));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//浮雕值改变
void ImageProcess::reliefChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	Mat gray;
	cvtColor(nowImage, gray, cv::COLOR_BGR2GRAY);
	tempImage = filter.relief(nowImage,val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");

}
//雕刻值改变
void ImageProcess::ScupltureChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	Mat gray;
	cvtColor(nowImage, gray, cv::COLOR_BGR2GRAY);
	tempImage = filter.scuplture(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");

}

//马赛克值改变
void ImageProcess::MaskChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = filter.myMask(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//油画值改变
void ImageProcess::OilChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int n1 = ui->horizontalSlider->value(); 
	int n2 = ui->horizontalSlider_2->value(); 
	tempImage = filter.oil(nowImage,n1, n2);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(n1));
	ui->lineEdit_2->setText(QString::number(n2));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//怀旧值改变
void ImageProcess::OldChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	tempImage = filter.old(nowImage, nowImage.rows, nowImage.cols);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//流年值改变
void ImageProcess::FleetChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = filter.fleet(nowImage, nowImage.rows, nowImage.cols,val/2);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//卡通值改变
void ImageProcess::CartoonChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 

	tempImage = filter.cartoon(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//光照值改变
void ImageProcess::IlluminationChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = filter.illumination(nowImage, nowImage.rows, nowImage.cols, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//模糊值改变
void ImageProcess::DimChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = filter.dim(nowImage, nowImage.rows, nowImage.cols, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//晕影值改变
void ImageProcess::VignettingChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int n1 = ui->horizontalSlider->value();
	int n2 = ui->horizontalSlider_2->value(); 
	Mat gray;
	cvtColor(nowImage, gray, COLOR_BGR2GRAY);
	tempImage = enhance.vignetting(nowImage, nowImage.rows, nowImage.cols, n1/100.0, n2/100.0);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(n1));
	ui->lineEdit_2->setText(QString::number(n2));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//熔铸值改变
void ImageProcess::CastingChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	tempImage = filter.casting(nowImage, nowImage.rows, nowImage.cols);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//冰冻值改变
void ImageProcess::FrozenChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	tempImage = filter.frozen(nowImage, nowImage.rows, nowImage.cols);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//连环画值改变
void ImageProcess::ComicChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	tempImage = filter.comic(nowImage, nowImage.rows, nowImage.cols);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//羽化值改变
void ImageProcess::FeatherChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = filter.feather(nowImage, nowImage.rows, nowImage.cols, val/100.0);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//色温值改变
void ImageProcess::ColorTemperatrueChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = enhance.colorTemperature(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//饱和度值改变
void ImageProcess::SaturabilityChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = enhance.saturability(nowImage, val/100.0);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//亮度值改变
void ImageProcess::LuminanceChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = enhance.luminance(nowImage, val / 100.0);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//对比度值改变
void ImageProcess::ContrastChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = enhance.contrast(nowImage, val / 100.0);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//色相值改变
void ImageProcess::HueChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = enhance.hue(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//颗粒值改变
void ImageProcess::GranularChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = enhance.granular(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//锐化值改变
void ImageProcess::SharpenChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = enhance.sharpen(nowImage, val/100.0);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//高光值改变
void ImageProcess::HighlightChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = enhance.HighLight(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//阴影值改变
void ImageProcess::ShadowChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = enhance.Shadow(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//反转值改变
void ImageProcess::ReversalChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	tempImage = greyTransform.reversal(nowImage);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//灰度值改变
void ImageProcess::GreyChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	tempImage = filter.grey(nowImage);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//黑白值改变
void ImageProcess::WhiteAndBlackChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = filter.whiteAndBlack(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//单色值改变
void ImageProcess::HomochromyChange(int n) {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	tempImage = filter.homochromy(nowImage,n);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//水彩值改变
void ImageProcess::WatercolorChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int n1 = ui->horizontalSlider->value(); 
	int n2 = ui->horizontalSlider_2->value();
	tempImage = filter.watercolor(nowImage, n1, n2 / 100.0);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(n1));
	ui->lineEdit_2->setText(QString::number(n2));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//单线值改变
void ImageProcess::LinedrawChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	tempImage = filter.linedraw(nowImage);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//凸透镜值改变
void ImageProcess::ConvexChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = filter.convex(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//凹透镜
void ImageProcess::ConcaveChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = filter.concave(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//霓虹值改变
void ImageProcess::NeonChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = filter.neon(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//重影值改变
void ImageProcess::GhostChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = filter.ghost(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//对数变换值改变
void ImageProcess::LogChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = greyTransform.logTransform(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//伽马变换值改变
void ImageProcess::GammaChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int n1 = ui->horizontalSlider->value(); 
	int n2 = ui->horizontalSlider_2->value(); 
	tempImage = greyTransform.gamma(nowImage, n1,n2/10.0);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(n1));
	ui->lineEdit_2->setText(QString::number(n2));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//直方图均衡化
void ImageProcess::HistogramEqualizationChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	tempImage = greyTransform.histogramEqualization(nowImage);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//均值滤波与算数均值滤波
void ImageProcess::AverageFilterChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = spatialFilter.averageFiltering(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//高斯滤波
void ImageProcess::GaussianFilterChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	
	int val = ui->horizontalSlider->value(); 
	tempImage = spatialFilter.gaussianFilter(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}


//中值滤波
void ImageProcess::MedianFilterChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");

	int val = ui->horizontalSlider->value(); 
	tempImage = spatialFilter.medianFilter(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//最小值滤波
void ImageProcess::MinFilterChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = spatialFilter.minFilter(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//最大值滤波
void ImageProcess::MaxFilterChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = spatialFilter.maxFilter(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//LaplacianFilter改变
void ImageProcess::LaplacianFilterChange(int n) {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	tempImage = spatialFilter.laplacianFilter(nowImage, n);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//PrewittFilter改变
void ImageProcess::PrewittFilterChange(int n) {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	tempImage = spatialFilter.prewittFilter(nowImage, n);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//SobelFilter改变
void ImageProcess::SobelFilterChange(int n) {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	tempImage = spatialFilter.sobelFilter(nowImage, n);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//RobertsFilter改变
void ImageProcess::RobertsFilterChange(int n) {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	tempImage = spatialFilter.robertsFilter(nowImage, n);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//butterworth 高通
void ImageProcess::ButterworthHighFilterChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int n1 = ui->horizontalSlider->value(); 
	int n2 = ui->horizontalSlider_2->value(); 
	tempImage = frequencyFilter.butterworthHighPassFilter(nowImage, n1, n2);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(n1));
	ui->lineEdit_2->setText(QString::number(n2));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//butterworth 低通
void ImageProcess::ButterworthLowFilterChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int n1 = ui->horizontalSlider->value();
	int n2 = ui->horizontalSlider_2->value(); 
	tempImage = frequencyFilter.butterworthLowPassFilter(nowImage, n1, n2);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(n1));
	ui->lineEdit_2->setText(QString::number(n2));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//理想高通
void ImageProcess::IdealHighFilterChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = frequencyFilter.idealHighPassFilter(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//理想低通
void ImageProcess::IdealLowFilterChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = frequencyFilter.idealLowPassFilter(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//高斯高通
void ImageProcess::GaussHighFilterChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = frequencyFilter.gaussHighPassFilter(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//高斯低通
void ImageProcess::GaussLowFilterChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = frequencyFilter.gaussLowPassFilter(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//旋转
void ImageProcess::RotationChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value(); 
	tempImage = spatialTransformation.rotation(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}
//缩放
void ImageProcess::ZoomChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int n1 = ui->horizontalSlider->value(); 
	int n2 = ui->horizontalSlider_2->value(); 
	tempImage = spatialTransformation.zoom(nowImage, n1 / 100.0, n2 / 100.0);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(n1));
	ui->lineEdit_2->setText(QString::number(n2));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//镜像
void ImageProcess::MirrorChange(int n) {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	tempImage = spatialTransformation.mirror(tempImage, n);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//添加高斯噪声
void ImageProcess::GaussNoiseChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int n1 = ui->horizontalSlider->value(); 
	int n2 = ui->horizontalSlider_2->value(); 
	tempImage = addNoise.gaussNoise(nowImage, n1, n2);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(n1));
	ui->lineEdit_2->setText(QString::number(n2));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//添加瑞利噪声
void ImageProcess::RayleighNoiseChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int n1 = ui->horizontalSlider->value(); 
	int n2 = ui->horizontalSlider_2->value(); 
	tempImage = addNoise.rayleighNoise(nowImage, n1, n2);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(n1));
	ui->lineEdit_2->setText(QString::number(n2));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//添加伽马噪声
void ImageProcess::GammaNoiseChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int n1 = ui->horizontalSlider->value(); 
	int n2 = ui->horizontalSlider_2->value(); 
	tempImage = addNoise.gammaNoise(nowImage, n1/40.0, n2/2.0);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(n1));
	ui->lineEdit_2->setText(QString::number(n2));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//添加指数分布噪声
void ImageProcess::ExponentialNoiseChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = addNoise.exponentialNoise(nowImage, val/2.0);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//添加均匀分布噪声
void ImageProcess::UniformNoiseChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = addNoise.uniformNoise(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//添加椒盐噪声
void ImageProcess::SaltandPepperNoiseChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = addNoise.saltandPepperNoise(nowImage, val/200.0);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//添加周期噪声
void ImageProcess::PeriodicNoiseChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int n1 = ui->horizontalSlider->value();
	int n2 = ui->horizontalSlider_2->value();
	int n3 = ui->horizontalSlider_3->value();
	tempImage = addNoise.periodicNoise(nowImage, n1, n2 / 200.0, n3 / 200.0);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(n1));
	ui->lineEdit_2->setText(QString::number(n2));
	ui->lineEdit_3->setText(QString::number(n3));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//几何均值
void ImageProcess::GeometricMeanChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = recovery.geometricMean(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//谐波均值
void ImageProcess::HarmonicMeanChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = recovery.harmonicMean(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//反谐波均值
void ImageProcess::AntiharmonicMeanChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int n1 = ui->horizontalSlider->value();
	int n2 = ui->horizontalSlider_2->value();
	tempImage = recovery.antiharmonicMean(nowImage, n1 , n2-5);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(n1));
	ui->lineEdit_2->setText(QString::number(n2));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//中点滤波
void ImageProcess::MidpointChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = recovery.midpoint(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//修正后的阿尔法滤波
void ImageProcess::AlphaTrimmedMeanChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int n1 = ui->horizontalSlider->value();
	int n2 = ui->horizontalSlider_2->value();
	tempImage = recovery.alphaTrimmedMean(nowImage, n1, n2/20.0);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(n1));
	ui->lineEdit_2->setText(QString::number(n2));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//自适应局部降噪滤波
void ImageProcess::AdaptiveNoiseCancelChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = recovery.adaptiveNoiseCancel(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//自适应中值滤波
void ImageProcess::AdaptiveMedianChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = recovery.adaptiveMedian(nowImage, val,21);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//膨胀
void ImageProcess::ExpansionChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = morphological.expansion(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//腐蚀
void ImageProcess::ErosionChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = morphological.erosion(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//开操作
void ImageProcess::OpenOperationChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = morphological.openOperation(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//闭操作
void ImageProcess::CloseOperationChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = morphological.closeOperation(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//高帽
void ImageProcess::TopHatChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = morphological.topHat(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//低帽
void ImageProcess::LowHatChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = morphological.lowHat(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//击中/击不中变换
void ImageProcess::HitMissChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = morphological.hitMiss(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//边界提取
void ImageProcess::BoundaryExtractionChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = morphological.boundaryExtraction(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//连通分量提取
void ImageProcess::ConnectedComponentExtractionChange(int n) {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	tempImage = morphological.connectedComponentExtraction(nowImage, n);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//凸壳
void ImageProcess::ConvexShellChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	tempImage = morphological.convexShell(nowImage);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//细化
void ImageProcess::RefinementChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = morphological.refinement(nowImage, val,typeRefinement);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//粗化
void ImageProcess::CoarseningChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = morphological.coarsening(nowImage, val,typeCoarsening);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//区域填充
void ImageProcess::AreaFillChange(int n) {
	
	
	
	ui->labelCrop->clear();
	ui->labelCrop->hide();
	cout << pStart.x << " " << pStart.y << endl;
	
	tempImage = morphological.areaFill(nowImage,pStart,n);
	cout << "rrrr" << endl;
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
	
}

//简单直方图分割
void ImageProcess::HistogramSegmentationChange(int n) {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	tempImage = imageSegmentation.histogramSegmentation(nowImage, n);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//迭代阈值分割
void ImageProcess::IterativeThresholdSegmentationChange(int n) {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = imageSegmentation.iterativeThresholdSegmentation(nowImage, val,n);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//最佳阈值分割
void ImageProcess::OtsuChange(int n) {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	tempImage = imageSegmentation.histogramSegmentation(nowImage, n);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//Kmeans聚类
void ImageProcess::KmeansChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int val = ui->horizontalSlider->value();
	tempImage = imageSegmentation.KmeansSegmentation(nowImage, val);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(val));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//meanShift算法
void ImageProcess::MeanShiftChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	int n1 = ui->horizontalSlider->value();
	int n2 = ui->horizontalSlider_2->value();
	tempImage = imageSegmentation.meanShiftSegmentation(nowImage, n1, n2);
	display_MatInQT(ui->labelNowImage, tempImage);
	ui->lineEdit->setText(QString::number(n1));
	ui->lineEdit_2->setText(QString::number(n2));
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//Grabcut
void ImageProcess::GrabCutChange(Rect rect) {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	cout << "change" << endl;
	
	tempImage = imageSegmentation.grabCutSegmentation(nowImage, rect);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//分水岭算法
void ImageProcess::WatershedChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	tempImage = imageSegmentation.watershedSegmentation(nowImage);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//区域生长
void ImageProcess::RegionalGrowthChange(int n) {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	ui->labelCrop->clear();
	ui->labelCrop->hide();
	cout << pBegin.x << " " << pBegin.y << endl;
	tempImage = imageSegmentation.regionalGrowth(nowImage, pBegin, 20,20,20,n);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}

//直方图显示
void ImageProcess::ShowHistogramChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	other.showHistogram(tempImage);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}
//频谱图显示
void ImageProcess::ShowSpectrogramChange() {
	ui->label_11->show();
	ui->label_11->setText("处理中...");
	other.showSpectrogram(tempImage);
	display_MatInQT(ui->labelNowImage, tempImage);
	string s = to_string(tempImage.rows) + "px" + " * " + to_string(tempImage.cols) + "px";
	QString qstr = QString::fromStdString(s);
	ui->label_5->show();
	ui->label_5->setText(qstr);
	ui->label_11->setText("处理完成");
}
// MAT 对象用 QT显示
void ImageProcess::display_MatInQT(QLabel* label, Mat mat)
{
	label->setPixmap(QPixmap::fromImage(MatToQImage(mat)).scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

// QImage 对象用 QT显示
void ImageProcess::display_QImageInQT(QLabel* label, QImage img)
{
	
	label->setPixmap(QPixmap::fromImage(img).scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}


cv::Mat ImageProcess::QImageToMat(const QImage& qim)
{
	Mat mat = Mat(qim.height(), qim.width(),
    CV_8UC3, (void*)qim.constBits(), qim.bytesPerLine());
	return mat;
}

// MAT类型 转为 QImage类型
QImage ImageProcess::MatToQImage(const cv::Mat& mat)
{
	// 8 位无符号，信道数 = 1
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);

		// 设置颜色表（用于将颜色索引转换为 q Rgb值）
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}

		// 复制输入 Mat
		uchar* pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar* pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}

	// 8 位无符号，信道数 = 3
	else if (mat.type() == CV_8UC3)
	{
		// 复制输入 Mat
		const uchar* pSrc = (const uchar*)mat.data;

		// 创建与输入 Mat 尺寸相同的 QImage
		QImage image(pSrc, mat.cols, mat.rows, (int)mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		//qDebug() << "CV_8UC4";
		// 复制输入 Mat
		const uchar* pSrc = (const uchar*)mat.data;

		// 创建与输入 Mat 尺寸相同的 QImage
		QImage image(pSrc, mat.cols, mat.rows, (int)mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		//qDebug() << "错误：Mat 无法转换为 QImage.";
		return QImage();
	}
}



