cmake_minimum_required(VERSION 3.16)
project(aries LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(PRECOMPILED_HEADER_FILE "src/ariespch.h")

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 10.1.1)
FetchContent_MakeAvailable(fmt)

add_executable(aries src/main.cpp "src/Game.h" "src/Game.cpp"
"src/ResourceHolder.h"  
"src/ariespch.h" "src/ariespch.cpp"
"src/Entity.h" "src/Player.h" "src/SceneNode.h" "src/SceneNode.cpp" "src/Player.cpp")
target_link_libraries(aries PRIVATE sfml-graphics fmt-header-only)
target_compile_features(aries PRIVATE cxx_std_20)
target_compile_definitions(aries PRIVATE TEXTURE_PATH="${CMAKE_SOURCE_DIR}/src/content/textures/")
target_precompile_headers(aries PRIVATE ${PRECOMPILED_HEADER_FILE})
if(WIN32)
    add_custom_command(
        TARGET aries
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:aries>
        VERBATIM)
endif()

install(TARGETS aries)
