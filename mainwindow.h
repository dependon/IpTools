#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class IpApiRequest;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_serach_clicked();

    // 定义信号，当IP信息接收成功时发出
    void slotIpInfoReceived(const QString& country, const QString& regionName, const QString& city, const QString& isp,const QString& query);
    // 定义信号，当出现错误时发出
    void slotErrorOccurred(const QString& errorMessage);

    void on_com_lang_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    IpApiRequest * m_api{nullptr};

};

#endif // MAINWINDOW_H
