#include "day10/machine.hpp"
#include "gtest/gtest.h"

class MachineTester {
public:
    explicit MachineTester(Machine &&machine): machine(machine) {
        // Empty
    }

    size_t lightsCount() const {
        return machine.lightsCount;
    }

    size_t lightsTarget() const {
        return machine.target;
    }

    size_t buttonCount() const {
        return machine.buttons.size();
    }

    std::vector<Machine::Button> buttons() const {
        return machine.buttons;
    }

    size_t joltageCount() const {
        return machine.joltages.size();
    }

    std::vector<Machine::Joltage> joltages() const {
        return machine.joltages;
    }

    Machine::Lights target() const {
        return machine.target;
    }

protected:
    const Machine machine;
};

TEST(Day10Test, ParsesMachineCorrectly) {
    const auto line = "[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}";
    const MachineTester machine{Machine{line}};

    ASSERT_EQ(4, machine.lightsCount());
    ASSERT_EQ(6, machine.lightsTarget());
    ASSERT_EQ(6, machine.buttonCount());
    ASSERT_EQ(4, machine.joltageCount());

    ASSERT_EQ(machine.lightsCount(), machine.joltageCount());

    ASSERT_EQ(std::vector({3uz, 5uz, 4uz, 7uz}), machine.joltages());
}

TEST(Day10Test, PressingButtonsWork) {
    const MachineTester machine{Machine{"[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}"}};

    auto buttons = machine.buttons();
    auto result = 0uz;
    result ^= buttons[0] ^= buttons[1] ^= buttons[2];

    ASSERT_EQ(machine.target(), result);
}

TEST(Day10Test, Exercise1GivenExampleMachine1) {
    const Machine machine{"[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}"};

    ASSERT_EQ(2, machine.exercise1());
}

TEST(Day10Test, Exercise1GivenExampleMachine2) {
    const Machine machine{"[...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}"};

    ASSERT_EQ(3, machine.exercise1());
}

TEST(Day10Test, Exercise1GivenExampleMachine3) {
    const Machine machine{"[.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}"};

    ASSERT_EQ(2, machine.exercise1());
}

TEST(Day10Test, Exercise1GivenExample) {
    std::vector machines{
        Machine{"[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}"},
        Machine{"[...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}"},
        Machine{"[.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}"},
    };

    auto solution =
        std::transform_reduce(machines.begin(), machines.end(), 0ull, std::plus{}, [](const Machine &machine) {
            return machine.exercise1();
        });

    ASSERT_EQ(7, solution);
}
//
// TEST(Day10Test, Exercise2GivenExampleMachine1) {
//     const Machine machine{"[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}"};
//
//     ASSERT_EQ(10, machine.exercise2());
// }
//
// TEST(Day10Test, Exercise2GivenExampleMachine2) {
//     const Machine machine{"[...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}"};
//
//     ASSERT_EQ(12, machine.exercise2());
// }
//
// TEST(Day10Test, Exercise2GivenExampleMachine3) {
//     const Machine machine{"[.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}"};
//
//     ASSERT_EQ(11, machine.exercise2());
// }
//
// TEST(Day10Test, Exercise2GivenExample) {
//     std::vector machines{
//         Machine{"[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}"},
//         Machine{"[...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}"},
//         Machine{"[.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}"},
//     };
//
//     auto solution =
//         std::transform_reduce(machines.begin(), machines.end(), 0ull, std::plus{}, [](const Machine &machine) {
//             return machine.exercise2();
//         });
//
//     ASSERT_EQ(33, solution);
// }
