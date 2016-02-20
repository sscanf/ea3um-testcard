#include <QDebug>
#include "capturethread.h"
#include <QCameraInfo>
#include <QCameraImageCapture>
#include <QDir>

captureThread::captureThread(QObject *parent) :
    QThread(parent)
{
}

void captureThread::run()
{
    while(1){

        while (QCameraInfo::availableCameras().count() == 0)
            msleep(1000);

        capWebcam.open(-1);

        emit cameraConnected();

        capWebcam.set(CV_CAP_PROP_FRAME_WIDTH,720);
        capWebcam.set(CV_CAP_PROP_FRAME_HEIGHT,513);

        do
        {
            try{
                capWebcam.read (matOriginal);
                cv::cvtColor (matOriginal, matOriginal, CV_BGR2RGB);
                m_qimOriginal  = QImage ((uchar *)matOriginal.data, matOriginal.cols, matOriginal.rows, matOriginal.step, QImage::Format_RGB888);
                emit imageReady(m_qimOriginal);
                msleep(50);
            }catch  ( cv::Exception &e){
                break;
            }
        }while (QCameraInfo::availableCameras().count());

        matOriginal.release();
        capWebcam.release();
        emit cameraDisconnected();
    }
}
