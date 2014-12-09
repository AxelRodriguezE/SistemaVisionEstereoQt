#ifndef DISTANCIASNAVEGACION_H
#define DISTANCIASNAVEGACION_H

#include <QDialog>
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
class distanciasnavegacion;
}

class distanciasnavegacion : public QDialog
{
    Q_OBJECT

public:
    explicit distanciasnavegacion(QWidget *parent = 0);
    ~distanciasnavegacion();

private:
    Ui::distanciasnavegacion *ui;

    int minHessian;

    vector<KeyPoint> kp_object;

    Mat escenaIzquierda;
    Mat mapaDisparidad;
    Mat imagenMapaDisp;

    Mat imagenMapaDispRGB;
    Mat escenaIzquierdaRGB;

    QImage qimagenMapaDisp;
    QImage qescenaIzquierda;
};

#endif // DISTANCIASNAVEGACION_H
