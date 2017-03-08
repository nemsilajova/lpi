cmake_minimum_required(VERSION 3.1)
project(Formula)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(formulaTest
	Formula.cpp
	FormulaTypes.cpp
	FormulaTest.cpp
)

add_custom_target(run
    COMMAND formulaTest
    COMMENT "Running formulaTest"
)
