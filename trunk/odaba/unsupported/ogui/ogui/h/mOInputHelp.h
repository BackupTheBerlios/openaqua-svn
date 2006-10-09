/****************************************************************************
** Meta object code from reading C++ file 'sOInputHelp.hpp'
**
** Created: So 27. Aug 20:58:26 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOInputHelp.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOInputHelp.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OInputHelp[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_OInputHelp[] = {
    "OInputHelp\0"
};

const QMetaObject OInputHelp::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OInputHelp,
      qt_meta_data_OInputHelp, 0 }
};

const QMetaObject *OInputHelp::metaObject() const
{
    return &staticMetaObject;
}

void *OInputHelp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OInputHelp))
	return static_cast<void*>(const_cast<OInputHelp*>(this));
    if (!strcmp(_clname, "ODataWidget"))
	return static_cast<ODataWidget*>(const_cast<OInputHelp*>(this));
    return QObject::qt_metacast(_clname);
}

int OInputHelp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
