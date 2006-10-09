/****************************************************************************
** Meta object code from reading C++ file 'sODSTree.hpp'
**
** Created: So 27. Aug 20:55:52 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sODSTree.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sODSTree.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_ODSTree[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      15,    9,    8,    8, 0x05,
      42,    9,    8,    8, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ODSTree[] = {
    "ODSTree\0\0pterm\0OnBeforeDataFill(logical*)\0OnBeforeDataSet(logical*)\0"
};

const QMetaObject ODSTree::staticMetaObject = {
    { &ODSRegion::staticMetaObject, qt_meta_stringdata_ODSTree,
      qt_meta_data_ODSTree, 0 }
};

const QMetaObject *ODSTree::metaObject() const
{
    return &staticMetaObject;
}

void *ODSTree::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ODSTree))
	return static_cast<void*>(const_cast<ODSTree*>(this));
    return ODSRegion::qt_metacast(_clname);
}

int ODSTree::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ODSRegion::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnBeforeDataFill((*reinterpret_cast< logical*(*)>(_a[1]))); break;
        case 1: OnBeforeDataSet((*reinterpret_cast< logical*(*)>(_a[1]))); break;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ODSTree::OnBeforeDataFill(logical * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ODSTree::OnBeforeDataSet(logical * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
