#ifndef SEARCH_H
#define SEARCH_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QVector>
#include <QString>
#include <QTableWidget> // <<<<< مهم: عشان تستخدم QTableWidget
#include <QVBoxLayout>

namespace Ui {
class search;
}

class search : public QMainWindow
{
    Q_OBJECT

public:
    explicit search(QWidget *parent = nullptr);
    ~search();
    void fetchOrders();

private slots:
    void onFetchOrdersFinished(QNetworkReply *reply);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::search *ui;
    QNetworkAccessManager *netManager;
    QTableWidget *ordersTable; // <<<<< هنا بنعرف الـ QTableWidget
    QVBoxLayout *mainLayout; // <<<<< هنا بنعرف الـ Layout عشان يحتوي الجدول

    // الـ arrays اللي هتخزن فيها البيانات
    QVector<QString> orderIds;
    QVector<QString> orderAddresses;
    QVector<QString> orderServices;
    QVector<QString> orderServicePrices;
    QVector<QString> orderNotes;
    QVector<QString> orderStatuses;

    void storeOrderData(const QJsonObject& orderObject);
    void displayOrdersInUI();
signals:
    void ordersFetchedSuccessfully();
    void ordersFetchFailed(const QString& error);
};

#endif // SEARCH_H
