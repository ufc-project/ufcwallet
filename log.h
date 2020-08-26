#ifndef LOG_H
#define LOG_H

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMutex>

namespace QT_LOG
{
    static int m_LogLevel = 0;
    static QString m_LogFile = QString("%1.log").arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    QMutex m_LogMutex;

    void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
    {
        if (type < m_LogLevel)
        {
            return;
        }
        QString log_info;
        switch (type)
        {
        case QtDebugMsg:
            log_info = QString("%1:%2").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),msg);
            break;

        case QtWarningMsg:
            log_info = QString("%1[Warning]:%2").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),msg);
            break;

        case QtCriticalMsg:
            log_info = QString("%1[Critical]:%2").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),msg);
            break;

        case QtFatalMsg:
            log_info = QString("%1[Fatal]:%2").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),msg);
            abort();
        }
        m_LogMutex.lock();

        QFile outFile(m_LogFile);
        outFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
        QTextStream ts(&outFile);
        ts << log_info << endl;
        outFile.close();
        m_LogMutex.unlock();
    }

    void logInit(QString logFile = "", int logLevel = 0)
    {
#ifdef QT_DEBUG
        m_LogLevel = logLevel;
#else
        if (logLevel < QtWarningMsg)
            m_LogLevel = QtWarningMsg;
#endif
        if (!logFile.isEmpty())
        {
            m_LogFile = logFile;
        }
        qInstallMessageHandler(customMessageHandler);
    }
}


#endif // LOG_H
