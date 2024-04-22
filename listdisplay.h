#ifndef LISTDISPLAY_H
#define LISTDISPLAY_H
#include "movie.h"
#include <QDialog>

namespace Ui {
class listdisplay;
}

// list display class from QDialog
class listdisplay : public QDialog
{
    Q_OBJECT

public:
    vector<pair<string,vector<movie>>> lists; // vector of pairs to store lists of movies
    // constructor and destructor
    explicit listdisplay(QWidget *parent = nullptr, vector<pair<string,vector<movie>>> lists = {});
    ~listdisplay();

private slots:
               // slot to handle list name combo box
    void on_listNameComboBox_activated(int index);

private:
    Ui::listdisplay *ui; // pointer to ui
};

#endif // LISTDISPLAY_H
