#include "cinemania.h"
#include "./ui_cinemania.h"
#include "listmaker.h"
#include "movie.h"
#include <chrono>
CineMania::CineMania(QWidget *parent, movie movArr[], int listSize)
    : QMainWindow(parent)
    , ui(new Ui::CineMania)
{
    ui->setupUi(this);
    this->movArr = movArr;
    this->listSize = listSize;
    for (size_t i = 0; i < listSize; i++) {
            ui->listWidget->addItem(QString::fromStdString(movArr[i].getTitle()));
    }

}

CineMania::~CineMania()
{
    delete ui;
}
void swap_abc(movie& a, movie& b) {
    movie temp = a;
    a = b;
    b = temp;
}

// quicksort and partition functions inspired from geeks for geeks
int partitionGenre (movie arr[], int low, int high) {
    string pivotGenre = arr[high].getGenre();
    string pivotTitle = arr[high].getTitle();

    int i = (low - 1);

    for (int j = low; j <=high; j++) {
        if (arr[j].getGenre() < pivotGenre || (arr[j].getGenre() == pivotGenre && arr[j].getTitle() < pivotTitle)) {
            i++;
            swap_abc(arr[i], arr[j]);
        }
    }
    swap_abc(arr[i+1], arr[high]);
    return (i+1);
}

int partitionRating (movie arr[], int low, int high) {
    string pivotRating = arr[high].getRating();
    string pivotTitle = arr[high].getTitle();

    int i = (low - 1);

    for (int j = low; j <=high; j++) {
        if (arr[j].getRating() > pivotRating || (arr[j].getRating() == pivotRating && arr[j].getTitle() < pivotTitle)) {
            i++;
            swap_abc(arr[i], arr[j]);
        }
    }
    swap_abc(arr[i+1], arr[high]);
    return (i+1);
}

int partitionTitle (movie arr[], int low, int high) {
    string pivotTitle = arr[high].getTitle();

    int i = (low - 1);

    for (int j = low; j <=high; j++) {
        if (arr[j].getTitle() < pivotTitle) {
            i++;
            swap_abc(arr[i], arr[j]);
        }
    }
    swap_abc(arr[i+1], arr[high]);
    return (i+1);
}

void quickSortGenre (movie arr[], int low, int high) {
    if (low < high) {
        int pi = partitionGenre(arr, low, high);
        quickSortGenre(arr, low, pi-1);
        quickSortGenre(arr,pi+1,high);
    }
}

void quickSortRating (movie arr[], int low, int high) {
    if (low < high) {
        int pi = partitionRating(arr, low, high);
        quickSortRating(arr, low, pi - 1);
        quickSortRating(arr,pi + 1, high);
    }
}

void quickSortTitle (movie arr[], int low, int high) {
    if (low < high) {
        int pi = partitionTitle(arr, low, high);
        quickSortTitle(arr, low, pi-1);
        quickSortTitle(arr,pi+1,high);
    }
}

void mergeGenre(movie arr[], int const left, int const mid, int const right) {
    int const subArr1 = mid - left + 1;
    int const subArr2 = right - mid;

    auto *leftArr = new movie[subArr1], *rightArr = new movie[subArr2];

    for(auto i = 0; i < subArr1; i++) {
        leftArr[i] = arr[left+i];
    }
    for (auto j = 0; j < subArr2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }

    auto indexSubArr1 = 0, indexSubArr2 = 0;
    int indexMergedArr = left;

    while (indexSubArr1 < subArr1 && indexSubArr2 < subArr2) {
        if (leftArr[indexSubArr1].getGenre() < rightArr[indexSubArr2].getGenre() ||
            (leftArr[indexSubArr1].getGenre() == rightArr[indexSubArr2].getGenre() &&
             leftArr[indexSubArr1].getTitle() < rightArr[indexSubArr2].getTitle())) {
            arr[indexMergedArr] = leftArr[indexSubArr1];
            indexSubArr1++;
        }
        else {
            arr[indexMergedArr] = rightArr[indexSubArr2];
            indexSubArr2++;
        }
        indexMergedArr++;
    }

    while (indexSubArr1 < subArr1) {
        arr[indexMergedArr] = leftArr[indexSubArr1];
        indexSubArr1++;
        indexMergedArr++;
    }

    while (indexSubArr2 < subArr2) {
        arr[indexMergedArr] = rightArr[indexSubArr2];
        indexSubArr2++;
        indexMergedArr++;
    }

    delete[] leftArr;
    delete[] rightArr;

}

