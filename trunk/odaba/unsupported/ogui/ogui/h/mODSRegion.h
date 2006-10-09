/****************************************************************************
** Meta object code from reading C++ file 'sODSRegion.hpp'
**
** Created: So 27. Aug 20:55:49 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sODSRegion.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sODSRegion.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_ODSRegion[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      35,   10,   10,   10, 0x0a,
      57,   10,   10,   10, 0x0a,
      80,   10,   10,   10, 0x0a,
     102,   10,   10,   10, 0x0a,
     125,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ODSRegion[] = {
    "ODSRegion\0\0slotCollectionChanged()\0slotCollectionReset()\0"
    "slotInstanceInserted()\0slotInstanceRemoved()\0slotInstanceSelected()\0"
    "slotInstanceUpdated()\0"
};

const QMetaObject ODSRegion::staticMetaObject = {
    { &ODSList::staticMetaObject, qt_meta_stringdata_ODSRegion,
      qt_meta_data_ODSRegion, 0 }
};

const QMetaObject *ODSRegion::metaObject() const
{
    return &staticMetaObject;
}

void *ODSRegion::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ODSRegion))
	return static_cast<void*>(const_cast<ODSRegion*>(this));
    return ODSList::qt_metacast(_clname);
}

int ODSRegion::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ODSList::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotCollectionChanged(); break;
        case 1: slotCollectionReset(); break;
        case 2: slotInstanceInserted(); break;
        case 3: slotInstanceRemoved(); break;
        case 4: slotInstanceSelected(); break;
        case 5: slotInstanceUpdated(); break;
        }
        _id -= 6;
    }
    return _id;
}
