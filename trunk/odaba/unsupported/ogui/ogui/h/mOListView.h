/****************************************************************************
** Meta object code from reading C++ file 'sOListView.hpp'
**
** Created: So 27. Aug 20:58:50 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOListView.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOListView.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OListView[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      21,   11,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      75,   52,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OListView[] = {
    "OListView\0\0pItemData\0OnCurrentRowChanged(ItemData*)\0"
    "qt_current,qt_previous\0currentChanged(QModelIndex,QModelIndex)\0"
};

const QMetaObject OListView::staticMetaObject = {
    { &QListView::staticMetaObject, qt_meta_stringdata_OListView,
      qt_meta_data_OListView, 0 }
};

const QMetaObject *OListView::metaObject() const
{
    return &staticMetaObject;
}

void *OListView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OListView))
	return static_cast<void*>(const_cast<OListView*>(this));
    if (!strcmp(_clname, "OListCtl"))
	return static_cast<OListCtl*>(const_cast<OListView*>(this));
    return QListView::qt_metacast(_clname);
}

int OListView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListView::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void OListView::OnCurrentRowChanged(ItemData * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
