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
    explicit    MainWindow(QWidget *parent = 0);
    void        initRFIDIcon();
    void        initTable();

    void        examSeatingSearching(QString id);
    void        toiletTripsChecking(QString id);
    void        toiletTripsGoIn(QString id);
    void        submissonScriptChecking(QString id);

    void        toiletTripsGoOut(QString studentRFID, QString staffRFID);

    void        clearContentsTable(int tab);
    bool        checkStudentToiletOut(QString card);

    ~MainWindow();

private slots:
    void        on_pushButton_clicked();
    void        resizeTable();
    void        handleTag(QString id);
    void        tabSelected();

    void        onResultexamSeatingSearching(QNetworkReply*);
    void        onResultToiletTripsChecking(QNetworkReply*);
    void        onResultToiletTripsGoIn(QNetworkReply*);
    void        onResultSubmissonScriptChecking(QNetworkReply*);

    void        onResultToiletTripsGoOut(QNetworkReply*);

protected:
    void        showEvent(QShowEvent *event);
    void        resizeEvent(QResizeEvent* event);

private:
    Ui::MainWindow      *ui;
    bool                listenForTag;
    ListeningTag        *listeningTag;
    QStringList         listStudentToiletOut;
    bool                isWaitingForTeacher;
    QString             currentStudentID;
};

#endif // MAINWINDOW_H
