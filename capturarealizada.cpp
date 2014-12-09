#include "capturarealizada.h"
#include "ui_capturarealizada.h"

capturaRealizada::capturaRealizada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::capturaRealizada)
{
    ui->setupUi(this);

    imagenIzquierda = imread("imagenIzquierda.png");
    imagenDerecha = imread("imagenDerecha.png");

    cvtColor(imagenIzquierda, imagenIzquierdaRGB, CV_BGR2RGB);
    cvtColor(imagenDerecha, imagenDerechaRGB, CV_BGR2RGB);

    QImage qimagenIzquierda((uchar*)imagenIzquierdaRGB.data, imagenIzquierdaRGB.cols, imagenIzquierdaRGB.rows, imagenIzquierdaRGB.step, QImage::Format_RGB888);
    QImage qimagenDerecha((uchar*)imagenDerechaRGB.data, imagenDerechaRGB.cols, imagenDerechaRGB.rows, imagenDerechaRGB.step, QImage::Format_RGB888);

    ui->imagenIzquierda->setPixmap(QPixmap::fromImage(qimagenIzquierda));
    ui->imagenDerecha->setPixmap(QPixmap::fromImage(qimagenDerecha));
}

capturaRealizada::~capturaRealizada()
{
    delete ui;
}
