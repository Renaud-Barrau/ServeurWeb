/****************************************************************************
** Meta object code from reading C++ file 'stats.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SERVEUR3/src/stats.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stats.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSStatsENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSStatsENDCLASS = QtMocHelpers::stringData(
    "Stats",
    "compteur_requete",
    "",
    "compteur_erreur",
    "compteur_erreur_403",
    "compteur_erreur_404",
    "compteur_erreur_503",
    "activate_serv"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSStatsENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[6];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[16];
    char stringdata4[20];
    char stringdata5[20];
    char stringdata6[20];
    char stringdata7[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSStatsENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSStatsENDCLASS_t qt_meta_stringdata_CLASSStatsENDCLASS = {
    {
        QT_MOC_LITERAL(0, 5),  // "Stats"
        QT_MOC_LITERAL(6, 16),  // "compteur_requete"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 15),  // "compteur_erreur"
        QT_MOC_LITERAL(40, 19),  // "compteur_erreur_403"
        QT_MOC_LITERAL(60, 19),  // "compteur_erreur_404"
        QT_MOC_LITERAL(80, 19),  // "compteur_erreur_503"
        QT_MOC_LITERAL(100, 13)   // "activate_serv"
    },
    "Stats",
    "compteur_requete",
    "",
    "compteur_erreur",
    "compteur_erreur_403",
    "compteur_erreur_404",
    "compteur_erreur_503",
    "activate_serv"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSStatsENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x0a,    1 /* Public */,
       3,    0,   51,    2, 0x0a,    2 /* Public */,
       4,    0,   52,    2, 0x0a,    3 /* Public */,
       5,    0,   53,    2, 0x0a,    4 /* Public */,
       6,    0,   54,    2, 0x0a,    5 /* Public */,
       7,    0,   55,    2, 0x0a,    6 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Stats::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSStatsENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSStatsENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSStatsENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Stats, std::true_type>,
        // method 'compteur_requete'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'compteur_erreur'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'compteur_erreur_403'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'compteur_erreur_404'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'compteur_erreur_503'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'activate_serv'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Stats::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Stats *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->compteur_requete(); break;
        case 1: _t->compteur_erreur(); break;
        case 2: _t->compteur_erreur_403(); break;
        case 3: _t->compteur_erreur_404(); break;
        case 4: _t->compteur_erreur_503(); break;
        case 5: _t->activate_serv(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *Stats::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Stats::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSStatsENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Stats::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
