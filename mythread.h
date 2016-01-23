#ifndef THREAD_H
#define THREAD_H

#include <QByteArray>
#include <QThread>
#include <QTimer>
#include "gpio.h"

//#define DATA_MODEM_TO_CPU
#define DATA_CPU_TO_MODEM

#ifdef DATA_CPU_TO_MODEM
    #define BIT_CLOCK   2
    #define BIT_DATA    3
    #define TOTAL_BYTES 5
#endif

#ifdef DATA_MODEM_TO_CPU
    #define BIT_CLOCK   7
    #define BIT_DATA    8
    #define TOTAL_BYTES 2
#endif

#define BIT_PTT         24
#define BIT_AUDIO       23
#define BIT_CLOCK_TX    17
#define BIT_DATA_TX     22

class mythread : public QThread
{
    Q_OBJECT
public:
    explicit mythread (QObject *parent = 0);
    void run();
    void send_status();

private:
    void wait_clock ();

    quint16 get_data();
    void shift_left (quint16 *word, int len);
    void shift_right(quint16 *word, int len);
    void wait_start ();
    void wait_stop  ();
    void send_byte (quint8 byte);
    void send_clock();
    void send_bit (bool bit);


private:
    QGpio    m_gpio;
    QTimer  *m_pTimer;
    quint16  m_word;
signals:
    void messageRx (QByteArray data);
    void dataRx();
    void error();
    void sended();

private slots:
    void on_timeout();

};

#endif // THREAD_H
