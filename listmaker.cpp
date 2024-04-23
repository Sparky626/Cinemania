#include "cinemania.h"
#include "listmaker.h"
#include "ui_listmaker.h"
#include <iostream>
#include <vector>

// constructor
ListMaker::ListMaker(QWidget *parent, movie movArr[], movie unchangedArr[], int listSize, vector<pair<string,vector<movie>>> lists)
    : QDialog(parent)
    , ui(new Ui::ListMaker)

{
    ui->setupUi(this); // set up user interface

    // add genre names to Genre combo box
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

    // add items to sort combo box
    ui->comboSortBox->addItem("None");
    ui->comboSortBox->addItem("Title");
    ui->comboSortBox->addItem("Genre");
    ui->comboSortBox->addItem("Rating");

    // add items to algorithm combo box
    ui->comboAlgoBox->addItem("None");
    ui->comboAlgoBox->addItem("Merge");
    ui->comboAlgoBox->addItem("Quick");

    // initialize variables
    this->movArr = movArr;
    this->unchangedArr = unchangedArr;
    this->listSize = listSize;

    // load Cinemania logo
    QPixmap pix("Cinemania_Logo.png");
    ui->logo_label->setPixmap(pix);

    // add movie info to movie list widget
    for (size_t i = 0; i < listSize; i++) {
        string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
        ui->listMovieWidget->addItem(QString::fromStdString(text));
    }
}

// destructor
ListMaker::~ListMaker()
{
    delete ui;
}

// swap function
void swap_abc(movie& a, movie& b) {
    movie temp = a;
    a = b;
    b = temp;
}

// quicksort and partition functions inspired from geeks for geeks

// partition function for sort by genre
int partitionGenre (movie arr[], int low, int high) {
    // pivots for sorting by genre (with title as tiebreaker)
    string pivotGenre = arr[high].getGenre();
    string pivotTitle = arr[high].getTitle();

    int i = (low - 1); // index of smaller element

    for (int j = low; j <=high; j++) {
        // if current element is smaller than pivot for genre, then by title
        if (arr[j].getGenre() < pivotGenre || (arr[j].getGenre() == pivotGenre && arr[j].getTitle() < pivotTitle)) {
            i++; // increment index of smaller element
            swap_abc(arr[i], arr[j]);
        }
    }
    swap_abc(arr[i+1], arr[high]);
    return (i+1);
}

// partition function for sort by rating
int partitionRating (movie arr[], int low, int high) {
    // pivots for sorting by rating (with title as tiebreaker)
    string pivotRating = arr[high].getRating();
    string pivotTitle = arr[high].getTitle();

    int i = (low - 1); // index of smaller element

    for (int j = low; j <=high; j++) {
        // if current element is smaller than pivot for rating, then by title
        if (arr[j].getRating() > pivotRating || (arr[j].getRating() == pivotRating && arr[j].getTitle() < pivotTitle)) {
            i++; // increment index of smaller element
            swap_abc(arr[i], arr[j]);
        }
    }
    swap_abc(arr[i+1], arr[high]);
    return (i+1);
}

// partition function for sort by title
int partitionTitle (movie arr[], int low, int high) {
    // pivot for sorting by title
    string pivotTitle = arr[high].getTitle();

    int i = (low - 1); // index of smaller element

    for (int j = low; j <=high; j++) {
        // if current element is smaller than pivot
        if (arr[j].getTitle() < pivotTitle) {
            i++; // increment index of smaller element
            swap_abc(arr[i], arr[j]);
        }
    }
    swap_abc(arr[i+1], arr[high]);
    return (i+1);
}

// quick sort function for sort by genre
void quickSortGenre (movie arr[], int low, int high) {
    if (low < high) { // if low is less than high
        // pi returns index of pivot
        int pi = partitionGenre(arr, low, high);
        quickSortGenre(arr, low, pi-1); // smaller element pivot goes left
        quickSortGenre(arr,pi+1,high); // higher element goes right
    }
}

// quick sort function for sort by rating
void quickSortRating (movie arr[], int low, int high) {
    if (low < high) { // if low is less than high
        // pi returns index of pivot
        int pi = partitionRating(arr, low, high);
        quickSortRating(arr, low, pi - 1); // smaller element pivot goes left
        quickSortRating(arr,pi + 1, high); // higher element goes right
    }
}

// quick sort function for sort by title
void quickSortTitle (movie arr[], int low, int high) {
    if (low < high) { // if low is less than high
        // pi returns index of pivot
        int pi = partitionTitle(arr, low, high);
        quickSortTitle(arr, low, pi-1); // smaller element pivot goes left
        quickSortTitle(arr,pi+1,high); // higher element goes right
    }
}

// merge sort and merge functions inspired by geeks for geeks

