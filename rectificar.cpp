#include "rectificar.h"
#include "ui_rectificar.h"

rectificar::rectificar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rectificar)
{
    ui->setupUi(this);

    imagenIzquierda = imread("imagenIzquierda.png");
    imagenDerecha = imread("imagenDerecha.png");

    Mat CM1 = Mat(3, 3, CV_64F);
    Mat CM2 = Mat(3, 3, CV_64F);
    Mat D1 = Mat(1, 5, CV_64F);
    Mat D2 = Mat(1, 5, CV_64F);
    Mat R = Mat(3, 3, CV_64F);
    Mat T = Mat(3, 1, CV_64F);
    Mat E = Mat(3, 3, CV_64F);
    Mat F = Mat(3, 3, CV_64F);
    Mat R1 = Mat(3, 3, CV_64F);
    Mat R2 = Mat(3, 3, CV_64F);
    Mat P1 = Mat(3, 4, CV_64F);
    Mat P2 = Mat(3, 4, CV_64F);
    Mat Q = Mat(4, 4, CV_64F);

    FileStorage fs2("stereocalib.yml", FileStorage::READ);
    fs2["CM1"] >> CM1;
    fs2["CM2"] >> CM2;
    fs2["D1"] >> D1;
    fs2["D2"] >> D2;
    fs2["R"] >> R;
    fs2["T"] >> T;
    fs2["E"] >> E;
    fs2["F"] >> F;
    fs2["R1"] >> R1;
    fs2["R2"] >> R2;
    fs2["P1"] >> P1;
    fs2["P2"] >> P2;
    fs2["Q"] >> Q;
    fs2.release();

    Mat map1x = Mat(imagenIzquierda.size().height, imagenIzquierda.size().width, CV_32F);
    Mat map1y = Mat(imagenIzquierda.size().height, imagenIzquierda.size().width, CV_32F);
    Mat map2x = Mat(imagenDerecha.size().height, imagenDerecha.size().width, CV_32F);
    Mat map2y = Mat(imagenDerecha.size().height, imagenDerecha.size().width, CV_32F);

    initUndistortRectifyMap(CM1, D1, R1, P1, imagenIzquierda.size(), CV_32FC1, map1x, map1y);
    initUndistortRectifyMap(CM2, D2, R2, P2, imagenDerecha.size(), CV_32FC1, map2x, map2y);

    imagenIzquierdaRect = Mat(imagenIzquierda.size(), imagenIzquierda.type());
    imagenDerechaRect = Mat(imagenDerecha.size(), imagenDerecha.type());

    remap(imagenIzquierda, imagenIzquierdaRect, map1x, map1y, INTER_LINEAR, BORDER_CONSTANT, Scalar());
    remap(imagenDerecha, imagenDerechaRect, map2x, map2y, INTER_LINEAR, BORDER_CONSTANT, Scalar());

    imwrite("imagenIzquierdaRect.png", imagenIzquierdaRect);
    imwrite("imagenDerechaRect.png", imagenDerechaRect);

    cvtColor(imagenIzquierdaRect, imagenIzquierdaRectRGB, CV_BGR2RGB);
    cvtColor(imagenDerechaRect, imagenDerechaRectRGB, CV_BGR2RGB);

    QImage qimagenIzquierdaRect((uchar*)imagenIzquierdaRectRGB.data, imagenIzquierdaRectRGB.cols, imagenIzquierdaRectRGB.rows, imagenIzquierdaRectRGB.step, QImage::Format_RGB888);
    QImage qimagenDerechaRect((uchar*)imagenDerechaRectRGB.data, imagenDerechaRectRGB.cols, imagenDerechaRectRGB.rows, imagenDerechaRectRGB.step, QImage::Format_RGB888);

    ui->imagenIzqRect->setPixmap(QPixmap::fromImage(qimagenIzquierdaRect));
    ui->imagenDerRect->setPixmap(QPixmap::fromImage(qimagenDerechaRect));
}

rectificar::~rectificar()
{
    delete ui;
}
