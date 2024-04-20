#include "cinemania.h"
#include "./ui_cinemania.h"
#include "listmaker.h"
#include "movie.h"
#include <QPixmap>
#include <synchapi.h>
#include <iostream>


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

CineMania::CineMania(QWidget *parent, movie movArr[], movie unchangedArr[], int listSize)
    : QMainWindow(parent)
    , ui(new Ui::CineMania)
{

    ui->setupUi(this);
    ui->progressBar->hide();
    ui->groupBox->hide();
    QPixmap pix("Cinemania_Logo.png");
    ui->logo_label->setPixmap(pix);
    this->movArr = movArr;
    this->unchangedArr = unchangedArr;
    this->listSize = listSize;
    QString text = "Number of tuples: ";
    ui->label_9->setText(text + QString::number(listSize));


    for (size_t i = 0; i < listSize; i++) {
        string text = movArr[i].getTitle();
        unchangedArr[i].setIndex(i);
        ui->listMovieWidget->addItem(QString::fromStdString(text));
    }
    cquickSortRating(movArr,0,listSize-1);
    for (size_t i = 0; i < 10; i++) {
        string text = movArr[i].getTitle();
        top10MovArr[i] = movArr[i];
        ui->listMovieWidget_2->addItem(QString::fromStdString(text));
    }
    int count = 0;
    for (size_t i = 0; count < 10; i++) {
        if(movArr[i].getGenre() == "Action"){
            string text = movArr[i].getTitle();
            top10ActArr[count] = movArr[i];
            ui->listMovieWidget_3->addItem(QString::fromStdString(text));
            count++;
        }
    }
    count = 0;
    for (size_t i = 0; count < 10; i++) {
        if(movArr[i].getGenre() == "Adventure"){
            string text = movArr[i].getTitle();
            top10AdvArr[count] = movArr[i];
            ui->listMovieWidget_4->addItem(QString::fromStdString(text));
            count++;
        }
    }
    count = 0;
    for (size_t i = 0; count < 10; i++) {
        if(movArr[i].getGenre() == "Animation"){
            string text = movArr[i].getTitle();
            top10AnimArr[count] = movArr[i];
            ui->listMovieWidget_5->addItem(QString::fromStdString(text));
            count++;
        }
    }
    count = 0;
    for (size_t i = 0; count < 10; i++) {
        if(movArr[i].getGenre() == "Comedy"){
            string text = movArr[i].getTitle();
            top10ComArr[count] = movArr[i];
            ui->listMovieWidget_6->addItem(QString::fromStdString(text));
            count++;
        }
    }
    count = 0;
    for (size_t i = 0; count < 10; i++) {
        if(movArr[i].getGenre() == "Drama"){
            string text = movArr[i].getTitle();
            top10DramArr[count] = movArr[i];
            ui->listMovieWidget_7->addItem(QString::fromStdString(text));
            count++;
        }
    }
    count = 0;
    for (size_t i = 0; count < 10; i++) {
        if(movArr[i].getGenre() == "Romance"){
            string text = movArr[i].getTitle();
            top10RomArr[count] = movArr[i];
            ui->listMovieWidget_8->addItem(QString::fromStdString(text));
            count++;
        }
    }


}

CineMania::~CineMania()
{
    delete ui;
}



void CineMania::on_createListButton_clicked()
{
    ui->progressBar->show();
    ListMaker listmaker(nullptr, unchangedArr, listSize);
    listmaker.setModal(true);
    for (int i = 0; i < 100; i++){
        int value = ui->progressBar->value();
        ui->progressBar->setValue(value+1);
        Sleep(100);
    }
    this->hide();
}

