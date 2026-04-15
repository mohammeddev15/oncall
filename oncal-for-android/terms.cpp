#include "terms.h"
#include "ui_terms.h"
#include"mainwindow.h"

Terms::Terms(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Terms)
{
    ui->setupUi(this);
}

Terms::~Terms()
{
    delete ui;
}

void Terms::on_pushButton_clicked()
{
    MainWindow *greet=new MainWindow();
    greet->show();
    this->close();
}

