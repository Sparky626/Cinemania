#include "listmaker.h"
#include "ui_listmaker.h"

ListMaker::ListMaker(QWidget *parent, movie movArr[], int listSize)
    : QDialog(parent)
    , ui(new Ui::ListMaker)
{
    ui->setupUi(this);
    for (size_t i = 0; i < listSize; i++) {
        ui->listWidget->addItem(QString::fromStdString(movArr[i].getTitle()));
    }
}

ListMaker::~ListMaker()
{
    delete ui;
}
