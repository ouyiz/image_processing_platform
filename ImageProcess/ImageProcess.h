#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ImageProcess.h"
#include<opencv2/opencv.hpp>
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui_c.h>
#include<iostream>
#include <QLabel>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QIntValidator>
#include <queue>
#include <QIcon>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QColorDialog>
using namespace cv;
using namespace std;
const double pi = 3.141592653;
namespace Ui
{
    class ImageProcessClass;
}

class ImageProcess : public QMainWindow
{
    Q_OBJECT

public:
    ImageProcess(QWidget *parent = nullptr);
    ~ImageProcess();
    void glassChange();
    void sketchChange();
    void reliefChange();
    void ScupltureChange();
    void OilChange();
    void MaskChange();
    void OldChange();
    void FleetChange();
    void CartoonChange();
    void IlluminationChange();
    void DimChange();
    void CastingChange();
    void FrozenChange();
    void ComicChange();
    void FeatherChange();
    void GreyChange();
    void WhiteAndBlackChange();
    void HomochromyChange(int n);
    void VignettingChange();
    void ColorTemperatrueChange();
    void SaturabilityChange();
    void LuminanceChange();
    void ContrastChange();
    void HueChange();
    void GranularChange();
    void SharpenChange();
    void HighlightChange();
    void ShadowChange();
    void WatercolorChange();
    void ReversalChange();
    void LinedrawChange();
    void ConvexChange();
    void ConcaveChange();
    void NeonChange();
    void GhostChange();
    void LogChange();
    void GammaChange();
    void HistogramEqualizationChange();
    void AverageFilterChange();
    void GaussianFilterChange();
    void MedianFilterChange();
    void MinFilterChange();
    void MaxFilterChange();
    void LaplacianFilterChange(int n);
    void PrewittFilterChange(int n);
    void RobertsFilterChange(int n);
    void SobelFilterChange(int n);
    void ButterworthHighFilterChange();
    void ButterworthLowFilterChange();
    void IdealHighFilterChange();
    void IdealLowFilterChange();
    void GaussHighFilterChange();
    void GaussLowFilterChange();
    void RotationChange();
    void ZoomChange();
    void MirrorChange(int n);
    //void CroppingChange();

    void GaussNoiseChange();
    void RayleighNoiseChange();
    void GammaNoiseChange();
    void ExponentialNoiseChange();
    void UniformNoiseChange();
    void SaltandPepperNoiseChange();
    void PeriodicNoiseChange();

    void GeometricMeanChange();
    void HarmonicMeanChange();
    void AntiharmonicMeanChange();
    void MidpointChange();
    void AlphaTrimmedMeanChange();
    void AdaptiveNoiseCancelChange();
    void AdaptiveMedianChange();

    void ExpansionChange();
    void ErosionChange();
    void OpenOperationChange();
    void CloseOperationChange();
    void TopHatChange();
    void LowHatChange();
    void HitMissChange();
    void BoundaryExtractionChange();
    void AreaFillChange(int n);
    void ConnectedComponentExtractionChange(int n);
    void ConvexShellChange();
    void CoarseningChange();
    void RefinementChange();

    void HistogramSegmentationChange(int n);
    void IterativeThresholdSegmentationChange(int n);
    void OtsuChange(int n);
    void KmeansChange();
    void MeanShiftChange();
    void WatershedChange();
    void GrabCutChange(Rect rect);
    void RegionalGrowthChange(int n);

    void ShowSpectrogramChange();
    void ShowHistogramChange();

    void flaginitial();

    QImage MatToQImage(const cv::Mat& mat);    // MAT类型 转为 QImage类型
    Mat QImageToMat(const QImage& image);
    void display_MatInQT(QLabel* label, Mat mat);    // MAT 对象用 QT显示
    void display_QImageInQT(QLabel* label, QImage img);
    Mat originImage;
    Mat nowImage;
    Mat tempImage;

    bool flagGlass;
    bool flagSketch;
    bool flagRelief;
    bool flagScuplture;
    bool flagFile;
    bool flagOil;
    bool flagMask;
    bool flagOld;
    bool flagFleet;
    bool flagCartoon;
    bool flagIllumination;
    bool flagDim;
    bool flagCasting;
    bool flagFrozen;
    bool flagComic;
    bool flagFeather;
    bool flagGrey;
    bool flagWhiteAndBlack;
    bool flagHomochromy;
    bool flagWatercolor;
    bool flagLinedraw;
    bool flagConvex;
    bool flagConcave;
    bool flagNeon;
    bool flagGhost;

