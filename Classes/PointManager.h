//
// Created by artem on 21.11.16.
//

#ifndef MYGAME_POINTMANAGER_H
#define MYGAME_POINTMANAGER_H

#include <vector>

class PointManager {
public:
    typedef unsigned int score_type;

    PointManager();

    PointManager(score_type);

    template <class T>
    void sellObjects(std::vector<T*> valuable_objects) {
        for (auto valuable_object: valuable_objects) {
            score += get_price(valuable_object);
        }
    }

    template <class T>
    void sellObject(T* valuable_object) {
        score += get_price(valuable_object);
    }

    template <class T>
    bool buyObjects(std::vector<T*> valuable_objects) {
        score_type price = get_price(valuable_objects);

        if (price >= score) {
            score -= price;
            return true;
        } else {
            return false;
        }
    }

    template <class T>
    bool buyObject(T* valuable_object) {
        score_type price = get_price(valuable_object);

        if (price >= score) {
            score -= price;
            return true;
        } else {
            return false;
        }
    };

    template <class T>
    bool requestObjectsCreation(std::vector<T *> valuable_objects) {
        return get_price(valuable_objects) >= score;
    };

    template <class T>
    bool requestObjectCreation(T* valuable_object) {
        return get_price(valuable_object) >= score;
    };

private:
    template <class T>
    score_type get_price(T *valuable_object) {
        return valuable_object->getBuyPrice();
    };

    template <class T>
    score_type get_price(std::vector<T *> valuable_objects) {
        score_type result = 0;
        for (auto valuable_object: valuable_objects) {
            result += get_price(valuable_object);
        }

        return result;
    };

    score_type score;
};


#endif //MYGAME_POINTMANAGER_H
