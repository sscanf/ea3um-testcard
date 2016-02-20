//JN01XG
//EA3UM

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QFont>
#include <QApplication>
#include <QSettings>
#include <QDebug>
#include <QByteArray>
#include <QDir>
#include <banner.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCameraInfo>
#include <QCameraImageCapture>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_imageIdx=0;

    bool    enabled;
    QString text;
    QString color;
    int     speed;
    int     direction;
    int     width;
    int     height;

    QSettings settings("/mnt/config/carta.ini",QSettings::IniFormat);

    enabled     = settings.value ("banner/enabled"  ,1).toBool();
    text        = settings.value ("banner/text"     ,"Ea3um carta ATV").toString();
    color       = settings.value ("banner/color"    ,"white").toString();
    speed       = settings.value ("banner/speed"    ,2).toInt();
    direction   = settings.value ("banner/direction",0).toInt();
    m_bDiapo    = settings.value ("slide/enabled"   ,false).toBool();
    m_timelapse = settings.value ("slide/timelapse" ,1).toBool();
    width       = settings.value ("video/width"     ,640).toInt();
    height      = settings.value ("video/height"    ,480).toInt();

    ui->setupUi (this);
    ui->lblvideo->hide();

    int screenWidth = this->width();
    int screenHeight = this->height();
    ui->lblvideo->setGeometry((screenWidth/2)-(width/2),(screenHeight/2)-(height/2),width,height);

    m_pTimer=new QTimer (this);
    connect (m_pTimer,SIGNAL (timeout()),this,SLOT(on_timeout()));
    m_pTimer->start (5000);

    if (enabled==true) {
        ui->mybanner->setText (text);
        ui->mybanner->setSpeed(speed);
        ui->mybanner->setDirection(direction);
        ui->mybanner->show();

        QString style = QString ("QLabel { background:none; color : %1; }").arg(color);
        ui->mybanner->setStyleSheet(style);
        ui->mybanner->show();
    }

    m_pCaptureThrd = new captureThread(this);
    connect (m_pCaptureThrd, SIGNAL (imageReady(QImage)), this, SLOT (on_drawFrames(QImage)));
    connect (m_pCaptureThrd, SIGNAL (cameraConnected()), this, SLOT (on_cameraConnected()));
    connect (m_pCaptureThrd, SIGNAL (cameraDisconnected()), this, SLOT (on_cameraDisconnected()));
    m_pCaptureThrd->start();

    m_pSlideTimer = new QTimer(this);
    connect (m_pSlideTimer,SIGNAL (timeout()),this,SLOT(on_slicerTimer()));

    QDir dir ("/mnt/imagen");
    dir.setNameFilters( QStringList ("*.jpg"));
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    m_imageList = dir.entryList();
    showSlide(m_bDiapo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showSlide(bool bShow)
{
    if ( bShow == true )
        m_pSlideTimer->start (m_timelapse*1000);
    else
        m_pSlideTimer->stop();

}

void MainWindow::on_sended()
{
    ui->mybanner->pause(true);
}

void MainWindow::on_slicerTimer()
{
    if (!m_imageList.isEmpty()){
        QString strFilename = m_imageList[m_imageIdx++];
        QString strStyle = "QWidget {\n	background-image: url(/mnt/imagen/"+strFilename+"); background-repeat: no-repeat; background-color: black};";
        this->setStyleSheet(strStyle);

        if (m_imageIdx>m_imageList.count()-1)
            m_imageIdx=0;
    }
}

void MainWindow::on_drawFrames(QImage video)
{

    ui->lblvideo->setPixmap(QPixmap::fromImage(video));
}

void MainWindow::on_cameraConnected()
{
    ui->lblvideo->show();
    QString strStyle = "QWidget {\n	background-image: ''; background-repeat: no-repeat; background-color: black};";
    this->setStyleSheet(strStyle);
    showSlide(false);
}

void MainWindow::on_cameraDisconnected()
{
    ui->lblvideo->hide();
    QString strStyle = "QWidget {\nbackground-image: url(/mnt/imagen/carta.jpg); background-repeat: no-repeat; background-color: black};";
    this->setStyleSheet(strStyle);
    showSlide(m_bDiapo);
}

void MainWindow::on_error()
{
    ui->mybanner->pause(false);
}

void MainWindow::on_timeout()
{
    ui->label->hide();
}
