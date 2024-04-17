#ifndef CINEMANIA_H
#define CINEMANIA_H
#include "movie.h"
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
    vector<movie> movList = {};
    CineMania(QWidget *parent = nullptr, vector<movie> movList = {});
    ~CineMania();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::CineMania *ui;
};
#endif // CINEMANIA_H
