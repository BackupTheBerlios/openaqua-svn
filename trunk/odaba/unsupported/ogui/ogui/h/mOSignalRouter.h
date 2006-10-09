/****************************************************************************
** Meta object code from reading C++ file 'sOSignalRouter.hpp'
**
** Created: So 27. Aug 20:59:30 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOSignalRouter.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOSignalRouter.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OSignalRouter[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_OSignalRouter[] = {
    "OSignalRouter\0\0Fire()\0"
};

const QMetaObject OSignalRouter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OSignalRouter,
      qt_meta_data_OSignalRouter, 0 }
};

const QMetaObject *OSignalRouter::metaObject() const
{
    return &staticMetaObject;
}

void *OSignalRouter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OSignalRouter))
	return static_cast<void*>(const_cast<OSignalRouter*>(this));
    return QObject::qt_metacast(_clname);
}

int OSignalRouter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Fire(); break;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void OSignalRouter::Fire()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
