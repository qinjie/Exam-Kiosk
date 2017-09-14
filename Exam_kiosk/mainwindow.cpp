#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QDebug"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initRFIDIcon();
    initTable();
    //connect(this, SIGNAL(resizeEvent(QResizeEvent *e)), this, SLOT(resizeTable()));
    listenForTag = false;
    listeningTag = new ListeningTag(this);
    connect(listeningTag, SIGNAL(foundTag(QString)), this, SLOT(handleTag(QString)));
}

void MainWindow::initRFIDIcon() {
    QPixmap pixmap("://img/rfid.jpg");
    int w = ui->seatRFIDIcon->width();
    int h = ui->seatRFIDIcon->height();
    ui->seatRFIDIcon->setPixmap(pixmap.scaled(w, h ,Qt::KeepAspectRatio));
    ui->toiletRFIDIcon->setPixmap(pixmap.scaled(w, h ,Qt::KeepAspectRatio));
    ui->subRFIDIcon->setPixmap(pixmap.scaled(w, h ,Qt::KeepAspectRatio));
}

void MainWindow::handleTag(QString id) {
    qDebug() << "Handle Tag ID : " << id << "Tab " << ui->tabWidget->currentIndex();
    int tab = ui->tabWidget->currentIndex();
    switch(tab) {
        case 0:
            qDebug() << "Exam seating";
            examSeatingSearching(id);
            break;
        case 1:
            qDebug() << "Toilet trips";
            break;
        case 2:
            qDebug() << "Submisson";
            break;
        default:
            qDebug() << "Window doesn't active";
    }
}

//get Data from server through API by ID (StudentID)
void MainWindow::examSeatingSearching(QString id) {
    qDebug() << "Exam Seating Searching";
    QString url = "https://2cdh0n36vg.execute-api.ap-southeast-1.amazonaws.com/api/seat/";
    url.append(id);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResultexamSeatingSearching(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::toiletTripsChecking(QString id){

}

void MainWindow::submissonScriptChecking(QString id) {

}

void MainWindow::onResultexamSeatingSearching(QNetworkReply *reply) {
    qDebug() << "On result Exam Seating Searching";

    //remove Row previous
//    for(int i = ui->seatTableWidget->rowCount() - 1; i >=0; i--) {
//        ui->seatTableWidget->removeRow(i);
//    }
    // clearTable(tab)  0 <-> seatTableWidget
    clearTable(0);
    //Read data return on reply
    QByteArray bytes = reply->readAll();
    QString data = bytes;
    QString str = QString::fromUtf8(bytes.data(), bytes.size());
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode != 200) {
        qDebug() << "Next work Error";
        return;
    } else {
        qDebug() << "Read successfull!" << statusCode << " : " << str;
    }
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonArray jsonArray = doc.array();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        QString str = obj["date"].toString() + obj["start_time"].toString() + obj["venue"].toString()
                        + obj["seat"].toString();
        qDebug() << str;
        int rowCount = ui->seatTableWidget->rowCount();
        ui->seatTableWidget->insertRow(rowCount);
        qDebug() << "Row Count : " << rowCount;
        ui->seatTableWidget->setItem(rowCount, 0 , new QTableWidgetItem(obj["date"].toString()));
        ui->seatTableWidget->setItem(rowCount, 1 , new QTableWidgetItem(obj["start_time"].toString()));
        ui->seatTableWidget->setItem(rowCount, 2 , new QTableWidgetItem(obj["module"].toString()));
        ui->seatTableWidget->setItem(rowCount, 3 , new QTableWidgetItem(obj["venue"].toString()));
        ui->seatTableWidget->setItem(rowCount, 4 , new QTableWidgetItem(obj["seat"].toString()));
        //QStringList row;
        //row <<  << obj["start_time"].toString() << obj["venue"].toString() << obj["seat"].toString();
        //ui->seatTableWidget->setR
        //Continue here
    }
}

void MainWindow::onResultToiletTripsChecking(QNetworkReply *reply) {

}

void MainWindow::onResultSubmissonScriptChecking(QNetworkReply *reply) {

}

void MainWindow::clearTable(int tab) {
    switch(tab) {
        case 0:
            for(int i = ui->seatTableWidget->rowCount() - 1; i >=0; i--) {
                ui->seatTableWidget->removeRow(i);
            }
            break;
        case 1:
            for(int i = ui->toiletTableWidget->rowCount() - 1; i >=0; i--) {
                ui->toiletTableWidget->removeRow(i);
            }
            break;
        case 2:
            for(int i = ui->subTableWidget->rowCount() - 1; i >=0; i--) {
                ui->subTableWidget->removeRow(i);
            }
            break;
        default:
            qDebug() << "Window doesn't active";
    }
}

void MainWindow::initTable() {
    ui->seatTableWidget->setColumnCount(5);
    ui->seatTableWidget->setHorizontalHeaderLabels(QStringList() << tr("Date") << tr("Time") << tr("Module")  << tr("Venue") << tr("Seat"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug()<< "Start thread! ";
    listeningTag->start();
}

//resize table proper contents
void MainWindow::resizeTable() {
    int w = ui->seatTableWidget->width();
    qDebug()<< "Width of Table : " << w;
    ui->seatTableWidget->setColumnWidth(0, w/4);
    ui->seatTableWidget->setColumnWidth(1, w/5);
    ui->seatTableWidget->setColumnWidth(2, 3*w/20);
    ui->seatTableWidget->setColumnWidth(3, w/5);
    ui->seatTableWidget->setColumnWidth(4, w/5);
}

//Resize table after UI load
void MainWindow::showEvent(QShowEvent *event) {
    QWidget::showEvent( event );
    qDebug() << "Comed in";
    resizeTable();
}

//Resize table when Window resize
void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   // Your code here.
   resizeTable();
}
