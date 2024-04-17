#ifndef LISTMAKER_H
#define LISTMAKER_H
#include "movie.h"
#include <QDialog>

namespace Ui {
class ListMaker;
}

class ListMaker : public QDialog
{
    Q_OBJECT

public:
    explicit ListMaker(QWidget *parent = nullptr, movie movArr[] = {}, int listSize = 0);
    ~ListMaker();

private:
    Ui::ListMaker *ui;
};

#endif // LISTMAKER_H
