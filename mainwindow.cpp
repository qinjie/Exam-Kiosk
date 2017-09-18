#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextEdit>
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initRFIDIcon();
    initTable();

    seatCheckingURL = "https://2cdh0n36vg.execute-api.ap-southeast-1.amazonaws.com/api/seat/";
    toiletTripsGoOutURL = "https://2cdh0n36vg.execute-api.ap-southeast-1.amazonaws.com/api/toilet";
    toiletTripsGoInURL = "https://2cdh0n36vg.execute-api.ap-southeast-1.amazonaws.com/api/toilet/update";
    subTripsCheckingURL = "https://2cdh0n36vg.execute-api.ap-southeast-1.amazonaws.com/api/submission";
    getListTripsCheckingURL = "https://2cdh0n36vg.execute-api.ap-southeast-1.amazonaws.com/api/toilet/";
    getUserInforURL = "https://2cdh0n36vg.execute-api.ap-southeast-1.amazonaws.com/api/user/";

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

void MainWindow::insertDataToCellTableWithTab(int32_t row, int32_t col, QString data, int tab) {
    QString str = "<font color = green> <b>" + data + "</b>";
    QLabel *text = new QLabel(str);
    text->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
    if (tab == 0) {
        ui->seatTableWidget->setCellWidget(row, col, text);
    } else if (tab == 1) {
        ui->toiletTableWidget->setCellWidget(row, col, text);
    } else if (tab == 2) {
        ui->subTableWidget->setCellWidget(row, col, text);
    }
}

//get infor of Student/Staff
void MainWindow::getInfor(QString id) {
    qDebug() << "   On Link Get Infor";
    QString url = "https://2cdh0n36vg.execute-api.ap-southeast-1.amazonaws.com/api/user/";
    url.append(id);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResultGetInfor(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::onResultGetInfor(QNetworkReply *reply) {
    qDebug() << "       On result Get Infor";
    QByteArray bytes = reply->readAll();
    QString data = bytes;
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject obj = doc.array().at(0).toObject();
    ui->seatLEStudentNo->setText(obj["card"].toString());
    ui->seatLEStudentName->setText(obj["name"].toString());
    qDebug() << "Card : " << obj["card"].toString() << "Name : " << obj["name"].toString();
}

//get Data from server through API by ID (StudentID)
void MainWindow::examSeatingSearching(QString id) {
    qDebug() << "   On Link Exam Seating Searching";
    QString url = seatCheckingURL;
    url.append(id);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResultexamSeatingSearching(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(url)));
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
        qDebug() << "           Read successfull on Exam seating Checking!";// << statusCode << " : " << str;
    }
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonArray jsonArray = doc.array();
    bool isFirstRow = true;
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        //QString str = obj["date"].toString() + obj["start_time"].toString() + obj["venue"].toString()
                        //+ obj["seat"].toString();
        //qDebug() << str;
        if (isFirstRow) {
            isFirstRow = false;
            ui->seatLEStudentNo->setText(obj["card"].toString());
            ui->seatLEStudentName->setText(obj["name"].toString());
        }
        int rowCount = ui->seatTableWidget->rowCount();
        ui->seatTableWidget->insertRow(rowCount);
        //qDebug() << "Row Count : " << rowCount;
        QDate date = QDate::fromString(obj["date"].toString(),"yyyy-MM-dd");
        QTime startTime = QTime::fromString(obj["start_time"].toString(), "h:mm:ss");
        QTime endTime = QTime::fromString(obj["end_time"].toString(), "h:mm:ss");
        insertDataToCellTableWithTab(rowCount, 0, date.toString("yyyy MMM dd (dddd)"), 0);
        insertDataToCellTableWithTab(rowCount, 1, startTime.toString("h:mmap") + " - " + endTime.toString("h:mmap"), 0);
        insertDataToCellTableWithTab(rowCount, 2, obj["module"].toString(), 0);
        insertDataToCellTableWithTab(rowCount, 3, obj["venue"].toString(), 0);
        insertDataToCellTableWithTab(rowCount, 4, obj["seat"].toString(), 0);
    }
    ui->seatTableWidget->scrollToBottom();
}

