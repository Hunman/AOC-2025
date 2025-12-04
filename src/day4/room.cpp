#include "day4/room.hpp"

#include <format>
#include <iostream>
#include <stdexcept>

Room::Room(const std::vector<std::string> &lines): _columns(0uz), _rows(0uz) {
    constexpr auto nullTerminator = 1uz;

    contents.reserve(lines.size() * lines[0].length() + nullTerminator);

    for (const auto &line: lines) {
        contents += line;
        _columns = std::max(_columns, line.length());
        _rows++;

        if (_columns != line.length()) [[unlikely]] {
            throw std::runtime_error(
                std::format("Line is {:d} characters long instead of {:d}", line.length(), _columns)
            );
        }
    }
}

Room::Cell Room::operator[](int32_t x, int32_t y) {
    return {*this, x, y};
}

Room::Cell::Cell(Room &room, int32_t x, int32_t y): room(room), x(x), y(y) {}

bool Room::Cell::isRoll() const {
    auto c = room.contents[y * room.columns() + x];

    return c == ROLL || c == MARK;
}

bool Room::Cell::isRemovable() const {
    auto neighbours = 0uz;

    if (!isRoll()) {
        return false;
    }

    // The m stands for modifier
    for (auto xm = -1; xm <= +1; xm++) {
        int32_t xx = xm + x;
        if (xx == -1 || xx >= room.columns()) {
            continue;
        }

        for (auto ym = -1; ym <= +1; ym++) {
            int32_t yy = ym + y;
            if (yy == -1 || yy >= room.rows() || (xm == 0 && ym == 0)) {
                continue;
            }

            if (room[xx, yy].isRoll()) {
                neighbours++;
            }
        }
    }

    return neighbours < 4;
}

void Room::Cell::remove() {
    room.contents[y * room.columns() + x] = MARK;
}

void Room::remove() {
    std::replace(contents.begin(), contents.end(), MARK, GROUND);
}
