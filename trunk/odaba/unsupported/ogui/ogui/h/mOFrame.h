/****************************************************************************
** Meta object code from reading C++ file 'sOFrame.hpp'
**
** Created: So 27. Aug 20:58:04 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOFrame.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOFrame.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OFrame[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OFrame[] = {
    "OFrame\0\0FillData()\0"
};

const QMetaObject OFrame::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_OFrame,
      qt_meta_data_OFrame, 0 }
};

const QMetaObject *OFrame::metaObject() const
{
    return &staticMetaObject;
}

void *OFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OFrame))
	return static_cast<void*>(const_cast<OFrame*>(this));
    if (!strcmp(_clname, "OEHControlValue"))
	return static_cast<OEHControlValue*>(const_cast<OFrame*>(this));
    return QFrame::qt_metacast(_clname);
}

int OFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: FillData(); break;
        }
        _id -= 1;
    }
    return _id;
}
