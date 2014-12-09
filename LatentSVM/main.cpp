#include <QCoreApplication>
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

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <sstream>
#include <stdio.h>


#if defined(WIN32) || defined(_WIN32)
#include <io.h>
#else
#include <dirent.h>
#endif

#ifdef HAVE_CVCONFIG_H
#include <cvconfig.h>
#endif

#ifdef HAVE_TBB
#include "tbb/task_scheduler_init.h"
#endif

using namespace std;
using namespace cv;

static void leermodelos(const string& directoryName, vector<string>& filenames, bool addDirectoryName=true)
{
    filenames.clear();

#if defined(WIN32) | defined(_WIN32)
    struct _finddata_t s_file;
    string str = directoryName + "\\*.*";

    intptr_t h_file = _findfirst( str.c_str(), &s_file );
    if( h_file != static_cast<intptr_t>(-1.0) )
    {
        do
        {
            if( addDirectoryName )
                filenames.push_back(directoryName + "\\" + s_file.name);
            else
                filenames.push_back((string)s_file.name);
        }
        while( _findnext( h_file, &s_file ) == 0 );
    }
    _findclose( h_file );
#else
    DIR* dir = opendir( directoryName.c_str() );
    if( dir != NULL )
    {
        struct dirent* dent;
        while( (dent = readdir(dir)) != NULL )
        {
            if( addDirectoryName )
                filenames.push_back( directoryName + "/" + string(dent->d_name) );
            else
                filenames.push_back( string(dent->d_name) );
        }

        closedir( dir );
    }
#endif

    sort( filenames.begin(), filenames.end() );
}

static void detectarobjetos(Mat& image, LatentSvmDetector& detector, float overlapThreshold, int numThreads, Mat& imageMapaDisp)
{
    int cont = 1;
    Mat mapaDisparidad = imread("mapaDisparidad.png", CV_8UC1);
    vector<LatentSvmDetector::ObjectDetection> detections;
    detector.detect(image, detections, overlapThreshold, numThreads);

    FileStorage distancias("distancias.yml", FileStorage::WRITE);

    for( size_t i = 0; i < detections.size(); i++ )
    {
        const LatentSvmDetector::ObjectDetection& od = detections[i];
        rectangle(image, od.rect, CV_RGB(255, 0, 0), 2);
        rectangle(imageMapaDisp, od.rect, CV_RGB(255, 0, 0), 2);
        int height = od.rect.height;
        int width = od.rect.width;
        int x = od.rect.y;
        int y = od.rect.x;
        int dispMax = -1;
        int disp;
        for(int h = x; h<=height+x; h++)
        {
            for(int w = y; w<=width+y; w++)
            {
                disp = mapaDisparidad.at<uchar>(h,w);
                if(disp>dispMax)
                    dispMax = disp;
            }
        }
        int Distancia = ((1100*85)/dispMax)/10;
        string DistanciaObj = static_cast<ostringstream*>(&(ostringstream() << Distancia << " cm."))->str();
        putText(image, DistanciaObj, Point(od.rect.x+4, od.rect.y+13), FONT_HERSHEY_SIMPLEX, 0.55, CV_RGB(255, 255, 255), 2);
        putText(imageMapaDisp, DistanciaObj, Point(od.rect.x+4, od.rect.y+13), FONT_HERSHEY_SIMPLEX, 0.55, CV_RGB(255, 255, 255), 2);

        //Guardar distancias en archivo
        Point coordenada;
        coordenada.x = x;
        coordenada.y = y;
        Size dimension;
        dimension.height = height;
        dimension.width = width;
        distancias << "Objeto" << cont;
        distancias << "Distancia" << Distancia;
        distancias << "Coordenada" << coordenada;
        distancias << "Dimension" << dimension;

        cont++;
    }
    distancias.release();
}

int main()
{
    vector<string> models_filenames;
    leermodelos( "modelos", models_filenames);
    LatentSvmDetector detector(models_filenames);
    if( detector.empty() )
    {
        cout << "No se pueden leer los modelos" << endl;
        exit(-1);
    }
    Mat image = imread("imagenIzquierda.png");
    Mat imageMapaDisp = imread("mapaDisparidad.png");
    float overlapThreshold = 0.009f;

    detectarobjetos(image, detector, overlapThreshold, -1, imageMapaDisp);

    namedWindow("Deteccion de Objetos", 1);
    namedWindow("Deteccion de Objetos Mapa Disparidad", 1);
    imshow("Deteccion de Objetos", image);
    imshow("Deteccion de Objetos Mapa Disparidad", imageMapaDisp);

    waitKey(0);
    return 0;
}