    bool flagVignetting;
    bool flagTemperature;
    bool flagSaturability;
    bool flagLuminance;
    bool flagContrast;
    bool flagHue;
    bool flagGranular;
    bool flagSharpen;
    bool flagHighlight;
    bool flagShadow;

    bool flagReversal;
    bool flagLog;
    bool flagGamma;
    bool flagHistogramEqualization;

    bool flagAverageFilter;
    bool flagGaussianFilter;
    bool flagMedianFilter;
    bool flagMinFilter;
    bool flagMaxFilter;
    bool flagSobelFilter;
    bool flagRobertsFilter;
    bool flagPrewittFilter;
    bool flagLaplacianFilter;

    bool flagButterworthHighFilter;
    bool flagButterworthLowFilter;
    bool flagIdealHighFilter;
    bool flagIdealLowFilter;
    bool flagGaussHighFilter;
    bool flagGaussLowFilter;

    bool flagRotation;
    bool flagZoom;
    bool flagMirror;
    bool flagCropping;

    bool flagGaussNoise;
    bool flagRayleighNoise;
    bool flagGammaNoise;
    bool flagExponentialNoise;
    bool flagUniformNoise;
    bool flagSaltandPepperNoise;
    bool flagPeriodicNoise;

    bool flagArithmeticMean;
    bool flagGeometricMean;
    bool flagHarmonicMean;
    bool flagAntiharmonicMean;
    bool flagMidpoint;
    bool flagAlphaTrimmedMean;
    bool flagAdaptiveNoiseCancel;
    bool flagAdaptiveMedian;
    bool flagExpansion;
    bool flagErosion;
    bool flagOpenOperation;
    bool flagCloseOperation;
    bool flagTopHat;
    bool flagLowHat;
    bool flagHitMiss;
    bool flagBoundaryExtraction;
    bool flagAreaFill;
    bool flagConnectedComponentExtraction;
    bool flagConvexShell;
    bool flagCoarsening;
    bool flagRefinement;

   

    bool flagHistogramSegmentation;
    bool flagIterativeThresholdSegmentation;
    bool flagOtsu;
    bool flagKmeans;
    bool flagMeanShift;
    bool flagWaterShed;
    bool flagGrabCut;
    bool flagRegionalGrowth;

    bool flagShowSpectrogram;
    bool flagShowHistogram;

    bool isModify;
    bool isGetPoint;
    bool isGrabCut;
    bool isRegionalGrowth;

    Point pStart;
    Point pBegin;
    double xcrop1, ycrop1, xcrop2, ycrop2;
    double xgrab1, ygrab1, xgrab2, ygrab2;
    double scale;

    int typeRefinement;
    int typeCoarsening;
    int typeIterativeThresholdSegmentation;

    
    vector<Mat> mats_back;
    vector<Mat> mats_next;
    QIcon back1;
    QIcon back2;
    QIcon next1;
    QIcon next2;
private:
    Ui::ImageProcessClass* ui;
private slots:
    void menu_file_open_clicked();
    void menu_file_save_clicked();
    void menu_filter_glass_clicked();
    void menu_filter_sketch_clicked();
    void menu_filter_relief_clicked();
    void menu_filter_sculpture_clicked();
    void menu_filter_oil_clicked();
    void menu_filter_mask_clicked();
    void menu_filter_old_clicked();
    void menu_filter_cartoon_clicked();
    void menu_filter_illumination_clicked();
    void menu_filter_dim_clicked();
    void menu_filter_fleet_clicked();
    void menu_filter_casting_clicked();
    void menu_filter_frozen_clicked();
    void menu_filter_comic_clicked();
    void menu_filter_feather_clicked();
    void menu_filter_grey_clicked();
    void menu_filter_whiteAndBlack_clicked();
    void menu_filter_homochromy_clicked();
    void menu_filter_watercolor_clicked();
    void menu_filter_linedraw_clicked();
    void menu_filter_concave_clicked();
    void menu_filter_convex_clicked();
    void menu_filter_neon_clicked();
    void menu_filter_ghost_clicked();
    void menu_enhance_colorTemperature_clicked();
    void menu_enhance_vignetting_clicked();
    void menu_enhance_saturability_clicked();
    void menu_enhance_luminance_clicked();
    void menu_enhance_contrast_clicked();
    void menu_enhance_hue_clicked();
    void menu_enhance_granular_clicked();
    void menu_enhance_sharpen_clicked();
    void menu_enhance_highlight_clicked();
    void menu_enhance_shadow_clicked();
    