// merge function for sort by genre
void mergeGenre(movie arr[], int const left, int const mid, int const right) {
    int const subArr1 = mid - left + 1;
    int const subArr2 = right - mid;

    // temp arrays
    auto *leftArr = new movie[subArr1], *rightArr = new movie[subArr2];

    // copy data to temp arrays
    for(auto i = 0; i < subArr1; i++) {
        leftArr[i] = arr[left+i];
    }
    for (auto j = 0; j < subArr2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }

    auto indexSubArr1 = 0, indexSubArr2 = 0;
    int indexMergedArr = left;

    // merge back into one array based on genre (with title as tiebreaker)
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

    // copy remaining elements of left
    while (indexSubArr1 < subArr1) {
        arr[indexMergedArr] = leftArr[indexSubArr1];
        indexSubArr1++;
        indexMergedArr++;
    }

    // copy remaining elements of right
    while (indexSubArr2 < subArr2) {
        arr[indexMergedArr] = rightArr[indexSubArr2];
        indexSubArr2++;
        indexMergedArr++;
    }

    // delete temp arrays
    delete[] leftArr;
    delete[] rightArr;

}

// merge function for sort by rating
void mergeRating(movie arr[], int const left, int const mid, int const right) {
    int const subArr1 = mid - left + 1;
    int const subArr2 = right - mid;

    // temp arrays
    auto *leftArr = new movie[subArr1], *rightArr = new movie[subArr2];

    // copy data to temp arrays
    for(auto i = 0; i < subArr1; i++) {
        leftArr[i] = arr[left+i];
    }
    for (auto j = 0; j < subArr2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }

    auto indexSubArr1 = 0, indexSubArr2 = 0;
    int indexMergedArr = left;

    // merge back into one array based on rating (with title as tiebreaker)
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

    // copy remaining elements of left
    while (indexSubArr1 < subArr1) {
        arr[indexMergedArr] = leftArr[indexSubArr1];
        indexSubArr1++;
        indexMergedArr++;
    }

    // copy remaining elements of right
    while (indexSubArr2 < subArr2) {
        arr[indexMergedArr] = rightArr[indexSubArr2];
        indexSubArr2++;
        indexMergedArr++;
    }

    // delete temp arrays
    delete[] leftArr;
    delete[] rightArr;
}

// merge function for sort by title
void mergeTitle(movie arr[], int const left, int const mid, int const right) {
    int const subArr1 = mid - left + 1;
    int const subArr2 = right - mid;

    // temp arrays
    auto *leftArr = new movie[subArr1], *rightArr = new movie[subArr2];

    // copy data to temp arrays
    for(auto i = 0; i < subArr1; i++) {
        leftArr[i] = arr[left+i];
    }
    for (auto j = 0; j < subArr2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }

    auto indexSubArr1 = 0, indexSubArr2 = 0;
    int indexMergedArr = left;

    // merge back into one array based on title
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

    // copy remaining elements of left
    while (indexSubArr1 < subArr1) {
        arr[indexMergedArr] = leftArr[indexSubArr1];
        indexSubArr1++;
        indexMergedArr++;
    }

    // copy remaining elements of right
    while (indexSubArr2 < subArr2) {
        arr[indexMergedArr] = rightArr[indexSubArr2];
        indexSubArr2++;
        indexMergedArr++;
    }

    // delete temp arrays
    delete[] leftArr;
    delete[] rightArr;

}

void mergeSortGenre (movie arr[], int const begin, int const end) { // begin = left index and end = right index
    if (begin >= end) {
        return;
    }
    int mid = begin + (end - begin) / 2; // find middle index
    mergeSortGenre(arr, begin, mid); // sort left half
    mergeSortGenre(arr, mid + 1, end); // sort right half
    mergeGenre(arr, begin, mid, end); // merge sorted halves
}

void mergeSortRating (movie arr[], int const begin, int const end) { // begin = left index and end = right index
    if (begin >= end) {
        return;
    }
    int mid = begin + (end - begin) / 2; // find middle index
    mergeSortRating(arr, begin, mid); // sort left half
    mergeSortRating(arr, mid + 1, end); // sort right half
    mergeRating(arr, begin, mid, end); // merge sorted halves
}

void mergeSortTitle (movie arr[], int const begin, int const end) { // begin = left index and end = right index
    if (begin >= end) {
        return;
    }
    int mid = begin + (end - begin) / 2; // find middle index
    mergeSortTitle(arr, begin, mid); // sort left half
    mergeSortTitle(arr, mid + 1, end); // sort right half
    mergeTitle(arr, begin, mid, end); // merge sorted halves
}

