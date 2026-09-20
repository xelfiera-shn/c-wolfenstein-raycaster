cmake_minimum_required(VERSION 3.15)
project(CWolfensteinRaycaster C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(raylib QUIET)

if(NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW TRUE
    )
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(raylib)
endif()

file(GLOB_RECURSE PROJECT_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.c
)

file(GLOB_RECURSE PROJECT_HEADERS
    ${CMAKE_SOURCE_DIR}/src/*.h
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

file(GLOB_RECURSE HEADER_FILES_FOR_DIRS ${CMAKE_SOURCE_DIR}/src/*.h)
set(INCLUDE_DIRS "")
foreach(HEADER ${HEADER_FILES_FOR_DIRS})
    get_filename_component(DIR ${HEADER} DIRECTORY)
    list(APPEND INCLUDE_DIRS ${DIR})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL"
    )
endif()

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm gdi32 opengl32)
endif()