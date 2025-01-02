#ifndef IRESULT_H
#define IRESULT_H

#include <QJsonValue>
#include "JsonSerializer.h"

class IResult : public JsonSerializable
{
	Q_GADGET
	JSON_SERIALIZABLE
public:
	JSON_PROPERTY(int, code)
	JSON_PROPERTY(QString, message)
	JSON_PROPERTY(QJsonValue, data)

public:
	template<typename T, typename std::enable_if<std::is_arithmetic<T>::value || std::is_same<T, QString>::value, int>::type=0>
	T dataValue() const
	{
		return data.toVariant().value<T>();
	}
};
#endif // !IRESULT_H
