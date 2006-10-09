/****************************************************************************
** Meta object code from reading C++ file 'sOTableView.hpp'
**
** Created: So 27. Aug 21:00:13 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOTableView.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOTableView.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OTableView[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      22,   12,   11,   11, 0x0a,
      76,   53,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OTableView[] = {
    "OTableView\0\0pItemData\0OnCurrentRowChanged(ItemData*)\0"
    "qt_current,qt_previous\0currentChanged(QModelIndex,QModelIndex)\0"
};

const QMetaObject OTableView::staticMetaObject = {
    { &QTableView::staticMetaObject, qt_meta_stringdata_OTableView,
      qt_meta_data_OTableView, 0 }
};

const QMetaObject *OTableView::metaObject() const
{
    return &staticMetaObject;
}

void *OTableView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OTableView))
	return static_cast<void*>(const_cast<OTableView*>(this));
    if (!strcmp(_clname, "OListCtl"))
	return static_cast<OListCtl*>(const_cast<OTableView*>(this));
    return QTableView::qt_metacast(_clname);
}

int OTableView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnCurrentRowChanged((*reinterpret_cast< ItemData*(*)>(_a[1]))); break;
        case 1: currentChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        }
        _id -= 2;
    }
    return _id;
}
