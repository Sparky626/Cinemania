#include "listmaker.h"
#include "ui_listmaker.h"

ListMaker::ListMaker(QWidget *parent, movie movArr[], int listSize)
    : QDialog(parent)
    , ui(new Ui::ListMaker)
{
    ui->setupUi(this);
    ui->comboGenreBox->addItem("All");
    ui->comboGenreBox->addItem("Action");
    ui->comboGenreBox->addItem("Adult");
    ui->comboGenreBox->addItem("Adventure");
    ui->comboGenreBox->addItem("Animation");
    ui->comboGenreBox->addItem("Biography");
    ui->comboGenreBox->addItem("Comedy");
    ui->comboGenreBox->addItem("Crime");
    ui->comboGenreBox->addItem("Documentary");
    ui->comboGenreBox->addItem("Drama");
    ui->comboGenreBox->addItem("Family");
    ui->comboGenreBox->addItem("Fantasy");
    ui->comboGenreBox->addItem("Film-Noir");
    ui->comboGenreBox->addItem("Horror");
    ui->comboGenreBox->addItem("Musical");
    ui->comboGenreBox->addItem("Mystery");
    ui->comboGenreBox->addItem("Romance");
    ui->comboGenreBox->addItem("War");
    ui->comboGenreBox->addItem("Western");
    ui->comboSortBox->addItem("None");
    ui->comboSortBox->addItem("Title");
    ui->comboSortBox->addItem("Genre");
    ui->comboSortBox->addItem("Rating");
    ui->comboAlgoBox->addItem("None");
    ui->comboAlgoBox->addItem("Merge");
    ui->comboAlgoBox->addItem("Quick");
    this->movArr = movArr;
    this->unchangedArr = movArr;
    this->listSize = listSize;
    QPixmap pix("Cinemania_Logo.png");
    ui->logo_label->setPixmap(pix);
    for (size_t i = 0; i < listSize; i++) {
        string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
        ui->listMovieWidget->addItem(QString::fromStdString(text));
    }
}

ListMaker::~ListMaker()
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

void ListMaker::on_comboGenreBox_activated(int index)
{
    switch(index){
    case 0:
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
            ui->listMovieWidget->addItem(QString::fromStdString(text));
        }
        break;
    case 1:
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Action"){
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 2:
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Adult"){
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 3:
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Adventure"){
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 4:
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Animation"){
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 5:
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Biography"){
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 6:
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Comedy"){
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 7:
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Crime"){
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 8:
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Documentary"){
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 9:
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Drama"){
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 10:
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Family"){
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 11:
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Fantasy"){
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 12:
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Film-Noir"){
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 13:
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Horror"){
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 14:
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Musical"){
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 15:
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Mystery"){
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 16:
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Romance"){
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 17:
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "War"){
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 18:
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Western"){
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    }

}

void ListMaker::on_comboSortBox_activated(int index)
{

}


