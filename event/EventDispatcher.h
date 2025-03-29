//
// Created by yhwach on 2/26/25.
//

#pragma once

#include <utility>

namespace event {
    template<typename ThreadType = std::thread>
    class EventDispatcher final {
    public:
        EventDispatcher()
            : running(false) {
        }

        EventDispatcher(EventDispatcher &&dispatcher) noexcept {
            running = dispatcher.running;
            thread = std::move(dispatcher.thread);
        }

        void start(auto matchingAlgo) {
            running = true;

            thread = ThreadType([this, matchingAlgo] {
                while (running) {
                    matchingAlgo();
                }
            });

            thread.detach();
        }

        void stop() {
            running = false;
        }

    private:
        bool running;
        ThreadType thread;
    };
}