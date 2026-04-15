#include "search.h"
#include "ui_search.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QUrl>
#include <QDebug>
#include <QHeaderView>
#include <QScreen>
#include "mainwindow.h"

search::search(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::search)
{
    ui->setupUi(this);
    setWindowTitle("Oncall");
    setWindowIcon(QIcon(":/icons/professional-logo-fored-as-a-sta.png"));
    setGeometry(QGuiApplication::primaryScreen()->availableGeometry());
    mainLayout = new QVBoxLayout(ui->widget); // بنعمل layout للـ widget بتاعنا
    ordersTable = new QTableWidget(ui->widget);

    ordersTable->setColumnCount(6); // عدد الأعمدة اللي هتعرضها (id, Address, Service, Price, Notes, Status)
    ordersTable->setHorizontalHeaderLabels({"ID", "number phone", "Service", "Price", "Notes", "Status"}); // أسماء الأعمدة
    ordersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 1. تفعيل الـ word wrap للخلايا:
    // ده هيخلي النص الطويل يتلف داخل الخلية بدل ما يتخطى حدودها
    ordersTable->setWordWrap(true);

    // 2. ضبط ارتفاع الصفوف تلقائياً بناءً على المحتوى:
    // ده هيخلي الصف يكبر في الطول عشان يستوعب كل سطور النص اللي اتلفت
    ordersTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // ... باقي إعدادات الجدول زي ما هي
    ordersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ordersTable->setSelectionBehavior(QAbstractItemView::SelectRows); // عشان لما تدوس على خلية، يحدد الصف كله

    mainLayout->addWidget(ordersTable); // إضافة الجدول للـ Layout بتاع الـ search

    netManager = new QNetworkAccessManager(this);

    // ربط إشارة الـ finished من الـ netManager بالدالة اللي هتستقبل الرد
    connect(netManager, &QNetworkAccessManager::finished,
            this, &search::onFetchOrdersFinished);
    fetchOrders();
}

search::~search()
{
    delete ui;
}


// دالة جلب الطلبات من السيرفر
void search::fetchOrders()
{
    qDebug() << "Fetching all orders...";
    QUrl url("https://mohammed5555.pythonanywhere.com/orders");
    QNetworkRequest request(url);

    QNetworkReply *reply = netManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        this->onFetchOrdersFinished(reply);
    });
}

// دالة لاستقبال رد الـ GET و تحليل الـ JSON
void search::onFetchOrdersFinished(QNetworkReply *reply)
{
    if (reply->url().path() == "/orders") { // نتأكد إن ده الرد اللي جاي من طلب /orders
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            qDebug() << "GET Server response:" << responseData;

            QJsonDocument doc = QJsonDocument::fromJson(responseData);
            if (doc.isArray()) { // لو الرد JSON Array
                QJsonArray jsonArray = doc.array();

                // مسح البيانات القديمة قبل إضافة الجديدة
                orderIds.clear();
                orderAddresses.clear();
                orderServices.clear();
                orderServicePrices.clear();
                orderNotes.clear();
                orderStatuses.clear();

                // الدخول في حلقة (for loop) لتحليل كل عنصر في الـ JSON Array
                for (const QJsonValue &value : jsonArray) {
                    if (value.isObject()) {
                        QJsonObject orderObject = value.toObject();
                        storeOrderData(orderObject); // تخزين بيانات كل طلب في الـ QVector
                    }
                }
                qDebug() << "Fetched " << orderIds.size() << " orders.";
                displayOrdersInUI(); // <<< هنا بننادي على الدالة اللي هتعرض البيانات في الجدول
                emit ordersFetchedSuccessfully();
            } else {
                qDebug() << "GET Response is not a JSON array.";
                emit ordersFetchFailed("Response is not a JSON array.");
            }
        } else {
            qDebug() << "GET Error:" << reply->errorString();
            emit ordersFetchFailed(reply->errorString());
        }
    }
    reply->deleteLater();
}

// دالة مساعدة لتخزين بيانات طلب واحد في الـ QVector
void search::storeOrderData(const QJsonObject& orderObject)
{
    // تأكد من الـ keys دي مطابقة تماماً للي بيرجعها سيرفر Flask
    orderIds.append(orderObject["id"].toString());
    orderAddresses.append(orderObject["Address"].toString());
    orderServices.append(orderObject["Service"].toString());
    orderServicePrices.append(orderObject["Service price"].toString());
    orderNotes.append(orderObject["notes"].toString());
    orderStatuses.append(orderObject["status"].toString());
}

// <<< الدالة الأساسية لتمثيل البيانات في الواجهة (QTableWidget)
void search::displayOrdersInUI()
{
    // 1. مسح أي صفوف موجودة في الجدول قبل إعادة ملئه بالبيانات الجديدة
    ordersTable->setRowCount(0);

    // 2. تعيين عدد الصفوف الجديد بناءً على عدد الطلبات اللي جبناها
    ordersTable->setRowCount(orderIds.size());

    // 3. الدخول في حلقة (for loop) على الـ QVector عشان نملأ كل صف في الجدول
    for (int i = 0; i < orderIds.size(); ++i) {
        // ID
        ordersTable->setItem(i, 0, new QTableWidgetItem(orderIds[i]));
        // Address
        ordersTable->setItem(i, 1, new QTableWidgetItem(orderAddresses[i]));
        // Service
        ordersTable->setItem(i, 2, new QTableWidgetItem(orderServices[i]));
        // Service price (مع تنسيق عشري)
        ordersTable->setItem(i, 3, new QTableWidgetItem(orderServicePrices[i]));
        // Notes
        ordersTable->setItem(i, 4, new QTableWidgetItem(orderNotes[i]));
        // Status
        ordersTable->setItem(i, 5, new QTableWidgetItem(orderStatuses[i]));
    }
}

void search::on_pushButton_clicked()
{
    MainWindow *back=new MainWindow();
    back->show();
    this->close();
}


void search::on_pushButton_2_clicked()
{
    search *sea=new search();
    sea->show();
    this->close();
}

