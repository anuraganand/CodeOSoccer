/****************************************************************************
** Meta object code from reading C++ file 'robotwidget.h'
**
** Created: Mon Oct 15 09:49:14 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../robotwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'robotwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RobotWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   13,   12,   12, 0x0a,
      42,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RobotWidget[] = {
    "RobotWidget\0\0,\0changeRobotOnOff(int,bool)\0"
    "setPoseBtnClicked()\0"
};

void RobotWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RobotWidget *_t = static_cast<RobotWidget *>(_o);
        switch (_id) {
        case 0: _t->changeRobotOnOff((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->setPoseBtnClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RobotWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RobotWidget::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_RobotWidget,
      qt_meta_data_RobotWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RobotWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RobotWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RobotWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RobotWidget))
        return static_cast<void*>(const_cast< RobotWidget*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int RobotWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
