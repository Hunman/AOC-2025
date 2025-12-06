cmake_minimum_required(VERSION 4.0)
project(AdventOfCode)

enable_testing()

find_package(PkgConfig REQUIRED)
find_package(GTest REQUIRED)
find_package(TBB REQUIRED COMPONENTS tbb)

set(CMAKE_CXX_STANDARD 23)

file(REAL_PATH ./input INPUT_DIRECTORY)
message(STATUS "INPUT_DIRECTORY=${INPUT_DIRECTORY}")

set(WARNING_FLAGS
        -Wall
        -Wextra
        -Wpedantic
        -pedantic
        -pedantic-errors
        -Wmissing-declarations
        -Wredundant-decls
        -Wcast-align=strict
        -Wcast-qual
        -Wvla
        -Wformat=2
        -Wformat-overflow=2
        -Wformat-signedness
        -Wnull-dereference
        -Wrestrict
        -Wmisleading-indentation
        -Wwrite-strings
        -Wunused
        -Wdouble-promotion
        -Wlogical-op
        -Wduplicated-cond
        -Wduplicated-branches
        -Wundef
        -Wconversion
        -Wsign-conversion
        -Wstrict-overflow=2
        -Wshift-overflow=2
        -Wimplicit-fallthrough=3
        -Wuninitialized
        -Winit-self
        -Winvalid-pch
        -Wmissing-include-dirs
        -Wold-style-cast
        -Wuseless-cast
        -Woverloaded-virtual
        -Wnon-virtual-dtor
        -Wzero-as-null-pointer-constant
        -Werror=unused-result
        -Werror=write-strings
)

include_directories(include)

function(make_day DAY)
    message(STATUS "Generating day ${DAY}")

    file(GLOB EXTRA_FILES "src/day${DAY}/*.cpp")

    add_executable("day${DAY}"
            "src/day${DAY}.cpp" "${EXTRA_FILES}"
    )

    target_compile_options("day${DAY}" PRIVATE ${WARNING_FLAGS})
    target_compile_definitions("day${DAY}" PUBLIC INPUT_DIRECTORY="${INPUT_DIRECTORY}")
    target_link_libraries("day${DAY}"
            tbb
    )

    add_executable("day${DAY}Test"
            "tests/day${DAY}.cpp"
            "${EXTRA_FILES}"
    )

    target_compile_options("day${DAY}Test" PRIVATE ${WARNING_FLAGS} --coverage)
    target_link_libraries("day${DAY}Test"
            GTest::Main
            tbb
            gcov
    )

    gtest_discover_tests("day${DAY}Test")
endfunction()

include(GoogleTest)
include(CTestCoverageCollectGCOV)

make_day(1)
make_day(2)
make_day(3)
make_day(4)
make_day(5)
make_day(6)
