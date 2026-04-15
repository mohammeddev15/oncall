#ifndef NEW_H
#define NEW_H

#include <QMainWindow>

namespace Ui {
class new;
}

class new : public QMainWindow
{
    Q_OBJECT

public:
    explicit new (QWidget *parent = nullptr);
    ~new ();

private:
    Ui::new *ui;
};

#endif // NEW_H
