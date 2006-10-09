/****************************************************************************
** Meta object code from reading C++ file 'sOComboListBox.hpp'
**
** Created: So 27. Aug 20:54:58 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOComboListBox.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOComboListBox.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OComboListBox[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      35,   26,   14,   14, 0x08,
      70,   60,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OComboListBox[] = {
    "OComboListBox\0\0FillList()\0rcqsText\0editTextChanged(QString)\0"
    "pItemData\0updateValue(ItemData*)\0"
};

const QMetaObject OComboListBox::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_OComboListBox,
      qt_meta_data_OComboListBox, 0 }
};

const QMetaObject *OComboListBox::metaObject() const
{
    return &staticMetaObject;
}

void *OComboListBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OComboListBox))
	return static_cast<void*>(const_cast<OComboListBox*>(this));
    if (!strcmp(_clname, "OEHControlListValue"))
	return static_cast<OEHControlListValue*>(const_cast<OComboListBox*>(this));
    return QWidget::qt_metacast(_clname);
}

int OComboListBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: FillList(); break;
        case 1: editTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: updateValue((*reinterpret_cast< ItemData*(*)>(_a[1]))); break;
        }
        _id -= 3;
    }
    return _id;
}
