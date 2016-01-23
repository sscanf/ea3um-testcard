#include <QDebug>
#include <QByteArray>
#include "mythread.h"º

mythread ::mythread(QObject *parent) :
    QThread(parent)
{
    m_pTimer = new QTimer(this);
    connect (m_pTimer,SIGNAL (timeout()),this,SLOT (on_timeout()));
}

void mythread::send_clock()
{

    while (m_gpio.bitValue(BIT_CLOCK)==1);
    m_gpio.bitClear (BIT_CLOCK_TX);

    while (m_gpio.bitValue(BIT_CLOCK)==0);
    m_gpio.bitSet (BIT_CLOCK_TX);
}

void mythread::wait_clock()
{
    while (m_gpio.bitValue(BIT_CLOCK)==1);
    while (m_gpio.bitValue(BIT_CLOCK)==0);
}

void mythread::shift_left(quint16 *word, int len)
{
    for (int n=0;n<len;n++)
    {
        wait_clock();
        *word= *word <<1;
        *word|=m_gpio.bitValue(BIT_DATA);
    }
}

void mythread::shift_right(quint16 *word, int len)
{
    for (int n=0;n<len;n++)
    {
        wait_clock();
        *word= (*word >>1);
        *word|=(m_gpio.bitValue(BIT_DATA)<<7);
    }
}

void mythread::wait_start ()
{
    do
    {
        wait_clock();
    }while (m_gpio.bitValue(BIT_DATA));
}

void mythread::wait_stop ()
{
    do
    {
        wait_clock();
    }while (!m_gpio.bitValue(BIT_DATA));
}

quint16 mythread::get_data()
{
    quint16 data=0;

    wait_start();
    shift_right(&data,4);

#ifdef DATA_CPU_TO_MODEM
    wait_stop();
    wait_stop();
#endif

    return data;
}

void mythread::send_bit (bool bit)
{
    if (bit)
        m_gpio.bitSet (BIT_DATA_TX);
    else
        m_gpio.bitClear (BIT_DATA_TX);
    send_clock();
}

void mythread::send_byte (quint8 byte)
{
    send_bit(0);    //Start bit

    quint8 mask=0x01;
    for (int n=0;n<4;n++)
    {
        send_bit(mask&byte);
        mask = mask << 1;
    }

    send_bit(1);    //stop bit
}

void mythread::send_status()
{
    m_gpio.bitSet(BIT_PTT);
    m_gpio.bitClear(BIT_AUDIO);
    send_clock();
    send_clock();
    send_clock();
    send_clock();

    send_clock();
    send_clock();
    send_clock();
    send_clock();

    send_byte(0x01);
    send_byte(0x00);
    send_byte(0x00);
    send_byte(0x00);
    emit sended();
    m_pTimer->start(2000);
}

void mythread::on_timeout()
{
    emit error();
    m_word=0;
}

void mythread ::run()
{
    m_word=0xffff;
    quint8  data=0;
    QByteArray arr;

    m_gpio.setOutput (BIT_AUDIO);
    m_gpio.setOutput (BIT_CLOCK_TX);
    m_gpio.setOutput (BIT_DATA_TX);
    m_gpio.setOutput (BIT_PTT);

    m_gpio.setInput (BIT_CLOCK);
    m_gpio.setInput (BIT_DATA);

    m_gpio.bitSet (BIT_AUDIO);
    m_gpio.bitSet (BIT_CLOCK_TX);
    m_gpio.bitSet (BIT_DATA_TX);
    m_gpio.bitClear(BIT_PTT);

    while (1)
    {

#ifdef DATA_CPU_TO_MODEM
        shift_left(&m_word,1);

        if ( m_word == 0xeca1)
        {
            m_gpio.bitSet(BIT_PTT);
            m_pTimer->stop();
#endif
            for (int n=0;n<TOTAL_BYTES;n++)
            {
                data  = (quint8) get_data() >> 4;
                data |= (quint8) get_data();
                arr.append(data);
            }

            m_word=0xffff;
            m_gpio.bitClear(BIT_PTT);
            m_gpio.bitSet (BIT_AUDIO);
            //qDebug() << arr.toHex();
            emit messageRx(arr);
            arr.clear();
#ifdef DATA_CPU_TO_MODEM
        }
#endif
    }
}
