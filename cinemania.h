#ifndef CINEMANIA_H
#define CINEMANIA_H

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
    CineMania(QWidget *parent = nullptr);
    ~CineMania();

private:
    Ui::CineMania *ui;
};
#endif // CINEMANIA_H
