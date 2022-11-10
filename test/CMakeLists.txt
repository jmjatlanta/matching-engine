add_executable(functional functional.cpp)
set(CMAKE_CXX_FLAGS "-O2")

target_include_directories(functional PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include 
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/Allocator )

add_executable(performance performance.cpp)
set(CMAKE_CXX_FLAGS "-O2")
target_include_directories(performance PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include 
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/Allocator
    ${CMAKE_CURRENT_SOURCE_DIR}/../util )

add_executable(generate_csv generate_csv.cpp)
