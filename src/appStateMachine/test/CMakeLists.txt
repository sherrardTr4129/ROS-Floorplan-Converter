cmake_minimum_required(VERSION 3.14)
project(test_app_state_machine)

include_directories(../include)
add_executable(testStateMachine ../src/appStateMachine.cpp test_state_machine.cpp)
target_link_libraries(testStateMachine gtest)