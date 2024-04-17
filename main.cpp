#include "cinemania.h"
#include <fstream>
#include "movie.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    vector<movie> movieList;
    string myText;
    int position;
    fstream MyReadFile("MovieDataset.txt");
    getline (MyReadFile, myText);
    while (getline (MyReadFile, myText)) {
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
        movie CurrentMovie(movieid, title, year, runtime, genre, rating, numVotes);
        movieList.push_back(CurrentMovie);
    }
    MyReadFile.close();
    movie* moviesArr = new movie[movieList.size()];
    copy(movieList.begin(), movieList.end(), moviesArr);
    QApplication a(argc, argv);
    CineMania w(nullptr, moviesArr, movieList.size());
    w.show();
    return a.exec();
}
