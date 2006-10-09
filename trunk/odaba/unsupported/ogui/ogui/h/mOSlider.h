/****************************************************************************
** Meta object code from reading C++ file 'sOSlider.hpp'
**
** Created: So 27. Aug 20:59:40 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOSlider.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOSlider.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OSlider[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OSlider[] = {
    "OSlider\0\0storeToValue()\0"
};

const QMetaObject OSlider::staticMetaObject = {
    { &QSlider::staticMetaObject, qt_meta_stringdata_OSlider,
      qt_meta_data_OSlider, 0 }
};

const QMetaObject *OSlider::metaObject() const
{
    return &staticMetaObject;
}

void *OSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OSlider))
	return static_cast<void*>(const_cast<OSlider*>(this));
    if (!strcmp(_clname, "OEHControlValue"))
	return static_cast<OEHControlValue*>(const_cast<OSlider*>(this));
    return QSlider::qt_metacast(_clname);
}

int OSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSlider::qt_metacall(_c, _id, _a);
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
