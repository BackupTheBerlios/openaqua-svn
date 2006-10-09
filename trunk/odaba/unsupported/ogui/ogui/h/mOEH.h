/****************************************************************************
** Meta object code from reading C++ file 'sOEH.hpp'
**
** Created: So 27. Aug 20:56:50 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOEH.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOEH.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OEH[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      13,    4,    5,    4, 0x0a,
      40,   28,    5,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OEH[] = {
    "OEH\0\0logical\0xx_doClicked()\0pQObject,id\0xx_doClicked(QObject*,int)\0"
};

const QMetaObject OEH::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OEH,
      qt_meta_data_OEH, 0 }
};

const QMetaObject *OEH::metaObject() const
{
    return &staticMetaObject;
}

void *OEH::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OEH))
	return static_cast<void*>(const_cast<OEH*>(this));
    return QObject::qt_metacast(_clname);
}

int OEH::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { logical _r = xx_doClicked();
            if (_a[0]) *reinterpret_cast< logical*>(_a[0]) = _r; }  break;
        case 1: { logical _r = xx_doClicked((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< logical*>(_a[0]) = _r; }  break;
        }
        _id -= 2;
    }
    return _id;
}
