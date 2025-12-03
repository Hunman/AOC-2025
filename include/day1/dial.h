#pragma once

#include <cstddef>
#include <cstdint>

class Dial {
public:
    Dial() = delete;
    Dial(int64_t initial, uint32_t limit);

    [[nodiscard]]
    inline int64_t value() const {
        return _value;
    }

    size_t left(size_t value);
    size_t right(size_t value);

protected:
    int64_t _value;
    const uint32_t limit;

    bool left();
    bool right();

    size_t rotate(int32_t);
};
