/****************************************************************************
** Meta object code from reading C++ file 'Live.h'
**
** Created: Mon Jan 16 17:30:12 2017
**      by: The Qt Meta Object Compiler version 67 (Qt 5.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../Live.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Live.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Live_t {
    QByteArrayData data[27];
    char stringdata[430];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Live_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Live_t qt_meta_stringdata_Live = {
    {
QT_MOC_LITERAL(0, 0, 4),
QT_MOC_LITERAL(1, 5, 15),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 16),
QT_MOC_LITERAL(4, 39, 12),
QT_MOC_LITERAL(5, 52, 13),
QT_MOC_LITERAL(6, 66, 15),
QT_MOC_LITERAL(7, 82, 16),
QT_MOC_LITERAL(8, 99, 20),
QT_MOC_LITERAL(9, 120, 21),
QT_MOC_LITERAL(10, 142, 17),
QT_MOC_LITERAL(11, 160, 16),
QT_MOC_LITERAL(12, 177, 15),
QT_MOC_LITERAL(13, 193, 20),
QT_MOC_LITERAL(14, 214, 19),
QT_MOC_LITERAL(15, 234, 11),
QT_MOC_LITERAL(16, 246, 7),
QT_MOC_LITERAL(17, 254, 19),
QT_MOC_LITERAL(18, 274, 18),
QT_MOC_LITERAL(19, 293, 16),
QT_MOC_LITERAL(20, 310, 5),
QT_MOC_LITERAL(21, 316, 19),
QT_MOC_LITERAL(22, 336, 19),
QT_MOC_LITERAL(23, 356, 23),
QT_MOC_LITERAL(24, 380, 12),
QT_MOC_LITERAL(25, 393, 7),
QT_MOC_LITERAL(26, 401, 27)
    },
    "Live\0OnBtnOpenCamera\0\0OnBtnCloseCamera\0"
    "OnBtnOpenMic\0OnBtnCloseMic\0OnBtnOpenPlayer\0"
    "OnBtnClosePlayer\0OnBtnOpenScreenShare\0"
    "OnBtnCloseScreenShare\0OnBtnSendGroupMsg\0"
    "OnBtnStartRecord\0OnBtnStopRecord\0"
    "OnBtnStartPushStream\0OnBtnStopPushStream\0"
    "OnBtnPraise\0OnTimer\0OnRequestViewsTimer\0"
    "OnDelayUpdateTimer\0OnMemberListMenu\0"
    "point\0OnActInviteInteract\0OnActCancelInteract\0"
    "OnVideoRenderFullScreen\0VideoRender*\0"
    "pRender\0OnExitVideoRenderFullScreen\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Live[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  124,    2, 0x08,
       3,    0,  125,    2, 0x08,
       4,    0,  126,    2, 0x08,
       5,    0,  127,    2, 0x08,
       6,    0,  128,    2, 0x08,
       7,    0,  129,    2, 0x08,
       8,    0,  130,    2, 0x08,
       9,    0,  131,    2, 0x08,
      10,    0,  132,    2, 0x08,
      11,    0,  133,    2, 0x08,
      12,    0,  134,    2, 0x08,
      13,    0,  135,    2, 0x08,
      14,    0,  136,    2, 0x08,
      15,    0,  137,    2, 0x08,
      16,    0,  138,    2, 0x08,
      17,    0,  139,    2, 0x08,
      18,    0,  140,    2, 0x08,
      19,    1,  141,    2, 0x08,
      21,    0,  144,    2, 0x08,
      22,    0,  145,    2, 0x08,
      23,    1,  146,    2, 0x08,
      26,    1,  149,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void, 0x80000000 | 24,   25,

       0        // eod
};

void Live::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Live *_t = static_cast<Live *>(_o);
        switch (_id) {
        case 0: _t->OnBtnOpenCamera(); break;
        case 1: _t->OnBtnCloseCamera(); break;
        case 2: _t->OnBtnOpenMic(); break;
        case 3: _t->OnBtnCloseMic(); break;
        case 4: _t->OnBtnOpenPlayer(); break;
        case 5: _t->OnBtnClosePlayer(); break;
        case 6: _t->OnBtnOpenScreenShare(); break;
        case 7: _t->OnBtnCloseScreenShare(); break;
        case 8: _t->OnBtnSendGroupMsg(); break;
        case 9: _t->OnBtnStartRecord(); break;
        case 10: _t->OnBtnStopRecord(); break;
        case 11: _t->OnBtnStartPushStream(); break;
        case 12: _t->OnBtnStopPushStream(); break;
        case 13: _t->OnBtnPraise(); break;
        case 14: _t->OnTimer(); break;
        case 15: _t->OnRequestViewsTimer(); break;
        case 16: _t->OnDelayUpdateTimer(); break;
        case 17: _t->OnMemberListMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 18: _t->OnActInviteInteract(); break;
        case 19: _t->OnActCancelInteract(); break;
        case 20: _t->OnVideoRenderFullScreen((*reinterpret_cast< VideoRender*(*)>(_a[1]))); break;
        case 21: _t->OnExitVideoRenderFullScreen((*reinterpret_cast< VideoRender*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 20:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< VideoRender* >(); break;
            }
            break;
        case 21:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< VideoRender* >(); break;
            }
            break;
        }
    }
}

const QMetaObject Live::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Live.data,
      qt_meta_data_Live,  qt_static_metacall, 0, 0}
};


const QMetaObject *Live::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Live::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Live.stringdata))
        return static_cast<void*>(const_cast< Live*>(this));
    return QDialog::qt_metacast(_clname);
}

int Live::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
