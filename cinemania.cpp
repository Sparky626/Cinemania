#include "cinemania.h"
#include "./ui_cinemania.h"

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
