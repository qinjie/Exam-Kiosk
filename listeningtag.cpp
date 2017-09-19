#include "listeningtag.h"
#include <QDebug>

extern "C" {
#include <wiringPi.h>
}

ListeningTag::ListeningTag(QObject *parent) :
    QThread(parent)
{
    qDebug() << "Creating new Thread" << QThread::currentThreadId();
}

void ListeningTag::run() {
    qDebug() << "Thread Run";
    if (wiringPiSetup() == -1) {
        qDebug() << "Setup wire fail";
        return;
    }
    pinMode(0, INPUT);
    int prevValueBack = 0;
    int prevValueNext = 0;
    while(1) {
        //qDebug() << "Running";
        bool press = false;
        int valueBack = digitalRead(0);
        if (valueBack && valueBack != prevValueBack) {
            qDebug() << "Back Press";
            press = true;
            emit foundTag("201720519");
        }
        prevValueBack = valueBack;

        int valueNext = digitalRead(1);
        if (valueNext && valueNext != prevValueNext) {
            qDebug() << "Next Press";
            press = true;
            emit foundTag("999999999");
        }
        prevValueNext = valueNext;
    }

}

void ListeningTag::DoWork()
{
    qDebug() << "Thread::DoWork() in thread:" << QThread::currentThreadId();
    sleep(10);
}
