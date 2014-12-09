#include "distanciasnavegacion.h"
#include "ui_distanciasnavegacion.h"

distanciasnavegacion::distanciasnavegacion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::distanciasnavegacion)
{
    ui->setupUi(this);

    escenaIzquierda = imread( "imagenIzquierda.png", CV_LOAD_IMAGE_GRAYSCALE );
    imagenMapaDisp = imread("mapaDisparidad.png");
    mapaDisparidad = imread("mapaDisparidad.png", CV_8UC1);

    minHessian = 500;
    SurfFeatureDetector detectorSURF(minHessian);

    detectorSURF.detect(escenaIzquierda, kp_object);

    int largo1 = escenaIzquierda.size().width/3;
    int largo2 = escenaIzquierda.size().width - largo1;
    int largo3 = escenaIzquierda.size().width;
    int dispMaxC1 = -1;
    int dispMaxC2 = -1;
    int dispMaxC3 = -1;
    int cantidadKeypoint = kp_object.size();

    for(int i = 0; i<=cantidadKeypoint; i++)
    {
        int x = kp_object[i].pt.x;
        int y = kp_object[i].pt.y;
        //cout << "(" << x << "," << y << ")" << endl;

        int dispKeypoint = mapaDisparidad.at<uchar>(y,x);
        //cout << dispKeypoint << endl;

        if(kp_object[i].pt.x <= largo1)
            if(dispKeypoint > dispMaxC1)
                dispMaxC1 = dispKeypoint;

        if(kp_object[i].pt.x > largo1 && kp_object[i].pt.x <= largo2)
            if(dispKeypoint > dispMaxC2)
                dispMaxC2 = dispKeypoint;

        if(kp_object[i].pt.x > largo2 && kp_object[i].pt.x <= largo3)
            if(dispKeypoint > dispMaxC3)
                dispMaxC3 = dispKeypoint;
    }

    int DistanciaC1 = ((1100*85)/dispMaxC1)/10;
    int DistanciaC2 = ((1100*85)/dispMaxC2)/10;
    int DistanciaC3 = ((1100*85)/dispMaxC3)/10;
    string DistanciaCamino1 = static_cast<ostringstream*>(&(ostringstream() << DistanciaC1 << " cm."))->str();
    string DistanciaCamino2 = static_cast<ostringstream*>(&(ostringstream() << DistanciaC2 << " cm."))->str();
    string DistanciaCamino3 = static_cast<ostringstream*>(&(ostringstream() << DistanciaC3 << " cm."))->str();
    putText(imagenMapaDisp, DistanciaCamino1, Point(50,escenaIzquierda.size().height/2), FONT_HERSHEY_SIMPLEX, 0.7, CV_RGB(255, 255, 255), 2);
    line(imagenMapaDisp, Point(largo1,0), Point(largo1,escenaIzquierda.size().height), CV_RGB(255, 0, 0), 2);

    putText(imagenMapaDisp, DistanciaCamino2, Point(largo1+50,escenaIzquierda.size().height/2), FONT_HERSHEY_SIMPLEX, 0.7, CV_RGB(255, 255, 255), 2);
    line(imagenMapaDisp, Point(largo2,0), Point(largo2,escenaIzquierda.size().height), CV_RGB(255, 0, 0), 2);

    putText(imagenMapaDisp, DistanciaCamino3, Point(largo2+50,escenaIzquierda.size().height/2), FONT_HERSHEY_SIMPLEX, 0.7, CV_RGB(255, 255, 255), 2);

    drawKeypoints(escenaIzquierda, kp_object, escenaIzquierda, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

    cvtColor(escenaIzquierda, escenaIzquierdaRGB, CV_BGR2RGB);
    cvtColor(imagenMapaDisp, imagenMapaDispRGB, CV_BGR2RGB);

    QImage qescenaIzquierda((uchar*)escenaIzquierdaRGB.data, escenaIzquierdaRGB.cols, escenaIzquierdaRGB.rows, escenaIzquierdaRGB.step, QImage::Format_RGB888);
    QImage qimagenMapaDisp((uchar*)imagenMapaDispRGB.data, imagenMapaDispRGB.cols, imagenMapaDispRGB.rows, imagenMapaDispRGB.step, QImage::Format_RGB888);

    ui->distanciaNavMapaDisp->setPixmap(QPixmap::fromImage(qescenaIzquierda));
    ui->keypointsEscena->setPixmap(QPixmap::fromImage(qimagenMapaDisp));
    ui->camino1->setNum(DistanciaC1);
    ui->camino2->setNum(DistanciaC2);
    ui->camino3->setNum(DistanciaC3);
    ui->cantkeypoints->setNum(cantidadKeypoint);
}

distanciasnavegacion::~distanciasnavegacion()
{
    delete ui;
}
