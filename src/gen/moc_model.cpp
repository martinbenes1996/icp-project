/****************************************************************************
** Meta object code from reading C++ file 'model.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../model.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'model.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Model_t {
    QByteArrayData data[13];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Model_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Model_t qt_meta_stringdata_Model = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Model"
QT_MOC_LITERAL(1, 6, 13), // "sigDeleteWire"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 3), // "key"
QT_MOC_LITERAL(4, 25, 15), // "slotCreateBlock"
QT_MOC_LITERAL(5, 41, 4), // "type"
QT_MOC_LITERAL(6, 46, 5), // "long&"
QT_MOC_LITERAL(7, 52, 15), // "slotDeleteBlock"
QT_MOC_LITERAL(8, 68, 14), // "slotCreateWire"
QT_MOC_LITERAL(9, 83, 6), // "PortID"
QT_MOC_LITERAL(10, 90, 8), // "startkey"
QT_MOC_LITERAL(11, 99, 6), // "endkey"
QT_MOC_LITERAL(12, 106, 14) // "slotDeleteWire"

    },
    "Model\0sigDeleteWire\0\0key\0slotCreateBlock\0"
    "type\0long&\0slotDeleteBlock\0slotCreateWire\0"
    "PortID\0startkey\0endkey\0slotDeleteWire"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Model[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   42,    2, 0x0a /* Public */,
       7,    1,   47,    2, 0x0a /* Public */,
       8,    3,   50,    2, 0x0a /* Public */,
      12,    1,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Long,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Long, 0x80000000 | 6,    5,    3,
    QMetaType::Void, QMetaType::Long,    3,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9, 0x80000000 | 6,   10,   11,    3,
    QMetaType::Void, QMetaType::Long,    3,

       0        // eod
};

void Model::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Model *_t = static_cast<Model *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigDeleteWire((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 1: _t->slotCreateBlock((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2]))); break;
        case 2: _t->slotDeleteBlock((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 3: _t->slotCreateWire((*reinterpret_cast< PortID(*)>(_a[1])),(*reinterpret_cast< PortID(*)>(_a[2])),(*reinterpret_cast< long(*)>(_a[3]))); break;
        case 4: _t->slotDeleteWire((*reinterpret_cast< long(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Model::*_t)(long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Model::sigDeleteWire)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Model::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Model.data,
      qt_meta_data_Model,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Model::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Model::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Model.stringdata0))
        return static_cast<void*>(const_cast< Model*>(this));
    return QObject::qt_metacast(_clname);
}

int Model::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Model::sigDeleteWire(long _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
