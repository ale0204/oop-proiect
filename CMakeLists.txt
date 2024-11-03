cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
project(oop)
# set(CMAKE_PROJECT_VERSION_MAJOR 0)
# set(CMAKE_PROJECT_VERSION_MINOR 0)
# set(CMAKE_PROJECT_VERSION_PATCH 1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)

###############################################################################

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
add_executable(${PROJECT_NAME} src/main.cpp)

include(cmake/CompilerFlags.cmake)

# SDL2 setup for Windows
if (WIN32)
    # Set SDL2 include and library directories manually
    set(SDL2_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/SDL2/include")
    set(SDL2_LIB_DIR "${CMAKE_SOURCE_DIR}/SDL2/lib")
        
    # Include SDL2 headers and link libraries using explicit paths
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR})
    target_link_directories(${PROJECT_NAME} PRIVATE ${SDL2_LIB_DIR})
    target_link_libraries(${PROJECT_NAME} PRIVATE "${SDL2_LIB_DIR}/libSDL2.a" "${SDL2_LIB_DIR}/libSDL2main.a"
    user32 gdi32 winmm imm32 setupapi version)
else()
    # Find SDL2 automatically on Linux/macOS
    find_package(SDL2 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)
endif()

###############################################################################

# external dependencies with FetchContent
# include(FetchContent)
#
# set(FETCHCONTENT_QUIET OFF)
# set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
#
# NOTE: Also update env vars used for caching in
#         - .github/actions/configure-cmake/action.yml
#         - .github/workflows/cmake.yml
# FetchContent_Declare(
#         SomeLib
#         GIT_REPOSITORY https://github.com/<SomeUser>/<SomeLib>.git
#         GIT_TAG        <some_git_hash> # <which tag/branch @ <some_date>>
#         GIT_SHALLOW    1  # works only with branches or tags, not with arbitrary commit hashes
# )
#
# FetchContent_MakeAvailable(SomeLib)

###############################################################################

# external dependencies with find_package

# find_package(Threads REQUIRED)

###############################################################################

# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE include)

# Additional target include directories and libraries
# target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ext/<SomeHppLib>/include)
# target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${<SomeLib>_SOURCE_DIR}/include)
# target_link_directories(${PROJECT_NAME} PRIVATE ${<SomeLib>_BINARY_DIR}/lib)
# target_link_libraries(${PROJECT_NAME} <SomeLib>)

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
install(TARGETS ${PROJECT_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

include(cmake/CopyHelper.cmake)
copy_files(FILES tastatura.txt)
# copy_files(FILES tastatura.txt config.json DIRECTORY images sounds)
# copy_files(DIRECTORY images sounds)