void CineMania::on_pushButton_clicked()
{
    if (ui->listMovieWidget->currentRow() != -1){
        unchangedArr[ui->listMovieWidget->currentRow()].setUserRating(ui->textEdit->toPlainText().toStdString());
    }
    if (ui->listMovieWidget_2->currentRow() != -1){
        int index = top10MovArr[ui->listMovieWidget_2->currentRow()].getIndex();
        top10ActArr[ui->listMovieWidget_2->currentRow()].setUserRating(ui->textEdit->toPlainText().toStdString());
        unchangedArr[index].setUserRating(ui->textEdit->toPlainText().toStdString());
    }
    if (ui->listMovieWidget_3->currentRow() != -1){
        int index = top10AdvArr[ui->listMovieWidget_3->currentRow()].getIndex();
        top10AdvArr[ui->listMovieWidget_3->currentRow()].setUserRating(ui->textEdit->toPlainText().toStdString());
        unchangedArr[index].setUserRating(ui->textEdit->toPlainText().toStdString());
    }
    if (ui->listMovieWidget_4->currentRow() != -1){
        int index = top10ActArr[ui->listMovieWidget_4->currentRow()].getIndex();
        top10ActArr[ui->listMovieWidget_4->currentRow()].setUserRating(ui->textEdit->toPlainText().toStdString());
        unchangedArr[index].setUserRating(ui->textEdit->toPlainText().toStdString());
    }
    if (ui->listMovieWidget_5->currentRow() != -1){
        int index = top10AnimArr[ui->listMovieWidget_5->currentRow()].getIndex();
        top10AnimArr[ui->listMovieWidget_5->currentRow()].setUserRating(ui->textEdit->toPlainText().toStdString());
        unchangedArr[index].setUserRating(ui->textEdit->toPlainText().toStdString());
    }
    if (ui->listMovieWidget_6->currentRow() != -1){
        int index = top10ComArr[ui->listMovieWidget_6->currentRow()].getIndex();
        top10ComArr[ui->listMovieWidget_6->currentRow()].setUserRating(ui->textEdit->toPlainText().toStdString());
        unchangedArr[index].setUserRating(ui->textEdit->toPlainText().toStdString());
    }
    if (ui->listMovieWidget_7->currentRow() != -1){
        int index = top10DramArr[ui->listMovieWidget_7->currentRow()].getIndex();
        top10DramArr[ui->listMovieWidget_7->currentRow()].setUserRating(ui->textEdit->toPlainText().toStdString());
        unchangedArr[index].setUserRating(ui->textEdit->toPlainText().toStdString());
    }
    if (ui->listMovieWidget_8->currentRow() != -1){
        int index = top10ActArr[ui->listMovieWidget_8->currentRow()].getIndex();
        top10RomArr[ui->listMovieWidget_8->currentRow()].setUserRating(ui->textEdit->toPlainText().toStdString());
        unchangedArr[index].setUserRating(ui->textEdit->toPlainText().toStdString());
    }
}





void CineMania::on_listMovieWidget_itemActivated(QListWidgetItem *item)
{
    int currentRow = ui->listMovieWidget->currentRow();
    ui->listMovieWidget_2->clearSelection();
    ui->listMovieWidget_3->clearSelection();
    ui->listMovieWidget_4->clearSelection();
    ui->listMovieWidget_5->clearSelection();
    ui->listMovieWidget_6->clearSelection();
    ui->listMovieWidget_7->clearSelection();
    ui->listMovieWidget_8->clearSelection();
    ui->groupBox->show();
    ui->titleLabel_2->setText(QString::fromStdString(unchangedArr[currentRow].getTitle()));
    ui->genreLabel_2->setText(QString::fromStdString(unchangedArr[currentRow].getGenre()));
    ui->ratingLabel_2->setText(QString::fromStdString(unchangedArr[currentRow].getRating()));
    ui->runtimeLabel_2->setText(QString::fromStdString(unchangedArr[currentRow].getRuntime()));
    ui->releaseYearLabel_2->setText(QString::fromStdString(unchangedArr[currentRow].getYear()));
    ui->textEdit->setText(QString::fromStdString(unchangedArr[currentRow].getUserRating()));
}


