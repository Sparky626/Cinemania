#ifndef LISTMAKER_H
#define LISTMAKER_H
#include "movie.h"
#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class ListMaker;
}

class ListMaker : public QDialog
{
    Q_OBJECT

public:
    movie* movArr = {};
    movie* unchangedArr = {};
    vector<movie> All;
    vector<movie> Action;
    vector<movie> Adult;
    vector<movie> Adventure;
    vector<movie> Animation;
    vector<movie> Comedy;
    vector<movie> Biography;
    vector<movie> Crime;
    vector<movie> Documentary;
    vector<movie> Drama;
    vector<movie> Family;
    vector<movie> Fantasy;
    vector<movie> FilmNoir;
    vector<movie> Horror;
    vector<movie> Musical;
    vector<movie> Mystery;
    vector<movie> Romance;
    vector<movie> War;
    vector<movie> Western;
    vector<pair<string,vector<movie>>> lists;
    vector<movie> currentList;
    vector<pair<string,vector<movie>>> getLists(){
        return this->lists;
    }
    int listSize = 0;
    explicit ListMaker(QWidget *parent = nullptr, movie movArr[] = {}, movie unchangedArr[] = {}, int listSize = 0, vector<pair<string,vector<movie>>> lists = {});
    ~ListMaker();

private slots:

    void on_sortPushButton_clicked();

    void on_saveListButton_clicked();

    void on_listMovieWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listUserWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::ListMaker *ui;

    void genreListFilter(int index);


};

#endif // LISTMAKER_H