void mergeRating(movie arr[], int const left, int const mid, int const right) {
    int const subArr1 = mid - left + 1;
    int const subArr2 = right - mid;

    auto *leftArr = new movie[subArr1], *rightArr = new movie[subArr2];

    for(auto i = 0; i < subArr1; i++) {
        leftArr[i] = arr[left+i];
    }
    for (auto j = 0; j < subArr2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }

    auto indexSubArr1 = 0, indexSubArr2 = 0;
    int indexMergedArr = left;

    while (indexSubArr1 < subArr1 && indexSubArr2 < subArr2) {
        if (leftArr[indexSubArr1].getRating() > rightArr[indexSubArr2].getRating() ||
            (leftArr[indexSubArr1].getRating() == rightArr[indexSubArr2].getRating() &&
             leftArr[indexSubArr1].getTitle() < rightArr[indexSubArr2].getTitle())) {
            arr[indexMergedArr] = leftArr[indexSubArr1];
            indexSubArr1++;
        }
        else {
            arr[indexMergedArr] = rightArr[indexSubArr2];
            indexSubArr2++;
        }
        indexMergedArr++;
    }

    while (indexSubArr1 < subArr1) {
        arr[indexMergedArr] = leftArr[indexSubArr1];
        indexSubArr1++;
        indexMergedArr++;
    }

    while (indexSubArr2 < subArr2) {
        arr[indexMergedArr] = rightArr[indexSubArr2];
        indexSubArr2++;
        indexMergedArr++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void mergeTitle(movie arr[], int const left, int const mid, int const right) {
    int const subArr1 = mid - left + 1;
    int const subArr2 = right - mid;

    auto *leftArr = new movie[subArr1], *rightArr = new movie[subArr2];

    for(auto i = 0; i < subArr1; i++) {
        leftArr[i] = arr[left+i];
    }
    for (auto j = 0; j < subArr2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }

    auto indexSubArr1 = 0, indexSubArr2 = 0;
    int indexMergedArr = left;

    while (indexSubArr1 < subArr1 && indexSubArr2 < subArr2) {
        if (leftArr[indexSubArr1].getTitle() < rightArr[indexSubArr2].getTitle()) {
            arr[indexMergedArr] = leftArr[indexSubArr1];
            indexSubArr1++;
        }
        else {
            arr[indexMergedArr] = rightArr[indexSubArr2];
            indexSubArr2++;
        }
        indexMergedArr++;
    }

    while (indexSubArr1 < subArr1) {
        arr[indexMergedArr] = leftArr[indexSubArr1];
        indexSubArr1++;
        indexMergedArr++;
    }

    while (indexSubArr2 < subArr2) {
        arr[indexMergedArr] = rightArr[indexSubArr2];
        indexSubArr2++;
        indexMergedArr++;
    }

    delete[] leftArr;
    delete[] rightArr;

}

void mergeSortGenre (movie arr[], int const begin, int const end) {
    if (begin >= end) {
        return;
    }
    int mid = begin + (end - begin) / 2;
    mergeSortGenre(arr, begin, mid);
    mergeSortGenre(arr, mid + 1, end);
    mergeGenre(arr, begin, mid, end);
}

void mergeSortRating (movie arr[], int const begin, int const end) {
    if (begin >= end) {
        return;
    }
    int mid = begin + (end - begin) / 2;
    mergeSortRating(arr, begin, mid);
    mergeSortRating(arr, mid + 1, end);
    mergeRating(arr, begin, mid, end);
}

void mergeSortTitle (movie arr[], int const begin, int const end) {
    if (begin >= end) {
        return;
    }
    int mid = begin + (end - begin) / 2;
    mergeSortTitle(arr, begin, mid);
    mergeSortTitle(arr, mid + 1, end);
    mergeTitle(arr, begin, mid, end);
}
void CineMania::on_pushButton_clicked()
{
    this->hide();
    ListMaker listmaker(nullptr, movArr, listSize);
    listmaker.setModal(true);
    listmaker.exec();
}


void CineMania::on_pushButton_2_clicked()
{
    chrono::time_point<std::chrono::system_clock> start, end;
    ui->listWidget->clear();
    start = chrono::system_clock::now();
    mergeSortGenre(movArr, 0, listSize-1);
    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    for (size_t i = 0; i < listSize; i++) {
        ui->listWidget->addItem(QString::fromStdString(movArr[i].getTitle()));
    }
    QString timer = "Time in Seconds: ";
    timer += QString::number(elapsed_seconds.count());
    ui->label_2->setText(timer);

}