//draw table
void MainWindow::drawTableData(QJsonArray jsonArray, int tab) {

    clearContentsTable(tab);
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        int rowCount = ui->toiletTableWidget->rowCount();
        ui->toiletTableWidget->insertRow(rowCount);
        insertDataToCellTableWithTab(rowCount, 0, obj["card"].toString(), tab);
        insertDataToCellTableWithTab(rowCount, 1, obj["name"].toString(), tab);
        insertDataToCellTableWithTab(rowCount, 2, obj["time_out"].toString(), tab);
        insertDataToCellTableWithTab(rowCount, 3, obj["time_in"].toString(), tab);
        insertDataToCellTableWithTab(rowCount, 4, obj["staff"].toString(), tab);
        //qDebug() << rowCount << " : " << obj["card"].toString() << " " << obj["name"].toString() << " " << obj["staff"].toString() << " "
                 //<< obj["time_out"].toString() << " " << obj["time_in"].toString();
    }
    ui->toiletTableWidget->scrollToBottom();
}

void MainWindow::toiletTripsChecking(QString id){
    if (!isHandleForToiletCheck) {
        isHandleForToiletCheck = true;
        currentStudentID = id;
        QString url = getUserInforURL;
        url.append(id);
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(toiletTripsUserChecking(QNetworkReply*)));
        manager->get(QNetworkRequest(QUrl(url)));
    } else {
        qDebug() << "System is handling, please wait!";
    }
}

void MainWindow::toiletTripsUserChecking(QNetworkReply *reply) {
    QByteArray bytes = reply->readAll();
    QString str = QString::fromUtf8(bytes.data(), bytes.size());
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode != 200) {
        qDebug() << "           Next work Error on toilet trip checking";
        return;
    } else {
        qDebug() << "           Read successfull on toilet trip checking!" << statusCode << " : " << str;
    }
    QString data = bytes;
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject obj = doc.array().at(0).toObject();
    QString role = obj["role"].toString();
    if (isWaitingForTeacher) {
        qDebug() << "   On Toilet Trip checking waiting for staff";
        if (currentStudentID != NULL && currentStudentID != "" && currentStudentID == studentIDGoOut) {
            qDebug() << "The same ID of Student";
            isHandleForToiletCheck = false;
            //isWaitingForTeacher = false;
        } else {
            if (role != "staff") {
                qDebug() << "Invalid one Student and one user";
                resetStateToiletTrips();
            } else {
                ui->toiletLELecturerID->setText(obj["card"].toString());
                toiletTripsGoOut(studentIDGoOut, currentStudentID);
            }
        }
    } else {
        if (role != "student") {
            qDebug() << "   Your'e not a Student";
            resetStateToiletTrips();
        } else {
            qDebug() << "   On Toilet Trip Checking Get List to check -> two case : goIn or Check to goOut";
            ui->toiletLEStudentNo->setText(obj["card"].toString());
            ui->toiletLEStudentName->setText(obj["name"].toString());
            QString url = getListTripsCheckingURL;
            url.append(currentStudentID);
            QNetworkAccessManager *manager = new QNetworkAccessManager(this);
            connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResultToiletTripsChecking(QNetworkReply*)));
            manager->get(QNetworkRequest(QUrl(url)));
        }
    }
}

void MainWindow::resetStateToiletTrips() {
    currentStudentID = "";
    studentIDGoOut = "";
    ui->toiletLEStudentNo->setText("");
    ui->toiletLEStudentName->setText("");
    ui->toiletLELecturerID->setText("");
    ui->toiletScanLabel->setText("Scan Student Card");
    isWaitingForTeacher = false;
    isHandleForToiletCheck = false;
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
        isHandleForToiletCheck = false;
        return;
    } else {
        qDebug() << "           Read successfull on toilet trip checking!" << statusCode << " : " << str;
    }

    bool goOut = true;
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonArray jsonArray = doc.array();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        if (obj["sender"].toBool()) {
            if (obj["time_out"].toString() != NULL && obj["time_in"].toString() == "None") {
                goOut = false;
                qDebug() << "Student go In";
                break;
            }
        }
    }
    if (goOut) {
        qDebug() << "Student want to go out - Please insert the Staff card";
        ui->toiletScanLabel->setText("Scan Staff card");
        drawTableData(jsonArray,1);
        studentIDGoOut = currentStudentID;
        isWaitingForTeacher = true;
        isHandleForToiletCheck = false;
    } else {
        qDebug() << "User come back";
        toiletTripsGoIn(currentStudentID);
    }
    ui->toiletTableWidget->scrollToBottom();
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
    QUrl serviceURL(toiletTripsGoInURL);
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
        isHandleForToiletCheck = false;
        return;
    } else {
        qDebug() << "           Toilet Trip go in successfull!" << statusCode << " : " << str;
    }
    QString data = bytes;
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    //Check respone
    QJsonObject obj = doc.array().at(0).toObject();
    if (obj["success"].toString() == "0") {
        //Not a Student
        ui->toiletLEStudentNo->setText("");
        ui->toiletLEStudentName->setText("");
        qDebug() << "Message : " << obj["success"].toString() << " : " <<obj["message"].toString();
        return;
    }
    clearContentsTable(1);
    QJsonArray jsonArray = doc.array();
    drawTableData(jsonArray, 1);
    isHandleForToiletCheck = false;
}

