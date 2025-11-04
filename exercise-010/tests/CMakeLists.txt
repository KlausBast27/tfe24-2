cmake_minimum_required(VERSION 3.14)

find_package(Catch2 CONFIG REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(test_myvector_json
  test_myvector_json.cpp
)

target_include_directories(test_myvector_json PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(test_myvector_json PRIVATE Catch2::Catch2WithMain nlohmann_json::nlohmann_json)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test_vectors.json ${CMAKE_CURRENT_BINARY_DIR}/test_vectors.json COPYONLY)

add_test(NAME test_myvector_json
  COMMAND test_myvector_json --reporter compact --success
)
