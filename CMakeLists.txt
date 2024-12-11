cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
project(oop)
set(CMAKE_PROJECT_VERSION_MAJOR 0)
set(CMAKE_PROJECT_VERSION_MINOR 1)
# set(CMAKE_PROJECT_VERSION_PATCH 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


###############################################################################

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
add_executable(${PROJECT_NAME} 
    src/main.cpp 
    src/AbstractTable.cpp
    src/MYSQLConnection.cpp
    src/TestTable.cpp
    src/TestTableEntry.cpp
    src/Entity.cpp
    src/CandyCrush/Candy.cpp
    src/CandyCrush/CandyCrush.cpp
    src/CandyCrush/Game.cpp
    src/CandyCrush/GameObject.cpp
    src/CandyCrush/GUIManager.cpp
    src/CandyCrush/TextureManager.cpp
    src/CandyCrush/exceptions/SDLInitException.cpp
    src/CandyCrush/exceptions/TTFInitException.cpp
    src/CandyCrush/exceptions/IMGInitException.cpp
)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE include)


set(MY_LIBRARIES_DIR "${CMAKE_SOURCE_DIR}/libraries")
# MySQL setup
set(MySQL_INCLUDE_DIR "${MY_LIBRARIES_DIR}/MySQL/include")
set(MySQL_LIB_DIR "${MY_LIBRARIES_DIR}/MySQL/lib")

# Include MySQL headers
target_include_directories(${PROJECT_NAME} PRIVATE ${MySQL_INCLUDE_DIR})

# Link against libmysql.dll instead of mysqlclient.lib
target_link_libraries(${PROJECT_NAME} PRIVATE "${MySQL_LIB_DIR}/libmysql.dll")

# SDL2 setup for Windows
if (WIN32)
    # Set SDL2 include and library directories manually
    set(SDL2_INCLUDE_DIR "${MY_LIBRARIES_DIR}/SDL2/include")
    set(SDL2_LIB_DIR "${MY_LIBRARIES_DIR}/SDL2/lib")
    set(SDL2_IMAGE_LIB_DIR "${MY_LIBRARIES_DIR}/SDL2_Image/lib")
    set(SDL2_TTF_LIB_DIR "${MY_LIBRARIES_DIR}/SDL2_ttf/lib")
    # MySQL setup
    set(MySQL_INCLUDE_DIR "{MY_LIBRARIES_DIR}/MySQL/include")
    set(MySQL_LIB_DIR "{MY_LIBRARIES_DIR}/MySQL/lib")
    # Include SDL2 headers and link libraries using explicit paths
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR} ${MySQL_INCLUDE_DIR})
    target_link_directories(${PROJECT_NAME} PRIVATE ${SDL2_LIB_DIR} ${MySQL_LIB_DIR}, ${SDL2_IMAGE_LIB_DIR}
        ${SDL2_TTF_LIB_DIR})
    target_link_libraries(${PROJECT_NAME} PRIVATE "${SDL2_LIB_DIR}/libSDL2.a" "${SDL2_LIB_DIR}/libSDL2main.a" 
        "${SDL2_IMAGE_LIB_DIR}/libSDL2_image.a" "${SDL2_TTF_LIB_DIR}/libSDL2_ttf.a"
        user32 gdi32 winmm imm32 rpcrt4 setupapi version)
    # List the DLLs to copy
    set(DLL_FILES
    "${MY_LIBRARIES_DIR}/SDL2/bin/SDL2.dll"
    "${MY_LIBRARIES_DIR}/SDL2_Image/bin/SDL2_Image.dll"
    "${MY_LIBRARIES_DIR}/SDL2_ttf/bin/SDL2_ttf.dll"
    "${MY_LIBRARIES_DIR}/MySQL/lib/libmysql.dll"
    "${MY_LIBRARIES_DIR}/MySQL/lib/libssl-3-x64.dll"
    "${MY_LIBRARIES_DIR}/MySQL/lib/libcrypto-3-x64.dll"
    
    )

    # Copy each DLL to the output directory after the executable is built
    foreach(DLL ${DLL_FILES})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying ${DLL} to $<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${DLL}"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach()
else()
    # SDL2 setup for Linux
    find_package(SDL2 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

    # Manually specify the paths for SDL2_image and SDL2_ttf
    set(SDL2_IMAGE_INCLUDE_DIR "/usr/include/SDL2")
    set(SDL2_IMAGE_LIB_DIR "/usr/lib/x86_64-linux-gnu")

    set(SDL2_TTF_INCLUDE_DIR "/usr/include/SDL2")
    set(SDL2_TTF_LIB_DIR "/usr/lib/x86_64-linux-gnu")

    # Include SDL2_image and SDL2_ttf headers
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

    # Link SDL2_image and SDL2_ttf libraries
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_IMAGE_LIB_DIR}/libSDL2_image.so)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_TTF_LIB_DIR}/libSDL2_ttf.so)

    # MySQL setup for Linux
    set(MYSQL_DIR "/usr/lib/x86_64-linux-gnu/cmake/mysql")

    # Include MySQL headers and libraries
    target_include_directories(${PROJECT_NAME} PRIVATE /usr/include/mysql)
    target_link_libraries(${PROJECT_NAME} PRIVATE /usr/lib/x86_64-linux-gnu/libmysqlclient.so)
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

copy_files(FILES tastatura.txt)
copy_files(DIRECTORY assets)
# copy_files(FILES tastatura.txt config.json DIRECTORY images sounds)
# copy_files(DIRECTORY images sounds)