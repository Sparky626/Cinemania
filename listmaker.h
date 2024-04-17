#ifndef LISTMAKER_H
#define LISTMAKER_H

#include <QDialog>

namespace Ui {
class ListMaker;
}

class ListMaker : public QDialog
{
    Q_OBJECT

public:
    explicit ListMaker(QWidget *parent = nullptr);
    ~ListMaker();

private:
    Ui::ListMaker *ui;
};

#endif // LISTMAKER_H
