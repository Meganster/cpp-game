//
// Created by artem on 28.12.16.
//

#ifndef MYGAME_DEBUGUI_H
#define MYGAME_DEBUGUI_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "../../managers/TreeManagement/TreeEvents.h"
#include "../../managers/ScoreManagement/ScoreManagement.h"


class GameInfoWidget: public cocos2d::Sprite {
public:
    GameInfoWidget(int score, std::string edge_name, std::string force_name, bool is_active=false):
            score_{score}, edge_name_{edge_name}, force_name_{force_name}, is_active_{is_active} {};

    static GameInfoWidget* create(int score, std::string edge_name, std::string force_name) {
        auto game_info_widget = new GameInfoWidget(score, edge_name, force_name);

        game_info_widget->autorelease();
        game_info_widget->initOptions();
        game_info_widget->addEvents();

        return game_info_widget;
    }

    static GameInfoWidget* create() {
        return GameInfoWidget::create(0, "Default edge", "Default force");
    }

    void updateScore(int score) {
        std::stringstream sstream;
        sstream << "Score: " << score;
        score_label_->setString(sstream.str());
    }

    void updateEdgeName(std::string& edge_name) {
        edge_label_->setString(edge_name);
    }

    void updateForceName(std::string& force_name) {
        force_label_->setString(force_name);
    }

    void setActive() {
        is_active_ = true;
    };

    void setPassive() {
        is_active_ = false;
    };

    bool isActive() {
        return is_active_;
    }

    void switchState() {
        if (isActive()) {
            setPassive();
        } else {
            setActive();
        }
    }

private:
    void initOptions() {
        setContentSize(cocos2d::Size(width_, height_));
        createWidgetParts();
    };

    void addEvents() {
        auto score_update_call_back = [this](tree_events::ScoreChangeEvent* event) -> void {
            if (isActive() == event->is_active_player_score) {
                updateScore(event->new_score);
                std::cout << "Score update" << std::endl;
            }
        };
        auto score_event_listener = event_wrappers::create_listener<tree_events::ScoreChangeEvent>(score_update_call_back);
        cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(score_event_listener, 1);
    };

    void createWidgetParts() {
        score_label_ = cocos2d::Label::createWithSystemFont("", "Helvetica", 20);

        std::stringstream score_stream;
        score_stream << "Score: " << score_;
        score_label_->setString(score_stream.str());

        score_label_->setContentSize(cocos2d::Size(width_, score_height_));
        score_label_->setPosition(0, force_height_ + edge_height_);
        addChild(score_label_);

        edge_label_ = cocos2d::Label::createWithSystemFont("", "Helvetica", 20);
        edge_label_->setString(edge_name_);
        edge_label_->setContentSize(cocos2d::Size(width_, edge_height_));
        edge_label_->setPosition(0, force_height_);
        addChild(edge_label_);

        force_label_ = cocos2d::Label::createWithSystemFont("", "Helvetica", 20);
        force_label_->setString(force_name_);
        force_label_->setContentSize(cocos2d::Size(width_, force_height_));
        force_label_->setPosition(0, 0);
        addChild(force_label_);
    }

    int score_;
    std::string edge_name_;
    std::string force_name_;
    bool is_active_;

    cocos2d::Label* score_label_;
    cocos2d::Label* edge_label_;
    cocos2d::Label* force_label_;

    static constexpr float width_ = 50;
    static constexpr float height_ = 90;

    static constexpr float score_height_ = 30;
    static constexpr float edge_height_ = 30;
    static constexpr float force_height_ = GameInfoWidget::height_ - (GameInfoWidget::edge_height_ + GameInfoWidget::score_height_);
};


class DebugUI: public cocos2d::Sprite {
public:
    DebugUI(GameInfoWidget* left_player_info, GameInfoWidget* right_player_info):
            left_player_info_{left_player_info}, right_player_info_{right_player_info} {}

    static DebugUI* create(GameInfoWidget* left_player_info, GameInfoWidget* right_player_info) {
        auto debug_ui = new DebugUI(left_player_info, right_player_info);

        debug_ui->autorelease();
        debug_ui->initOptions();
        debug_ui->addEvents();

        return debug_ui;
    }

    static DebugUI* create() {
        auto left_widget = GameInfoWidget::create();
        left_widget->setActive();

        auto right_widget = GameInfoWidget::create();
        right_widget->setPassive();

        return DebugUI::create(left_widget, right_widget);
    }

    void switchState() {
        left_player_info_->switchState();
        right_player_info_->switchState();
    }

    void setLeftPlayerScore(int score) {
        left_player_info_->updateScore(score);
    }

    void setRightPlayerScore(int score) {
        right_player_info_->updateScore(score);
    }

private:
    void initOptions() {
        createGameInfo();
        createButtons();
    };

    void addEvents() {
        auto turn_finished_call_back = [this](tree_events::TurnFinishedEvent* event) -> void {
            switchState();
            std::cout << "Debug GUI: turn finished" << std::endl;
        };
        auto turn_finished_listener = event_wrappers::create_listener<tree_events::TurnFinishedEvent>(turn_finished_call_back);
        cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(turn_finished_listener, 1);
    };

    void createGameInfo() {
        auto window_size = cocos2d::Director::getInstance()->getVisibleSize();
        auto game_info_level = window_size.height * 0.7f;
        auto hor_offset = window_size.width * 0.1f;

        left_player_info_->setPosition(hor_offset, game_info_level);
        left_player_info_->setAnchorPoint(cocos2d::Vec2(0, 0));

        right_player_info_->setPosition(window_size.width - right_player_info_->getContentSize().width - hor_offset * 0.5f,
                                        game_info_level);
        right_player_info_->setAnchorPoint(cocos2d::Vec2(0, 0));

        addChild(left_player_info_);
        addChild(right_player_info_);
    }

    void createButtons() {
        auto window_size = cocos2d::Director::getInstance()->getVisibleSize();
        auto button_level = window_size.height * 0.9f;

        submit_button_ = cocos2d::ui::Button::create("ui/debug_ui/submit_button.png");
        submit_button_->setScale(0.3);
        submit_button_->setPosition(cocos2d::Vec2(900, button_level));
        submit_button_->setSwallowTouches(true);
        submit_button_->addClickEventListener([this](cocos2d::Ref* pSender) -> void {
            auto event = tree_events::SubmitChangesEvent();
            this->_eventDispatcher->dispatchEvent(&event); });
        this->addChild(submit_button_, 12);
        addChild(submit_button_);


        revert_button_ = cocos2d::ui::Button::create("ui/debug_ui/undo_button.png");
        revert_button_->setScale(0.5);
        revert_button_->setPosition(cocos2d::Vec2(100, button_level));
        revert_button_->setSwallowTouches(true);
        revert_button_->addClickEventListener([this](cocos2d::Ref* pSender) -> void {
            auto event = tree_events::RevertLastChangeEvent();
            this->_eventDispatcher->dispatchEvent(&event); });
        this->addChild(revert_button_, 12);
    }


    GameInfoWidget* left_player_info_;
    GameInfoWidget* right_player_info_;
    cocos2d::ui::Button* submit_button_;
    cocos2d::ui::Button* revert_button_;
};


#endif //MYGAME_DEBUGUI_H
