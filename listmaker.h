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
    movie* movArr = {};
    movie* unchangedArr = {};
    int listSize = 0;
    explicit ListMaker(QWidget *parent = nullptr, movie movArr[] = {}, int listSize = 0);
    ~ListMaker();

private slots:
    void on_comboGenreBox_activated(int index);

    void on_comboSortBox_activated(int index);

    void on_comboAlgoBox_activated(int index);

    void on_sortPushButton_clicked();

    void on_ListMaker_destroyed();

private:
    Ui::ListMaker *ui;

    void genreListFilter(int index);
};

#endif // LISTMAKER_H
