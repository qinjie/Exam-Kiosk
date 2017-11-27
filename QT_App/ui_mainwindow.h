/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QLabel *label_3;
    QLabel *seatRFIDIcon;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *seatLEStudentName;
    QLineEdit *seatLEStudentNo;
    QLabel *staticMessageExamSeating;
    QTableWidget *seatTableWidget;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_3;
    QLabel *toiletScanLabel;
    QLabel *toiletRFIDIcon;
    QLabel *label_15;
    QLabel *label_16;
    QLineEdit *toiletLEStudentName;
    QLineEdit *toiletLEStudentNo;
    QLabel *label_17;
    QLineEdit *toiletLELecturerID;
    QLabel *staticMessageToiletTrips;
    QTableWidget *toiletTableWidget;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_4;
    QLabel *label_18;
    QLabel *subRFIDIcon;
    QLabel *label_20;
    QLabel *label_21;
    QLineEdit *subLEStudentName;
    QLineEdit *subLEStudentNo;
    QLabel *staticMessageSubmission;
    QTableWidget *subTableWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(818, 504);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMinimumSize(QSize(800, 420));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(0, 120));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(590, 50, 171, 20));
        label_3->setStyleSheet(QStringLiteral("font: 12pt \"MS Shell Dlg 2\"; color: blue"));
        seatRFIDIcon = new QLabel(groupBox);
        seatRFIDIcon->setObjectName(QStringLiteral("seatRFIDIcon"));
        seatRFIDIcon->setGeometry(QRect(440, 10, 100, 100));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 50, 111, 16));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 20, 91, 16));
        seatLEStudentName = new QLineEdit(groupBox);
        seatLEStudentName->setObjectName(QStringLiteral("seatLEStudentName"));
        seatLEStudentName->setGeometry(QRect(170, 50, 181, 20));
        seatLEStudentNo = new QLineEdit(groupBox);
        seatLEStudentNo->setObjectName(QStringLiteral("seatLEStudentNo"));
        seatLEStudentNo->setGeometry(QRect(170, 20, 181, 20));
        staticMessageExamSeating = new QLabel(groupBox);
        staticMessageExamSeating->setObjectName(QStringLiteral("staticMessageExamSeating"));
        staticMessageExamSeating->setGeometry(QRect(120, 80, 311, 31));

        verticalLayout->addWidget(groupBox);

        seatTableWidget = new QTableWidget(tab);
        if (seatTableWidget->columnCount() < 5)
            seatTableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        seatTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        seatTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        seatTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        seatTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        seatTableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        seatTableWidget->setObjectName(QStringLiteral("seatTableWidget"));
        seatTableWidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(seatTableWidget->sizePolicy().hasHeightForWidth());
        seatTableWidget->setSizePolicy(sizePolicy);
        seatTableWidget->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(seatTableWidget);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_4 = new QVBoxLayout(tab_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(0, 120));
        toiletScanLabel = new QLabel(groupBox_3);
        toiletScanLabel->setObjectName(QStringLiteral("toiletScanLabel"));
        toiletScanLabel->setGeometry(QRect(590, 50, 171, 20));
        toiletScanLabel->setStyleSheet(QStringLiteral("font: 12pt \"MS Shell Dlg 2\"; color: blue"));
        toiletRFIDIcon = new QLabel(groupBox_3);
        toiletRFIDIcon->setObjectName(QStringLiteral("toiletRFIDIcon"));
        toiletRFIDIcon->setGeometry(QRect(440, 10, 100, 100));
        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(40, 30, 111, 16));
        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(40, 0, 91, 16));
        toiletLEStudentName = new QLineEdit(groupBox_3);
        toiletLEStudentName->setObjectName(QStringLiteral("toiletLEStudentName"));
        toiletLEStudentName->setGeometry(QRect(190, 30, 181, 20));
        toiletLEStudentNo = new QLineEdit(groupBox_3);
        toiletLEStudentNo->setObjectName(QStringLiteral("toiletLEStudentNo"));
        toiletLEStudentNo->setGeometry(QRect(190, 0, 181, 20));
        label_17 = new QLabel(groupBox_3);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(40, 60, 91, 16));
        toiletLELecturerID = new QLineEdit(groupBox_3);
        toiletLELecturerID->setObjectName(QStringLiteral("toiletLELecturerID"));
        toiletLELecturerID->setGeometry(QRect(190, 60, 181, 20));
        staticMessageToiletTrips = new QLabel(groupBox_3);
        staticMessageToiletTrips->setObjectName(QStringLiteral("staticMessageToiletTrips"));
        staticMessageToiletTrips->setGeometry(QRect(80, 90, 441, 21));

        verticalLayout_4->addWidget(groupBox_3);

        toiletTableWidget = new QTableWidget(tab_2);
        if (toiletTableWidget->columnCount() < 2)
            toiletTableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        toiletTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        toiletTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        toiletTableWidget->setObjectName(QStringLiteral("toiletTableWidget"));

        verticalLayout_4->addWidget(toiletTableWidget);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayout_5 = new QVBoxLayout(tab_3);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        groupBox_4 = new QGroupBox(tab_3);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(0, 120));
        label_18 = new QLabel(groupBox_4);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(590, 50, 171, 20));
        label_18->setStyleSheet(QStringLiteral("font: 12pt \"MS Shell Dlg 2\"; color: blue"));
        subRFIDIcon = new QLabel(groupBox_4);
        subRFIDIcon->setObjectName(QStringLiteral("subRFIDIcon"));
        subRFIDIcon->setGeometry(QRect(440, 10, 100, 100));
        label_20 = new QLabel(groupBox_4);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(30, 50, 111, 16));
        label_21 = new QLabel(groupBox_4);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(30, 20, 91, 16));
        subLEStudentName = new QLineEdit(groupBox_4);
        subLEStudentName->setObjectName(QStringLiteral("subLEStudentName"));
        subLEStudentName->setGeometry(QRect(160, 50, 181, 20));
        subLEStudentNo = new QLineEdit(groupBox_4);
        subLEStudentNo->setObjectName(QStringLiteral("subLEStudentNo"));
        subLEStudentNo->setGeometry(QRect(160, 20, 181, 20));
        staticMessageSubmission = new QLabel(groupBox_4);
        staticMessageSubmission->setObjectName(QStringLiteral("staticMessageSubmission"));
        staticMessageSubmission->setGeometry(QRect(90, 90, 401, 21));

        verticalLayout_5->addWidget(groupBox_4);

        subTableWidget = new QTableWidget(tab_3);
        if (subTableWidget->columnCount() < 1)
            subTableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        subTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        subTableWidget->setObjectName(QStringLiteral("subTableWidget"));

        verticalLayout_5->addWidget(subTableWidget);

        tabWidget->addTab(tab_3, QString());

        verticalLayout_3->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 818, 27));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox->setTitle(QString());
        label_3->setText(QApplication::translate("MainWindow", "Scan Student Card", 0));
        seatRFIDIcon->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_2->setText(QApplication::translate("MainWindow", "Student Name:", 0));
        label->setText(QApplication::translate("MainWindow", "Student No:", 0));
        staticMessageExamSeating->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = seatTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Date", 0));
        QTableWidgetItem *___qtablewidgetitem1 = seatTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Time", 0));
        QTableWidgetItem *___qtablewidgetitem2 = seatTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Module", 0));
        QTableWidgetItem *___qtablewidgetitem3 = seatTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Venue", 0));
        QTableWidgetItem *___qtablewidgetitem4 = seatTableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Seat", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Exam Seating", 0));
        groupBox_3->setTitle(QString());
        toiletScanLabel->setText(QApplication::translate("MainWindow", "Scan Student Card", 0));
        toiletRFIDIcon->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_15->setText(QApplication::translate("MainWindow", "Student Name:", 0));
        label_16->setText(QApplication::translate("MainWindow", "Student No:", 0));
        label_17->setText(QApplication::translate("MainWindow", "Lecturer ID :", 0));
        staticMessageToiletTrips->setText(QString());
        QTableWidgetItem *___qtablewidgetitem5 = toiletTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "New Column", 0));
        QTableWidgetItem *___qtablewidgetitem6 = toiletTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "New Column", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Toilet Trips", 0));
        groupBox_4->setTitle(QString());
        label_18->setText(QApplication::translate("MainWindow", "Scan Student Card", 0));
        subRFIDIcon->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_20->setText(QApplication::translate("MainWindow", "Student Name:", 0));
        label_21->setText(QApplication::translate("MainWindow", "Student No:", 0));
        staticMessageSubmission->setText(QString());
        QTableWidgetItem *___qtablewidgetitem7 = subTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "New Column", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Early Submission", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
