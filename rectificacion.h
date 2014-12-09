#ifndef RECTIFICACION_H
#define RECTIFICACION_H

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
class rectificacion;
}

class rectificacion : public QDialog
{
    Q_OBJECT

public:
    explicit rectificacion(QWidget *parent = 0);
    ~rectificacion();

private:
    Ui::rectificacion *ui;

    Mat imagenIzquierda;
    Mat imagenDerecha;
    Mat imagenIzquierdaRect;
    Mat imagenDerechaRect;
    Mat imagenIzquierdaRectRGB;
    Mat imagenDerechaRectRGB;

    QImage qimagenIzquierdaRect;
    QImage qimagenDerechaRect;

};

#endif // RECTIFICACION_H
