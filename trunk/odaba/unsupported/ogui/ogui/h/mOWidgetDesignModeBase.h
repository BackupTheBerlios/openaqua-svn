/****************************************************************************
** Meta object code from reading C++ file 'sOWidgetDesignModeBase.hpp'
**
** Created: So 27. Aug 21:00:49 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOWidgetDesignModeBase.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOWidgetDesignModeBase.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OWidgetDesignModeBase[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_OWidgetDesignModeBase[] = {
    "OWidgetDesignModeBase\0"
};

const QMetaObject OWidgetDesignModeBase::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OWidgetDesignModeBase,
      qt_meta_data_OWidgetDesignModeBase, 0 }
};

const QMetaObject *OWidgetDesignModeBase::metaObject() const
{
    return &staticMetaObject;
}

void *OWidgetDesignModeBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OWidgetDesignModeBase))
	return static_cast<void*>(const_cast<OWidgetDesignModeBase*>(this));
    return QObject::qt_metacast(_clname);
}

int OWidgetDesignModeBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
