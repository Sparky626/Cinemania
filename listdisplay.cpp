#include "listdisplay.h"
#include "ui_listdisplay.h"
#include <iostream>

// constructor
listdisplay::listdisplay(QWidget *parent, vector<pair<string,vector<movie>>> lists)
    : QDialog(parent)
    , ui(new Ui::listdisplay)
{
    ui->setupUi(this); // set up ui
    ui->listNameComboBox->addItem("None"); // none as default option
    this->lists = lists;
    // add names of lists to the combo box
    for(pair<string,vector<movie>> l : lists){
        ui->listNameComboBox->addItem(QString::fromStdString(l.first));
    }

}

// destructor
listdisplay::~listdisplay()
{
    delete ui;
}

void listdisplay::on_listNameComboBox_activated(int index)
{
    ui->listWidget->clear(); // clear widget list every time a list name is selected in the combo box
    // iterate through movies in selected list and add them to the list widget
    if(this->lists[index-1].second.empty() != true){
        for(movie& m : this->lists[index-1].second){
            ui->listWidget->addItem(QString::fromStdString(m.getTitle() + + " - Genre: " + m.getGenre() + " - Rating: " + m.getRating() + " - User Rating: " + m.getUserRating()));
        }
    }

}