void MainWindow::toiletTripsGoOut(QString studentID, QString staffID) {
    qDebug() << "   On Link Toilet Trip cerificate  Go Out : " << studentID << " " << staffID;
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
    QUrl serviceURL(toiletTripsGoOutURL);
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

    //Check respone
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject obj = doc.array().at(0).toObject();
    if (obj["success"].toString() == "0") {
        //Not a Student
        ui->toiletLEStudentNo->setText("");
        ui->toiletLEStudentName->setText("");
        ui->toiletLELecturerID->setText("");
        qDebug() << "Message : " << obj["success"].toString() << " : " <<obj["message"].toString();
        isWaitingForTeacher = false;
        currentStudentID = "";
        studentIDGoOut = "";
        ui->toiletScanLabel->setText("Scan Student card");
        isHandleForToiletCheck = false;
        return;
    }
    //clearContentsTable(1);
    qDebug() << "Drawing toilet Table";
    QJsonArray jsonArray = doc.array();
    drawTableData(jsonArray, 1);

    isWaitingForTeacher = false;
    currentStudentID = "";
    studentIDGoOut = "";
    ui->toiletScanLabel->setText("Scan Student card");
    isHandleForToiletCheck = false;
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
    QUrl serviceURL(subTripsCheckingURL);
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
        qDebug() << "           On Submit successfull!";// << statusCode << " : " << str;
        //qDebug() << "   on result : " << str;
    }
    QString data = bytes;
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());

    //Check respone
    QJsonObject obj = doc.array().at(0).toObject();
    if (obj["success"].toString() == "0") {
        //Not a Student
        ui->subLEStudentNo->setText("");
        ui->subLEStudentName->setText("");
        qDebug() << "Message : " << obj["success"].toString() << " : " <<obj["message"].toString();
        return;
    }
    clearContentsTable(2);
    QJsonArray jsonArray = doc.array();
    foreach (const QJsonValue & value, jsonArray) {
        obj = value.toObject();
        //QString str = obj["card"].toString() + obj["name"].toString() + obj["module"].toString()
        //                + obj["submission_time"].toString();
        //qDebug() << str;

        if (obj["sender"].toBool()) {
            ui->subLEStudentNo->setText(obj["card"].toString());
            ui->subLEStudentName->setText(obj["name"].toString());
        }

        int rowCount = ui->subTableWidget->rowCount();
        ui->subTableWidget->insertRow(rowCount);
        //qDebug() << "Row Count : " << rowCount;
        insertDataToCellTableWithTab(rowCount, 0, obj["card"].toString(), 2);
        insertDataToCellTableWithTab(rowCount, 1, obj["name"].toString(), 2);
        insertDataToCellTableWithTab(rowCount, 2, obj["module"].toString(), 2);
        insertDataToCellTableWithTab(rowCount, 3, obj["submission_time"].toString(), 2);
    }
    ui->subTableWidget->scrollToBottom();
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
    //set style for header of table
    QString styleSheet = "::section {"
                         "color: white;"
                         "border: 1px solid black;"
                         "border-bottom: 0px;"
                         "background-color: blue;"
                         "border-top-left-radius: 5;"
                         "border-top-right-radius: 5;"
                         //"margin: 1px;"
                         "font-weight: bold;"
                         "font-family: arial;"
                         "font-size: 12px; }";
    ui->seatTableWidget->horizontalHeader()->setStyleSheet(styleSheet);
    ui->toiletTableWidget->horizontalHeader()->setStyleSheet(styleSheet);
    ui->subTableWidget->horizontalHeader()->setStyleSheet(styleSheet);

    //Init No and Name display
    ui->seatLEStudentNo->setStyleSheet("font-weight: bold; color : blue");
    ui->seatLEStudentName->setStyleSheet("font-weight: bold; color : blue");
    ui->toiletLEStudentNo->setStyleSheet("font-weight: bold; color : blue");
    ui->toiletLEStudentName->setStyleSheet("font-weight: bold; color : blue");
    ui->toiletLELecturerID->setStyleSheet("font-weight: bold; color : blue");
    ui->subLEStudentNo->setStyleSheet("font-weight: bold; color : blue");
    ui->subLEStudentName->setStyleSheet("font-weight: bold; color : blue");
}

MainWindow::~MainWindow()
{
    delete ui;
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
    ui->subTableWidget->setColumnWidth(3, 9*subTableWidth/40);
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

