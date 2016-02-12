#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H

#include <QImage>
#include <QThread>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class captureThread : public QThread
{
    Q_OBJECT
public:
    explicit        captureThread(QObject *parent = 0);
    void            run();

private:
    cv::VideoCapture                 capWebcam;
    cv::Mat                          matOriginal;

public:
    QImage                           m_qimOriginal;

signals:
    void imageReady(QImage);
    void cameraConnected();
    void cameraDisconnected();
public slots:

};

#endif // CAPTURETHREAD_H
