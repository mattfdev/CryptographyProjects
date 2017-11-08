cmake_minimum_required(VERSION 3.5)
project(lab2)

set(CMAKE_CXX_STANDARD 11)

#Lab 2 Cmake configuration
set(OPENSSL_INCLUDE_DIR  /usr/local/opt/openssl .)

find_package(OpenSSL)

include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(task3 ${SOURCE_FILES} lab2/task3.cpp)

add_executable(task4 ${SOURCE_FILES} lab2/task4.cpp)

add_executable(task5 ${SOURCE_FILES} lab2/task5.cpp)

target_link_libraries(task3 ${OPENSSL_LIBRARIES})

target_link_libraries(task4 ${OPENSSL_LIBRARIES})

target_link_libraries(task5 ${OPENSSL_LIBRARIES})

target_link_libraries(task5 crypt)

#Lab 3 CMAKE configuration

add_executable(lab3 ${SOURCE_FILES} lab3/lab3.cpp lab3/lab3.cpp)
