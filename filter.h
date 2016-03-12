#ifndef FILTER_H
#define FILTER_H

#include <QAbstractVideoFilter>
#include <QVideoFilterRunnable>
#include <QDebug>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class MyFilter : public QAbstractVideoFilter {
    Q_OBJECT
public:
    QVideoFilterRunnable *createFilterRunnable();

signals:
    void finished(QObject *result);
};

class MyFilterRunnable : public QVideoFilterRunnable {
public:
    MyFilterRunnable();
    QVideoFrame run         (QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags);
    void        toVideoFrame(QVideoFrame *input, cv::Mat &mat);

private:
    int m_scMin1;
    int m_scMin2;
    int m_scMin3;
    int m_scMax1;
    int m_scMax2;
    int m_scMax3;
    cv::Mat matProcessed;
};

#endif // FILTER_H
