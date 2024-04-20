//
// Created by geogo on 4/9/2024.
//

#ifndef PROJECT3_MOVIE_H
#define PROJECT3_MOVIE_H
#include <string>

using namespace std;

class movie {
    private:
        string movieid;
        string title;
        string year;
        string runtime;
        string genre;
        string rating;
        string numVotes;
        string userRating;
        int index;
    public:
        movie(){

        }
        movie(string id, string title, string year, string runtime, string genre, string rating, string numVotes){
            this->movieid = id;
            this->title = title;
            this->year = year;
            this->runtime = runtime;
            this->genre = genre;
            this->rating = rating;
            this->numVotes = numVotes;
            this->userRating = "0";
            this->index = 0;
        }
        string getID(){
            return this->movieid;
        }
        string getTitle(){
            return this->title;
        }
        string getYear(){
            return this->year;
        }
        string getRuntime(){
            return this->runtime;
        }
        string getGenre(){
            return this->genre;
        }
        string getRating(){
            return this->rating;
        }
        string getNumVotes(){
            return this->numVotes;
        }
        void setUserRating(string rating){
            this->userRating = rating;
        }
        string getUserRating(){
            return this->userRating;
        }
        void setIndex(int index){
            this->index = index;
        }
        int getIndex(){
            return this->index;
        }
};


#endif //PROJECT3_MOVIE_H
