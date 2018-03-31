/****************************************************************************
** Meta object code from reading C++ file 'view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_View_t {
    QByteArrayData data[14];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_View_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_View_t qt_meta_stringdata_View = {
    {
QT_MOC_LITERAL(0, 0, 4), // "View"
QT_MOC_LITERAL(1, 5, 14), // "sigCreateBlock"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 4), // "type"
QT_MOC_LITERAL(4, 26, 5), // "long&"
QT_MOC_LITERAL(5, 32, 3), // "key"
QT_MOC_LITERAL(6, 36, 14), // "sigDeleteBlock"
QT_MOC_LITERAL(7, 51, 13), // "sigCreateWire"
QT_MOC_LITERAL(8, 65, 6), // "PortID"
QT_MOC_LITERAL(9, 72, 8), // "startkey"
QT_MOC_LITERAL(10, 81, 6), // "endkey"
QT_MOC_LITERAL(11, 88, 2), // "id"
QT_MOC_LITERAL(12, 91, 13), // "sigDeleteWire"
QT_MOC_LITERAL(13, 105, 14) // "slotDeleteWire"

    },
    "View\0sigCreateBlock\0\0type\0long&\0key\0"
    "sigDeleteBlock\0sigCreateWire\0PortID\0"
    "startkey\0endkey\0id\0sigDeleteWire\0"
    "slotDeleteWire"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_View[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       6,    1,   44,    2, 0x06 /* Public */,
       7,    3,   47,    2, 0x06 /* Public */,
      12,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Long, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Long,    5,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 8, 0x80000000 | 4,    9,   10,   11,
    QMetaType::Void, QMetaType::Long,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Long,    5,

       0        // eod
};

void View::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        View *_t = static_cast<View *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigCreateBlock((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2]))); break;
        case 1: _t->sigDeleteBlock((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 2: _t->sigCreateWire((*reinterpret_cast< PortID(*)>(_a[1])),(*reinterpret_cast< PortID(*)>(_a[2])),(*reinterpret_cast< long(*)>(_a[3]))); break;
        case 3: _t->sigDeleteWire((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 4: _t->slotDeleteWire((*reinterpret_cast< long(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (View::*_t)(long , long & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&View::sigCreateBlock)) {
                *result = 0;
            }
        }
        {
            typedef void (View::*_t)(long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&View::sigDeleteBlock)) {
                *result = 1;
            }
        }
        {
            typedef void (View::*_t)(PortID , PortID , long & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&View::sigCreateWire)) {
                *result = 2;
            }
        }
        {
            typedef void (View::*_t)(long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&View::sigDeleteWire)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject View::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_View.data,
      qt_meta_data_View,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *View::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *View::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_View.stringdata0))
        return static_cast<void*>(const_cast< View*>(this));
    return QObject::qt_metacast(_clname);
}

int View::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void View::sigCreateBlock(long _t1, long & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void View::sigDeleteBlock(long _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void View::sigCreateWire(PortID _t1, PortID _t2, long & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void View::sigDeleteWire(long _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
