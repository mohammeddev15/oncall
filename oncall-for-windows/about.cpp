#include "about.h"
#include "ui_about.h"
#include <QScreen>
#include "mainwindow.h"

about::about(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::about)
{
    ui->setupUi(this);
    setWindowTitle("Oncall");
    setWindowIcon(QIcon(":/icons/professional-logo-fored-as-a-sta.png"));
    setGeometry(QGuiApplication::primaryScreen()->availableGeometry());
}


about::~about()
{
    delete ui;
}

void about::on_pushButton_clicked()
{
    MainWindow *back=new MainWindow();
    back->show();
    this->close();
}

