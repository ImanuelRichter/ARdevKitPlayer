/****************************************************************************
** Meta object code from reading C++ file 'NativeScene.h'
**
** Created: Sat 25. Jan 21:57:51 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../NativeScene.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NativeScene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NativeScene[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_NativeScene[] = {
    "NativeScene\0"
};

void NativeScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData NativeScene::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NativeScene::staticMetaObject = {
    { &SceneBase::staticMetaObject, qt_meta_stringdata_NativeScene,
      qt_meta_data_NativeScene, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NativeScene::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NativeScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NativeScene::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NativeScene))
        return static_cast<void*>(const_cast< NativeScene*>(this));
    if (!strcmp(_clname, "metaio::IMetaioSDKCallback"))
        return static_cast< metaio::IMetaioSDKCallback*>(const_cast< NativeScene*>(this));
    return SceneBase::qt_metacast(_clname);
}

int NativeScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SceneBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
