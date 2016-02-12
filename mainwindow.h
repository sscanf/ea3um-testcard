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
    ~MainWindow();    

private:

private:

    Ui::MainWindow      *ui;
    QTimer              *m_pTimer;
    QTimer              *m_pRequestTimer;
    QTimer              *m_pSliceTimer;
    QString              m_strBanner;
    QStringList          m_imageList;
    int                  m_imageIdx;
    captureThread       *m_pCaptureThrd;

private slots:

    void on_error();
    void on_timeout();
    void on_dataReady(QByteArray data);
    void on_sended();
    void on_slicerTimer();
    void on_drawFrames(QImage video);
    void on_cameraConnected();
    void on_cameraDisconnected();
};

#endif // MAINWINDOW_H
