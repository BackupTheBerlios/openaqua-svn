/****************************************************************************
** Meta object code from reading C++ file 'sODocument.hpp'
**
** Created: So 27. Aug 20:56:40 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sODocument.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sODocument.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_ODocument[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      25,   11,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ODocument[] = {
    "ODocument\0\0crQTextCursor\0slotCursorPositionChanged(QTextCursor)\0"
};

const QMetaObject ODocument::staticMetaObject = {
    { &QTextDocument::staticMetaObject, qt_meta_stringdata_ODocument,
      qt_meta_data_ODocument, 0 }
};

const QMetaObject *ODocument::metaObject() const
{
    return &staticMetaObject;
}

void *ODocument::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ODocument))
	return static_cast<void*>(const_cast<ODocument*>(this));
    return QTextDocument::qt_metacast(_clname);
}

int ODocument::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextDocument::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotCursorPositionChanged((*reinterpret_cast< const QTextCursor(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
