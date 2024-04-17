#include "listmaker.h"
#include "ui_listmaker.h"

ListMaker::ListMaker(QWidget *parent, vector<movie> movList)
    : QDialog(parent)
    , ui(new Ui::ListMaker)
{
    ui->setupUi(this);
    for (movie m : movList){
        ui->listWidget->addItem(QString::fromStdString(m.getTitle()));
    }
}

ListMaker::~ListMaker()
{
    delete ui;
}
