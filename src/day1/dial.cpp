#include "day1/dial.h"

Dial::Dial(int64_t initial, uint32_t limit): _value(initial), limit(limit) {
    // ...
}

size_t Dial::left(size_t value) {
    auto zeros = 0uz;

    for (auto i = 0uz; i < value; i++) {
        zeros += left();
    }

    return zeros;
}

size_t Dial::right(size_t value) {
    auto zeros = 0uz;

    for (auto i = 0uz; i < value; i++) {
        zeros += right();
    }

    return zeros;
}

bool Dial::left() {
    _value--;
    if (_value < 0) {
        _value = limit - 1;
    }

    return _value == 0;
}

bool Dial::right() {
    _value++;
    if (_value == limit) {
        _value = 0;
    }

    return _value == 0;
}
