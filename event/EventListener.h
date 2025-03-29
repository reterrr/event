//
// Created by yhwach on 2/25/25.
//

#pragma once

#include "Event.h"

namespace event {
    class EventListener_ {
    public:
        virtual ~EventListener_() = default;

        virtual void handleEvent(const Event &event) = 0;

        [[nodiscard]] virtual bool matches(const Event &event) const = 0;
    };

    template<typename Event_>
    class EventListener : public EventListener_ {
    public:
        ~EventListener() override = default;

        virtual void onEvent(const Event_ &event) = 0;

        void handleEvent(const Event &event) override {
            onEvent(static_cast<const Event_ &>(event));
        }

        [[nodiscard]] bool matches(const Event &event) const override {
            return dynamic_cast<const Event_ *>(&event) != nullptr;
        }
    };
}
