#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QEventLoop>
#include <type_traits>
#include "IResult.h"

class HttpClient : public QObject
{
	Q_GADGET
public:
	HttpClient(QObject* parent = nullptr) : QObject(parent)
	{

	}

public:
	IResult Get(const QString& url)
	{
		QNetworkAccessManager manager;
		QNetworkRequest request(url);
		request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json;charset=utf-8;");
		QNetworkReply* reply = manager.get(request);

		QEventLoop eloop;
		QObject::connect(reply, &QNetworkReply::finished, &eloop, &QEventLoop::quit);
		QObject::connect(reply, &QNetworkReply::errorOccurred, &eloop, &QEventLoop::quit);
		eloop.exec();

		IResult data;
		if (reply->error() != QNetworkReply::NoError)
		{
			data.set_code(-2);
			data.set_message(reply->errorString());
			reply->deleteLater();
			return data;
		}

		auto jsonStr = reply->readAll();
		reply->deleteLater();
		if (jsonStr.size() == 0) return data;

		data.fromJson(jsonStr);
		return data;
	}

	IResult Get(const QUrl& url)
	{
		QNetworkAccessManager manager;
		QNetworkRequest request(url);
		request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json;charset=utf-8;");
		QNetworkReply* reply = manager.get(request);

		QEventLoop eloop;
		QObject::connect(reply, &QNetworkReply::finished, &eloop, &QEventLoop::quit);
		QObject::connect(reply, &QNetworkReply::errorOccurred, &eloop, &QEventLoop::quit);
		eloop.exec();

		IResult data;
		if (reply->error() != QNetworkReply::NoError)
		{
			data.set_code(-2);
			data.set_message(reply->errorString());
			reply->deleteLater();
			return data;
		}

		auto jsonStr = reply->readAll();
		reply->deleteLater();
		if (jsonStr.size() == 0) return data;

		data.fromJson(jsonStr);
		return data;
	}

	IResult Post(const QString& url, const QByteArray& jsonObj)
	{
		QNetworkAccessManager manager;
		QNetworkRequest request(url);
		request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json;charset=utf-8;");
		QNetworkReply* reply = manager.post(request, jsonObj);

		QEventLoop eloop;
		QObject::connect(reply, &QNetworkReply::finished, &eloop, &QEventLoop::quit);
		QObject::connect(reply, &QNetworkReply::errorOccurred, &eloop, &QEventLoop::quit);
		eloop.exec();

		IResult data;
		if (reply->error() != QNetworkReply::NoError)
		{
			data.set_code(-2);
			data.set_message(reply->errorString());
			reply->deleteLater();
			return data;
		}

		auto jsonStr = reply->readAll();
		reply->deleteLater();
		if (!jsonStr.isEmpty())
		{
			data.fromJson(jsonStr);
		}
		return data;
	}

	IResult Post(const QUrl& url, const QByteArray& jsonObj)
	{
		QNetworkAccessManager manager;
		QNetworkRequest request(url);
		request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json;charset=utf-8;");
		QNetworkReply* reply = manager.post(request, jsonObj);

		QEventLoop eloop;
		QObject::connect(reply, &QNetworkReply::finished, &eloop, &QEventLoop::quit);
		QObject::connect(reply, &QNetworkReply::errorOccurred, &eloop, &QEventLoop::quit);
		eloop.exec();

		IResult data;
		if (reply->error() != QNetworkReply::NoError)
		{
			data.set_code(-2);
			data.set_message(reply->errorString());
			reply->deleteLater();
			return data;
		}

		auto jsonStr = reply->readAll();
		reply->deleteLater();
		if (!jsonStr.isEmpty())
		{
			data.fromJson(jsonStr);
		}
		return data;
	}

	IResult Put(const QString& url, const QByteArray& jsonObj)
	{
		QNetworkAccessManager manager;
		QNetworkRequest request(url);
		request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json;charset=utf-8;");
		QNetworkReply* reply = manager.put(request, jsonObj);

		QEventLoop eloop;
		QObject::connect(reply, &QNetworkReply::finished, &eloop, &QEventLoop::quit);
		QObject::connect(reply, &QNetworkReply::errorOccurred, &eloop, &QEventLoop::quit);
		eloop.exec();

		IResult data;
		if (reply->error() != QNetworkReply::NoError)
		{
			data.set_code(-2);
			data.set_message(reply->errorString());
			reply->deleteLater();
			return data;
		}

		auto jsonStr = reply->readAll();
		reply->deleteLater();
		if (!jsonStr.isEmpty())
		{
			data.fromJson(jsonStr);
		}
		return data;
	}

