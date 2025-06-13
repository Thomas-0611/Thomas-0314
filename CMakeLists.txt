cmake_minimum_required(VERSION 3.16)
project(PLANTS_VS_ZOMBIES)

set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0135 NEW)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
        ptsd

        GIT_REPOSITORY  https://github.com/Tommy0313/practical-tools-for-simple-design.git
        GIT_TAG         main  # 或你的目標分支/標籤/commit hash

        # Or alternatively if you want to use a specific git commit instead of a release:
        # GIT_REPOSITORY  https://github.com/ntut-open-source-club/practical-tools-for-simple-design.git
        # GIT_TAG         <git_tag>

        SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/PTSD
)

FetchContent_MakeAvailable(ptsd)

include(files.cmake)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
list(TRANSFORM SRC_FILES PREPEND ${SRC_DIR}/)
list(TRANSFORM INCLUDE_FILES PREPEND ${INCLUDE_DIR}/)

# file(GLOB_RECURSE SRC_FILES src/*)
# file(GLOB_RECURSE HEADER_FILES include/*)

add_executable(${PROJECT_NAME}
    ${SRC_DIR}/main.cpp
    ${SRC_FILES}
    ${HEADER_FILES}
        include/AnimatedCharacter.hpp
        src/AnimatedCharacter.cpp
        src/AnimatedCharacter.cpp
        include/BackgroundImage.hpp
        include/zombie/Zombie.hpp
        src/zombie/Zombie.cpp
        include/plant/Peashooter.hpp
        src/plant/Peashooter.cpp
        include/plant/Pea.hpp
        src/Pea.cpp
        include/Button.hpp
        include/plant/Sun.hpp
        src/Sun.cpp
        include/plant/Plant.hpp
        include/plant/Sunflower.hpp
        src/plant/Sunflower.cpp
        include/GameContext.hpp
        include/plant/Wallnut.hpp
        src/plant/Wallnut.cpp
        include/plant/Repeater.hpp
        src/Repeater.cpp
        include/zombie/Coneheadzombie.hpp
        src/zombie/Coneheadzombie.cpp
        include/zombie/Bucketheadzombie.hpp
        src/zombie/Bucketheadzombie.cpp
        include/zombie/Flagzombie.hpp
        src/zombie/Flagzombie.cpp
        include/zombie/Polevaultingzombie.hpp
        src/zombie/Polevaultingzombie.cpp
        include/plant/Snowpeashooter.hpp
        src/plant/Snowpeashooter.cpp
        include/plant/Snowpea.hpp
        src/Snowpea.cpp
        include/plant/Cherrybomb.hpp
        src/plant/Cherrybomb.cpp
        include/plant/Potatomine.hpp
        src/plant/Potatomine.cpp
        include/plant/Chomper.hpp
        src/plant/Chomper.cpp
        include/ZombieSpawner.hpp
        include/level/Level1.hpp
        include/level/LevelManager.hpp
        include/level/Level.hpp
        include/Lawnmower.hpp
        src/Lawnmower.cpp
        include/level/Level2.hpp
        include/level/Level3.hpp
        include/level/Level4.hpp
        include/level/Level5.hpp
        include/level/Level6.hpp
        include/level/Level7.hpp
        include/level/Level8.hpp
        include/level/Level9.hpp
        include/level/Level10.hpp
        include/Shovel.hpp
        src/Shovel.cpp
        include/plant/IExplosive.hpp
        include/plant/IShooter.hpp
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Resources")
else()
    message(FATAL_ERROR "relative RESOURCE_DIR is WIP, Please use `-DCMAKE_BUILD_TYPE=Debug` build for now.")
    # target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_DIR="${CMAKE_INSTALL_PREFIX}/Resources")
endif()

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${DEPENDENCY_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/PTSD/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2main
    PTSD
)
