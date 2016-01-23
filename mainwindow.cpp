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

#include <banner.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    bool  enabled;
    QString text;
    QString color;
    int speed;
    int direction;

    QSettings settings("/mnt/config/carta.ini",QSettings::IniFormat);

    enabled = settings.value    ("banner/enabled",1).toBool();
    text = settings.value       ("banner/text","Ea3um carta ATV").toString();
    color = settings.value      ("banner/color","white").toString();
    speed = settings.value      ("banner/speed",2).toInt();
    direction=settings.value    ("banner/direction",0).toInt();

    ui->setupUi (this);
    m_pTimer=new QTimer (this);
    connect (m_pTimer,SIGNAL (timeout()),this,SLOT(on_timeout()));
    m_pTimer->start (5000);

/*    m_pRequestTimer = new QTimer(this);
    connect (m_pRequestTimer,SIGNAL (timeout()),this,SLOT(on_request_timer()));
    m_pRequestTimer->start(7000);
*/
    if (enabled==true)
    {
        ui->mybanner->setText (text);
        ui->mybanner->setSpeed(speed);
        ui->mybanner->setDirection(direction);
        ui->mybanner->show();

        QString style = QString ("QLabel { background:none; color : %1; }").arg(color);
        ui->mybanner->setStyleSheet(style);
    }
/*
    m_pThread = new mythread (this);
    connect (m_pThread,SIGNAL (messageRx(QByteArray)),this,SLOT(on_dataReady(QByteArray)));
    connect (m_pThread,SIGNAL (error()),this,SLOT(on_error()));
    connect (m_pThread,SIGNAL (sended()),this,SLOT(on_sended()));
    m_pThread->start();//(QThread::HighestPriority);
*/
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

void MainWindow::on_error()
{
    qDebug() << "Error";
    ui->mybanner->pause(false);
}

void MainWindow::on_request_timer()
{
    m_pThread->send_status();
}

void MainWindow::on_timeout()
{
    ui->label->hide();
}
