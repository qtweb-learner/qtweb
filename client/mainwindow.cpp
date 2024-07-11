#include "mainwindow.h"
#include "msgdlg.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_loadwidget = nullptr;
    m_workerwidget = nullptr;
    m_networkMgr = new QNetworkAccessManager(this);
    m_loginwidget = new LoginWidget();
    setCentralWidget(m_loginwidget);
    connect(m_loginwidget, SIGNAL(login(const QString &,const QString &)), this, SLOT(OnLogin(const QString &, const QString & )));
}

MainWindow::~MainWindow() {}

void MainWindow::ShowLoadWidget(){
    if (m_loadwidget == nullptr){
        m_loadwidget = new WaitDlg(this);
    }
}
void MainWindow::CloseLoadWidget(){
    if (m_loadwidget != nullptr){
        m_loadwidget->close();
        m_loadwidget = nullptr;
    }
}

void MainWindow::MessageBox(const QString & msg){
    auto pmsg = new msgdlg(msg, this);
    pmsg->show();
}

void MainWindow::SetUUID(const QString & uuid){
    m_uuid = uuid;
}

void MainWindow::ToggleWorkForm(){
    m_workerwidget = new WorkerForm(this);
    setCentralWidget(m_workerwidget);
    m_loginwidget->deleteLater();
    m_loginwidget = nullptr;
}

void MainWindow::Post(QString urlpath, const QJsonDocument & jsonReq , int millseconds, std::function<void(QString,QJsonDocument)> callback){
    QNetworkRequest request(QUrl("http://127.0.0.1:8080"+urlpath));
    request.setTransferTimeout(millseconds);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    if (!m_uuid.isEmpty()){
        request.setRawHeader("QUUID", m_uuid.toUtf8());
    }
    QNetworkReply *reply = m_networkMgr->post(request,  jsonReq.toJson());
    reply->ignoreSslErrors();
    QObject::connect(reply, &QNetworkReply::finished, [reply,callback](){
        if(reply->error() != QNetworkReply::NoError){
            qInfo()<<"Http Error:"<<reply->errorString();
            reply->deleteLater();
            callback("http 请求失败", QJsonDocument());
            return;
        }
        QByteArray response = reply->readAll();
        QJsonParseError parseError;
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response, &parseError);
        if (parseError.error != QJsonParseError::NoError){
            qInfo()<< "Error parsing JSON:" << parseError.errorString();
            reply->deleteLater();
            callback("解析json失败", QJsonDocument());
            return;
        }
        reply->deleteLater();
        callback("", jsonResponse);
    });
}

void MainWindow::OnLogin(const QString & username, const QString & password){
    ShowLoadWidget();
    QJsonObject json;
    json["username"] = username;
    json["password"] = password;
    Post("/login", QJsonDocument(json), 15000, [this](QString err, QJsonDocument doc){
        this->CloseLoadWidget();
        if (!err.isEmpty()){
            this->MessageBox(err);
            return;
        }
        auto object = doc.object();
        if (object["code"].toInt(0) != 200){
            this->MessageBox(object["message"].toString());
            return;
        }
        this->SetUUID(object["uuid"].toString());
        this->ToggleWorkForm();
    });
}
