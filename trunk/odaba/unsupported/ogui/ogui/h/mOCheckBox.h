/****************************************************************************
** Meta object code from reading C++ file 'sOCheckBox.hpp'
**
** Created: So 27. Aug 20:54:48 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOCheckBox.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOCheckBox.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OCheckBox[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_OCheckBox[] = {
    "OCheckBox\0\0storeToValue()\0"
};

const QMetaObject OCheckBox::staticMetaObject = {
    { &QCheckBox::staticMetaObject, qt_meta_stringdata_OCheckBox,
      qt_meta_data_OCheckBox, 0 }
};

const QMetaObject *OCheckBox::metaObject() const
{
    return &staticMetaObject;
}

void *OCheckBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OCheckBox))
	return static_cast<void*>(const_cast<OCheckBox*>(this));
    if (!strcmp(_clname, "OEHControlValue"))
	return static_cast<OEHControlValue*>(const_cast<OCheckBox*>(this));
    return QCheckBox::qt_metacast(_clname);
}

int OCheckBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCheckBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: storeToValue(); break;
        }
        _id -= 1;
    }
    return _id;
}
