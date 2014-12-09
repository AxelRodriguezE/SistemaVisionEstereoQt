#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QMessageBox>
#include <QString>
#include <capturarealizada.h>
#include <rectificar.h>
#include <rectificacion.h>
#include <mapadisparidad.h>
#include <distanciasnavegacion.h>
#include <calibrarcamaraest.h>

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    numSnapshotLeft = 0;
    numSnapshotRight = 0;
    snapshotFilenameLeft = "0";
    snapshotFilenameRight = "0";
    cantCapturasTab = 0;

    capturaIzquierda.open(1);
    capturaDerecha.open(0);

    if(capturaIzquierda.isOpened()==false || capturaDerecha.isOpened()==false){
        //poner aqui una ventana emergente diciendo que no estan conectadas adecuadamente las camaras...
    }

    tmrTimer = new QTimer(this);
    connect(tmrTimer, SIGNAL(timeout()), this, SLOT(verCamaras()));
    tmrTimer->start(20);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//int existeArchivo(char* nombreArchivo){
//    FILE *archivo = fopen(nombreArchivo,"r");
//    if(archivo) {
//        return 1;
//        fclose(archivo);
//    }
//    else {
//        return 0;
//    }
//}

void MainWindow::verCamaras(){
    capturaIzquierda.read(cuadrosIzquierdos);
    capturaDerecha.read(cuadrosDerechos);

    if(cuadrosIzquierdos.empty()==true || cuadrosDerechos.empty()==true){
        return;
    }

    cvtColor(cuadrosIzquierdos, cuadrosIzquierdosRGB, CV_BGR2RGB);
    cvtColor(cuadrosDerechos, cuadrosDerechosRGB, CV_BGR2RGB);

    QImage qcapturaIzquierda((uchar*)cuadrosIzquierdosRGB.data, cuadrosIzquierdosRGB.cols, cuadrosIzquierdosRGB.rows, cuadrosIzquierdosRGB.step, QImage::Format_RGB888);
    QImage qcapturaDerecha((uchar*)cuadrosDerechosRGB.data, cuadrosDerechosRGB.cols, cuadrosDerechosRGB.rows, cuadrosDerechosRGB.step, QImage::Format_RGB888);

    ui->camaraIzquierda->setPixmap(QPixmap::fromImage(qcapturaIzquierda));
    ui->camaraDerecha->setPixmap(QPixmap::fromImage(qcapturaDerecha));
}

void MainWindow::on_capturaEscena_clicked()
{
    imwrite("imagenIzquierda.png", cuadrosIzquierdos);
    imwrite("imagenDerecha.png", cuadrosDerechos);

    capturaRealizada *capturas = new capturaRealizada();
    capturas->show();
}

void MainWindow::on_rectificarImagenes_clicked()
{
    rectificar *rectificarimg = new rectificar();
    rectificarimg->show();
}

void MainWindow::on_mapaDisparidad_clicked()
{
    mapadisparidad *disparidad = new mapadisparidad();
    disparidad->show();
}

void MainWindow::on_distanciaObjetos_clicked()
{
    system("./LatentSVM");
}

void MainWindow::on_distanciaNavegacion_clicked()
{
    distanciasnavegacion *distNav = new distanciasnavegacion();
    distNav->show();
}

void MainWindow::on_capturatablero_clicked()
{
}

void MainWindow::on_capturaTablero_clicked()
{
    imwrite("imagenes/imgIzquierda" + snapshotFilenameLeft + ".png", cuadrosIzquierdos);
    numSnapshotLeft++;
    snapshotFilenameLeft = static_cast<ostringstream*>(&(ostringstream() << numSnapshotLeft))->str();

    imwrite("imagenes/imgDerecha" + snapshotFilenameRight + ".png", cuadrosDerechos);
    numSnapshotRight++;
    snapshotFilenameRight = static_cast<ostringstream*>(&(ostringstream() << numSnapshotRight))->str();

    cantCapturasTab++;

    ui->cantidadCapTab->setNum(cantCapturasTab);

    QMessageBox messageBox;
    messageBox.information(0,"Captura de Tablero","La captura se ha realizado con exito!");
    messageBox.setFixedSize(500,200);
}

void MainWindow::on_calibrarCAM_clicked()
{
    calibrarcamaraest *calibcam = new calibrarcamaraest();
    calibcam->show();
}

void MainWindow::on_abrirDirectorio_clicked()
{
    //system("/home/axel/build-ProyectoVisionEstereo-Desktop-Debug");
}
