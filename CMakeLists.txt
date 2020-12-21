cmake_minimum_required(VERSION 3.1)
project(earley)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_INSTALL_RPATH "${PROJECT_SOURCE_DIR}/bin")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(earley main.cpp Grammar.cpp Earley.cpp)
enable_testing()
add_executable(Test tests.cpp Grammar.cpp Earley.cpp)

target_link_libraries(Test Threads::Threads ${GTEST_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})
target_link_libraries(Test -fprofile-arcs)
install(
        TARGETS Test
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
)

install(
        TARGETS earley
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
)
