/****************************************************************************
** Meta object code from reading C++ file 'sOFixedText.hpp'
**
** Created: So 27. Aug 20:57:58 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOFixedText.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOFixedText.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OFixedText[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      24,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_OFixedText[] = {
    "OFixedText\0\0ClearData()\0FillData()\0"
};

const QMetaObject OFixedText::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_OFixedText,
      qt_meta_data_OFixedText, 0 }
};

const QMetaObject *OFixedText::metaObject() const
{
    return &staticMetaObject;
}

void *OFixedText::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OFixedText))
	return static_cast<void*>(const_cast<OFixedText*>(this));
    if (!strcmp(_clname, "OEHControlValue"))
	return static_cast<OEHControlValue*>(const_cast<OFixedText*>(this));
    return QLabel::qt_metacast(_clname);
}

int OFixedText::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ClearData(); break;
        case 1: FillData(); break;
        }
        _id -= 2;
    }
    return _id;
}
