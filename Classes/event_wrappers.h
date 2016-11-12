//
// Created by artem on 12.11.16.
//

#ifndef MYGAME_EVENT_WRAPPERS_H
#define MYGAME_EVENT_WRAPPERS_H

#include "cocos2d.h"
#include <vector>
#include <string>

class MyEventCustom : public cocos2d::EventCustom {
public:
    MyEventCustom() : cocos2d::EventCustom(kEventName) {};
    static const std::string kEventName;
};

const std::string MyEventCustom::kEventName = "Some event";


class MyEventListenerCustom : public cocos2d::EventListenerCustom {
public:
    /** This method is defined as a template to enable its specification in
     * case of creation of events with non-standard behavior.
     */
    template <typename T=MyEventCustom>
    static cocos2d::EventListenerCustom* create(const T* event, const std::function<void(T*)>& callback) {
        return cocos2d::EventListenerCustom::create(event->kEventName, callback);
    };
};

#endif //MYGAME_EVENT_WRAPPERS_H
