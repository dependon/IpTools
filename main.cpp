#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>

// 自定义消息处理函数
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // 获取当前日期并格式化为 YYYY-MM-DD
    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString logFileName = "log/" + currentDate + ".log";
    QDir().mkpath("log");

    QFile outFile(logFileName);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);

    switch (type) {
    case QtDebugMsg:
        ts << "Debug: ";
        break;
    case QtInfoMsg:
        ts << "Info: ";
        break;
    case QtWarningMsg:
        ts << "Warning: ";
        break;
    case QtCriticalMsg:
        ts << "Critical: ";
        break;
    case QtFatalMsg:
        ts << "Fatal: ";
        break;
    }

    ts << msg << " (" << context.file << ":" << context.line << ")";
    outFile.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 安装自定义消息处理函数
    qInstallMessageHandler(myMessageOutput);

    MainWindow w;
    w.show();

    return a.exec();
}
