
#ifndef LISTMAKER_H
#define LISTMAKER_H
#include "movie.h"
#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class ListMaker;
}

class ListMaker : public QDialog // listmaker class is a QDialog subclass
{
    Q_OBJECT

public:
    // public variables to store movie arrays, list of movies, different genres, etc
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

    vector<pair<string,vector<movie>>> lists; // vector of pairs of list names and movies
    vector<movie> currentList; // vector storing list of current movies being displayed
    vector<pair<string,vector<movie>>> getLists(){ // getter to return lists vector
        return this->lists;
    }
    int listSize = 0;

    // constructor and destructor
    explicit ListMaker(QWidget *parent = nullptr, movie movArr[] = {}, movie unchangedArr[] = {}, int listSize = 0, vector<pair<string,vector<movie>>> lists = {});
    ~ListMaker();

private slots:
               // private slots for button clicks and double clicks

    void on_sortPushButton_clicked();

    void on_saveListButton_clicked();

    void on_listMovieWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listUserWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::ListMaker *ui; // pointer to ui object

    void genreListFilter(int index); // private method for filtering lists by genre


};

#endif // LISTMAKER_H
