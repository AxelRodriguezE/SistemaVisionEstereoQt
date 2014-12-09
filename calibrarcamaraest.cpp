#include "calibrarcamaraest.h"
#include "ui_calibrarcamaraest.h"

#include <opencv2/opencv.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv/cxmisc.h>
#include <opencv/cvaux.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"

#include <rectificacion.h>

using namespace std;
using namespace cv;

void leerparestereo(Mat &img1, Mat &img2, int i)
{
    stringstream ss1, ss2;

    ss1 << "imagenes/imgIzquierda" << i << ".png";
    ss2 << "imagenes/imgDerecha" << i << ".png";

    img1 = imread(ss1.str());
    img2 = imread(ss2.str());
}

calibrarcamaraest::calibrarcamaraest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calibrarcamaraest)
{
    ui->setupUi(this);
}

calibrarcamaraest::~calibrarcamaraest()
{
    delete ui;
}

void calibrarcamaraest::on_iniciarCalib_clicked()
{
    QString qimageCount=ui->cantCapt->text();
    int imageCount = qimageCount.toInt();

    cout << imageCount << endl;

    CvSize chessboardSize = cvSize(9,6);
    float squareSize = 2.5f;

    vector<vector<Point3f> > objPoints;
    vector<vector<Point2f> > imagePoints1, imagePoints2;
    vector<Point2f> corners1, corners2;
    vector<Point3f> obj;

    for (int y = 0; y < chessboardSize.height; y++) {
        for (int x = 0; x < chessboardSize.width; x++) {
            obj.push_back(Point3f(y * squareSize, x * squareSize, 0));
        }
    }

    Mat img1, img2;
    Mat gray1, gray2;

    int i = 0;
    bool found1 = false, found2 = false;

    while (i < imageCount)
    {
        ui->procedimientoCalib->appendPlainText(QString("Leyendo par de imagenes: ")+QString::number(i));
        leerparestereo(img1, img2, i);

        cvtColor(img1, gray1, CV_BGR2GRAY);
        cvtColor(img2, gray2, CV_BGR2GRAY);

        found1 = findChessboardCorners(img1, chessboardSize, corners1, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
        found2 = findChessboardCorners(img2, chessboardSize, corners2, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

        if (found1) {
            cornerSubPix(gray1, corners1, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
            drawChessboardCorners(gray1, chessboardSize, corners1, found1);
        }
        if (found2) {
            cornerSubPix(gray2, corners2, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
            drawChessboardCorners(gray2, chessboardSize, corners2, found2);
        }

        if (found1 && found2) {
            imagePoints1.push_back(corners1);
            imagePoints2.push_back(corners2);
            objPoints.push_back(obj);
            ui->procedimientoCalib->appendPlainText(QString("Guardando esquinas"));
            i++;
        }
    }
    ui->procedimientoCalib->appendPlainText(QString("Iniciando calibracion"));
    Mat CM1 = Mat(3, 3, CV_64F);
    Mat CM2 = Mat(3, 3, CV_64F);
    Mat D1 = Mat(1, 5, CV_64F);
    Mat D2 = Mat(1, 5, CV_64F);
    Mat R = Mat(3, 3, CV_64F);
    Mat T = Mat(3, 1, CV_64F);
    Mat E = Mat(3, 3, CV_64F);
    Mat F = Mat(3, 3, CV_64F);

    stereoCalibrate(objPoints, imagePoints1, imagePoints2, CM1, D1, CM2, D2, img1.size(), R, T, E, F,
            cvTermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 100, 1e-5), 0);
    ui->procedimientoCalib->appendPlainText(QString("Calibracion terminada"));

    ui->procedimientoCalib->appendPlainText(QString("Iniciando rectificacion"));
    Mat R1 = Mat(3, 3, CV_64F);
    Mat R2 = Mat(3, 3, CV_64F);
    Mat P1 = Mat(3, 4, CV_64F);
    Mat P2 = Mat(3, 4, CV_64F);
    Mat Q = Mat(4, 4, CV_64F);
    stereoRectify(CM1, D1, CM2, D2, img1.size(), R, T, R1, R2, P1, P2, Q);
    ui->procedimientoCalib->appendPlainText(QString("Rectificacion terminada"));

    ui->procedimientoCalib->appendPlainText(QString("Guardando archivo de rectificacion"));
    ui->procedimientoCalib->appendPlainText(QString("stereocalib.yml"));

    FileStorage fs("stereocalib.yml", FileStorage::WRITE);
    fs << "CM1" << CM1;
    fs << "CM2" << CM2;
    fs << "D1" << D1;
    fs << "D2" << D2;
    fs << "R" << R;
    fs << "T" << T;
    fs << "E" << E;
    fs << "F" << F;
    fs << "R1" << R1;
    fs << "R2" << R2;
    fs << "P1" << P1;
    fs << "P2" << P2;
    fs << "Q" << Q;
    fs.release();

    ui->procedimientoCalib->appendPlainText(QString("Iniciando aplicacion de distorsion"));
    Mat map1x = Mat(img1.size().height, img1.size().width, CV_32F);
    Mat map1y = Mat(img1.size().height, img1.size().width, CV_32F);
    Mat map2x = Mat(img2.size().height, img2.size().width, CV_32F);
    Mat map2y = Mat(img2.size().height, img2.size().width, CV_32F);

    initUndistortRectifyMap(CM1, D1, R1, P1, img1.size(), CV_32FC1, map1x, map1y);
    initUndistortRectifyMap(CM2, D2, R2, P2, img2.size(), CV_32FC1, map2x, map2y);
    ui->procedimientoCalib->appendPlainText(QString("Distorsion finalizada"));

    ui->procedimientoCalib->appendPlainText(QString("Calibracion y Rectificacion Finalizada!"));
}

void calibrarcamaraest::on_verrectificacion_clicked()
{
    rectificacion *rectificacionImg = new rectificacion(this);
    rectificacionImg->show();
}
