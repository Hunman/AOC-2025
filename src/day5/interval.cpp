#include "day5/interval.hpp"

#include <cassert>

Interval::Interval() {
    map[0] = false;
}

/** @see https://ideone.com/DDitxZ */
void Interval::add(uint64_t start, uint64_t end) {
    auto val = true;

    if (!(start < end)) {
        return;
    }
    auto nextInterval = --map.upper_bound(end);
    auto inserted1 = map.end();
    auto inserted2 = map.end();
    assert(nextInterval != map.end());
    if (nextInterval->second == val) {
        ++nextInterval;
    } else if (nextInterval->first < end) {
        const bool &nextValue = nextInterval->second;
        ++nextInterval;
        inserted1 = nextInterval = map.emplace_hint(nextInterval, end, nextValue);
    }
    try {
        auto prevInterval = nextInterval;
        --prevInterval;
        assert(prevInterval != map.end());
        if (start < prevInterval->first) {
            prevInterval = --map.upper_bound(start);
        }
        assert(prevInterval != map.end());
        if (!(prevInterval->second == val)) {
            if (prevInterval->first < start) {
                ++prevInterval;
                inserted2 = prevInterval = map.emplace_hint(prevInterval, start, val);
            } else {
                prevInterval->second = val;
                if (prevInterval != map.begin() && !((--prevInterval)->second == val)) {
                    ++prevInterval;
                }
            }
        }
        assert(prevInterval != map.end());
        map.erase(++prevInterval, nextInterval);
    } catch (...) {
        if (inserted1 != map.end()) {
            map.erase(inserted1);
        }
        if (inserted2 != map.end()) {
            map.erase(inserted2);
        }
        throw;
    }
}

bool Interval::operator[](uint64_t key) const {
    auto it = map.upper_bound(key);
    if (it == map.begin()) {
        return false;
    }

    return (--it)->second;
}

uint64_t Interval::getValidCount() const {
    uint64_t validCount = 0uz;
    uint64_t lastKey = 0uz;
    auto lastValue = false;

    for (const auto &[key, value]: map) {
        if (lastValue && value) {
            continue;
        }
        if (!value) {
            validCount += (key - lastKey);
        }
        lastKey = key;
        lastValue = value;
    }

    return validCount;
}
