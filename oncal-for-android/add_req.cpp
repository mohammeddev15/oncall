#include "add_req.h"
#include "ui_add_req.h"
#include"mainwindow.h"
#include <QScreen>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>
#include <QDebug>

add_req::add_req(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::add_req)
{
    ui->setupUi(this);
    netManager = new QNetworkAccessManager(this);

    // ربط إشارة finished() بالدالة onOrderRequestFinished
    connect(netManager, &QNetworkAccessManager::finished,
            this, &add_req::onOrderRequestFinished);
}

add_req::~add_req()
{
    delete ui;
}

void add_req::on_pushButton_clicked()
{
    qDebug() << "Sending order request...";

    QUrl url("https://mohammed5555.pythonanywhere.com/order");
    QJsonObject orderData;
    orderData["Address"] = ui->lineEdit->text();
    orderData["Service"] = ui->lineEdit_2->text();
    orderData["Service price"] = ui->lineEdit_3->text();
    orderData["notes"] = ui->lineEdit_4->text();

    QJsonDocument doc(orderData);
    QByteArray postData = doc.toJson(QJsonDocument::Compact);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    netManager->post(request, postData);

}
void add_req::onOrderRequestFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        qDebug() << "Server response:" << responseData;

        QJsonDocument responseDoc = QJsonDocument::fromJson(responseData);
        if (!responseDoc.isNull() && responseDoc.isObject()) {
            QJsonObject responseObject = responseDoc.object();
            qDebug() << "Order ID received:" << responseObject["id"].toInt();
            qDebug() << "Status:" << responseObject["status"].toString();

        }

    } else {
        qDebug() << "Error:" << reply->errorString();
    }

    reply->deleteLater();
}


void add_req::on_pushButton_2_clicked()
{
    MainWindow *back=new MainWindow();
    back->show();
    this->close();
}