    void menu_greyTransform_reversal_clicked();
    void menu_greyTransform_log_clicked();
    void menu_greyTransform_gamma_clicked();
    void menu_greyTransform_histogramEqualization_clicked();

    void menu_spatialFilter_averageFilter_clicked();
    void menu_spatialFilter_gaussianFilter_clicked();
    void menu_spatialFilter_medianFilter_clicked();
    void menu_spatialFilter_maxFilter_clicked();
    void menu_spatialFilter_minFilter_clicked();
    void menu_spatialFilter_SobelFilter_clicked();
    void menu_spatialFilter_RobertsFilter_clicked();
    void menu_spatialFilter_PrewittFilter_clicked();
    void menu_spatialFilter_LaplacianFilter_clicked();

    void menu_frequency_ButterworthLowPass_clicked();
    void menu_frequency_ButterworthHighPass_clicked();
    void menu_frequency_GaussLowPass_clicked();
    void menu_frequency_GaussHighPass_clicked();
    void menu_frequency_idealLowPass_clicked();
    void menu_frequency_idealHighPass_clicked();

    void menu_spatialtransformation_rotation_clicked();
    void menu_spatialtransformation_zoom_clicked();
    void menu_spatialtransformation_mirror_clicked();
    void menu_spatialtransformation_cropping_clicked();
    void menu_addNoise_GaussNoise_clicked();
    void menu_addNoise_RayleighNoise_clicked();
    void menu_addNoise_GammaNoise_clicked();
    void menu_addNoise_ExponentialNoise_clicked();
    void menu_addNoise_UniformNoise_clicked();
    void menu_addNoise_SaltandPepperNoise_clicked();
    void menu_addNoise_PeriodicNoise_clicked();

    void menu_recovery_arithmeticMean_clicked();
    void menu_recovery_geometricMean_clicked();
    void menu_recovery_harmonicMean_clicked();
    void menu_recovery_antiharmonicMean_clicked();
    void menu_recovery_midpoint_clicked();
    void menu_recovery_alphaTrimmedMean_clicked();
    void menu_recovery_adaptiveNoiseCancel_clicked();
    void menu_recovery_adaptiveMedian_clicked();

    void menu_morphological_expansion_clicked();
    void menu_morphological_erosion_clicked();
    void menu_morphological_openOperation_clicked();
    void menu_morphological_closeOperation_clicked();
    void menu_morphological_topHat_clicked();
    void menu_morphological_lowHat_clicked();
    void menu_morphological_hitMiss_clicked();
    void menu_morphological_boundaryExtraction_clicked();
    void menu_morphological_areaFill_clicked();
    void menu_morphological_connectedComponentExtraction_clicked();
    void menu_morphological_convexShell_clicked();
    void menu_morphological_coarsening_clicked();
    void menu_morphological_refinement_clicked();

    

    void menu_imageSegmentation_histogramSegmentation_clicked();
    void menu_imageSegmentation_iterativeThresholdSegmentation_clicked();
    void menu_imageSegmentation_otsu_clicked();
    void menu_imageSegmentation_Kmeans_clicked();
    void menu_imageSegmentation_meanShift_clicked();
    void menu_imageSegmentation_watershed_clicked();
    void menu_imageSegmentation_grabCut_clicked();
    void menu_imageSegmentation_regionalGrowth_clicked();

    void menu_other_showHistogram_clicked();
    void menu_other_showSpectrogram_clicked();

    void slider_change();
    void slider2_change();
    void slider3_change();
    void button_yes_clicked();
    void button_no_clicked();
    void button_red_clicked();
    void button_green_clicked();
    void button_blue_clicked();
    void button_red2_clicked();
    void button_blue2_clicked();
    void button_green2_clicked();
    void LineEdit_first_clicked();
    void LineEdit_second_clicked();
    void LineEdit_third_clicked();

    void button_back_clicked();
    void button_next_clicked();
 protected:
        bool eventFilter(QObject* watched, QEvent* event) override;
};
