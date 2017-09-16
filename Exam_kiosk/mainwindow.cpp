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
    isWaitingForTeacher = false;
    listeningTag = new ListeningTag(this);
    connect(listeningTag, SIGNAL(foundTag(QString)), this, SLOT(handleTag(QString)));
    //check if user clicked at a tab
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabSelected()));
    listeningTag->start();

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
            qDebug() << "On Handle tag :Exam seating";
            examSeatingSearching(id);
            break;
        case 1:
            qDebug() << "On Handle tag :Toilet trips";
            toiletTripsChecking(id);
            break;
        case 2:
            qDebug() << "On Handle tag :Submisson script";
            submissonScriptChecking(id);
            break;
        default:
            qDebug() << "On Handle tag : Window doesn't active";
    }
}

//get Data from server through API by ID (StudentID)
void MainWindow::examSeatingSearching(QString id) {
    qDebug() << "   On Link Exam Seating Searching";
    QString url = "https://2cdh0n36vg.execute-api.ap-southeast-1.amazonaws.com/api/seat/";
    url.append(id);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResultexamSeatingSearching(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::toiletTripsChecking(QString id){
    if (isWaitingForTeacher) {
        qDebug() << "   On Toilet Trip checking waiting for staff";
        if (currentStudentID != NULL && currentStudentID != "" && currentStudentID == id) {
            qDebug() << "The same ID of Student";
        } else {
            toiletTripsGoOut(currentStudentID, id);
            isWaitingForTeacher = false;
            currentStudentID = "";
            ui->toiletScanLabel->setText("Scan Student card");
        }
    } else {
        qDebug() << "   On Toilet Trip Checking Get List to check -> two case : goIn or Check to goOut";
        currentStudentID = id;
        QString url = "https://2cdh0n36vg.execute-api.ap-southeast-1.amazonaws.com/api/toilet/";
        url.append(id);
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResultToiletTripsChecking(QNetworkReply*)));
        manager->get(QNetworkRequest(QUrl(url)));
    }
}

void MainWindow::toiletTripsGoIn(QString id) {
    qDebug() << "   On Link Toilet Trip Student Go In";
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResultToiletTripsGoIn(QNetworkReply*)));

    // Build your JSON string as usual
    QByteArray jsonString; //"201720519" +  + "999999999" + ;
    jsonString.append("{\"student_rfid\":\"");
    jsonString.append(id);
    jsonString.append("\"}");
    // For your "Content-Length" header
    QByteArray postDataSize = QByteArray::number(jsonString.size());

    // Time for building request
    QUrl serviceURL("https://2cdh0n36vg.execute-api.ap-southeast-1.amazonaws.com/api/toilet/update");
    QNetworkRequest request(serviceURL);

    // Add the headers specifying their names and their values with the following method : void QNetworkRequest::setRawHeader(const QByteArray & headerName, const QByteArray & headerValue);
    request.setRawHeader("User-Agent", "My app name v0.1");
    request.setRawHeader("X-Custom-User-Agent", "My app name v0.1");
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Content-Length", postDataSize);

    manager->post(request, jsonString);
}

void MainWindow::onResultToiletTripsGoIn(QNetworkReply *reply) {
    qDebug() << "       On Result Toilet Trip go In";
    QByteArray bytes = reply->readAll();
    QString str = QString::fromUtf8(bytes.data(), bytes.size());
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode != 200) {
        qDebug() << "           Result : " << str;
        return;
    } else {
        qDebug() << "           Toilet Trip go in successfull!" << statusCode << " : " << str;
    }
}

void MainWindow::toiletTripsGoOut(QString studentID, QString staffID) {
    qDebug() << "   On Link Toilet Trip cerificate  Go Out";
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResultToiletTripsGoOut(QNetworkReply*)));

    // Build your JSON string as usual
    QByteArray jsonString; //"201720519" +  + "999999999" + ;
    jsonString.append("{\"student_rfid\":\"");
    jsonString.append(studentID);
    jsonString.append("\",\"staff_rfid\":\"");
    jsonString.append(staffID);
    jsonString.append("\"}");
    // For your "Content-Length" header
    QByteArray postDataSize = QByteArray::number(jsonString.size());

    // Time for building request
    QUrl serviceURL("https://2cdh0n36vg.execute-api.ap-southeast-1.amazonaws.com/api/toilet");
    QNetworkRequest request(serviceURL);

    // Add the headers specifying their names and their values with the following method : void QNetworkRequest::setRawHeader(const QByteArray & headerName, const QByteArray & headerValue);
    request.setRawHeader("User-Agent", "My app name v0.1");
    request.setRawHeader("X-Custom-User-Agent", "My app name v0.1");
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Content-Length", postDataSize);

    manager->post(request, jsonString);
}

