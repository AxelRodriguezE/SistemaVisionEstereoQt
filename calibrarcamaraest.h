#ifndef CALIBRARCAMARAEST_H
#define CALIBRARCAMARAEST_H

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
class calibrarcamaraest;
}

class calibrarcamaraest : public QDialog
{
    Q_OBJECT

public:
    explicit calibrarcamaraest(QWidget *parent = 0);
    ~calibrarcamaraest();

private slots:
    void on_iniciarCalib_clicked();

    void on_verrectificacion_clicked();

private:
    Ui::calibrarcamaraest *ui;


};

#endif // CALIBRARCAMARAEST_H
