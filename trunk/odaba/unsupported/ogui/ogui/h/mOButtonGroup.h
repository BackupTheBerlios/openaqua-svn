/****************************************************************************
** Meta object code from reading C++ file 'sOButtonGroup.hpp'
**
** Created: So 27. Aug 20:54:45 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOButtonGroup.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOButtonGroup.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OButtonGroup[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_OButtonGroup[] = {
    "OButtonGroup\0"
};

const QMetaObject OButtonGroup::staticMetaObject = {
    { &QButtonGroup::staticMetaObject, qt_meta_stringdata_OButtonGroup,
      qt_meta_data_OButtonGroup, 0 }
};

const QMetaObject *OButtonGroup::metaObject() const
{
    return &staticMetaObject;
}

void *OButtonGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OButtonGroup))
	return static_cast<void*>(const_cast<OButtonGroup*>(this));
    if (!strcmp(_clname, "ODataWidget"))
	return static_cast<ODataWidget*>(const_cast<OButtonGroup*>(this));
    return QButtonGroup::qt_metacast(_clname);
}

int OButtonGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QButtonGroup::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
