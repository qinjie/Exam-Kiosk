#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initRFIDIcon();
}

void MainWindow::initRFIDIcon() {
    QPixmap pixmap("://img/rfid.jpg");
    int w = ui->seatRFIDIcon->width();
    int h = ui->seatRFIDIcon->height();
    ui->seatRFIDIcon->setPixmap(pixmap.scaled(w, h ,Qt::KeepAspectRatio));
    ui->toiletRFIDIcon->setPixmap(pixmap.scaled(w, h ,Qt::KeepAspectRatio));
    ui->subRFIDIcon->setPixmap(pixmap.scaled(w, h ,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}
