#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

using namespace std;
using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    VideoCapture capturaIzquierda; // open the Left camera
    VideoCapture capturaDerecha; // open the Right camera

    Mat cuadrosIzquierdos;
    Mat cuadrosDerechos;
    Mat cuadrosIzquierdosRGB;
    Mat cuadrosDerechosRGB;

    QImage qcapturaIzquierda;
    QImage qcapturaDerecha;

    QTimer* tmrTimer;

    QString qimagenIzq;

    int numSnapshotLeft;
    int numSnapshotRight;
    string snapshotFilenameLeft;
    string snapshotFilenameRight;

    int cantCapturasTab;

public slots:
    void verCamaras();
    //void capturarImagenes();

private slots:
    void on_capturaEscena_clicked();



    void on_rectificarImagenes_clicked();
    void on_mapaDisparidad_clicked();
    void on_distanciaObjetos_clicked();
    void on_distanciaNavegacion_clicked();
    void on_capturarEscena_clicked();
    void on_pushButton_2_clicked();
    void on_calibrarcamara_clicked();
    void on_capturatablero_clicked();
    void on_capturaTablero_clicked();
    void on_calibrarCAM_clicked();
    void on_abrirDirectorio_clicked();
};

#endif // MAINWINDOW_H
