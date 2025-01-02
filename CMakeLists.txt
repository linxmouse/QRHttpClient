cmake_minimum_required(VERSION 3.10)

project(httpClientDemo LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Network REQUIRED)

add_library(httpClient STATIC "")

file(GLOB ALL_SOURCE "*.cpp" "*.c")
file(GLOB ALL_HEAD "*.hpp" "*.h" "Models/*.h" "RESTAPI/*.h")

target_sources(httpClient
  PRIVATE
  ${ALL_SOURCE}
  PUBLIC
  ${ALL_HEAD}
)

target_include_directories(httpClient
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/RESTAPI
)

target_link_libraries(httpClient
	PUBLIC
	Qt5::Core
	Qt5::Network
)

add_executable(httpClientDemo main.cpp TyLogger.h)
target_include_directories(httpClientDemo
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${CMAKE_CURRENT_LIST_DIR}/RESTAPI
)
target_link_libraries(httpClientDemo
	PUBLIC
	httpClient
	Qt5::Core
	Qt5::Network
)