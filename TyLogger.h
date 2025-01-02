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
			// 当日期跨度后相应的更新日志文件名
			if (!isCurrentLogFile()) {
				file.close();
				createLogFile();
			}

			if (file.isOpen()) {
				QTextStream stream(&file);
				// 设置编码为UTF-8
				stream.setCodec("UTF-8");
				stream << msg << endl;
			}
		}
		//// 重置标志允许write在QtConcurrent::run中运行
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

		// 输出到控制台
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
			// 使用QtConcurrent::run在后台线程中异步写入日志文件
			logger.writeFuture = QtConcurrent::run(&instance(), &TyLogger::write);
		}
	}

	static TyLogger& instance()
	{
		// C++11标准保证静态局部变量的初始化是线程安全的
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