#include "cinemania.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include "movie.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    unordered_map<string, movie> Movies;
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
        position = myText.find('\t');
        string year = myText.substr(0, position);
        myText = myText.substr(position + 1, myText.size());
        position = myText.find('\t');
        string runtime = myText.substr(0, position);
        myText = myText.substr(position + 1, myText.size());
        position = myText.find('\t');
        string genre = myText.substr(0, position);
        myText = myText.substr(position + 1, myText.size());
        position = myText.find('\t');
        string rating = myText.substr(0, position);
        myText = myText.substr(position + 1, myText.size());
        position = myText.find('\t');
        string numVotes = myText.substr(0, position);
        myText = myText.substr(position + 1, myText.size());
        movie CurrentMovie(movieid, title, year, runtime, genre, rating, numVotes);
        Movies[title] = CurrentMovie;
    }
    MyReadFile.close();
    QApplication a(argc, argv);
    CineMania w;
    w.show();
    return a.exec();
}
