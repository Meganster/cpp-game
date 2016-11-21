//
// Created by artem on 21.11.16.
//

#ifndef MYGAME_POINTMANAGER_H
#define MYGAME_POINTMANAGER_H

#include <vector>
#include "Scorable.h"

namespace score_management {

    enum Player {player_1, player_2};

    /**
     * This class manages points distribution between 2 players
     */
    class ScoreManager {
    public:
        static ScoreManager& getInstance();

        score_type getPlayer1Score() const;

        score_type getPlayer2Score() const;

        Player getActivePlayer() const;

        void setPlayer1Score(score_type);

        void setPlayer2Score(score_type);

        void setActivePlayer(Player);

        void switchActivePlayer();

        void sellObjects(const std::vector<Scorable*>&);

        void sellObject(const Scorable* valuable_object);

        bool buyObjects(const std::vector<Scorable*>&);

        bool buyObject(const Scorable*);

        /**
         *
         * @return returns true if player has enough points to create objects and false otherwise
         */
        bool requestObjectsCreation(const std::vector<Scorable*>&) const;

        bool requestObjectCreation(const Scorable*) const;

    private:
        ScoreManager();

        score_type getSellPrice(const std::vector<Scorable*>&) const ;

        score_type getSellPrice(const Scorable *) const ;

        score_type getBuyPrice(const Scorable *) const ;

        score_type getBuyPrice(const std::vector<Scorable*>&) const ;

        void spend(score_type);

        void deposit(score_type);

        Player active_player;
        score_type* active_score;
        score_type player_1_score;
        score_type player_2_score;
    };

}


#endif //MYGAME_POINTMANAGER_H
