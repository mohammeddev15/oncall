#ifndef ADD_REQ_H
#define ADD_REQ_H

#include <QMainWindow>
#include <QNetworkAccessManager> // <-- أضف هذا السطر
#include <QNetworkReply>

namespace Ui {
class add_req;
}

class add_req : public QMainWindow
{
    Q_OBJECT

public:
    explicit add_req(QWidget *parent = nullptr);
    ~add_req();

private slots:
    void on_pushButton_clicked();
    void onOrderRequestFinished(QNetworkReply *reply);

    //void on_pushButton_2_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::add_req *ui;
    QNetworkAccessManager *netManager;
};

#endif // ADD_REQ_H
