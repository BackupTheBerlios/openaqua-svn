/****************************************************************************
** Meta object code from reading C++ file 'sOTimeEdit.hpp'
**
** Created: So 27. Aug 21:00:17 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOTimeEdit.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOTimeEdit.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OTimeEdit[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      23,   10,   10,   10, 0x0a,
      34,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OTimeEdit[] = {
    "OTimeEdit\0\0ClearData()\0FillData()\0storeToValue()\0"
};

const QMetaObject OTimeEdit::staticMetaObject = {
    { &QTimeEdit::staticMetaObject, qt_meta_stringdata_OTimeEdit,
      qt_meta_data_OTimeEdit, 0 }
};

const QMetaObject *OTimeEdit::metaObject() const
{
    return &staticMetaObject;
}

void *OTimeEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OTimeEdit))
	return static_cast<void*>(const_cast<OTimeEdit*>(this));
    if (!strcmp(_clname, "OEHControlValue"))
	return static_cast<OEHControlValue*>(const_cast<OTimeEdit*>(this));
    return QTimeEdit::qt_metacast(_clname);
}

int OTimeEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTimeEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ClearData(); break;
        case 1: FillData(); break;
        case 2: storeToValue(); break;
        }
        _id -= 3;
    }
    return _id;
}