void ListMaker::genreListFilter(int index){
    // switch statement to handle different genre filters based on index
    switch(index){
    // case 0 = all genres selected
    case 0:
        // clear list widget and vector
        ui->listMovieWidget->clear();
        All.clear();
        // loop through movies and add them to list widget
        for (size_t i = 0; i < listSize; i++) {
            All.push_back(movArr[i]);
            string text = movArr[i].getTitle() + " - Genre: " + movArr[i].getGenre() + " - Rating: " + movArr[i].getRating();
            ui->listMovieWidget->addItem(QString::fromStdString(text));
        }
        break;

        // case 1 = action genre selected
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

        // case 2 = adult genre selected
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

        // case 3 = adventure genre selected
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

        // case 4 = animation genre selected
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

        // case 5 = biography genre selected
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

        // case 6 = comedy genre selected
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

        // case 7 = crime genre selected
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

        // case 8 = documentary genre selected
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

        // case 9 = drama genre selected
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

        // case 10 = family genre selected
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

        // case 11 = fantasy genre selected
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

        // case 12 = film-noir genre selected
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

        // case 13 = horror genre selected
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

        // case 14 = musical genre selected
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

        // case 15 = mystery genre selected
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

        // case 16 = romance genre selected
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

        // case 17 = war genre selected
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

        // case 18 = western genre selected
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
    // new array to store cloned copy of original array
    movie* clonedArr = new movie[this->listSize];
    for (int i = 0; i < this->listSize; i++) { // copy elements into cloned array
        clonedArr[i] = unchangedArr[i];
    }
    delete[] movArr; // delete original array
    this->movArr = clonedArr;

    // clock variables to measure time (for comparing algorithms)
    chrono::duration<double> elapsed_seconds;
    chrono::time_point<std::chrono::system_clock> start, end;
    QString timer = "";

    // switch case based on algorithm type
    switch(ui->comboAlgoBox->currentIndex()){
    // case 0 = no algorithm selected
    case 0:
        break;

        // case 1 = merge sort selected
    case 1:
        switch (ui->comboSortBox->currentIndex()){
        case 0: // no criteria selected for merge sort
            break;

            // case 1 = sort by title
        case 1:
            ui->listMovieWidget->clear();
            start = chrono::system_clock::now();
            mergeSortTitle(movArr, 0, listSize-1); // call merge sort function
            end = chrono::system_clock::now();
            elapsed_seconds = end - start; // keep track of time

            genreListFilter(ui->comboGenreBox->currentIndex());
            timer = "Time in Seconds: ";
            timer += QString::number(elapsed_seconds.count());
            ui->timer->setText(timer); // display time
            break;

            // case 2 = sort by genre
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

            // case 3 = sort by rating
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

        // case 2 = quick sort selected
    case 2:
        switch (ui->comboSortBox->currentIndex()){
        case 0: // no criteria selected for quick sort
            break;

            // case 1 = sort by title
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

            // case 2 = sort by genre
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

            // case 3 = sort by rating
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
    pair<string, vector<movie>> cList; // pair to store list name and movies

    cList.first = ui->listNameTextEdit->toPlainText().toStdString(); // get list name and convert to string
    cList.second = this->currentList; // assign vector of movies from current list to second element of pair
    lists.push_back(cList); // add pair to vector

    // clear vector, text edit, and widget
    this->currentList.clear();
    ui->listNameTextEdit->clear();
    ui->listUserWidget->clear();
}



void ListMaker::on_listMovieWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int currentRow = ui->listMovieWidget->currentRow(); // get row index of clicked item
    int index = ui->comboGenreBox->currentIndex(); // get index of selected genre from combo box

    // switch based on selected genre to add selected movie to the user list
    switch(index){
    // case 0 = all selected
    case 0:
        if(All.empty() == true){ // add movie to user list
            ui->listUserWidget->addItem(QString::fromStdString(unchangedArr[currentRow].getTitle() + " -- User Rating: " + unchangedArr[currentRow].getUserRating()));
            currentList.push_back(unchangedArr[currentRow]);
        }
        else{
            ui->listUserWidget->addItem(QString::fromStdString(All[currentRow].getTitle() + " -- User Rating: " + All[currentRow].getUserRating()));
            currentList.push_back(All[currentRow]);
        }
        break;

        // case 1 = action genre selected
    case 1:
        // add movie to user list
        ui->listUserWidget->addItem(QString::fromStdString(Action[currentRow].getTitle() + " -- User Rating: " + Action[currentRow].getUserRating()));
        currentList.push_back(Action[currentRow]);
        break;

        // case 2 = adult genre selected
    case 2:
        ui->listUserWidget->addItem(QString::fromStdString(Adult[currentRow].getTitle() +  " -- User Rating: " + Adult[currentRow].getUserRating()));
        currentList.push_back(Adult[currentRow]);
        break;

        // case 3 = adventure genre selected
    case 3:
        ui->listUserWidget->addItem(QString::fromStdString(Adventure[currentRow].getTitle() + " -- User Rating: " + Adventure[currentRow].getUserRating()));
        currentList.push_back(Adventure[currentRow]);
        break;

        // case 4 = animation genre selected
    case 4:
        ui->listUserWidget->addItem(QString::fromStdString(Animation[currentRow].getTitle() + " -- User Rating: " + Animation[currentRow].getUserRating()));
        currentList.push_back(Animation[currentRow]);
        break;

        // case 5 = biography genre selected
    case 5:
        ui->listUserWidget->addItem(QString::fromStdString(Biography[currentRow].getTitle() + " -- User Rating: " + Biography[currentRow].getUserRating()));
        currentList.push_back(Biography[currentRow]);
        break;

        // case 6 = comedy genre selected
    case 6:
        ui->listUserWidget->addItem(QString::fromStdString(Comedy[currentRow].getTitle()+ " -- User Rating: " + Comedy[currentRow].getUserRating()));
        currentList.push_back(Comedy[currentRow]);
        break;

        // case 7 = crime genre selected
    case 7:
        ui->listUserWidget->addItem(QString::fromStdString(Crime[currentRow].getTitle() + " -- User Rating: " + Crime[currentRow].getUserRating()));
        currentList.push_back(Crime[currentRow]);
        break;

        // case 8 = documentary genre selected
    case 8:
        ui->listUserWidget->addItem(QString::fromStdString(Documentary[currentRow].getTitle() + " -- User Rating: " + Documentary[currentRow].getUserRating()));
        currentList.push_back(Documentary[currentRow]);
        break;

        // case 9 = drama genre selected
    case 9:
        ui->listUserWidget->addItem(QString::fromStdString(Drama[currentRow].getTitle()+ " -- User Rating: " + Drama[currentRow].getUserRating()));
        currentList.push_back(Drama[currentRow]);
        break;

        // case 10 = family genre selected
    case 10:
        ui->listUserWidget->addItem(QString::fromStdString(Family[currentRow].getTitle()+ " -- User Rating: " + Family[currentRow].getUserRating()));
        currentList.push_back(Family[currentRow]);
        break;

        // case 11 = fantasy genre selected
    case 11:
        ui->listUserWidget->addItem(QString::fromStdString(Fantasy[currentRow].getTitle()+ " -- User Rating: " + Fantasy[currentRow].getUserRating()));
        currentList.push_back(Fantasy[currentRow]);
        break;

        // case 12 = film-noir genre selected
    case 12:
        ui->listUserWidget->addItem(QString::fromStdString(FilmNoir[currentRow].getTitle()+ " -- User Rating: " + FilmNoir[currentRow].getUserRating()));
        currentList.push_back(FilmNoir[currentRow]);
        break;

        // case 13 = horror genre selected
    case 13:
        ui->listUserWidget->addItem(QString::fromStdString(Horror[currentRow].getTitle()+ " -- User Rating: " + Horror[currentRow].getUserRating()));
        currentList.push_back(Horror[currentRow]);
        break;

        // case 14 = musical genre selected
    case 14:
        ui->listUserWidget->addItem(QString::fromStdString(Musical[currentRow].getTitle()+ " -- User Rating: " + Musical[currentRow].getUserRating()));
        currentList.push_back(Musical[currentRow]);
        break;

        // case 15 = mystery genre selected
    case 15:
        ui->listUserWidget->addItem(QString::fromStdString(Mystery[currentRow].getTitle()+ " -- User Rating: " + Mystery[currentRow].getUserRating()));
        currentList.push_back(Mystery[currentRow]);
        break;

        // case 16 = romance genre selected
    case 16:
        ui->listUserWidget->addItem(QString::fromStdString(Romance[currentRow].getTitle()+ " -- User Rating: " + Romance[currentRow].getUserRating()));
        currentList.push_back(Romance[currentRow]);
        break;

        // case 17 = war genre selected
    case 17:
        ui->listUserWidget->addItem(QString::fromStdString(War[currentRow].getTitle()+ " -- User Rating: " + War[currentRow].getUserRating()));
        currentList.push_back(War[currentRow]);
        break;

        // case 18 = western genre selected
    case 18:
        ui->listUserWidget->addItem(QString::fromStdString(Western[currentRow].getTitle()+ " -- User Rating: " + Western[currentRow].getUserRating()));
        currentList.push_back(Western[currentRow]);
        break;
    }
}



void ListMaker::on_listUserWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int currentRow = ui->listUserWidget->currentRow(); // get row index of item clicked
    movie curMovie = currentList[currentRow]; // get movie object that was clicked

    auto it = ::find(currentList.begin(), currentList.end(), curMovie);
    if (it != currentList.end()) { //if movie is found then erase from list
        currentList.erase(it);
    }

    ui->listUserWidget->model()->removeRow(currentRow); // remove row
}
