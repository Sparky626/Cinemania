#include "cinemania.h"
#include "./ui_cinemania.h"
#include "listmaker.h"
#include "movie.h"
#include <QPixmap>
#include <synchapi.h>


CineMania::CineMania(QWidget *parent, movie movArr[], int listSize)
    : QMainWindow(parent)
    , ui(new Ui::CineMania)
{

    ui->setupUi(this);
    ui->progressBar->hide();
    ui->groupBox->hide();
    QPixmap pix("Cinemania_Logo.png");
    ui->logo_label->setPixmap(pix);
    this->movArr = movArr;
    this->listSize = listSize;
    for (size_t i = 0; i < listSize; i++) {
        string text = movArr[i].getTitle();
        ui->listMovieWidget->addItem(QString::fromStdString(text));
    }

}

CineMania::~CineMania()
{
    delete ui;
}

void cswap_abc(movie& a, movie& b) {
    movie temp = a;
    a = b;
    b = temp;
}
int cpartitionRating (movie arr[], int low, int high) {
    string pivotRating = arr[high].getRating();
    string pivotTitle = arr[high].getTitle();

    int i = (low - 1);

    for (int j = low; j <=high; j++) {
        if (arr[j].getRating() > pivotRating || (arr[j].getRating() == pivotRating && arr[j].getTitle() < pivotTitle)) {
            i++;
            cswap_abc(arr[i], arr[j]);
        }
    }
    cswap_abc(arr[i+1], arr[high]);
    return (i+1);
}
void cquickSortRating (movie arr[], int low, int high) {
    if (low < high) {
        int pi = cpartitionRating(arr, low, high);
        cquickSortRating(arr, low, pi - 1);
        cquickSortRating(arr,pi + 1, high);
    }
}


void CineMania::on_createListButton_clicked()
{
    ui->progressBar->show();
    ListMaker listmaker(nullptr, movArr, listSize);
    listmaker.setModal(true);
    for (int i = 0; i < 100; i++){
        int value = ui->progressBar->value();
        ui->progressBar->setValue(value+1);
        Sleep(100);
    }
    this->hide();
    listmaker.exec();
}



void CineMania::on_listMovieWidget_currentRowChanged(int currentRow)
{
    ui->groupBox->show();
    ui->titleLabel_2->setText(QString::fromStdString(movArr[currentRow].getTitle()));
    ui->genreLabel_2->setText(QString::fromStdString(movArr[currentRow].getGenre()));
    ui->ratingLabel_2->setText(QString::fromStdString(movArr[currentRow].getRating()));
    ui->runtimeLabel_2->setText(QString::fromStdString(movArr[currentRow].getRuntime()));
    ui->textEdit->setText(QString::fromStdString(movArr[currentRow].getUserRating()));
}




void CineMania::on_pushButton_clicked()
{
    movArr[ui->listMovieWidget->currentRow()].setUserRating(ui->textEdit->toPlainText().toStdString());
}

