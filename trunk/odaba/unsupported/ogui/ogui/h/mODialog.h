/****************************************************************************
** Meta object code from reading C++ file 'sODialog.hpp'
**
** Created: So 27. Aug 20:56:31 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sODialog.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sODialog.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_ODialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      18,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ODialog[] = {
    "ODialog\0\0accept()\0reject()\0"
};

const QMetaObject ODialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ODialog,
      qt_meta_data_ODialog, 0 }
};

const QMetaObject *ODialog::metaObject() const
{
    return &staticMetaObject;
}

void *ODialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ODialog))
	return static_cast<void*>(const_cast<ODialog*>(this));
    if (!strcmp(_clname, "OEHDataWidget"))
	return static_cast<OEHDataWidget*>(const_cast<ODialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ODialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: accept(); break;
        case 1: reject(); break;
        }
        _id -= 2;
    }
    return _id;
}
