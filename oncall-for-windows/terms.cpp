#include "terms.h"
#include "ui_terms.h"
#include <QScreen>
#include"mainwindow.h"

Terms::Terms(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Terms)
{
    ui->setupUi(this);
    setWindowTitle("Oncall");
    setWindowIcon(QIcon(":/icons/professional-logo-fored-as-a-sta.png"));
    setGeometry(QGuiApplication::primaryScreen()->availableGeometry());
}

Terms::~Terms()
{
    delete ui;
}

void Terms::on_pushButton_clicked()
{
    MainWindow *greet =new MainWindow();
    greet->show();
    this->close();
}

