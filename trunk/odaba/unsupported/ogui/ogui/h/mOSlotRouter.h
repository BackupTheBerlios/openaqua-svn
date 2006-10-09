/****************************************************************************
** Meta object code from reading C++ file 'sOSlotRouter.hpp'
**
** Created: So 27. Aug 20:59:44 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOSlotRouter.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOSlotRouter.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OSlotRouter[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OSlotRouter[] = {
    "OSlotRouter\0\0xFire()\0"
};

const QMetaObject OSlotRouter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OSlotRouter,
      qt_meta_data_OSlotRouter, 0 }
};

const QMetaObject *OSlotRouter::metaObject() const
{
    return &staticMetaObject;
}

void *OSlotRouter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OSlotRouter))
	return static_cast<void*>(const_cast<OSlotRouter*>(this));
    return QObject::qt_metacast(_clname);
}

int OSlotRouter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: xFire(); break;
        }
        _id -= 1;
    }
    return _id;
}
