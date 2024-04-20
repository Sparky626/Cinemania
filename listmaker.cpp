#include "cinemania.h"
#include "listmaker.h"
#include "ui_listmaker.h"
#include <iostream>
#include <vector>
ListMaker::ListMaker(QWidget *parent, movie movArr[], movie unchangedArr[], int listSize, vector<pair<string,vector<movie>>> lists)
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
    this->unchangedArr = unchangedArr;
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

void ListMaker::genreListFilter(int index){
    switch(index){
    case 0:
        ui->listMovieWidget->clear();
        All.clear();
        for (size_t i = 0; i < listSize; i++) {
            All.push_back(movArr[i]);
            string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
            ui->listMovieWidget->addItem(QString::fromStdString(text));
        }
        break;
    case 1:
        ui->listMovieWidget->clear();
        Action.clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Action"){
                Action.push_back(movArr[i]);
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 2:
        ui->listMovieWidget->clear();
        Adult.clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Adult"){
                Adult.push_back(movArr[i]);
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 3:
        ui->listMovieWidget->clear();
        Adventure.clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Adventure"){
                Adventure.push_back(movArr[i]);
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 4:
        Animation.clear();
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Animation"){
                Animation.push_back(movArr[i]);
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 5:
        Biography.clear();
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Biography"){
                Biography.push_back(movArr[i]);
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 6:
        Comedy.clear();
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Comedy"){
                Comedy.push_back(movArr[i]);
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 7:
        Crime.clear();
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Crime"){
                Crime.push_back(movArr[i]);
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 8:
        Documentary.clear();
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Documentary"){
                Documentary.push_back(movArr[i]);
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 9:
        Drama.clear();
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Drama"){
                Drama.push_back(movArr[i]);
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 10:
        Family.clear();
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Family"){
                Family.push_back(movArr[i]);
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 11:
        Fantasy.clear();
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Fantasy"){
                Fantasy.push_back(movArr[i]);
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 12:
        FilmNoir.clear();
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Film-Noir"){
                FilmNoir.push_back(movArr[i]);
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 13:
        Horror.clear();
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Horror"){
                Horror.push_back(movArr[i]);
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 14:
        Musical.clear();
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Musical"){
                Musical.push_back(movArr[i]);
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 15:
        Mystery.clear();
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Mystery"){
                Mystery.push_back(movArr[i]);
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 16:
        Romance.clear();
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Romance"){
                Romance.push_back(movArr[i]);
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 17:
        War.clear();
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "War"){
                War.push_back(movArr[i]);
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    case 18:
        Western.clear();
        ui->listMovieWidget->clear();
        for (size_t i = 0; i < listSize; i++) {
            if(movArr[i].getGenre() == "Western"){
                Western.push_back(movArr[i]);
                string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
                ui->listMovieWidget->addItem(QString::fromStdString(text));
            }
        }
        break;
    }
}


void ListMaker::on_sortPushButton_clicked()
{
    movie* clonedArr = new movie[this->listSize];
    for (int i = 0; i < this->listSize; i++) {
        clonedArr[i] = unchangedArr[i];
    }
    delete[] movArr;
    this->movArr = clonedArr;
    chrono::duration<double> elapsed_seconds;
    chrono::time_point<std::chrono::system_clock> start, end;
    QString timer = "";
    switch(ui->comboAlgoBox->currentIndex()){
    case 0:
        break;
    case 1:
        switch (ui->comboSortBox->currentIndex()){
        case 0:
            break;
        case 1:
            ui->listMovieWidget->clear();
            start = chrono::system_clock::now();
            mergeSortTitle(movArr, 0, listSize-1);
            end = chrono::system_clock::now();
            elapsed_seconds = end - start;
            genreListFilter(ui->comboGenreBox->currentIndex());
            timer = "Time in Seconds: ";
            timer += QString::number(elapsed_seconds.count());
            ui->timer->setText(timer);
            break;
        case 2:
            ui->listMovieWidget->clear();
            start = chrono::system_clock::now();
            mergeSortGenre(movArr, 0, listSize-1);
            end = chrono::system_clock::now();
            elapsed_seconds = end - start;
            genreListFilter(ui->comboGenreBox->currentIndex());
            timer = "Time in Seconds: ";
            timer += QString::number(elapsed_seconds.count());
            ui->timer->setText(timer);
            break;
        case 3:
            ui->listMovieWidget->clear();
            start = chrono::system_clock::now();
            mergeSortRating(movArr, 0, listSize-1);
            end = chrono::system_clock::now();
            elapsed_seconds = end - start;
            genreListFilter(ui->comboGenreBox->currentIndex());
            timer = "Time in Seconds: ";
            timer += QString::number(elapsed_seconds.count());
            ui->timer->setText(timer);
            break;
        }
        break;
    case 2:
        switch (ui->comboSortBox->currentIndex()){
        case 0:
            break;
        case 1:
            ui->listMovieWidget->clear();
            start = chrono::system_clock::now();
            quickSortTitle(movArr, 0, listSize-1);
            end = chrono::system_clock::now();
            elapsed_seconds = end - start;
            genreListFilter(ui->comboGenreBox->currentIndex());
            timer = "Time in Seconds: ";
            timer += QString::number(elapsed_seconds.count());
            ui->timer->setText(timer);
            break;
        case 2:
            ui->listMovieWidget->clear();
            start = chrono::system_clock::now();
            quickSortGenre(movArr, 0, listSize-1);
            end = chrono::system_clock::now();
            elapsed_seconds = end - start;
            genreListFilter(ui->comboGenreBox->currentIndex());
            timer = "Time in Seconds: ";
            timer += QString::number(elapsed_seconds.count());
            ui->timer->setText(timer);
            break;
        case 3:
            ui->listMovieWidget->clear();
            start = chrono::system_clock::now();
            quickSortRating(movArr, 0, listSize-1);
            end = chrono::system_clock::now();
            elapsed_seconds = end - start;
            genreListFilter(ui->comboGenreBox->currentIndex());
            timer = "Time in Seconds: ";
            timer += QString::number(elapsed_seconds.count());
            ui->timer->setText(timer);
            break;
        }
        break;
    }
}