void CineMania::on_listMovieWidget_2_itemActivated(QListWidgetItem *item)
{
    int currentRow = ui->listMovieWidget_2->currentRow();
    ui->listMovieWidget->clearSelection();
    ui->listMovieWidget_3->clearSelection();
    ui->listMovieWidget_4->clearSelection();
    ui->listMovieWidget_5->clearSelection();
    ui->listMovieWidget_6->clearSelection();
    ui->listMovieWidget_7->clearSelection();
    ui->listMovieWidget_8->clearSelection();
    ui->groupBox->show();
    ui->titleLabel_2->setText(QString::fromStdString(top10MovArr[currentRow].getTitle()));
    ui->genreLabel_2->setText(QString::fromStdString(top10MovArr[currentRow].getGenre()));
    ui->ratingLabel_2->setText(QString::fromStdString(top10MovArr[currentRow].getRating()));
    ui->runtimeLabel_2->setText(QString::fromStdString(top10MovArr[currentRow].getRuntime()));
    ui->releaseYearLabel_2->setText(QString::fromStdString(top10MovArr[currentRow].getYear()));
    ui->textEdit->setText(QString::fromStdString(top10MovArr[currentRow].getUserRating()));
}


void CineMania::on_listMovieWidget_3_itemActivated(QListWidgetItem *item)
{
    int currentRow = ui->listMovieWidget_3->currentRow();
    ui->listMovieWidget_2->clearSelection();
    ui->listMovieWidget->clearSelection();
    ui->listMovieWidget_4->clearSelection();
    ui->listMovieWidget_5->clearSelection();
    ui->listMovieWidget_6->clearSelection();
    ui->listMovieWidget_7->clearSelection();
    ui->listMovieWidget_8->clearSelection();
    ui->groupBox->show();
    ui->titleLabel_2->setText(QString::fromStdString(top10ActArr[currentRow].getTitle()));
    ui->genreLabel_2->setText(QString::fromStdString(top10ActArr[currentRow].getGenre()));
    ui->ratingLabel_2->setText(QString::fromStdString(top10ActArr[currentRow].getRating()));
    ui->runtimeLabel_2->setText(QString::fromStdString(top10ActArr[currentRow].getRuntime()));
    ui->releaseYearLabel_2->setText(QString::fromStdString(top10ActArr[currentRow].getYear()));
    ui->textEdit->setText(QString::fromStdString(top10ActArr[currentRow].getUserRating()));
}


void CineMania::on_listMovieWidget_4_itemActivated(QListWidgetItem *item)
{
    int currentRow = ui->listMovieWidget_4->currentRow();
    ui->listMovieWidget_2->clearSelection();
    ui->listMovieWidget_3->clearSelection();
    ui->listMovieWidget->clearSelection();
    ui->listMovieWidget_5->clearSelection();
    ui->listMovieWidget_6->clearSelection();
    ui->listMovieWidget_7->clearSelection();
    ui->listMovieWidget_8->clearSelection();
    ui->groupBox->show();
    ui->titleLabel_2->setText(QString::fromStdString(top10AdvArr[currentRow].getTitle()));
    ui->genreLabel_2->setText(QString::fromStdString(top10AdvArr[currentRow].getGenre()));
    ui->ratingLabel_2->setText(QString::fromStdString(top10AdvArr[currentRow].getRating()));
    ui->runtimeLabel_2->setText(QString::fromStdString(top10AdvArr[currentRow].getRuntime()));
    ui->releaseYearLabel_2->setText(QString::fromStdString(top10AdvArr[currentRow].getYear()));
    ui->textEdit->setText(QString::fromStdString(top10AdvArr[currentRow].getUserRating()));
}


void CineMania::on_listMovieWidget_5_itemActivated(QListWidgetItem *item)
{
    int currentRow = ui->listMovieWidget_5->currentRow();
    ui->listMovieWidget_2->clearSelection();
    ui->listMovieWidget_3->clearSelection();
    ui->listMovieWidget_4->clearSelection();
    ui->listMovieWidget->clearSelection();
    ui->listMovieWidget_6->clearSelection();
    ui->listMovieWidget_7->clearSelection();
    ui->listMovieWidget_8->clearSelection();
    ui->groupBox->show();
    ui->titleLabel_2->setText(QString::fromStdString(top10AnimArr[currentRow].getTitle()));
    ui->genreLabel_2->setText(QString::fromStdString(top10AnimArr[currentRow].getGenre()));
    ui->ratingLabel_2->setText(QString::fromStdString(top10AnimArr[currentRow].getRating()));
    ui->runtimeLabel_2->setText(QString::fromStdString(top10AnimArr[currentRow].getRuntime()));
    ui->releaseYearLabel_2->setText(QString::fromStdString(top10AnimArr[currentRow].getYear()));
    ui->textEdit->setText(QString::fromStdString(top10AnimArr[currentRow].getUserRating()));
}


