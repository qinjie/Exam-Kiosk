#ifndef LISTENINGTAG_H
#define LISTENINGTAG_H
#include <QThread>

#include <stdlib.h>
#include "nfc/nfc.h"

class ListeningTag : public QThread
{
    Q_OBJECT
public:
    explicit ListeningTag(QObject *parent = 0);
    void    run();
    void    print_hex(const uint8_t *pbtData, const size_t szBytes);
    void    emit_data(const uint8_t *pbtData, const size_t szBytes);

signals:
    void    foundTag(QString id);

public slots:
    void    DoWork();
};

#endif // LISTENINGTAG_H
