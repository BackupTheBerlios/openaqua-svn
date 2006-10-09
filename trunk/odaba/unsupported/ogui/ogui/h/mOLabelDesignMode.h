/****************************************************************************
** Meta object code from reading C++ file 'sOLabelDesignMode.hpp'
**
** Created: So 27. Aug 20:58:40 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOLabelDesignMode.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOLabelDesignMode.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OLabelDesignMode[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OLabelDesignMode[] = {
    "OLabelDesignMode\0\0CMChangeText()\0"
};

const QMetaObject OLabelDesignMode::staticMetaObject = {
    { &OWidgetDesignMode::staticMetaObject, qt_meta_stringdata_OLabelDesignMode,
      qt_meta_data_OLabelDesignMode, 0 }
};

const QMetaObject *OLabelDesignMode::metaObject() const
{
    return &staticMetaObject;
}

void *OLabelDesignMode::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OLabelDesignMode))
	return static_cast<void*>(const_cast<OLabelDesignMode*>(this));
    return OWidgetDesignMode::qt_metacast(_clname);
}

int OLabelDesignMode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = OWidgetDesignMode::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: CMChangeText(); break;
        }
        _id -= 1;
    }
    return _id;
}
