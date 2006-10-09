/****************************************************************************
** Meta object code from reading C++ file 'sOSplitter.hpp'
**
** Created: So 27. Aug 20:59:57 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sOSplitter.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sOSplitter.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_OSplitter[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      28,   10,   10,   10, 0x0a,
      40,   10,   10,   10, 0x0a,
      52,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OSplitter[] = {
    "OSplitter\0\0activateHandle()\0loadValue()\0openValue()\0resizeEvent()\0"
};

const QMetaObject OSplitter::staticMetaObject = {
    { &QSplitter::staticMetaObject, qt_meta_stringdata_OSplitter,
      qt_meta_data_OSplitter, 0 }
};

const QMetaObject *OSplitter::metaObject() const
{
    return &staticMetaObject;
}

void *OSplitter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OSplitter))
	return static_cast<void*>(const_cast<OSplitter*>(this));
    if (!strcmp(_clname, "OEHDataWidget"))
	return static_cast<OEHDataWidget*>(const_cast<OSplitter*>(this));
    return QSplitter::qt_metacast(_clname);
}

int OSplitter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSplitter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: activateHandle(); break;
        case 1: loadValue(); break;
        case 2: openValue(); break;
        case 3: resizeEvent(); break;
        }
        _id -= 4;
    }
    return _id;
}
