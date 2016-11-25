//
// Created by artem on 21.11.16.
//

#include "ScoreManagement.h"

score_management::ScoreManager::ScoreManager(): player_1_score{0}, player_2_score{0}, active_player{player_1} {
    active_score = &player_1_score;
};

score_management::ScoreManager& score_management::ScoreManager::getInstance() {
    static ScoreManager instance;
    return instance;
}

score_type score_management::ScoreManager::getPlayer1Score() const {
    return player_1_score;
}

score_type score_management::ScoreManager::getPlayer2Score() const {
    return player_2_score;
}

score_type score_management::ScoreManager::getActivePlayerScore() const {
    return *active_score;
}

score_management::Player score_management::ScoreManager::getActivePlayer() const {
    return active_player;
}

void score_management::ScoreManager::setPlayer1Score(score_type score) {
    player_1_score = score;
}

void score_management::ScoreManager::setPlayer2Score(score_type score) {
    player_2_score = score;
}

void score_management::ScoreManager::setActivePlayer(Player player) {
    active_player = player;

    if (player == player_1) {
        active_score = &player_1_score;
    } else {
        active_score = &player_2_score;
    }
}

void score_management::ScoreManager::switchActivePlayer() {
    if (active_player == player_1) {
        active_score = &player_2_score;
        active_player = player_2;
    } else {
        active_score = &player_1_score;
        active_player = player_1;
    }
}

void score_management::ScoreManager::sell(const Scorable *scorable) {
    deposit(getSellPrice(scorable));
}

void score_management::ScoreManager::sell(const std::shared_ptr<Scorable> scorable) {
    deposit(getSellPrice(scorable));
}

bool score_management::ScoreManager::buy(const Scorable *scorable) {
    score_type price = getBuyPrice(scorable);

    if (price >= *active_score) {
        spend(price);
        return true;
    } else {
        return false;
    }
}

bool score_management::ScoreManager::buy(const std::shared_ptr<Scorable> scorable) {
    score_type price = getBuyPrice(scorable);

    if (price >= *active_score) {
        spend(price);
        return true;
    } else {
        return false;
    }
}

void score_management::ScoreManager::revert(const Scorable* scorable) {
    deposit(scorable->getBuyPrice());
}

bool score_management::ScoreManager::hasEnoughMoney(const Scorable *scorable) const {
    return getBuyPrice(scorable) >= *active_score;
}

score_type score_management::ScoreManager::getSellPrice(const Scorable *scorable) const {
    return scorable->getSellPrice();
}

score_type score_management::ScoreManager::getSellPrice(const std::shared_ptr<Scorable> scorable) const {
    return scorable->getSellPrice();
}

score_type score_management::ScoreManager::getBuyPrice(const Scorable *scorable) const {
    return scorable->getBuyPrice();
}

score_type score_management::ScoreManager::getBuyPrice(const std::shared_ptr<Scorable> scorable) const {
    return scorable->getBuyPrice();
}

void score_management::ScoreManager::spend(score_type amount) {
    *active_score -= amount;
}

void score_management::ScoreManager::deposit(score_type amount) {
    *active_score += amount;
}