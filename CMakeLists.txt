cmake_minimum_required(VERSION 3.10)
project(Sudoku-Software-Project C)

set(CMAKE_C_STANDARD 90)
set(GCC_COVERAGE_COMPILE_FLAGS "-c -fmessage-length=0 –ansi -Wall -O3 -Wextra -Werror -pedantic-errors")
add_library(gurobi801 SHARED IMPORTED)
set_target_properties(gurobi801 PROPERTIES IMPORTED_LOCATION "/Library/gurobi801/mac64/lib/libgurobi80.so")

add_executable(sudoku main.c Solver.c Solver.h Game.c Game.h Parser.c Parser.h MainAux.c MainAux.h List.c List.h Exceptions.c Exceptions.h gurobi_c.h GameAux.c GameAux.h)

