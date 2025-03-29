//
// Created by yhwach on 2/15/25.
//

#pragma once

#include <algorithm>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>

#include "Event.h"
#include "EventDispatcher.h"
#include "EventListener.h"

namespace event {
    class EventBroker_ {
    public:
        virtual ~EventBroker_() = default;

        virtual void registerEvent(std::unique_ptr<Event> &&event) = 0;

        virtual void registerListener(std::unique_ptr<EventListener_> &&listener) = 0;
    };

    class EventBroker final : public EventBroker_ {
    public:
        explicit EventBroker(EventDispatcher<std::thread> &&dispatcher)
            : dispatcher(std::move(dispatcher)) {
            dispatcher.start(matchingAlgo);
        }

        ~EventBroker() override {
            while (!events.empty()) {
            }

            dispatcher.stop();
        }

        void registerEvent(std::unique_ptr<Event> &&event) override {
            std::unique_lock lock(events_mutex);
            events.push(std::move(event));
        }

        void registerListener(std::unique_ptr<EventListener_> &&listener) override {
            std::unique_lock lock(listeners_mutex);
            listeners.push_back(std::move(listener));
        }

    private:
        EventDispatcher<std::thread> dispatcher{};

        static inline auto listeners = std::vector<std::unique_ptr<EventListener_> >();
        static inline auto events = std::queue<std::unique_ptr<Event> >();

        static inline std::mutex events_mutex;
        static inline std::mutex listeners_mutex;

        constexpr static auto matchingAlgo = [] {
            std::unique_lock event_lock(events_mutex);

            if (!events.empty()) {
                auto event = std::move(events.front());

                event_lock.unlock();

                std::unique_lock listeners_lock(listeners_mutex);
                for (const auto &listener: listeners) {
                    if (listener->matches(*event))
                        listener->handleEvent(*event);
                }

                events.pop();
            }
        };
    };
}
