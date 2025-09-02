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

# SDL2 setup for Windows
if (WIN32)
    # Set SDL2 include and library directories manually
    set(SDL2_INCLUDE_DIR "${MY_LIBRARIES_DIR}/SDL2/include")
    set(SDL2_LIB_DIR "${MY_LIBRARIES_DIR}/SDL2/lib")
    set(SDL2_IMAGE_LIB_DIR "${MY_LIBRARIES_DIR}/SDL2_image/lib")
    set(SDL2_TTF_LIB_DIR "${MY_LIBRARIES_DIR}/SDL2_ttf/lib")
    # MySQL setup (Windows specific paths)
    set(MySQL_INCLUDE_DIR "${MY_LIBRARIES_DIR}/MySQL/include")
    set(MySQL_LIB_DIR "${MY_LIBRARIES_DIR}/MySQL/lib")
    # Include SDL2 headers and link libraries using explicit paths
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR} ${MySQL_INCLUDE_DIR})
    target_link_directories(${PROJECT_NAME} PRIVATE ${SDL2_LIB_DIR} ${MySQL_LIB_DIR} ${SDL2_IMAGE_LIB_DIR}
        ${SDL2_TTF_LIB_DIR})
    
    # Check if AddressSanitizer is enabled and use appropriate libraries
    get_target_property(COMPILE_OPTIONS ${PROJECT_NAME} COMPILE_OPTIONS)
    if(COMPILE_OPTIONS)
        string(FIND "${COMPILE_OPTIONS}" "fsanitize=address" ASAN_FOUND)
    else()
        set(ASAN_FOUND -1)
    endif()
    
    if(ASAN_FOUND GREATER -1)
        # Use DLL import libraries for ASAN builds to avoid COMDAT issues
        target_link_libraries(${PROJECT_NAME} PRIVATE "${SDL2_LIB_DIR}/libSDL2.dll.a" "${SDL2_LIB_DIR}/libSDL2main.a" 
            "${SDL2_IMAGE_LIB_DIR}/libSDL2_image.dll.a" "${SDL2_TTF_LIB_DIR}/libSDL2_ttf.dll.a"
            "${MySQL_LIB_DIR}/libmysql.lib"
            user32 gdi32 winmm imm32 rpcrt4 setupapi version)
    else()
        # Use static libraries for regular builds
        target_link_libraries(${PROJECT_NAME} PRIVATE "${SDL2_LIB_DIR}/libSDL2.a" "${SDL2_LIB_DIR}/libSDL2main.a" 
            "${SDL2_IMAGE_LIB_DIR}/libSDL2_image.a" "${SDL2_TTF_LIB_DIR}/libSDL2_ttf.a"
            "${MySQL_LIB_DIR}/libmysql.lib"
            user32 gdi32 winmm imm32 rpcrt4 setupapi version)
    endif()
    # List the DLLs to copy
    set(DLL_FILES
    "${MY_LIBRARIES_DIR}/SDL2/bin/SDL2.dll"
    "${MY_LIBRARIES_DIR}/SDL2_image/bin/SDL2_image.dll"
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
    if(APPLE)
        # macOS Dependencies - Use FindPackage approach
        find_package(PkgConfig REQUIRED)
        
        # Explicitly exclude Windows libraries directory from all searches
        set(CMAKE_IGNORE_PATH "${CMAKE_SOURCE_DIR}/libraries")
        
        # Set Homebrew prefix
        execute_process(COMMAND brew --prefix OUTPUT_VARIABLE BREW_PREFIX OUTPUT_STRIP_TRAILING_WHITESPACE)
        set(CMAKE_PREFIX_PATH "${BREW_PREFIX}")
        
        # Try to find SDL2 using pkg-config
        pkg_check_modules(SDL2 REQUIRED sdl2)
        pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)  
        pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
        
        # Find MySQL manually for macOS since mysql-client doesn't provide mysqlclient.pc
        # Use NO_DEFAULT_PATH to avoid finding Windows libraries in libraries/MySQL/
        find_path(MYSQL_INCLUDE_DIR mysql.h 
            PATHS ${BREW_PREFIX}/include/mysql ${BREW_PREFIX}/opt/mysql-client/include/mysql
            NO_DEFAULT_PATH)
        find_library(MYSQL_LIBRARY mysqlclient 
            PATHS ${BREW_PREFIX}/lib ${BREW_PREFIX}/opt/mysql-client/lib
            NO_DEFAULT_PATH)
        
        # Verify we found a proper macOS library (not Windows DLL)
        if(MYSQL_LIBRARY)
            get_filename_component(MYSQL_LIB_EXT ${MYSQL_LIBRARY} EXT)
            if(MYSQL_LIB_EXT STREQUAL ".dll")
                message(WARNING "Found Windows DLL instead of macOS library: ${MYSQL_LIBRARY}")
                unset(MYSQL_LIBRARY CACHE)
                set(MYSQL_LIBRARY "")
            endif()
        endif()
        
        if(MYSQL_INCLUDE_DIR AND MYSQL_LIBRARY)
            set(MYSQL_FOUND TRUE)
            set(MYSQL_INCLUDE_DIRS ${MYSQL_INCLUDE_DIR})
            set(MYSQL_LIBRARIES ${MYSQL_LIBRARY})
            message(STATUS "Found MySQL: ${MYSQL_LIBRARY}")
        else()
            message(FATAL_ERROR "MySQL client library not found in Homebrew paths")
        endif()
        
        target_include_directories(${PROJECT_NAME} PRIVATE 
            ${SDL2_INCLUDE_DIRS} 
            ${SDL2_IMAGE_INCLUDE_DIRS} 
            ${SDL2_TTF_INCLUDE_DIRS}
            ${MYSQL_INCLUDE_DIRS})
            
        target_link_directories(${PROJECT_NAME} PRIVATE 
            ${SDL2_LIBRARY_DIRS} 
            ${SDL2_IMAGE_LIBRARY_DIRS} 
            ${SDL2_TTF_LIBRARY_DIRS})
            
        target_link_libraries(${PROJECT_NAME} PRIVATE 
            ${SDL2_LIBRARIES} 
            ${SDL2_IMAGE_LIBRARIES} 
            ${SDL2_TTF_LIBRARIES}
            ${MYSQL_LIBRARIES})
            
        target_compile_options(${PROJECT_NAME} PRIVATE 
            ${SDL2_CFLAGS_OTHER} 
            ${SDL2_IMAGE_CFLAGS_OTHER} 
            ${SDL2_TTF_CFLAGS_OTHER})
        
    else()
        # Linux Dependencies  
        find_package(PkgConfig REQUIRED)
        pkg_check_modules(SDL2 REQUIRED sdl2)
        pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
        pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
        
        target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
        target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
        target_compile_options(${PROJECT_NAME} PRIVATE ${SDL2_CFLAGS_OTHER} ${SDL2_IMAGE_CFLAGS_OTHER} ${SDL2_TTF_CFLAGS_OTHER})

        # MySQL setup for Linux
        target_include_directories(${PROJECT_NAME} PRIVATE /usr/include/mysql)
        target_link_libraries(${PROJECT_NAME} PRIVATE mysqlclient)
    endif()
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

# copy_files(FILES tastatura.txt)  # Removed - not used by the application
copy_files(DIRECTORY assets)
# copy_files(FILES tastatura.txt config.json DIRECTORY images sounds)
# copy_files(DIRECTORY images sounds)