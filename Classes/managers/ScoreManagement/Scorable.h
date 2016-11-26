//
// Created by artem on 21.11.16.
//

#ifndef MYGAME_SCOREABLE_H
#define MYGAME_SCOREABLE_H

typedef unsigned int score_type;

class Scorable {
public:
    virtual score_type getBuyPrice() const = 0;
    virtual score_type getSellPrice() const = 0;

};

#endif //MYGAME_SCOREABLE_H
