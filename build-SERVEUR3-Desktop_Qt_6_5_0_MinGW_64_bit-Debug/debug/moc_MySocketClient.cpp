/****************************************************************************
** Meta object code from reading C++ file 'MySocketClient.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SERVEUR3/src/MySocketClient.h"
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MySocketClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMySocketClientENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMySocketClientENDCLASS = QtMocHelpers::stringData(
    "MySocketClient",
    "error",
    "",
    "QTcpSocket::SocketError",
    "socketError",
    "new_requete",
    "new_erreur",
    "new_erreur_403",
    "new_erreur_404",
    "new_erreur_503",
    "changement_etat"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMySocketClientENDCLASS_t {
    uint offsetsAndSizes[22];
    char stringdata0[15];
    char stringdata1[6];
    char stringdata2[1];
    char stringdata3[24];
    char stringdata4[12];
    char stringdata5[12];
    char stringdata6[11];
    char stringdata7[15];
    char stringdata8[15];
    char stringdata9[15];
    char stringdata10[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMySocketClientENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMySocketClientENDCLASS_t qt_meta_stringdata_CLASSMySocketClientENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "MySocketClient"
        QT_MOC_LITERAL(15, 5),  // "error"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 23),  // "QTcpSocket::SocketError"
        QT_MOC_LITERAL(46, 11),  // "socketError"
        QT_MOC_LITERAL(58, 11),  // "new_requete"
        QT_MOC_LITERAL(70, 10),  // "new_erreur"
        QT_MOC_LITERAL(81, 14),  // "new_erreur_403"
        QT_MOC_LITERAL(96, 14),  // "new_erreur_404"
        QT_MOC_LITERAL(111, 14),  // "new_erreur_503"
        QT_MOC_LITERAL(126, 15)   // "changement_etat"
    },
    "MySocketClient",
    "error",
    "",
    "QTcpSocket::SocketError",
    "socketError",
    "new_requete",
    "new_erreur",
    "new_erreur_403",
    "new_erreur_404",
    "new_erreur_503",
    "changement_etat"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMySocketClientENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x06,    1 /* Public */,
       5,    0,   59,    2, 0x06,    3 /* Public */,
       6,    0,   60,    2, 0x06,    4 /* Public */,
       7,    0,   61,    2, 0x06,    5 /* Public */,
       8,    0,   62,    2, 0x06,    6 /* Public */,
       9,    0,   63,    2, 0x06,    7 /* Public */,
      10,    0,   64,    2, 0x06,    8 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MySocketClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_CLASSMySocketClientENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMySocketClientENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMySocketClientENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MySocketClient, std::true_type>,
        // method 'error'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTcpSocket::SocketError, std::false_type>,
        // method 'new_requete'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'new_erreur'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'new_erreur_403'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'new_erreur_404'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'new_erreur_503'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'changement_etat'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MySocketClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MySocketClient *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< std::add_pointer_t<QTcpSocket::SocketError>>(_a[1]))); break;
        case 1: _t->new_requete(); break;
        case 2: _t->new_erreur(); break;
        case 3: _t->new_erreur_403(); break;
        case 4: _t->new_erreur_404(); break;
        case 5: _t->new_erreur_503(); break;
        case 6: _t->changement_etat(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MySocketClient::*)(QTcpSocket::SocketError );
            if (_t _q_method = &MySocketClient::error; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MySocketClient::*)();
            if (_t _q_method = &MySocketClient::new_requete; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MySocketClient::*)();
            if (_t _q_method = &MySocketClient::new_erreur; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MySocketClient::*)();
            if (_t _q_method = &MySocketClient::new_erreur_403; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MySocketClient::*)();
            if (_t _q_method = &MySocketClient::new_erreur_404; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MySocketClient::*)();
            if (_t _q_method = &MySocketClient::new_erreur_503; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MySocketClient::*)();
            if (_t _q_method = &MySocketClient::changement_etat; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject *MySocketClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MySocketClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMySocketClientENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int MySocketClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void MySocketClient::error(QTcpSocket::SocketError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MySocketClient::new_requete()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MySocketClient::new_erreur()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MySocketClient::new_erreur_403()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MySocketClient::new_erreur_404()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MySocketClient::new_erreur_503()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MySocketClient::changement_etat()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
