#include "listeningtag.h"
#include <QDebug>
#include <QTCore>

ListeningTag::ListeningTag(QObject *parent) :
    QThread(parent)
{
    qDebug() << "Creating new Thread" << QThread::currentThreadId();
}

void ListeningTag::run() {
    qDebug() << "Thread Run";
    this->msleep(5000);
    bool check = true;
    while(1) {
        if (check) {
            check = false;
            emit foundTag("201720519");
        } else {
            check = true;
            emit foundTag("999999999");
        }
        this->msleep(20000);
    }
}

void ListeningTag::DoWork()
{
    qDebug() << "Thread::DoWork() in thread:" << QThread::currentThreadId();
    sleep(10);
}
