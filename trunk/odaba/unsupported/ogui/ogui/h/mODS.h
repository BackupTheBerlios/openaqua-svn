/****************************************************************************
** Meta object code from reading C++ file 'sODS.hpp'
**
** Created: Tue Aug 29 18:49:03 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sODS.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sODS.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_ODS[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      16,    5,    4,    4, 0x05,
      37,    4,    4,    4, 0x05,
      60,   54,    4,    4, 0x05,
      90,   86,    4,    4, 0x05,
     126,  116,    4,    4, 0x05,
     150,    4,    4,    4, 0x05,
     172,    4,    4,    4, 0x05,
     192,    4,    4,    4, 0x05,
     221,  214,    4,    4, 0x05,
     252,    4,    4,    4, 0x05,
     269,    4,    4,    4, 0x05,
     286,    4,    4,    4, 0x05,
     307,    4,    4,    4, 0x05,
     327,    4,    4,    4, 0x05,
     345,    4,    4,    4, 0x05,
     366,    4,    4,    4, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ODS[] = {
    "ODS\0\0fActivated\0OnActivated(logical)\0OnAfterDataSet()\0pterm\0"
    "OnBeforeDataSet(logical*)\0lID\0OnBlockInstChanged(int32)\0block_opt\0"
    "OnBlockSignals(logical)\0OnCollectionChanged()\0OnCollectionReset()\0"
    "OnCollectionUpdated()\0fDmode\0OnDesignModeActivated(logical)\0"
    "OnHandleClosed()\0OnHandleOpened()\0OnInstanceInserted()\0"
    "OnInstanceRemoved()\0OnInstanceReset()\0OnInstanceSelected()\0"
    "OnInstanceUpdated()\0"
};

const QMetaObject ODS::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ODS,
      qt_meta_data_ODS, 0 }
};

const QMetaObject *ODS::metaObject() const
{
    return &staticMetaObject;
}

void *ODS::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ODS))
	return static_cast<void*>(const_cast<ODS*>(this));
    if (!strcmp(_clname, "ODSItemState"))
	return static_cast<ODSItemState*>(const_cast<ODS*>(this));
    return QObject::qt_metacast(_clname);
}

int ODS::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnActivated((*reinterpret_cast< logical(*)>(_a[1]))); break;
        case 1: OnAfterDataSet(); break;
        case 2: OnBeforeDataSet((*reinterpret_cast< logical*(*)>(_a[1]))); break;
        case 3: OnBlockInstChanged((*reinterpret_cast< int32(*)>(_a[1]))); break;
        case 4: OnBlockSignals((*reinterpret_cast< logical(*)>(_a[1]))); break;
        case 5: OnCollectionChanged(); break;
        case 6: OnCollectionReset(); break;
        case 7: OnCollectionUpdated(); break;
        case 8: OnDesignModeActivated((*reinterpret_cast< logical(*)>(_a[1]))); break;
        case 9: OnHandleClosed(); break;
        case 10: OnHandleOpened(); break;
        case 11: OnInstanceInserted(); break;
        case 12: OnInstanceRemoved(); break;
        case 13: OnInstanceReset(); break;
        case 14: OnInstanceSelected(); break;
        case 15: OnInstanceUpdated(); break;
        }
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void ODS::OnActivated(logical _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ODS::OnAfterDataSet()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ODS::OnBeforeDataSet(logical * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ODS::OnBlockInstChanged(int32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ODS::OnBlockSignals(logical _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ODS::OnCollectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void ODS::OnCollectionReset()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void ODS::OnCollectionUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void ODS::OnDesignModeActivated(logical _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ODS::OnHandleClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}

// SIGNAL 10
void ODS::OnHandleOpened()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}

// SIGNAL 11
void ODS::OnInstanceInserted()
{
    QMetaObject::activate(this, &staticMetaObject, 11, 0);
}

// SIGNAL 12
void ODS::OnInstanceRemoved()
{
    QMetaObject::activate(this, &staticMetaObject, 12, 0);
}

// SIGNAL 13
void ODS::OnInstanceReset()
{
    QMetaObject::activate(this, &staticMetaObject, 13, 0);
}

// SIGNAL 14
void ODS::OnInstanceSelected()
{
    QMetaObject::activate(this, &staticMetaObject, 14, 0);
}

// SIGNAL 15
void ODS::OnInstanceUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 15, 0);
}
