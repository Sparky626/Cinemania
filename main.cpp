#include "cinemania.h"
#include <fstream>
#include "movie.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    vector<movie> movieList; // initial vector to hold movie data
    string myText;
    int position;

    fstream MyReadFile("MovieDataset.txt");
    getline (MyReadFile, myText); // read first line to skip header

    // loop through each line of text in the file
    while (getline (MyReadFile, myText)) {
        // parsing to get movie attributes separated by tabs
        position = myText.find('\t');
        string movieid = myText.substr(0, position);
        myText = myText.substr(position + 1, myText.size());
        position = myText.find('\t');
        string title = myText.substr(0, position);
        myText = myText.substr(position + 1, myText.size());
        if (title[0] == '\"'){
            title = title.substr(1, title.size()-2);
        }
        position = myText.find('\t');
        string year = myText.substr(0, position);
        myText = myText.substr(position + 1, myText.size());
        position = myText.find('\t');
        string runtime = myText.substr(0, position);
        myText = myText.substr(position + 1, myText.size());
        position = myText.find('\t');
        string genre = myText.substr(0, position);
        myText = myText.substr(position + 1, myText.size());
        if (genre[0] == '\"'){
            position = genre.find(',');
            genre = genre.substr(1, position-1);
        }
        position = myText.find('\t');
        string rating = myText.substr(0, position);
        myText = myText.substr(position + 1, myText.size());
        position = myText.find('\t');
        string numVotes = myText.substr(0, position);
        myText = myText.substr(position + 1, myText.size());

        // create movie object that contains all attributes found
        movie CurrentMovie(movieid, title, year, runtime, genre, rating, numVotes);
        movieList.push_back(CurrentMovie); // put in vector
    }

    MyReadFile.close(); // close input file

    // create arrays to store movie objects
    movie* moviesArr = new movie[movieList.size()];
    movie* unchangedArr = new movie[movieList.size()];

    // copy objects from initial vector into the new arrays
    copy(movieList.begin(), movieList.end(), moviesArr);
    copy(movieList.begin(), movieList.end(), unchangedArr);

    QApplication a(argc, argv); // create QApplication object

    CineMania w(nullptr, moviesArr, unchangedArr, movieList.size()); // create cinemania object

    w.show(); // display main window

    return a.exec();
}
