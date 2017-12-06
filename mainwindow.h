#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "listeningtag.h"
#include "QtNetwork"
#include "QTableWidget"
#include "QMessageBox"
#include "QTimer"

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

    void        getInfor(QString id);
    void        examSeatingSearching(QString id);
    void        toiletTripsChecking(QString id);
    void        toiletTripsGoIn(QString id);
    void        submissonScriptChecking(QString id);
    void        toiletTripsGoOut(QString studentRFID, QString staffRFID);
    void        clearContentsTable(int tab);
    void        resetStateToiletTrips();

    void        insertDataToCellTableWithTab(int32_t row, int32_t col, QString data, int32_t tab);
    void        insertDataToCellTableWithTab(int32_t row, int32_t col, QString data, int32_t tab, QString color);

    void        drawTableData(QJsonArray jsonArray, int tab, QString studentIDGoOut);

    void        alert(QString title, QString message, int type ,int time);
    void        staticAlert(QString title, QString message, int type ,int time, int tab);

    void        changeColorRowTable(int row, int color, int tab);

    ~MainWindow();

private slots:
    void        resizeTable();
    void        handleTag(QString id);
    void        tabSelected();

    void        onResultGetInfor(QNetworkReply*);
    void        onResultexamSeatingSearching(QNetworkReply*);
    void        onResultToiletTripsChecking(QNetworkReply*);
    void        toiletTripsUserChecking(QNetworkReply*);
    void        onResultToiletTripsGoIn(QNetworkReply*);
    void        onResultSubmissonScriptChecking(QNetworkReply*);

    void        onResultToiletTripsGoOut(QNetworkReply*);

    void        resetMessageAlert();
    void        resetMessageStaticAlert();
    void        resetMessageStaticAlertTab1();
    void        resetMessageStaticAlertTab2();
    void        resetMessageStaticAlertTab3();

protected:
    void        showEvent(QShowEvent *event);
    void        resizeEvent(QResizeEvent* event);

private:
    Ui::MainWindow      *ui;
    bool                listenForTag;
    bool                isHandleForToiletCheck = false;
    int                 curMsgTab;
    ListeningTag        *listeningTag;
    bool                isWaitingForTeacher;
    QString             currentStudentID;
    QString             studentIDGoOut;

    QString             seatCheckingURL;
    QString             toiletTripsGoInURL;
    QString             toiletTripsGoOutURL;
    QString             subTripsCheckingURL;
    QString             getUserInforURL;
    QString             getListTripsCheckingURL;

    QMessageBox         msgBox;

    QTimer*             mes_timer;
};

#endif // MAINWINDOW_H
