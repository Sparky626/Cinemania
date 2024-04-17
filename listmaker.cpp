#include "listmaker.h"
#include "ui_listmaker.h"

ListMaker::ListMaker(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ListMaker)
{
    ui->setupUi(this);
}

ListMaker::~ListMaker()
{
    delete ui;
}
