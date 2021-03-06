cmake_minimum_required (VERSION 3.3.0)

set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# When in debug mode, we run Address Sanitizer to find memory errors
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -fsanitize=address")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(PROJECT_TRDPARTY_DIR 3rdparty/)
include(cmake/clang-format.cmake)

set(SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SoundManager.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/GameObjects/GenericObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GameObjects/GameObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GameObjects/Ball.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GameObjects/Paddle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GameObjects/Ground.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GameObjects/Rotatable.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/States/State.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/States/GameState.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/States/MenuState.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/ECSManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/System.cpp
)

project(Project2)

set(OGRE_DIR "/lusr/opt/ogre-1.11/lib/OGRE/cmake")

find_package(OGRE 1.11 REQUIRED COMPONENTS Bites RTShaderSystem)

# copy resource.cfg next to our binaries where OGRE looks for it
file(COPY ${OGRE_CONFIG_DIR}/resources.cfg DESTINATION ${CMAKE_BINARY_DIR})

add_executable(Project2 ${SRCS})

find_package(SDL2 REQUIRED) 
if (SDL_FOUND)
    string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES) # remove the whitespace in the path on the lab machines
endif (SDL_FOUND)

message(STATUS "sdl2 lib: " ${SDL2_LIBRARY})
message(STATUS "sdl2 include: " ${SDL2_INCLUDE_DIR})

find_package(SDL2_mixer QUIET) 
if (NOT SDL2MIXER_FOUND) # this is for the lab machines, where find_package doesn't work for sdl_mixer
    set(SDL2MIXER_LIBRARY "/usr/lib/x86_64-linux-gnu/libSDL2_mixer-2.0.so.0")
    set(SDL2MIXER_INCLUDE_DIR "/usr/")
endif (NOT SDL2MIXER_FOUND)

#set(CMAKE_PREFIX_PATH "/lusr/opt/bullet-2.86/;")
#find_package(Bullet REQUIRED PATHS /lusr/opt/bullet-2.86)
#message(STATUS ${BULLET_LIBRARIES})
#message(STATUS ${BULLET_INCLUDE_DIR})

#set(CMAKE_PREFIX_PATH "/lusr/opt/cegui-0.8.7/lib/pkgconfig;${CMAKE_PREFIX_PATH}")
find_package(CEGUI REQUIRED OgreRenderer)
message(STATUS ${CEGUI_FOUND})
message(STATUS ${CEGUI_INCLUDE_DIR})
message(STATUS ${CEGUI_LIBRARIES})

message(STATUS ${CEGUI_OgreRenderer_FOUND})
message(STATUS ${CEGUI_OgreRenderer_INCLUDE_DIR})
message(STATUS ${CEGUI_OgreRenderer_LIBRARIES})

# Everything in the include directory can be #include'd from cpp and h files
# without using relative paths
target_include_directories(Project2 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${SDL2MIXER_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIR}
    #${CEGUI_INCLUDE_DIR}
    #${CEGUI_OgreRenderer_INCLUDE_DIR}

    #${BULLET_INCLUDE_DIR}
    /lusr/opt/bullet-2.86/include/bullet
)

target_link_libraries(Project2 PUBLIC
    ${OGRE_LIBRARIES}
    ${OIS_LIBRARIES}
    ${SDL2_LIBRARY}
    ${SDL2MIXER_LIBRARY}
    #${CEGUI_LIBRARIES}
    #${CEGUI_OgreRenderer_LIBRARIES}

    #${BULLET_LIBRARIES}

    # THIS IS BAD BUT IT WON'T WORK ANY OTHER WAY
    # the find_package is broken, even when setting prefix_path
    /lusr/opt/bullet-2.86/lib/libBulletDynamics.a
    /lusr/opt/bullet-2.86/lib/libBulletCollision.a
    /lusr/opt/bullet-2.86/lib/libLinearMath.a
)
