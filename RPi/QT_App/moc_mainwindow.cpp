/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata[369];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 11),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 9),
QT_MOC_LITERAL(4, 34, 2),
QT_MOC_LITERAL(5, 37, 11),
QT_MOC_LITERAL(6, 49, 16),
QT_MOC_LITERAL(7, 66, 14),
QT_MOC_LITERAL(8, 81, 28),
QT_MOC_LITERAL(9, 110, 27),
QT_MOC_LITERAL(10, 138, 23),
QT_MOC_LITERAL(11, 162, 23),
QT_MOC_LITERAL(12, 186, 31),
QT_MOC_LITERAL(13, 218, 24),
QT_MOC_LITERAL(14, 243, 17),
QT_MOC_LITERAL(15, 261, 23),
QT_MOC_LITERAL(16, 285, 27),
QT_MOC_LITERAL(17, 313, 27),
QT_MOC_LITERAL(18, 341, 27)
    },
    "MainWindow\0resizeTable\0\0handleTag\0id\0"
    "tabSelected\0onResultGetInfor\0"
    "QNetworkReply*\0onResultexamSeatingSearching\0"
    "onResultToiletTripsChecking\0"
    "toiletTripsUserChecking\0onResultToiletTripsGoIn\0"
    "onResultSubmissonScriptChecking\0"
    "onResultToiletTripsGoOut\0resetMessageAlert\0"
    "resetMessageStaticAlert\0"
    "resetMessageStaticAlertTab1\0"
    "resetMessageStaticAlertTab2\0"
    "resetMessageStaticAlertTab3"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    1,   90,    2, 0x08 /* Private */,
       5,    0,   93,    2, 0x08 /* Private */,
       6,    1,   94,    2, 0x08 /* Private */,
       8,    1,   97,    2, 0x08 /* Private */,
       9,    1,  100,    2, 0x08 /* Private */,
      10,    1,  103,    2, 0x08 /* Private */,
      11,    1,  106,    2, 0x08 /* Private */,
      12,    1,  109,    2, 0x08 /* Private */,
      13,    1,  112,    2, 0x08 /* Private */,
      14,    0,  115,    2, 0x08 /* Private */,
      15,    0,  116,    2, 0x08 /* Private */,
      16,    0,  117,    2, 0x08 /* Private */,
      17,    0,  118,    2, 0x08 /* Private */,
      18,    0,  119,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->resizeTable(); break;
        case 1: _t->handleTag((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->tabSelected(); break;
        case 3: _t->onResultGetInfor((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 4: _t->onResultexamSeatingSearching((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 5: _t->onResultToiletTripsChecking((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 6: _t->toiletTripsUserChecking((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 7: _t->onResultToiletTripsGoIn((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 8: _t->onResultSubmissonScriptChecking((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 9: _t->onResultToiletTripsGoOut((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 10: _t->resetMessageAlert(); break;
        case 11: _t->resetMessageStaticAlert(); break;
        case 12: _t->resetMessageStaticAlertTab1(); break;
        case 13: _t->resetMessageStaticAlertTab2(); break;
        case 14: _t->resetMessageStaticAlertTab3(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
