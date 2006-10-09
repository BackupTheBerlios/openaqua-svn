/****************************************************************************
** Meta object code from reading C++ file 'sODateEdit.hpp'
**
** Created: So 27. Aug 20:56:18 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sODateEdit.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sODateEdit.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_ODateEdit[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      23,   10,   10,   10, 0x08,
      34,   10,   10,   10, 0x08,
      50,   45,   10,   10, 0x08,
      70,   63,   10,   10, 0x08,
      85,   10,   10,   10, 0x08,
     101,   10,   10,   10, 0x08,
     124,  117,   10,   10, 0x08,
     146,  140,   10,   10, 0x08,
     160,   10,   10,   10, 0x0a,
     172,   10,   10,   10, 0x0a,
     190,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ODateEdit[] = {
    "ODateEdit\0\0ClearData()\0FillData()\0pickDate()\0iDay\0pickDay(int)\0"
    "iMonth\0pickMonth(int)\0pickNextMonth()\0pickPrevMonth()\0iDelta\0"
    "pickScroll(int)\0iYear\0pickYear(int)\0resetDate()\0slotContextMenu()\0"
    "storeToValue()\0"
};

const QMetaObject ODateEdit::staticMetaObject = {
    { &QDateEdit::staticMetaObject, qt_meta_stringdata_ODateEdit,
      qt_meta_data_ODateEdit, 0 }
};

const QMetaObject *ODateEdit::metaObject() const
{
    return &staticMetaObject;
}

void *ODateEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ODateEdit))
	return static_cast<void*>(const_cast<ODateEdit*>(this));
    if (!strcmp(_clname, "OEHControlValue"))
	return static_cast<OEHControlValue*>(const_cast<ODateEdit*>(this));
    return QDateEdit::qt_metacast(_clname);
}

int ODateEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDateEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ClearData(); break;
        case 1: FillData(); break;
        case 2: pickDate(); break;
        case 3: pickDay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: pickMonth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: pickNextMonth(); break;
        case 6: pickPrevMonth(); break;
        case 7: pickScroll((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: pickYear((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: resetDate(); break;
        case 10: slotContextMenu(); break;
        case 11: storeToValue(); break;
        }
        _id -= 12;
    }
    return _id;
}
