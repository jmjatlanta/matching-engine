add_executable(functional functional.cpp)
target_include_directories(functional PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include )

add_executable(performance performance.cpp)
target_include_directories(performance PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include ${CMAKE_CURRENT_SOURCE_DIR}/../util )

add_executable(generate_csv generate_csv.cpp)