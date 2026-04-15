#include "about.h"
#include "ui_about.h"
#include"mainwindow.h"

about::about(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::about)
{
    ui->setupUi(this);
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