void MainWindow::onResultToiletTripsGoOut(QNetworkReply *reply) {
    qDebug() << "       On Result Toilet Trip Certificate Go Out";
    QByteArray bytes = reply->readAll();
    QString data = bytes;
    QString str = QString::fromUtf8(bytes.data(), bytes.size());
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode != 200) {
        qDebug() << "           Next work Error in certificate go out!";
        return;
    } else {
        qDebug() << "           Read successfull in certificate go out!" << statusCode << " : " << str;
    }
}

void MainWindow::submissonScriptChecking(QString id) {
    qDebug() << "   On Link submission Script checking";
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResultSubmissonScriptChecking(QNetworkReply*)));

    // Build your JSON string as usual
    QByteArray jsonString;
    jsonString.append("{\"student_rfid\":\"");
    jsonString.append(id);
    jsonString.append("\"}");
    // For your "Content-Length" header
    QByteArray postDataSize = QByteArray::number(jsonString.size());

    // Time for building request
    QUrl serviceURL("https://2cdh0n36vg.execute-api.ap-southeast-1.amazonaws.com/api/submission");
    QNetworkRequest request(serviceURL);

    // Add the headers specifying their names and their values with the following method : void QNetworkRequest::setRawHeader(const QByteArray & headerName, const QByteArray & headerValue);
    request.setRawHeader("User-Agent", "My app name v0.1");
    request.setRawHeader("X-Custom-User-Agent", "My app name v0.1");
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Content-Length", postDataSize);

    manager->post(request, jsonString);
}

void MainWindow::onResultSubmissonScriptChecking(QNetworkReply *reply) {
    qDebug() << "       On result Submission Script Checking";
    QByteArray bytes = reply->readAll();
    QString str = QString::fromUtf8(bytes.data(), bytes.size());
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode != 200) {
        qDebug() << "           Interal System error";
        qDebug() << "               on result : " << str;
        return;
    } else {
        qDebug() << "           Toilet Trip go in successfull!" << statusCode << " : " << str;
        //qDebug() << "   on result : " << str;
    }
    QString data = bytes;
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonArray jsonArray = doc.array();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        QString str = obj["date"].toString() + obj["start_time"].toString() + obj["venue"].toString()
                        + obj["seat"].toString();
        qDebug() << str;
        int rowCount = ui->subTableWidget->rowCount();
        ui->subTableWidget->insertRow(rowCount);
        qDebug() << "Row Count : " << rowCount;
        ui->subTableWidget->setItem(rowCount, 0 , new QTableWidgetItem(obj["card"].toString()));
        ui->subTableWidget->setItem(rowCount, 1 , new QTableWidgetItem(obj["name"].toString()));
        ui->subTableWidget->setItem(rowCount, 2 , new QTableWidgetItem(obj["module"].toString()));
        ui->subTableWidget->setItem(rowCount, 3 , new QTableWidgetItem(obj["submission_time"].toString()));
    }
}

void MainWindow::onResultexamSeatingSearching(QNetworkReply *reply) {
    qDebug() << "       On result Exam Seating Searching";
    clearContentsTable(0);
    //Read data return on reply
    QByteArray bytes = reply->readAll();
    QString data = bytes;
    QString str = QString::fromUtf8(bytes.data(), bytes.size());
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode != 200) {
        qDebug() << "           Next work Error on Result Exam Seating";
        return;
    } else {
        qDebug() << "           Read successfull on Exam seating Checking!" << statusCode << " : " << str;
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
    }
}