	IResult Put(const QUrl& url, const QByteArray& jsonObj)
	{
		QNetworkAccessManager manager;
		QNetworkRequest request(url);
		request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json;charset=utf-8;");
		QNetworkReply* reply = manager.put(request, jsonObj);

		QEventLoop eloop;
		QObject::connect(reply, &QNetworkReply::finished, &eloop, &QEventLoop::quit);
		QObject::connect(reply, &QNetworkReply::errorOccurred, &eloop, &QEventLoop::quit);
		eloop.exec();

		IResult data;
		if (reply->error() != QNetworkReply::NoError)
		{
			data.set_code(-2);
			data.set_message(reply->errorString());
			reply->deleteLater();
			return data;
		}

		auto jsonStr = reply->readAll();
		reply->deleteLater();
		if (!jsonStr.isEmpty())
		{
			data.fromJson(jsonStr);
		}
		return data;
	}

	IResult Delete(const QString& url)
	{
		QNetworkAccessManager manager;
		QNetworkRequest request(url);
		request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json;charset=utf-8;");
		QNetworkReply* reply = manager.deleteResource(request);

		QEventLoop eloop;
		QObject::connect(reply, &QNetworkReply::finished, &eloop, &QEventLoop::quit);
		QObject::connect(reply, &QNetworkReply::errorOccurred, &eloop, &QEventLoop::quit);
		eloop.exec();

		IResult data;
		if (reply->error() != QNetworkReply::NoError)
		{
			data.set_code(-2);
			data.set_message(reply->errorString());
			reply->deleteLater();
			return data;
		}

		auto jsonStr = reply->readAll();
		reply->deleteLater();
		if (!jsonStr.isEmpty())
		{
			data.fromJson(jsonStr);
		}
		return data;
	}

	IResult Delete(const QUrl& url)
	{
		QNetworkAccessManager manager;
		QNetworkRequest request(url);
		request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json;charset=utf-8;");
		QNetworkReply* reply = manager.deleteResource(request);

		QEventLoop eloop;
		QObject::connect(reply, &QNetworkReply::finished, &eloop, &QEventLoop::quit);
		QObject::connect(reply, &QNetworkReply::errorOccurred, &eloop, &QEventLoop::quit);
		eloop.exec();

		IResult data;
		if (reply->error() != QNetworkReply::NoError)
		{
			data.set_code(-2);
			data.set_message(reply->errorString());
			reply->deleteLater();
			return data;
		}

		auto jsonStr = reply->readAll();
		reply->deleteLater();
		if (!jsonStr.isEmpty())
		{
			data.fromJson(jsonStr);
		}
		return data;
	}

	static QUrl createWithQuerystring(const QString& baseUrl, const QMap<QString, QString>& queryParams)
	{
		QUrl url(baseUrl);
		QUrlQuery query;
		//for (auto it = queryParams.constBegin(); it != queryParams.constEnd(); ++it) query.addQueryItem(it.key(), it.value());
		for (const auto& key: queryParams.keys()) query.addQueryItem(key, queryParams.value(key));
		url.setQuery(query);
		return url;
	}

	static QUrl createWithQuerystring(const QString& baseUrl, const QJsonObject& queryParams)
	{
		QUrl url(baseUrl);
		QUrlQuery query;
		// 获取QSerializer的toJson()方法得到QJsonObject对象然后遍历键值对
		//for (auto it = queryParams.constBegin(); it != queryParams.constEnd(); ++it)
		//{
		//	QString key = it.key();
		//	// 这里需要对it.value()的类型进行判断
		//	// 假定都是简单类型直接使用转换为QVariant后转换为QString类型
		//	// 避免it.value()为数值类型时使用toString()将返回EmptyString
		//	QString value = it.value().toVariant().toString();
		//	query.addQueryItem(key, value);
		//}
		for (const auto& key : queryParams.keys())
		{
			// 这里需要对value的类型进行判断
			// 假定都是简单类型直接使用转换为QVariant后转换为QString类型
			// 避免value为数值类型时使用toString()将返回EmptyString
			QString value = queryParams.value(key).toVariant().toString();
			query.addQueryItem(key, value);
		}
		url.setQuery(query);
		return url;
	}

	template<class T, typename std::enable_if<std::is_base_of<JsonSerializable, T>::value, int>::type = 0>
	static QUrl createWithQuerystring(const QString& baseUrl, const T& queryParams)
	{
		QJsonObject jsonObj = queryParams.toJson();
		return createWithQuerystring(baseUrl, jsonObj);
	}
};

Q_GLOBAL_STATIC(HttpClient, httpClient)
#endif