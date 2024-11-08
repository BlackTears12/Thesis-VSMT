#ifndef QMLSINGLETON_HPP
#define QMLSINGLETON_HPP

#include <QQmlEngine>
#include <QtQml/qqmlregistration.h>

namespace qml
{

#define NAMED_QML_SINGLETON(type) \
        QML_SINGLETON \
        QML_NAMED_ELEMENT(type)

/*
 * Can be used the create a new instance of a class with a protected cctor
*/
template <typename T>
struct InstanceCreator : public T
{
    static T* create() { return new InstanceCreator<T>(); }
};

/*
 * Classes can inherit from QmlSingleton<child> to declare them as singleton object which can be used in qml
 * requirements:
 *      Q_OBJECT
 *      NAMED_QML_SINGLETON(type)
 *      protected default cctor
*/
template <typename T>
class QmlSingleton
{
public:
    static T* create(QQmlEngine* qmlEngine,QJSEngine*);
protected:
    static T* instance;
};

template <typename T>
T* QmlSingleton<T>::create(QQmlEngine *qmlEngine, QJSEngine *)
{
    if(!instance)
        instance = InstanceCreator<T>::create();
    return instance;
}

template <typename T>
T* QmlSingleton<T>::instance = nullptr;

}

#endif // QMLSINGLETON_HPP
