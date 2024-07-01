#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <functional>
#include <QJsonDocument>
#include "loadwidget.h"
#include "loginwidget.h"
#include "messagewidget.h"
#include "workerform.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ShowLoadWidget();
    void CloseLoadWidget();
    void MessageBox(const QString & msg);
    void SetUUID(const QString & uuid);
    void ToggleWorkForm();
    void Post(QString urlpath, const QJsonDocument & json , int millseconds, std::function<void(QString,QJsonDocument)> callback);
private slots:
    void OnLogin(const QString & username, const QString & password);
private:
    MessageWidget * m_message;
    LoginWidget * m_loginwidget;
    WorkerForm *m_workerwidget;
    LoadWidget * m_loadwidget;
    QNetworkAccessManager * m_networkMgr;
    QString m_uuid;
};
#endif // MAINWINDOW_H
