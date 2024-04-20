#ifndef LISTDISPLAY_H
#define LISTDISPLAY_H
#include "movie.h"
#include <QDialog>

namespace Ui {
class listdisplay;
}

class listdisplay : public QDialog
{
    Q_OBJECT

public:
    vector<pair<string,vector<movie>>> lists;
    explicit listdisplay(QWidget *parent = nullptr, vector<pair<string,vector<movie>>> lists = {});
    ~listdisplay();

private slots:

    void on_listNameComboBox_activated(int index);

private:
    Ui::listdisplay *ui;
};

#endif // LISTDISPLAY_H
