/****************************************************************************
** Meta object code from reading C++ file 'sFAssociate.hpp'
**
** Created: So 27. Aug 20:54:05 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sFAssociate.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sFAssociate.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_FAssociate[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      24,   12,   11,   11, 0x0a,
      48,   11,   11,   11, 0x08,
      63,   57,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FAssociate[] = {
    "FAssociate\0\0model_index\0ToggleItem(QModelIndex)\0accept()\0pterm\0"
    "slotHideAssociated(logical*)\0"
};

const QMetaObject FAssociate::staticMetaObject = {
    { &ODialog::staticMetaObject, qt_meta_stringdata_FAssociate,
      qt_meta_data_FAssociate, 0 }
};

const QMetaObject *FAssociate::metaObject() const
{
    return &staticMetaObject;
}

void *FAssociate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FAssociate))
	return static_cast<void*>(const_cast<FAssociate*>(this));
    return ODialog::qt_metacast(_clname);
}

int FAssociate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ODialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ToggleItem((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: accept(); break;
        case 2: slotHideAssociated((*reinterpret_cast< logical*(*)>(_a[1]))); break;
        }
        _id -= 3;
    }
    return _id;
}
