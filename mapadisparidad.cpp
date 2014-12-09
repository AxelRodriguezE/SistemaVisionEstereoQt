#include "mapadisparidad.h"
#include "ui_mapadisparidad.h"

mapadisparidad::mapadisparidad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mapadisparidad)
{
    ui->setupUi(this);

    imagenIzquierda = imread("imagenIzquierdaRect.png");
    imagenDerecha = imread("imagenDerechaRect.png");

    generarMapaDisp();
}

mapadisparidad::~mapadisparidad()
{
    delete ui;
}

void mapadisparidad::generarMapaDisp(){

    StereoSGBM stereoSGBM;

    stereoSGBM.SADWindowSize = 2;
    stereoSGBM.numberOfDisparities = 192;
    stereoSGBM.preFilterCap = 2;
    stereoSGBM.minDisparity = -50;
    stereoSGBM.uniquenessRatio = 2;
    stereoSGBM.speckleWindowSize = 300;
    stereoSGBM.speckleRange = 2;
    stereoSGBM.disp12MaxDiff = 20;
    stereoSGBM.fullDP = false;
    stereoSGBM.P1 = 1200;
    stereoSGBM.P2 = 3000;

    Mat imgDisparity16S = Mat(imagenIzquierda.rows, imagenIzquierda.cols, CV_16S);
    mapaDisparidad = Mat(imagenIzquierda.rows, imagenIzquierda.cols, CV_8UC1);

    stereoSGBM(imagenIzquierda, imagenDerecha, imgDisparity16S);

    double minVal; double maxVal;

    minMaxLoc(imgDisparity16S, &minVal, &maxVal);

    imgDisparity16S.convertTo(mapaDisparidad, CV_8UC1, 255/(maxVal - minVal));

    imwrite("mapaDisparidad.png", mapaDisparidad);

    cvtColor(mapaDisparidad, mapaDisparidadRGB, CV_GRAY2RGB);

    QImage qmapaDisparidad((uchar*)mapaDisparidadRGB.data, mapaDisparidadRGB.cols, mapaDisparidadRGB.rows, mapaDisparidadRGB.step, QImage::Format_RGB888);

    ui->mapadeDisp->setPixmap(QPixmap::fromImage(qmapaDisparidad));
}