void CineMania::on_listMovieWidget_6_itemActivated(QListWidgetItem *item)
{
    int currentRow = ui->listMovieWidget_6->currentRow();
    ui->listMovieWidget_2->clearSelection();
    ui->listMovieWidget_3->clearSelection();
    ui->listMovieWidget_4->clearSelection();
    ui->listMovieWidget_5->clearSelection();
    ui->listMovieWidget->clearSelection();
    ui->listMovieWidget_7->clearSelection();
    ui->listMovieWidget_8->clearSelection();
    ui->groupBox->show();
    ui->titleLabel_2->setText(QString::fromStdString(top10ComArr[currentRow].getTitle()));
    ui->genreLabel_2->setText(QString::fromStdString(top10ComArr[currentRow].getGenre()));
    ui->ratingLabel_2->setText(QString::fromStdString(top10ComArr[currentRow].getRating()));
    ui->runtimeLabel_2->setText(QString::fromStdString(top10ComArr[currentRow].getRuntime()));
    ui->releaseYearLabel_2->setText(QString::fromStdString(top10ComArr[currentRow].getYear()));
    ui->textEdit->setText(QString::fromStdString(top10ComArr[currentRow].getUserRating()));
}


void CineMania::on_listMovieWidget_7_itemActivated(QListWidgetItem *item)
{
    int currentRow = ui->listMovieWidget_7->currentRow();
    ui->listMovieWidget_2->clearSelection();
    ui->listMovieWidget_3->clearSelection();
    ui->listMovieWidget_4->clearSelection();
    ui->listMovieWidget_5->clearSelection();
    ui->listMovieWidget_6->clearSelection();
    ui->listMovieWidget->clearSelection();
    ui->listMovieWidget_8->clearSelection();
    ui->groupBox->show();
    ui->titleLabel_2->setText(QString::fromStdString(top10DramArr[currentRow].getTitle()));
    ui->genreLabel_2->setText(QString::fromStdString(top10DramArr[currentRow].getGenre()));
    ui->ratingLabel_2->setText(QString::fromStdString(top10DramArr[currentRow].getRating()));
    ui->runtimeLabel_2->setText(QString::fromStdString(top10DramArr[currentRow].getRuntime()));
    ui->releaseYearLabel_2->setText(QString::fromStdString(top10DramArr[currentRow].getYear()));
    ui->textEdit->setText(QString::fromStdString(top10DramArr[currentRow].getUserRating()));
}


void CineMania::on_listMovieWidget_8_itemActivated(QListWidgetItem *item)
{
    int currentRow = ui->listMovieWidget_8->currentRow();
    ui->listMovieWidget_2->clearSelection();
    ui->listMovieWidget_3->clearSelection();
    ui->listMovieWidget_4->clearSelection();
    ui->listMovieWidget_5->clearSelection();
    ui->listMovieWidget_6->clearSelection();
    ui->listMovieWidget_7->clearSelection();
    ui->listMovieWidget->clearSelection();
    ui->groupBox->show();
    ui->titleLabel_2->setText(QString::fromStdString(top10RomArr[currentRow].getTitle()));
    ui->genreLabel_2->setText(QString::fromStdString(top10RomArr[currentRow].getGenre()));
    ui->ratingLabel_2->setText(QString::fromStdString(top10RomArr[currentRow].getRating()));
    ui->runtimeLabel_2->setText(QString::fromStdString(top10RomArr[currentRow].getRuntime()));
    ui->releaseYearLabel_2->setText(QString::fromStdString(top10RomArr[currentRow].getYear()));
    ui->textEdit->setText(QString::fromStdString(top10RomArr[currentRow].getUserRating()));
}

