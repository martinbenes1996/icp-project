/****************************************************************************
** Meta object code from reading C++ file 'playground.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../playground.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playground.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PlayGround_t {
    QByteArrayData data[17];
    char stringdata0[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayGround_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayGround_t qt_meta_stringdata_PlayGround = {
    {
QT_MOC_LITERAL(0, 0, 10), // "PlayGround"
QT_MOC_LITERAL(1, 11, 17), // "sigChoiceRejected"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 14), // "sigCreateBlock"
QT_MOC_LITERAL(4, 45, 9), // "BlockType"
QT_MOC_LITERAL(5, 55, 4), // "type"
QT_MOC_LITERAL(6, 60, 5), // "long&"
QT_MOC_LITERAL(7, 66, 3), // "key"
QT_MOC_LITERAL(8, 70, 14), // "sigDeleteBlock"
QT_MOC_LITERAL(9, 85, 13), // "sigCreateWire"
QT_MOC_LITERAL(10, 99, 6), // "PortID"
QT_MOC_LITERAL(11, 106, 8), // "startkey"
QT_MOC_LITERAL(12, 115, 6), // "endkey"
QT_MOC_LITERAL(13, 122, 2), // "id"
QT_MOC_LITERAL(14, 125, 13), // "sigDeleteWire"
QT_MOC_LITERAL(15, 139, 14), // "slotChoiceMode"
QT_MOC_LITERAL(16, 154, 6) // "choice"

    },
    "PlayGround\0sigChoiceRejected\0\0"
    "sigCreateBlock\0BlockType\0type\0long&\0"
    "key\0sigDeleteBlock\0sigCreateWire\0"
    "PortID\0startkey\0endkey\0id\0sigDeleteWire\0"
    "slotChoiceMode\0choice"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayGround[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    2,   45,    2, 0x06 /* Public */,
       8,    1,   50,    2, 0x06 /* Public */,
       9,    3,   53,    2, 0x06 /* Public */,
      14,    1,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    1,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 6,    5,    7,
    QMetaType::Void, QMetaType::Long,    7,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 10, 0x80000000 | 6,   11,   12,   13,
    QMetaType::Void, QMetaType::Long,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   16,

       0        // eod
};

void PlayGround::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlayGround *_t = static_cast<PlayGround *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigChoiceRejected(); break;
        case 1: _t->sigCreateBlock((*reinterpret_cast< BlockType(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2]))); break;
        case 2: _t->sigDeleteBlock((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 3: _t->sigCreateWire((*reinterpret_cast< PortID(*)>(_a[1])),(*reinterpret_cast< PortID(*)>(_a[2])),(*reinterpret_cast< long(*)>(_a[3]))); break;
        case 4: _t->sigDeleteWire((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 5: _t->slotChoiceMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PlayGround::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayGround::sigChoiceRejected)) {
                *result = 0;
            }
        }
        {
            typedef void (PlayGround::*_t)(BlockType , long & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayGround::sigCreateBlock)) {
                *result = 1;
            }
        }
        {
            typedef void (PlayGround::*_t)(long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayGround::sigDeleteBlock)) {
                *result = 2;
            }
        }
        {
            typedef void (PlayGround::*_t)(PortID , PortID , long & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayGround::sigCreateWire)) {
                *result = 3;
            }
        }
        {
            typedef void (PlayGround::*_t)(long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayGround::sigDeleteWire)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject PlayGround::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PlayGround.data,
      qt_meta_data_PlayGround,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PlayGround::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayGround::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PlayGround.stringdata0))
        return static_cast<void*>(const_cast< PlayGround*>(this));
    return QWidget::qt_metacast(_clname);
}

int PlayGround::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void PlayGround::sigChoiceRejected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void PlayGround::sigCreateBlock(BlockType _t1, long & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PlayGround::sigDeleteBlock(long _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PlayGround::sigCreateWire(PortID _t1, PortID _t2, long & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PlayGround::sigDeleteWire(long _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
