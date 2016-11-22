//
// Created by artem on 21.11.16.
//

#include "ScoreManagement.h"

score_management::ScoreManagement::ScoreManagement(): player_1_score{0}, player_2_score{0}, active_player{player_1} {
    active_score = &player_1_score;
};

score_management::ScoreManagement& score_management::ScoreManagement::getInstance() {
    static ScoreManagement instance;
    return instance;
}

score_type score_management::ScoreManagement::getPlayer1Score() const {
    return player_1_score;
}

score_type score_management::ScoreManagement::getPlayer2Score() const {
    return player_2_score;
}

score_management::Player score_management::ScoreManagement::getActivePlayer() const {
    return active_player;
}

void score_management::ScoreManagement::setPlayer1Score(score_type score) {
    player_1_score = score;
}

void score_management::ScoreManagement::setPlayer2Score(score_type score) {
    player_2_score = score;
}

void score_management::ScoreManagement::setActivePlayer(Player player) {
    active_player = player;

    if (player == player_1) {
        active_score = &player_1_score;
    } else {
        active_score = &player_2_score;
    }
}

void score_management::ScoreManagement::switchActivePlayer() {
    if (active_player == player_1) {
        active_score = &player_2_score;
        active_player = player_2;
    } else {
        active_score = &player_1_score;
        active_player = player_1;
    }
}

void score_management::ScoreManagement::sellObjects(const std::vector<Scorable*>& scorable_objects) {
    deposit(getSellPrice(scorable_objects));
}

void score_management::ScoreManagement::sellObject(const Scorable* scorable) {
    deposit(getSellPrice(scorable));
}

bool score_management::ScoreManagement::buyObjects(const std::vector<Scorable*>& scorable_objects) {
    score_type price = getBuyPrice(scorable_objects);

    if (price >= *active_score) {
        spend(price);
        return true;
    } else {
        return false;
    }
}

bool score_management::ScoreManagement::buyObject(const Scorable* scorable) {
    score_type price = getBuyPrice(scorable);

    if (price >= *active_score) {
        spend(price);
        return true;
    } else {
        return false;
    }
}

bool score_management::ScoreManagement::requestObjectsCreation(const std::vector<Scorable*>& scorable_objects) const {
    return getBuyPrice(scorable_objects) >= *active_score;
}

bool score_management::ScoreManagement::requestObjectCreation(const Scorable* scorable) const {
    return getBuyPrice(scorable) >= *active_score;
}

score_type score_management::ScoreManagement::getSellPrice(const std::vector<Scorable *>& scorable_objects) const {
    score_type result = 0;
    for (auto scorable: scorable_objects) {
        result += getSellPrice(scorable);
    }

    return result;
}

score_type score_management::ScoreManagement::getSellPrice(const Scorable *scorable) const {
    return scorable->getSellPrice();
}

score_type score_management::ScoreManagement::getBuyPrice(const std::vector<Scorable *>& scorable_objects) const {
    score_type result = 0;
    for (auto valuable_object: scorable_objects) {
        result += getBuyPrice(valuable_object);
    }

    return result;
}

score_type score_management::ScoreManagement::getBuyPrice(const Scorable *scorable) const {
    return scorable->getBuyPrice();
}

void score_management::ScoreManagement::spend(score_type amount) {
    *active_score -= amount;
}

void score_management::ScoreManagement::deposit(score_type amount) {
    *active_score += amount;
}