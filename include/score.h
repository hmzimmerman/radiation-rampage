#ifndef SCORE_H
#define SCORE_H

#include <string>
#include <vector>

class Score {
    private:
        int score;
        std::string name;

    public:
        Score(std::string n, int s) : score(s), name(n) {}
        std::string getString() const {std::string str = " " + name + "              " +  std::to_string(score); return str; };
        int getScore() const { return score; };

};



#endif