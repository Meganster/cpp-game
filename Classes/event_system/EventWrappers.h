//
// Created by artem on 12.11.16.
//

#ifndef MYGAME_EVENTWRAPPERS_H
#define MYGAME_EVENTWRAPPERS_H

#include "cocos2d.h"
#include <vector>
#include <string>

namespace event_wrappers {
/** This class is a wrapper around cocos2d::EventCustom.
 *  The only purpose of this class creation is std::string kEventName,
 *  which enables to use unnamed custom events.
 */
    class MyEventCustom : public cocos2d::EventCustom {
    public:
        MyEventCustom() = delete;

        /**
         * Every constructor of child classes must begin with MyEventCustom(this) to initialize
         * MyEventCustom with kEventName of the childClass
         */
        template <class T>
        MyEventCustom(const T* event): cocos2d::EventCustom(event->kEventName) {};
        static const std::string kEventName;
    };


/**
 * This function is to be used to create event listeners for arbitrary custom events.
 * It enables to use any behavior defined in the classes inherited from MyEventCustom.
 * When used, event class has to be explicitly provided to the function call:
 * Usage example: auto listener = create_listener<EventClass>([](EventClass* event)->{std::cout << eventkEventName})
 */
    template <class T>
    cocos2d::EventListenerCustom* create_listener(const std::function<void(T*)>& callback) {
        auto inner_function = [callback](cocos2d::EventCustom* event_ptr) -> void {
            auto original_event_ptr = (T*)event_ptr;
            callback(original_event_ptr);
        };

        return cocos2d::EventListenerCustom::create(T::kEventName, inner_function);
    };
}



#endif //MYGAME_EVENTWRAPPERS_H
