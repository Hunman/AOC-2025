#include "day8/circuit.hpp"

#include "day8/junction_box.hpp"

void Circuit::merge(Circuit *other) {
    if (this == other) {
        return;
    }

    boxes.reserve(boxes.size() + other->boxes.size());
    while (other->boxes.size()) {
        boxes.push_back(other->boxes.back()->moveTo(this));
    }
}

void Circuit::remove(JunctionBox *box) {
    std::erase(boxes, box);
}
