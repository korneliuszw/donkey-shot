cmake_minimum_required(VERSION 3.0)
project(DonkeyShot)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} include)

add_executable(DonkeyShot
    main.cpp
        include/DataStructures.h
        src/TextureManager.cpp  include/TextureManager.h
        src/Entity.cpp include/Entity.h
        src/AnimatedEntity.cpp  include/AnimatedEntity.h
        include/StaticEntities.h
        src/Player.cpp include/Player.h
        src/Window.cpp include/Window.h
        src/Game.cpp include/Game.h
        src/WindowManager.cpp include/WindowManager.h src/StaticEntities.cpp src/DataStructures.cpp src/InfoWindow.cpp include/InfoWindow.h include/Collider.h)

target_link_libraries(DonkeyShot ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

set_target_properties(DonkeyShot PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)