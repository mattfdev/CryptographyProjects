cmake_minimum_required(VERSION 3.5)
project(Lab2)

set(CMAKE_CXX_STANDARD 11)

set(OPENSSL_INCLUDE_DIR  /usr/local/opt/openssl ..)

find_package(OpenSSL)

include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(task3 ${SOURCE_FILES} task3.cpp)

add_executable(task4 ${SOURCE_FILES} task4.cpp)

add_executable(task5 ${SOURCE_FILES} task5.cpp)

target_link_libraries(task3 ${OPENSSL_LIBRARIES})

target_link_libraries(task4 ${OPENSSL_LIBRARIES})

target_link_libraries(task5 ${OPENSSL_LIBRARIES})

target_link_libraries(task5 crypt)
