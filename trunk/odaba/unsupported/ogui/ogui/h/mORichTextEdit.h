/****************************************************************************
** Meta object code from reading C++ file 'sORichTextEdit.hpp'
**
** Created: So 27. Aug 20:59:20 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sORichTextEdit.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sORichTextEdit.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_ORichTextEdit[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      26,   14,   14,   14, 0x0a,
      72,   54,   14,   14, 0x0a,
     115,  107,   14,   14, 0x0a,
     142,  107,   14,   14, 0x0a,
     167,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ORichTextEdit[] = {
    "ORichTextEdit\0\0FillData()\0slotCursorPositionChanged()\0"
    "crQTextCharFormat\0slotFormatChanged(QTextCharFormat)\0qscText\0"
    "slotSetFontFamily(QString)\0slotSetFontSize(QString)\0storeToValue()\0"
};

const QMetaObject ORichTextEdit::staticMetaObject = {
    { &OMultiLineEdit::staticMetaObject, qt_meta_stringdata_ORichTextEdit,
      qt_meta_data_ORichTextEdit, 0 }
};

const QMetaObject *ORichTextEdit::metaObject() const
{
    return &staticMetaObject;
}

void *ORichTextEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ORichTextEdit))
	return static_cast<void*>(const_cast<ORichTextEdit*>(this));
    return OMultiLineEdit::qt_metacast(_clname);
}

int ORichTextEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = OMultiLineEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: FillData(); break;
        case 1: slotCursorPositionChanged(); break;
        case 2: slotFormatChanged((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        case 3: slotSetFontFamily((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: slotSetFontSize((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: storeToValue(); break;
        }
        _id -= 6;
    }
    return _id;
}
