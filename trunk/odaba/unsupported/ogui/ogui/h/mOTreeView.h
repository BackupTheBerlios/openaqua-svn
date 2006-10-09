/****************************************************************************
** Meta object code from reading C++ file 'sOTreeView.hpp'
**
** Created: So 27. Aug 21:00:34 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOTreeView.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOTreeView.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OTreeView[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      21,   11,   10,   10, 0x0a,
      75,   52,   10,   10, 0x0a,
     147,  115,   10,   10, 0x0a,
     201,  189,   10,   10, 0x0a,
     232,  189,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OTreeView[] = {
    "OTreeView\0\0pItemData\0OnCurrentRowChanged(ItemData*)\0"
    "qt_current,qt_previous\0currentChanged(QModelIndex,QModelIndex)\0"
    "mi_parent,start_index,end_index\0"
    "rowsAboutToBeRemoved(QModelIndex,int,int)\0model_index\0"
    "slotItemCollapsed(QModelIndex)\0slotItemExpanded(QModelIndex)\0"
};

const QMetaObject OTreeView::staticMetaObject = {
    { &QTreeView::staticMetaObject, qt_meta_stringdata_OTreeView,
      qt_meta_data_OTreeView, 0 }
};

const QMetaObject *OTreeView::metaObject() const
{
    return &staticMetaObject;
}

void *OTreeView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OTreeView))
	return static_cast<void*>(const_cast<OTreeView*>(this));
    if (!strcmp(_clname, "OListCtl"))
	return static_cast<OListCtl*>(const_cast<OTreeView*>(this));
    return QTreeView::qt_metacast(_clname);
}

int OTreeView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnCurrentRowChanged((*reinterpret_cast< ItemData*(*)>(_a[1]))); break;
        case 1: currentChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 2: rowsAboutToBeRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: slotItemCollapsed((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: slotItemExpanded((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        }
        _id -= 5;
    }
    return _id;
}
