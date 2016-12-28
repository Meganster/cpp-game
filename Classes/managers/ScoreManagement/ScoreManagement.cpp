//
// Created by artem on 21.11.16.
//

#include "ScoreManagement.h"
#include <iostream>

using namespace score_management;

ScoreManager::ScoreManager(): player_1_score{0}, player_2_score{0}, active_player{player_1} {
    active_score = &player_1_score;
    passive_score = &player_2_score;
};

ScoreManager& ScoreManager::getInstance() {
    static ScoreManager instance;
    return instance;
}

score_type ScoreManager::getPlayer1Score() const {
    return player_1_score;
}

score_type ScoreManager::getPlayer2Score() const {
    return player_2_score;
}

score_type ScoreManager::getActivePlayerScore() const {
    return *active_score;
}

Player ScoreManager::getActivePlayer() const {
    return active_player;
}

void ScoreManager::setPlayer1Score(score_type score) {
    player_1_score = score;
}

void ScoreManager::setPlayer2Score(score_type score) {
    player_2_score = score;
}

void ScoreManager::setActivePlayer(Player player) {
    active_player = player;

    if (player == player_1) {
        active_score = &player_1_score;
    } else {
        active_score = &player_2_score;
    }
}

void ScoreManager::switchActivePlayer() {
    if (active_player == player_1) {
        active_score = &player_2_score;
        active_player = player_2;
        passive_score = &player_1_score;
    } else {
        active_score = &player_1_score;
        active_player = player_1;
        passive_score = &player_2_score;
    }
}

void ScoreManager::sell(const Scorable *scorable) {
    deposit(getSellPrice(scorable));
}

void ScoreManager::sell(const std::shared_ptr<Scorable> scorable) {
    deposit(getSellPrice(scorable));
}

void ScoreManager::sellToPassive(const Scorable *scorable) {
    depositToPassive(getBuyPrice(scorable));
}

bool ScoreManager::buy(const Scorable *scorable) {
    score_type price = getBuyPrice(scorable);

    if (hasEnoughMoney(scorable)) {
        spend(price);
        return true;
    } else {
        return false;
    }
}

bool ScoreManager::buy(const std::shared_ptr<Scorable> scorable) {
    score_type price = getBuyPrice(scorable);

    if (hasEnoughMoney(scorable)) {
        spend(price);
        return true;
    } else {
        return false;
    }
}

void ScoreManager::revert(const Scorable* scorable) {
    deposit(scorable->getBuyPrice());
}

bool ScoreManager::hasEnoughMoney(const Scorable *scorable) const {
    return getBuyPrice(scorable) <= *active_score;
}

bool ScoreManager::hasEnoughMoney(const std::shared_ptr<Scorable> scorable) const {
    return getBuyPrice(scorable) <= *active_score;
}

score_type ScoreManager::getSellPrice(const Scorable *scorable) const {
    return scorable->getSellPrice();
}

score_type ScoreManager::getSellPrice(const std::shared_ptr<Scorable> scorable) const {
    return scorable->getSellPrice();
}

score_type ScoreManager::getBuyPrice(const Scorable *scorable) const {
    return scorable->getBuyPrice();
}

score_type ScoreManager::getBuyPrice(const std::shared_ptr<Scorable> scorable) const {
    return scorable->getBuyPrice();
}

void ScoreManager::spend(score_type amount) {
    *active_score -= amount;
    sendScoreChangeEvent(*active_score, true);
}

void ScoreManager::deposit(score_type amount) {
    *active_score += amount;
    sendScoreChangeEvent(*active_score, true);
}

void ScoreManager::depositToPassive(score_type amount) {
    *passive_score += amount;
    sendScoreChangeEvent(*passive_score, false);
    std::cout << "Passive: " << *passive_score << std::endl;
}

void ScoreManager::sendScoreChangeEvent(int new_score, bool is_active_player) {
    auto e = tree_events::ScoreChangeEvent(new_score, is_active_player);
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&e);
}

