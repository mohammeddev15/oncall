#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "about.h"
#include"add_req.h"
#include"search.h"
#include <QScreen>
#include"terms.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Oncall");
    setWindowIcon(QIcon(":/icons/professional-logo-fored-as-a-sta.png"));
    setGeometry(QGuiApplication::primaryScreen()->availableGeometry());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    about *abou=new about();
    abou->show();
    this->close();
}


void MainWindow::on_pushButton_3_clicked()
{
    add_req *add=new add_req();
    add->show();
    this->close();
}


void MainWindow::on_pushButton_2_clicked()
{
    search *sear=new search();
    sear->show();
    this->close();
}


void MainWindow::on_pushButton_4_clicked()
{
    Terms *term =new Terms();
    term->show();
    this->close();
}

