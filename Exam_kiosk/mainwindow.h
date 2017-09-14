#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "listeningtag.h"
#include "QtNetwork"
#include "QTableWidget"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void        initRFIDIcon();
    void        initTable();

    void        examSeatingSearching(QString id);
    void        toiletTripsChecking(QString id);
    void        submissonScriptChecking(QString id);

    void        clearTable(int tab);

    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void        resizeTable();
    void        handleTag(QString id);

    void        onResultexamSeatingSearching(QNetworkReply*);
    void        onResultToiletTripsChecking(QNetworkReply*);
    void        onResultSubmissonScriptChecking(QNetworkReply*);

protected:
    void    showEvent(QShowEvent *event);
    void    resizeEvent(QResizeEvent* event);

private:
    Ui::MainWindow *ui;
    bool listenForTag;
    ListeningTag *listeningTag;
};

#endif // MAINWINDOW_H
