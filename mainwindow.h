#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QString>
#include <QStringList>
#include "capturethread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void showSlide(bool bShow);
    ~MainWindow();

private:

private:

    Ui::MainWindow      *ui;
    QTimer              *m_pTimer;
    QTimer              *m_pRequestTimer;
    QTimer              *m_pSlideTimer;
    QString              m_strBanner;
    QStringList          m_imageList;
    int                  m_imageIdx;
    captureThread       *m_pCaptureThrd;
    bool                 m_bDiapo;
    int                  m_timelapse;

private slots:
    void on_error();
    void on_timeout();
    void on_sended();
    void on_slicerTimer();
    void on_drawFrames(QImage video);
    void on_cameraConnected();
    void on_cameraDisconnected();
};

#endif // MAINWINDOW_H
