
cmake_minimum_required(VERSION 3.0)

# Required for YCM to work
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(
	hill_drawer
	VERSION 0.0.0
	LANGUAGES CXX
)

# ===========
# Definitions
#============

add_executable(
	${PROJECT_NAME}
	./src/main.cpp
	./src/hill_climber.cpp
)

# SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED network audio graphics window system)

target_link_libraries(
	${PROJECT_NAME}
	${SFML_LIBRARIES}
	${SFML_DEPENDENCIES}
)

