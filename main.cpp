#include <QCoreApplication>
#include <QDebug>
#include "TyLogger.h"
#include "HttpClient.h"
#include "Models/CNCStatus.h"

const QString BASE_URL = "http://127.0.0.1:19001";

int main(int argc, char** argv)
{
	qInstallMessageHandler(TyLogger::customMessageHandler);
	QCoreApplication a(argc, argv);

	QString apiPath = "/das/services/pull";
	QUrl url = httpClient->createWithQuerystring(BASE_URL + apiPath, QJsonObject{ {"fCode", "cnc_status"} });
	IResult result = httpClient->Get(url);
	if (result.code() == 0)
	{
		CNCStatus cncStatus;
		cncStatus.fromJson(result.data());
	}
	else qCritical() << result.message();

	return a.exec();
}