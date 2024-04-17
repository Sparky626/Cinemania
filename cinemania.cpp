#include "cinemania.h"
#include "./ui_cinemania.h"
#include "listmaker.h"
#include "movie.h"
#include <chrono>
CineMania::CineMania(QWidget *parent, vector<movie> movList)
    : QMainWindow(parent)
    , ui(new Ui::CineMania)
{
    ui->setupUi(this);
    this->movList = movList;
    for (movie m : movList){
        ui->listWidget->addItem(QString::fromStdString(m.getTitle()));
    }

}

CineMania::~CineMania()
{
    delete ui;
}

void CineMania::on_pushButton_clicked()
{
    this->hide();
    ListMaker listmaker(nullptr, movList);
    listmaker.setModal(true);
    listmaker.exec();
}
void swap_abc(movie& a, movie& b) {
    movie temp = a;
    a = b;
    b = temp;
}

vector<movie>::iterator partition(vector<movie>& arr, vector<movie>::iterator low, vector<movie>::iterator high) {
    string pivotGenre = high->getGenre();
    string pivotTitle = high->getTitle();

    auto i = low;

    for (auto j = low; j != high; j++) {
        if (j->getGenre() < pivotGenre || (j->getGenre() == pivotGenre && j->getTitle() < pivotTitle)) {
            swap_abc(*i, *j);
            i++;
        }
    }
    swap_abc(*i, *high);
    return i;
}

void quickSort(vector<movie>& arr, vector<movie>::iterator low, vector<movie>::iterator high) {
    if (low < high) {
        auto pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(vector<movie>& arr, vector<movie>& temp, int const left, int const mid, int const right) {
    int indexSubArr1 = left;
    int indexSubArr2 = mid + 1;
    int indexMergedArr = left;

    while (indexSubArr1 <= mid && indexSubArr2 <= right) {
        if (arr[indexSubArr1].getGenre() < arr[indexSubArr2].getGenre() ||
            (arr[indexSubArr1].getGenre() == arr[indexSubArr2].getGenre() &&
             arr[indexSubArr1].getTitle() < arr[indexSubArr2].getTitle())) {
            temp[indexMergedArr] = arr[indexSubArr1];
            indexSubArr1++;
        } else {
            temp[indexMergedArr] = arr[indexSubArr2];
            indexSubArr2++;
        }
        indexMergedArr++;
    }

    while (indexSubArr1 <= mid) {
        temp[indexMergedArr] = arr[indexSubArr1];
        indexMergedArr++;
        indexSubArr1++;
    }

    while (indexSubArr2 <= right) {
        temp[indexMergedArr] = arr[indexSubArr2];
        indexMergedArr++;
        indexSubArr2++;
    }

    for (int i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

void mergeSort(vector<movie>& arr, vector<movie>& temp, int const begin, int const end) {
    if (begin < end) {
        int mid = begin + (end - begin) / 2;
        mergeSort(arr, temp, begin, mid);
        mergeSort(arr, temp, mid + 1, end);
        merge(arr, temp, begin, mid, end);
    }
}

void CineMania::on_pushButton_2_clicked()
{
    chrono::time_point<std::chrono::system_clock> start, end;
    ui->listWidget->clear();
    vector<movie> temp(movList.size());
    start = chrono::system_clock::now();
    mergeSort(movList, temp, 0, movList.size()-1);
    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    for (movie m : movList){
        ui->listWidget->addItem(QString::fromStdString(m.getTitle()));
    }
    QString timer = "Time in Seconds: ";
    timer += QString::number(elapsed_seconds.count());
    ui->label_2->setText(timer);

}

