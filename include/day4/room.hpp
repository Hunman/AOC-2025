#pragma once
#include <string>
#include <vector>

class Room {
public:
    static constexpr char ROLL = '@';
    static constexpr char MARK = '!';
    static constexpr char GROUND = '.';

    class Cell {
    public:
        Cell() = delete;
        Cell(Room &, int32_t x, int32_t y);

        bool isRoll() const;
        bool isRemovable() const;
        void remove();

    private:
        Room &room;
        int32_t x, y;
    };

    Room() = delete;

    explicit Room(const std::vector<std::string> &lines);

    Cell operator[](int32_t x, int32_t y);

    inline size_t columns() const {
        return _columns;
    }

    inline size_t rows() const {
        return _rows;
    }

    void remove();

private:
    size_t _columns, _rows;

    std::string contents;
};
