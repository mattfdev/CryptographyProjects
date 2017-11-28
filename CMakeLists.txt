cmake_minimum_required(VERSION 3.5)
project(crypto_labs)

set(CMAKE_CXX_STANDARD 11)

set(OPENSSL_INCLUDE_DIR  /usr/local/opt/openssl@1.1 ..)

find_package(OpenSSL)

include_directories(${OPENSSL_INCLUDE_DIR})


add_executable(lab3 ${SOURCE_FILES} lab3/lab3.cpp lab3/lab3.cpp)

add_executable(dhe ${SOURCE_FILES} lab4/dhe.c lab4/dhe.c)
add_executable(dhe_server ${SOURCE_FILES} lab4/dhe_server.c lab4/dhe_server.c)


target_link_libraries(dhe ${OPENSSL_LIBRARIES})
target_link_libraries(dhe_server ${OPENSSL_LIBRARIES})