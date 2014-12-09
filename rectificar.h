#ifndef RECTIFICAR_H
#define RECTIFICAR_H

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
class rectificar;
}

class rectificar : public QDialog
{
    Q_OBJECT

public:
    explicit rectificar(QWidget *parent = 0);
    ~rectificar();

private:
    Ui::rectificar *ui;

    Mat imagenIzquierda;
    Mat imagenDerecha;
    Mat imagenIzquierdaRect;
    Mat imagenDerechaRect;
    Mat imagenIzquierdaRectRGB;
    Mat imagenDerechaRectRGB;

    QImage qimagenIzquierdaRect;
    QImage qimagenDerechaRect;
};

#endif // RECTIFICAR_H
