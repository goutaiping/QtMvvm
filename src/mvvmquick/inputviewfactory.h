#ifndef QTMVVM_INPUTVIEWFACTORY_H
#define QTMVVM_INPUTVIEWFACTORY_H

#include <QtCore/qurl.h>
#include <QtCore/qvariant.h>
#include <QtCore/qscopedpointer.h>
#include <QtCore/qobject.h>
#include <QtCore/qmetaobject.h>

#include "QtMvvmQuick/qtmvvmquick_global.h"

namespace QtMvvm {

class Q_MVVMQUICK_EXPORT Formatter
{
	Q_DISABLE_COPY(Formatter)

public:
	Formatter();
	virtual ~Formatter();

	virtual QString format(const QString &formatString,
						   const QVariant &value,
						   const QVariantMap &viewProperties) const = 0;
};

template <typename T>
class SimpleFormatter : public Formatter
{
public:
	inline QString format(const QString &formatString,
						  const QVariant &value,
						  const QVariantMap &viewProperties) const override;
};

class InputViewFactoryPrivate;
//! A factory class to generate input edit views by their type names
class Q_MVVMQUICK_EXPORT InputViewFactory : public QObject
{
	Q_OBJECT

public:
	//! Default constructor
	Q_INVOKABLE InputViewFactory(QObject *parent = nullptr);
	~InputViewFactory() override;

	//! Find the input view URL of the given input type
	Q_INVOKABLE virtual QUrl getInputUrl(const QByteArray &type, const QVariantMap &viewProperties);
	//! Find the input list delegate URL of the given input type
	Q_INVOKABLE virtual QUrl getDelegate(const QByteArray &type, const QVariantMap &viewProperties);

	Q_REVISION(1) Q_INVOKABLE QString format(const QByteArray &type,
											 const QString &formatString,
											 const QVariant &value,
											 const QVariantMap &viewProperties);

	//! Adds a new QML file to create views for the given type
	template <typename TType>
	inline void addSimpleInput(const QUrl &qmlFileUrl);
	//! @copybrief addSimpleInput(const QUrl &)
	Q_INVOKABLE virtual void addSimpleInput(const QByteArray &type, const QUrl &qmlFileUrl);

	//! Adds a new QML file to create delegates for the given type
	template <typename TType>
	inline void addSimpleDelegate(const QUrl &qmlFileUrl);
	//! @copybrief addSimpleDelegate(const QUrl &)
	Q_INVOKABLE virtual void addSimpleDelegate(const QByteArray &type, const QUrl &qmlFileUrl);

	template <typename TType>
	inline void addFormatter(Formatter *formatter);
	void addFormatter(const QByteArray &type, Formatter *formatter);

	//! Adds a type name alias for views
	template <typename TAliasType, typename TTargetType>
	inline void addInputAlias();
	//! @copybrief addInputAlias()
	Q_INVOKABLE virtual void addInputAlias(const QByteArray &alias, const QByteArray &targetType);

	//! Adds a type name alias for delegates
	template <typename TAliasType, typename TTargetType>
	inline void addDelegateAlias();
	//! @copybrief addDelegateAlias()
	Q_INVOKABLE virtual void addDelegateAlias(const QByteArray &alias, const QByteArray &targetType);

	template <typename TAliasType, typename TTargetType>
	inline void addFormatterAlias();
	Q_REVISION(1) Q_INVOKABLE void addFormatterAlias(const QByteArray &alias, const QByteArray &targetType);

private:
	QScopedPointer<InputViewFactoryPrivate> d;
};

template<typename TType>
inline void InputViewFactory::addSimpleInput(const QUrl &qmlFileUrl)
{
	addSimpleInput(QMetaType::typeName(qMetaTypeId<TType>()), qmlFileUrl);
}

template<typename TType>
void InputViewFactory::addSimpleDelegate(const QUrl &qmlFileUrl)
{
	addSimpleDelegate(QMetaType::typeName(qMetaTypeId<TType>()), qmlFileUrl);
}

template<typename TType>
void InputViewFactory::addFormatter(Formatter *formatter)
{
	addFormatter(QMetaType::typeName(qMetaTypeId<TType>()), formatter);
}

template<typename TAliasType, typename TTargetType>
inline void InputViewFactory::addInputAlias()
{
	addInputAlias(QMetaType::typeName(qMetaTypeId<TAliasType>()), QMetaType::typeName(qMetaTypeId<TTargetType>()));
}

template<typename TAliasType, typename TTargetType>
void InputViewFactory::addDelegateAlias()
{
	addDelegateAlias(QMetaType::typeName(qMetaTypeId<TAliasType>()), QMetaType::typeName(qMetaTypeId<TTargetType>()));
}

template<typename TAliasType, typename TTargetType>
void InputViewFactory::addFormatterAlias()
{
	addFormatterAlias(QMetaType::typeName(qMetaTypeId<TAliasType>()), QMetaType::typeName(qMetaTypeId<TTargetType>()));
}



template<typename T>
QString SimpleFormatter<T>::format(const QString &formatString, const QVariant &value, const QVariantMap &viewProperties) const
{
	Q_UNUSED(viewProperties);
	return formatString.arg(value.template value<T>());
}

}

#endif // QTMVVM_INPUTVIEWFACTORY_H
