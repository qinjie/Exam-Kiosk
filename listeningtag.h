#ifndef LISTENINGTAG_H
#define LISTENINGTAG_H
#include <QThread>

class ListeningTag : public QThread
{
    Q_OBJECT
public:
    explicit ListeningTag(QObject *parent = 0);
    void    run();

signals:
    void    foundTag(QString id);

public slots:
    void    DoWork();
};

#endif // LISTENINGTAG_H
