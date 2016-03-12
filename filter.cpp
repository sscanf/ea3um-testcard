#include <QThread>
#include "filter.h"

MyFilterRunnable::MyFilterRunnable()
{
    m_scMin1 = 0;
    m_scMin2 = 0;
    m_scMin3 = 175;

    m_scMax1 = 256;
    m_scMax2 = 256;
    m_scMax3 = 256;
}

QVideoFrame MyFilterRunnable::run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, QVideoFilterRunnable::RunFlags flags)
{
    Q_UNUSED (surfaceFormat)
    Q_UNUSED (flags)

    std::vector<cv::Vec3f> vecCircles;

    if (!input->isValid())
        return *input;

    if (input->map (QAbstractVideoBuffer::ReadWrite)) {
        cv::Mat matOriginal(input->height(),input->width(), CV_8UC3, input->bits(),input->bytesPerLine());
        //cv::inRange(matOriginal, cv::Scalar(m_scMin1,m_scMin2, m_scMin3), cv::Scalar(m_scMax1,m_scMax2,m_scMax3), matProcessed);
        cv::GaussianBlur(matOriginal, matOriginal, cv::Size(5,5),10);
        input->unmap();
    }
    return *input;
}

void MyFilterRunnable::toVideoFrame(QVideoFrame *input, cv::Mat &mat)
{
    int aCols = 4*mat.cols;
    int aRows = mat.rows;
    uchar* inputBits = input->bits();

    for (int i=0; i<aRows; i++)
    {
        uchar* p = mat.ptr<uchar>(i);
        for (int j=0; j<aCols; j++)
        {
            int index = i*aCols + j;
            inputBits[index] = p[j];
        }
    }
}

QVideoFilterRunnable *MyFilter::createFilterRunnable()
{
    return new MyFilterRunnable;
}