void ListMaker::on_comboAlgoBox_activated(int index)
{
    chrono::duration<double> elapsed_seconds;
    chrono::time_point<std::chrono::system_clock> start, end;
    QString timer = "";
    switch(index){
    case 0:
        break;
    case 1:
        switch (ui->comboAlgoBox->currentIndex()){
            case 0:
                break;
            case 1:
                movArr = unchangedArr;
                ui->listMovieWidget->clear();
                start = chrono::system_clock::now();
                mergeSortTitle(movArr, 0, listSize-1);
                end = chrono::system_clock::now();
                elapsed_seconds = end - start;
                if (ui->comboGenreBox->currentIndex() == 0){
                    for (size_t i = 0; i < listSize; i++) {
                        string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                        ui->listMovieWidget->addItem(QString::fromStdString(text));
                    }
                }
                else{
                    for (size_t i = 0; i < listSize; i++) {
                        if (movArr[i].getGenre() == ui->comboGenreBox->itemData(ui->comboGenreBox->currentIndex()).toString().toStdString()){
                            string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                            ui->listMovieWidget->addItem(QString::fromStdString(text));
                        }
                    }
                }
                timer = "Time in Seconds: ";
                timer += QString::number(elapsed_seconds.count());
                ui->timer->setText(timer);
                break;
            case 2:
                movArr = unchangedArr;
                ui->listMovieWidget->clear();
                start = chrono::system_clock::now();
                mergeSortGenre(movArr, 0, listSize-1);
                end = chrono::system_clock::now();
                elapsed_seconds = end - start;
                if (ui->comboGenreBox->currentIndex() == 0){
                    for (size_t i = 0; i < listSize; i++) {
                        string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                        ui->listMovieWidget->addItem(QString::fromStdString(text));
                    }
                }
                else{
                    for (size_t i = 0; i < listSize; i++) {
                        if (movArr[i].getGenre() == ui->comboGenreBox->itemData(ui->comboGenreBox->currentIndex()).toString().toStdString()){
                            string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                            ui->listMovieWidget->addItem(QString::fromStdString(text));
                        }
                    }
                }
                timer = "Time in Seconds: ";
                timer += QString::number(elapsed_seconds.count());
                ui->timer->setText(timer);
                break;
            case 3:
                movArr = unchangedArr;
                ui->listMovieWidget->clear();
                start = chrono::system_clock::now();
                mergeSortRating(movArr, 0, listSize-1);
                end = chrono::system_clock::now();
                elapsed_seconds = end - start;
                if (ui->comboGenreBox->currentIndex() == 0){
                    for (size_t i = 0; i < listSize; i++) {
                        string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                        ui->listMovieWidget->addItem(QString::fromStdString(text));
                    }
                }
                else{
                    for (size_t i = 0; i < listSize; i++) {
                        if (movArr[i].getGenre() == ui->comboGenreBox->itemData(ui->comboGenreBox->currentIndex()).toString().toStdString()){
                            string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                            ui->listMovieWidget->addItem(QString::fromStdString(text));
                        }
                    }
                }
                timer = "Time in Seconds: ";
                timer += QString::number(elapsed_seconds.count());
                ui->timer->setText(timer);
                break;
        }
        break;
    case 2:
        switch (ui->comboAlgoBox->currentIndex()){
        case 0:
            break;
        case 1:
            movArr = unchangedArr;
            ui->listMovieWidget->clear();
            start = chrono::system_clock::now();
            quickSortTitle(movArr, 0, listSize-1);
            end = chrono::system_clock::now();
            elapsed_seconds = end - start;
            if (ui->comboGenreBox->currentIndex() == 0){
                for (size_t i = 0; i < listSize; i++) {
                    string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                    ui->listMovieWidget->addItem(QString::fromStdString(text));
                }
            }
            else{
                for (size_t i = 0; i < listSize; i++) {
                    if (movArr[i].getGenre() == ui->comboGenreBox->itemData(ui->comboGenreBox->currentIndex()).toString().toStdString()){
                        string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                        ui->listMovieWidget->addItem(QString::fromStdString(text));
                    }
                }
            }
            timer = "Time in Seconds: ";
            timer += QString::number(elapsed_seconds.count());
            ui->timer->setText(timer);
            break;
        case 2:
            movArr = unchangedArr;
            ui->listMovieWidget->clear();
            start = chrono::system_clock::now();
            quickSortGenre(movArr, 0, listSize-1);
            end = chrono::system_clock::now();
            elapsed_seconds = end - start;
            if (ui->comboGenreBox->currentIndex() == 0){
                for (size_t i = 0; i < listSize; i++) {
                    string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                    ui->listMovieWidget->addItem(QString::fromStdString(text));
                }
            }
            else{
                for (size_t i = 0; i < listSize; i++) {
                    if (movArr[i].getGenre() == ui->comboGenreBox->itemData(ui->comboGenreBox->currentIndex()).toString().toStdString()){
                        string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                        ui->listMovieWidget->addItem(QString::fromStdString(text));
                    }
                }
            }
            timer = "Time in Seconds: ";
            timer += QString::number(elapsed_seconds.count());
            ui->timer->setText(timer);
            break;
        case 3:
            movArr = unchangedArr;
            ui->listMovieWidget->clear();
            start = chrono::system_clock::now();
            quickSortRating(movArr, 0, listSize-1);
            end = chrono::system_clock::now();
            elapsed_seconds = end - start;
            if (ui->comboGenreBox->currentIndex() == 0){
                for (size_t i = 0; i < listSize; i++) {
                    string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                    ui->listMovieWidget->addItem(QString::fromStdString(text));
                }
            }
            else{
                for (size_t i = 0; i < listSize; i++) {
                    if (movArr[i].getGenre() == ui->comboGenreBox->itemData(ui->comboGenreBox->currentIndex()).toString().toStdString()){
                        string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                        ui->listMovieWidget->addItem(QString::fromStdString(text));
                    }
                }
            }
            timer = "Time in Seconds: ";
            timer += QString::number(elapsed_seconds.count());
            ui->timer->setText(timer);
            break;
        }
        break;
    }
}
