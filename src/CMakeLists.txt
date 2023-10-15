cmake_minimum_required(VERSION 3.10)
project(floorPlanToMap)
set(CMAKE_CXX_STANDARD 20)
find_package(OpenCV REQUIRED)
include_directories(appStateMachine/include
                    cmdLineArgHandler/include
                    procMapImage/include)
add_executable(floorPlanToMap floorPlanToMap.cpp
                              appStateMachine/src/appStateMachine.cpp
                              cmdLineArgHandler/src/cmdLineArgHandler.cpp
                              procMapImage/src/procMapImage.cpp)
target_link_libraries(floorPlanToMap ${OpenCV_LIBRARIES})