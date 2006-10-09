/****************************************************************************
** Meta object code from reading C++ file 'sOPushButton.hpp'
**
** Created: So 27. Aug 20:59:17 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOPushButton.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOPushButton.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OPushButton[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      21,   12,   13,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OPushButton[] = {
    "OPushButton\0\0logical\0doClicked()\0"
};

const QMetaObject OPushButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_OPushButton,
      qt_meta_data_OPushButton, 0 }
};

const QMetaObject *OPushButton::metaObject() const
{
    return &staticMetaObject;
}

void *OPushButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OPushButton))
	return static_cast<void*>(const_cast<OPushButton*>(this));
    if (!strcmp(_clname, "ODataWidget"))
	return static_cast<ODataWidget*>(const_cast<OPushButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int OPushButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { logical _r = doClicked();
            if (_a[0]) *reinterpret_cast< logical*>(_a[0]) = _r; }  break;
        }
        _id -= 1;
    }
    return _id;
}
