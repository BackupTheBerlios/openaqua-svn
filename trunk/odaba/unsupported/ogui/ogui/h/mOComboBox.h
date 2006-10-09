/****************************************************************************
** Meta object code from reading C++ file 'sOComboBox.hpp'
**
** Created: So 27. Aug 20:54:52 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOComboBox.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOComboBox.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OComboBox[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      23,   10,   10,   10, 0x08,
      34,   10,   10,   10, 0x08,
      45,   10,   10,   10, 0x0a,
      66,   10,   10,   10, 0x0a,
      85,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_OComboBox[] = {
    "OComboBox\0\0ClearData()\0FillData()\0FillList()\0ListCurrentChanged()\0"
    "SelectionChanged()\0storeToValue()\0"
};

const QMetaObject OComboBox::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_OComboBox,
      qt_meta_data_OComboBox, 0 }
};

const QMetaObject *OComboBox::metaObject() const
{
    return &staticMetaObject;
}

void *OComboBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OComboBox))
	return static_cast<void*>(const_cast<OComboBox*>(this));
    if (!strcmp(_clname, "OEHControlListValue"))
	return static_cast<OEHControlListValue*>(const_cast<OComboBox*>(this));
    return QComboBox::qt_metacast(_clname);
}

int OComboBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ClearData(); break;
        case 1: FillData(); break;
        case 2: FillList(); break;
        case 3: ListCurrentChanged(); break;
        case 4: SelectionChanged(); break;
        case 5: storeToValue(); break;
        }
        _id -= 6;
    }
    return _id;
}
