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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_imageIdx=0;

    bool    enabled;
    bool    diapo;
    QString text;
    QString color;
    int     speed;
    int     direction;

    QSettings settings("/mnt/config/carta.ini",QSettings::IniFormat);

    enabled     = settings.value ("banner/enabled"  ,1).toBool();
    text        = settings.value ("banner/text"     ,"Ea3um carta ATV").toString();
    color       = settings.value ("banner/color"    ,"white").toString();
    speed       = settings.value ("banner/speed"    ,2).toInt();
    direction   = settings.value ("banner/direction",0).toInt();
    diapo       = settings.value ("carta/diapo"     ,0).toBool();

    ui->setupUi (this);

    ui->lblvideo->hide();
    m_pTimer=new QTimer (this);
    connect (m_pTimer,SIGNAL (timeout()),this,SLOT(on_timeout()));
    m_pTimer->start (5000);

    if (enabled==true){
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

    if (diapo == true){
        QDir dir ("/mnt/imagen");
        dir.setNameFilters( QStringList ("*.jpg"));
        dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
        m_imageList = dir.entryList();

        m_pSliceTimer = new QTimer(this);
        connect (m_pTimer,SIGNAL (timeout()),this,SLOT(on_slicerTimer()));
        m_pSliceTimer->start (1000);
    }
}

void MainWindow::on_dataReady(QByteArray data)
{
    ui->mybanner->pause(false);
    qDebug() << "Datos recibidos : " << data.toHex();
}

MainWindow::~MainWindow()
{
    delete ui;
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
    QString strStyle = "QWidget {\n	background-image: ''; background-repeat: no-repeat; background-color: black};";
    ui->lblvideo->show();
    this->setStyleSheet(strStyle);
}

void MainWindow::on_cameraDisconnected()
{
    ui->lblvideo->hide();
    QString strStyle = "QWidget {\nbackground-image: url(/mnt/imagen/carta.jpg); background-repeat: no-repeat; background-color: black};";
    this->setStyleSheet(strStyle);

}

void MainWindow::on_error()
{
    qDebug() << "Error";
    ui->mybanner->pause(false);
}

void MainWindow::on_timeout()
{
    ui->label->hide();
}
