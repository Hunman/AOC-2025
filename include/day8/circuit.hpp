#pragma once
#include <vector>

class JunctionBox;

class Circuit {
public:
    Circuit(JunctionBox *box): boxes({box}) {
        // Empty
    }

    void merge(Circuit *other);

    void remove(JunctionBox *box);

    size_t size() const {
        return boxes.size();
    }

private:
    std::vector<JunctionBox *> boxes;
};
