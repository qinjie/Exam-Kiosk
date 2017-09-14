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
    while(1) {
        emit foundTag("201720519");
        this->msleep(3000);
    }
}

void ListeningTag::DoWork()
{
    qDebug() << "Thread::DoWork() in thread:" << QThread::currentThreadId();
    sleep(10);
}
