/****************************************************************************
** Meta object code from reading C++ file 'sOListBox.hpp'
**
** Created: Tue 20. Jun 12:50:22 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOListBox.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOListBox.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OListBox[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      27,   10,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OListBox[] = {
    "OListBox\0\0pQListWidgetItem\0doCurrentChanged(QListWidgetItem*)\0"
};

const QMetaObject OListBox::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata_OListBox,
      qt_meta_data_OListBox, 0 }
};

const QMetaObject *OListBox::metaObject() const
{
    return &staticMetaObject;
}

void *OListBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OListBox))
	return static_cast<void*>(const_cast<OListBox*>(this));
    if (!strcmp(_clname, "OListCtl"))
	return static_cast<OListCtl*>(const_cast<OListBox*>(this));
    return QListWidget::qt_metacast(_clname);
}

int OListBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: doCurrentChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
