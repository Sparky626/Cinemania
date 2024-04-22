#ifndef CINEMANIA_H
#define CINEMANIA_H
#include "movie.h"
#include <QListWidget>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class CineMania;
}
QT_END_NAMESPACE

class CineMania : public QMainWindow
{
    Q_OBJECT

public:
    // public variables to store arrays of movie objects for top 10 in each category
    movie* movArr = {};
    movie* unchangedArr = {};
    movie top10MovArr[10] = {};
    movie top10ActArr[10] = {};
    movie top10AdvArr[10] = {};
    movie top10AnimArr[10] = {};
    movie top10ComArr[10] = {};
    movie top10DramArr[10] = {};
    movie top10RomArr[10] = {};
    int listSize = 0;
    vector<pair<string,vector<movie>>> lists = {};

    // constructor and destructor
    CineMania(QWidget *parent = nullptr, movie movArr[] = {}, movie unchangedArr[] = {}, int listSize = 0, vector<pair<string,vector<movie>>> lists = {});
    ~CineMania();

private slots:
               // private slots (functions called in response to a particular signal) for button clicked and item clicked signals
    void on_createListButton_clicked();

    void on_pushButton_clicked();

    void on_listMovieWidget_itemClicked(QListWidgetItem *item);

    void on_listMovieWidget_2_itemClicked(QListWidgetItem *item);

    void on_listMovieWidget_3_itemClicked(QListWidgetItem *item);

    void on_listMovieWidget_4_itemClicked(QListWidgetItem *item);

    void on_listMovieWidget_5_itemClicked(QListWidgetItem *item);

    void on_listMovieWidget_6_itemClicked(QListWidgetItem *item);

    void on_listMovieWidget_7_itemClicked(QListWidgetItem *item);

    void on_listMovieWidget_8_itemClicked(QListWidgetItem *item);

    void on_showListsButton_clicked();

private:
    Ui::CineMania *ui; // pointer to ui
};
#endif // CINEMANIA_H
