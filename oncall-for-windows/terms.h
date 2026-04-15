#ifndef TERMS_H
#define TERMS_H

#include <QMainWindow>

namespace Ui {
class Terms;
}

class Terms : public QMainWindow
{
    Q_OBJECT

public:
    explicit Terms(QWidget *parent = nullptr);
    ~Terms();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Terms *ui;
};

#endif // TERMS_H
