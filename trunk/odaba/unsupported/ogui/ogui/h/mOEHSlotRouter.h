/****************************************************************************
** Meta object code from reading C++ file 'sOEHSlotRouter.hpp'
**
** Created: So 27. Aug 20:57:51 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOEHSlotRouter.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOEHSlotRouter.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OEHSlotRouter[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      22,   15,   14,   14, 0x0a,
      50,   14,   14,   14, 0x0a,
      67,   14,   14,   14, 0x0a,
      81,   14,   14,   14, 0x0a,
      94,   14,   14,   14, 0x0a,
     107,   14,   14,   14, 0x0a,
     119,   14,   14,   14, 0x0a,
     132,   14,   14,   14, 0x0a,
     146,   14,   14,   14, 0x0a,
     160,   14,   14,   14, 0x0a,
     173,   14,   14,   14, 0x0a,
     187,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OEHSlotRouter[] = {
    "OEHSlotRouter\0\0fDmode\0activateDesignMode(logical)\0handleActivate()\0"
    "handleClose()\0handleOpen()\0listChange()\0listReset()\0listUpdate()\0"
    "valueInsert()\0valueRemove()\0valueReset()\0valueSelect()\0"
    "valueUpdate()\0"
};

const QMetaObject OEHSlotRouter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OEHSlotRouter,
      qt_meta_data_OEHSlotRouter, 0 }
};

const QMetaObject *OEHSlotRouter::metaObject() const
{
    return &staticMetaObject;
}

void *OEHSlotRouter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OEHSlotRouter))
	return static_cast<void*>(const_cast<OEHSlotRouter*>(this));
    return QObject::qt_metacast(_clname);
}

int OEHSlotRouter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: activateDesignMode((*reinterpret_cast< logical(*)>(_a[1]))); break;
        case 1: handleActivate(); break;
        case 2: handleClose(); break;
        case 3: handleOpen(); break;
        case 4: listChange(); break;
        case 5: listReset(); break;
        case 6: listUpdate(); break;
        case 7: valueInsert(); break;
        case 8: valueRemove(); break;
        case 9: valueReset(); break;
        case 10: valueSelect(); break;
        case 11: valueUpdate(); break;
        }
        _id -= 12;
    }
    return _id;
}
