#include "cinemania.h"
#include "./ui_cinemania.h"
#include "listmaker.h"

CineMania::CineMania(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CineMania)
{
    ui->setupUi(this);
}

CineMania::~CineMania()
{
    delete ui;
}

void CineMania::on_pushButton_clicked()
{
    this->hide();
    ListMaker listmaker;
    listmaker.setModal(true);
    listmaker.exec();
}