void MainWindow::onResultToiletTripsChecking(QNetworkReply *reply) {
    qDebug() << "       On result Toilet trip checking -> check want go out or go in";

    //Read list of toilet trip return on reply
    QByteArray bytes = reply->readAll();
    QString data = bytes;
    QString str = QString::fromUtf8(bytes.data(), bytes.size());
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode != 200) {
        qDebug() << "           Next work Error on toilet trip checking";
        return;
    } else {
        qDebug() << "           Toilet Trip Read successfull!";// << statusCode << " : " << str;
    }

    bool goOut = true;
    //QString sender_card;
    clearContentsTable(1);
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());

    if (!doc.isArray()) {
        qDebug() << "Toi let Trip get Fail";
        return;
    }

    QJsonArray jsonArray = doc.array();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        QString str = obj["card"].toString() + obj["name"].toString() + obj["time_out"].toString()
                        + obj["time_in"].toString() + obj["sender"].toBool();
        //qDebug() << str;
        if (obj["sender"].toBool()) {
            //sender_card = obj["card"].toString();
            if (obj["time_out"].toString() != NULL && obj["time_in"].toString() == "None") {
                goOut = false;
                //qDebug() << "Student go In";
            }
            //qDebug() << "Time in/out : " <<obj["time_out"].toString() << " " << obj["time_in"].toString();
        }
        int rowCount = ui->toiletTableWidget->rowCount();
        ui->toiletTableWidget->insertRow(rowCount);
        //qDebug() << "Row Count : " << rowCount;
        ui->toiletTableWidget->setItem(rowCount, 0 , new QTableWidgetItem(obj["card"].toString()));
        ui->toiletTableWidget->setItem(rowCount, 1 , new QTableWidgetItem(obj["name"].toString()));
        ui->toiletTableWidget->setItem(rowCount, 2 , new QTableWidgetItem(obj["time_out"].toString()));
        ui->toiletTableWidget->setItem(rowCount, 3 , new QTableWidgetItem(obj["time_in"].toString()));
        ui->toiletTableWidget->setItem(rowCount, 4 , new QTableWidgetItem(obj["staff"].toString()));
    }
    if (goOut) {
        qDebug() << "Please insert the Staff card";
        ui->toiletScanLabel->setText("Scan Staff card");
        isWaitingForTeacher = true;
    } else {
        qDebug() << "User come back";
        toiletTripsGoIn(currentStudentID);
    }
}

void MainWindow::clearContentsTable(int tab) {
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
    ui->toiletTableWidget->setColumnCount(5);
    ui->toiletTableWidget->setHorizontalHeaderLabels(QStringList() << tr("Student No.") << tr("Student Name") << tr("Time Out")  << tr("Time In") << tr("Staff"));
    ui->subTableWidget->setColumnCount(4);
    ui->subTableWidget->setHorizontalHeaderLabels(QStringList() << tr("Student No.") << tr("Student Name") << tr("Module")  << tr("Submission"));
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
    //qDebug()<< "Rezing table : ";
    int seatTableWidth = ui->seatTableWidget->width();
    ui->seatTableWidget->setColumnWidth(0, seatTableWidth/5);
    ui->seatTableWidget->setColumnWidth(1, seatTableWidth/5);
    ui->seatTableWidget->setColumnWidth(2, 3*seatTableWidth/20);
    ui->seatTableWidget->setColumnWidth(3, seatTableWidth/5);
    ui->seatTableWidget->setColumnWidth(4, seatTableWidth/5);

    int toiletTableWidth = ui->toiletTableWidget->width();
    ui->toiletTableWidget->setColumnWidth(0, toiletTableWidth/5);
    ui->toiletTableWidget->setColumnWidth(1, toiletTableWidth/4);
    ui->toiletTableWidget->setColumnWidth(2, toiletTableWidth/6);
    ui->toiletTableWidget->setColumnWidth(3, toiletTableWidth/6);
    ui->toiletTableWidget->setColumnWidth(4, toiletTableWidth/6);

    int subTableWidth = ui->subTableWidget->width();
    ui->subTableWidget->setColumnWidth(0, subTableWidth/5);
    ui->subTableWidget->setColumnWidth(1, 3*subTableWidth/10);
    ui->subTableWidget->setColumnWidth(2, subTableWidth/5);
    ui->subTableWidget->setColumnWidth(3, subTableWidth/4);
}

//Resize table after UI load
void MainWindow::showEvent(QShowEvent *event) {
    QWidget::showEvent( event );
    resizeTable();
}

//Resize table when Window resize
void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   resizeTable();
}

//Update table in tab when it is selected
void MainWindow::tabSelected() {
    resizeTable();
}

bool MainWindow::checkStudentToiletOut(QString card) {
    qDebug() << "List out :";
    foreach (const QString str, listStudentToiletOut) {
        qDebug() << "List out : " << (str);
    }
    return false;
}
