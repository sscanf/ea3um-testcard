#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QString>
#include <QStringList>
#include "mythread.h"

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

    Ui::MainWindow      *ui;
    QTimer              *m_pTimer;
    QTimer              *m_pRequestTimer;
    QTimer              *m_pSliceTimer;
    QString              m_strBanner;
    mythread            *m_pThread;
    QStringList          m_imageList;
    int                  m_imageIdx;
private slots:

    void on_error();
    void on_timeout();
    void on_request_timer();
    void on_dataReady(QByteArray data);
    void on_sended();
    void on_slicerTimer();
};

#endif // MAINWINDOW_H
