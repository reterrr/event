# Event Library

A simple and efficient event library for handling events and listeners in C++.

## Features
- **Easy event registration and dispatching**
- **Custom event and listener support**
- **Lightweight and flexible design**

## Installation
To build and install the library, use the following commands:

```sh
git clone <repo_url>
cd <repo_name>
mkdir build && cd build
cmake ..
make
```

## Usage Example
Here is an example demonstrating how to use the event library:

```cpp
#include <iostream>
#include "event/event.hpp"

struct CustomEvent final : event::Event {
    explicit CustomEvent(std::string s) : str(std::move(s)) {}
    std::string str;
};

class CustomListener final : public event::EventListener<CustomEvent> {
public:
    void onEvent(const CustomEvent &event) override {
        std::cout << event.str << std::endl;
    }
};

int main() {
    event::EventBroker broker{event::EventDispatcher()};
    broker.registerListener(std::make_unique<CustomListener>());
    broker.registerEvent(std::make_unique<CustomEvent>("Hello World!"));
    return 0;
}
```
