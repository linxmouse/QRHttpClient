#ifndef TY_LOGGER_HEADER
#define TY_LOGGER_HEADER
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QDate>
#include <QDateTime>
#include <QMutex>
#include <QQueue>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

class TyLogger
{
private:
	TyLogger()
	{
		//writeRunning = 0;
		createLogFile();
	}
	TyLogger(const TyLogger&) = delete;
	TyLogger& operator=(const TyLogger&) = delete;

public:
	~TyLogger() 
	{
		writeFuture.cancel();
		writeFuture.waitForFinished();
		file.close();
	}

	void write()
	{
		//if (!writeRunning.testAndSetAcquire(0, 1))
		//{
		//	//qInfo() << "write log has running queue";
		//	return;
		//}
		while (true)
		{
			QMutexLocker locker(&mutex);
			if (queue.isEmpty()) break;
			const auto msg = queue.dequeue();
			// �����ڿ�Ⱥ���Ӧ�ĸ�����־�ļ���
			if (!isCurrentLogFile()) {
				file.close();
				createLogFile();
			}

			if (file.isOpen()) {
				QTextStream stream(&file);
				// ���ñ���ΪUTF-8
				stream.setCodec("UTF-8");
				stream << msg << endl;
			}
		}
		//// ���ñ�־����write��QtConcurrent::run������
		//writeRunning.store(0);
	}

	static void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
	{
		QString level;
		switch (type)
		{
		case QtDebugMsg:
			level = "DEBUG";
			break;
		case QtWarningMsg:
			level = "WARN";
			break;
		case QtCriticalMsg:
			level = "ERROR";
			break;
		case QtFatalMsg:
			level = "FATAL";
			break;
		case QtInfoMsg:
			level = "INFO";
			break;
		default:
			level = "UNKN ";
			break;
		}
#if _DEBUG
		auto fileName = QFileInfo(context.file).fileName();
		QString formattedMessage = QString("[%1 %3:%4 %2] %5")
			.arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"))
			.arg(level)
			.arg(fileName)
			.arg(context.line)
			.arg(msg);
#else
		QString formattedMessage = QString("[%1 %2] %5")
			.arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"))
			.arg(level)
			.arg(msg);
#endif

		// ���������̨
		QTextStream cs(stdout);
		cs << formattedMessage << endl;

		auto& logger = instance();
		// locker mutex scope
		{
			QMutexLocker locker(&logger.mutex);
			logger.queue.enqueue(formattedMessage);
		}
		if (!logger.writeFuture.isRunning())
		{
			// ʹ��QtConcurrent::run�ں�̨�߳����첽д����־�ļ�
			logger.writeFuture = QtConcurrent::run(&instance(), &TyLogger::write);
		}
	}

	static TyLogger& instance()
	{
		// C++11��׼��֤��̬�ֲ������ĳ�ʼ�����̰߳�ȫ��
		static TyLogger logger;
		return logger;
	}

private:
	void createLogFile()
	{
		QString logDirPath = "Logs";
		QDir logDir(logDirPath);
		if (!logDir.exists()) {
			logDir.mkpath(".");
		}

		QString logFilePath = logDirPath + "/" + QDateTime::currentDateTime().toString("yyyy-MM-dd") + ".log";
		file.setFileName(logFilePath);
		file.open(QIODevice::WriteOnly | QIODevice::Append);
		currentLogFileDate = QDate::currentDate();
	}

	bool isCurrentLogFile() const
	{
		return currentLogFileDate == QDate::currentDate();
	}

private:
	QMutex mutex;
	QQueue<QString> queue;
	//QAtomicInt writeRunning;
	QFuture<void> writeFuture;

	QFile file;
	QDate currentLogFileDate;
};
#endif // TY_LOGGER_HEADER