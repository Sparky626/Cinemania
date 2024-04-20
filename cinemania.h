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
    CineMania(QWidget *parent = nullptr, movie movArr[] = {}, movie unchangedArr[] = {}, int listSize = 0);
    ~CineMania();

private slots:
    void on_createListButton_clicked();

    void on_pushButton_clicked();

    void on_listMovieWidget_itemActivated(QListWidgetItem *item);

    void on_listMovieWidget_2_itemActivated(QListWidgetItem *item);

    void on_listMovieWidget_3_itemActivated(QListWidgetItem *item);

    void on_listMovieWidget_4_itemActivated(QListWidgetItem *item);

    void on_listMovieWidget_5_itemActivated(QListWidgetItem *item);

    void on_listMovieWidget_6_itemActivated(QListWidgetItem *item);

    void on_listMovieWidget_7_itemActivated(QListWidgetItem *item);

    void on_listMovieWidget_8_itemActivated(QListWidgetItem *item);

private:
    Ui::CineMania *ui;
};
#endif // CINEMANIA_H
