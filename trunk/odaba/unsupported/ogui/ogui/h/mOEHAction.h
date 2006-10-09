/****************************************************************************
** Meta object code from reading C++ file 'sOEHAction.hpp'
**
** Created: So 27. Aug 20:56:53 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOEHAction.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOEHAction.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OEHAction[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      28,   19,   11,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OEHAction[] = {
    "OEHAction\0\0logical\0bChecked\0doTriggered(bool)\0"
};

const QMetaObject OEHAction::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OEHAction,
      qt_meta_data_OEHAction, 0 }
};

const QMetaObject *OEHAction::metaObject() const
{
    return &staticMetaObject;
}

void *OEHAction::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OEHAction))
	return static_cast<void*>(const_cast<OEHAction*>(this));
    return QObject::qt_metacast(_clname);
}

int OEHAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { logical _r = doTriggered((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< logical*>(_a[0]) = _r; }  break;
        }
        _id -= 1;
    }
    return _id;
}
