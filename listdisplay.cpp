#include "listdisplay.h"
#include "ui_listdisplay.h"
#include <iostream>
listdisplay::listdisplay(QWidget *parent, vector<pair<string,vector<movie>>> lists)
    : QDialog(parent)
    , ui(new Ui::listdisplay)
{
    ui->setupUi(this);
    ui->listNameComboBox->addItem("None");
    this->lists = lists;
    for(pair<string,vector<movie>> l : lists){
        ui->listNameComboBox->addItem(QString::fromStdString(l.first));
    }



}


listdisplay::~listdisplay()
{
    delete ui;
}

void listdisplay::on_listNameComboBox_activated(int index)
{
    ui->listWidget->clear();
    if(this->lists[index-1].second.empty() != true){
        for(movie& m : this->lists[0].second){
            ui->listWidget->addItem(QString::fromStdString(m.getTitle() + + " - Genre: " + m.getGenre() + " - Rating: " + m.getRating() + " - User Rating: " + m.getUserRating()));
        }
    }

}

