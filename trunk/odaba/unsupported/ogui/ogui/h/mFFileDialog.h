/****************************************************************************
** Meta object code from reading C++ file 'sFFileDialog.hpp'
**
** Created: So 27. Aug 20:54:08 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sFFileDialog.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sFFileDialog.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_FFileDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_FFileDialog[] = {
    "FFileDialog\0"
};

const QMetaObject FFileDialog::staticMetaObject = {
    { &QFileDialog::staticMetaObject, qt_meta_stringdata_FFileDialog,
      qt_meta_data_FFileDialog, 0 }
};

const QMetaObject *FFileDialog::metaObject() const
{
    return &staticMetaObject;
}

void *FFileDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FFileDialog))
	return static_cast<void*>(const_cast<FFileDialog*>(this));
    if (!strcmp(_clname, "OEHDataWidget"))
	return static_cast<OEHDataWidget*>(const_cast<FFileDialog*>(this));
    return QFileDialog::qt_metacast(_clname);
}

int FFileDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFileDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