void ListMaker::on_saveListButton_clicked()
{
    pair<string, vector<movie>> cList;
    cList.first = ui->listNameTextEdit->toPlainText().toStdString();
    cList.second = this->currentList;
    lists.push_back(cList);
    this->currentList.clear();
    ui->listNameTextEdit->clear();
    ui->listUserWidget->clear();
}



void ListMaker::on_listMovieWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int currentRow = ui->listMovieWidget->currentRow();
    int index = ui->comboGenreBox->currentIndex();
    switch(index){
    case 0:
        if(All.empty() == true){
            ui->listUserWidget->addItem(QString::fromStdString(unchangedArr[currentRow].getTitle() + " -- User Rating: " + unchangedArr[currentRow].getUserRating()));
            currentList.push_back(unchangedArr[currentRow]);
        }
        else{
            ui->listUserWidget->addItem(QString::fromStdString(All[currentRow].getTitle() + " -- User Rating: " + All[currentRow].getUserRating()));
            currentList.push_back(All[currentRow]);
        }
        break;
    case 1:
        ui->listUserWidget->addItem(QString::fromStdString(Action[currentRow].getTitle() + " -- User Rating: " + Action[currentRow].getUserRating()));
        currentList.push_back(Action[currentRow]);
        break;
    case 2:
        ui->listUserWidget->addItem(QString::fromStdString(Adult[currentRow].getTitle() +  " -- User Rating: " + Adult[currentRow].getUserRating()));
        currentList.push_back(Adult[currentRow]);
        break;
    case 3:
        ui->listUserWidget->addItem(QString::fromStdString(Adventure[currentRow].getTitle() + " -- User Rating: " + Adventure[currentRow].getUserRating()));
        currentList.push_back(Adventure[currentRow]);
        break;
    case 4:
        ui->listUserWidget->addItem(QString::fromStdString(Animation[currentRow].getTitle()));
        currentList.push_back(Animation[currentRow]);
        break;
    case 5:
        ui->listUserWidget->addItem(QString::fromStdString(Biography[currentRow].getTitle()));
        currentList.push_back(Biography[currentRow]);
        break;
    case 6:
        ui->listUserWidget->addItem(QString::fromStdString(Comedy[currentRow].getTitle()));
        currentList.push_back(Comedy[currentRow]);
        break;
    case 7:
        ui->listUserWidget->addItem(QString::fromStdString(Crime[currentRow].getTitle()));
        currentList.push_back(Crime[currentRow]);
        break;
    case 8:
        ui->listUserWidget->addItem(QString::fromStdString(Documentary[currentRow].getTitle()));
        currentList.push_back(Documentary[currentRow]);
        break;
    case 9:
        ui->listUserWidget->addItem(QString::fromStdString(Drama[currentRow].getTitle()));
        currentList.push_back(Drama[currentRow]);
        break;
    case 10:
        ui->listUserWidget->addItem(QString::fromStdString(Family[currentRow].getTitle()));
        currentList.push_back(Family[currentRow]);
        break;
    case 11:
        ui->listUserWidget->addItem(QString::fromStdString(Fantasy[currentRow].getTitle()));
        currentList.push_back(Fantasy[currentRow]);
        break;
    case 12:
        ui->listUserWidget->addItem(QString::fromStdString(FilmNoir[currentRow].getTitle()));
        currentList.push_back(FilmNoir[currentRow]);
        break;
    case 13:
        ui->listUserWidget->addItem(QString::fromStdString(Horror[currentRow].getTitle()));
        currentList.push_back(Horror[currentRow]);
        break;
    case 14:
        ui->listUserWidget->addItem(QString::fromStdString(Musical[currentRow].getTitle()));
        currentList.push_back(Musical[currentRow]);
        break;
    case 15:
        ui->listUserWidget->addItem(QString::fromStdString(Mystery[currentRow].getTitle()));
        currentList.push_back(Mystery[currentRow]);
        break;
    case 16:
        ui->listUserWidget->addItem(QString::fromStdString(Romance[currentRow].getTitle()));
        currentList.push_back(Romance[currentRow]);
        break;
    case 17:
        ui->listUserWidget->addItem(QString::fromStdString(War[currentRow].getTitle()));
        currentList.push_back(War[currentRow]);
        break;
    case 18:
        ui->listUserWidget->addItem(QString::fromStdString(Western[currentRow].getTitle()));
        currentList.push_back(Western[currentRow]);
        break;
    }
}



void ListMaker::on_listUserWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int currentRow = ui->listUserWidget->currentRow();
    movie curMovie = currentList[currentRow];
    auto it = ::find(currentList.begin(), currentList.end(), curMovie);
    if (it != currentList.end()) {
        currentList.erase(it);
    }
    ui->listUserWidget->model()->removeRow(currentRow);
}

