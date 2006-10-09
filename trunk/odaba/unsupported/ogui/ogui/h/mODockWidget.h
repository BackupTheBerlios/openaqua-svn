/****************************************************************************
** Meta object code from reading C++ file 'sODockWidget.hpp'
**
** Created: So 27. Aug 20:56:37 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sODockWidget.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sODockWidget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_ODockWidget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      23,   13,   12,   12, 0x08,
      53,   45,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ODockWidget[] = {
    "ODockWidget\0\0top_level\0TopLevelChanged(bool)\0checked\0"
    "VisibilityChanged(bool)\0"
};

const QMetaObject ODockWidget::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_ODockWidget,
      qt_meta_data_ODockWidget, 0 }
};

const QMetaObject *ODockWidget::metaObject() const
{
    return &staticMetaObject;
}

void *ODockWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ODockWidget))
	return static_cast<void*>(const_cast<ODockWidget*>(this));
    if (!strcmp(_clname, "ODataWidget"))
	return static_cast<ODataWidget*>(const_cast<ODockWidget*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int ODockWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: TopLevelChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: VisibilityChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        }
        _id -= 2;
    }
    return _id;
}
