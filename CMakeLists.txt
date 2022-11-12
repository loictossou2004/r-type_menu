cmake_minimum_required(VERSION 3.17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_definitions("-std=c++17")

include(build/conanbuildinfo.cmake)

set(MY_CLIENT r-type_client)
project(${MY_CLIENT})
file(GLOB FILES_SRC_CLIENT Client/src/*.cpp)
file(GLOB FILES_INCLUDE_CLIENT Client/include/*.hpp)
set(CLIENT_SRC ${FILES_SRC_CLIENT})
set(CLIENT_INCLUDE ${FILES_INCLUDE_CLIENT})
conan_basic_setup()
add_executable(${MY_CLIENT} ${CLIENT_SRC} ${CLIENT_INCLUDE})
TARGET_LINK_LIBRARIES(${MY_CLIENT} ${CONAN_LIBS})

set(MY_SERVER r-type_server)
project(${MY_SERVER})
file(GLOB FILES_SRC_SERVER Server/src/*.cpp)
file(GLOB FILES_INCLUDE_SERVER Server/src/*.hpp)
set(SERVER_SRC ${FILES_SRC_SERVER})
set(SERVER_INCLUDE ${FILES_INCLUDE_SERVER})
conan_basic_setup()
add_executable(${MY_SERVER} ${SERVER_SRC} ${SERVER_INCLUDE})
TARGET_LINK_LIBRARIES(${MY_SERVER} ${CONAN_LIBS})
