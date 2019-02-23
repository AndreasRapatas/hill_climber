cmake_minimum_required(VERSION 3.0)

project(
	hill_climber
	VERSION 0.0.0
	LANGUAGES CXX
)

# Dependencies {{{

list(APPEND CMAKE_MODULE_PATH
	"${CMAKE_SOURCE_DIR}/cmake/modules"
)

# SFML
find_package(
	SFML 2 REQUIRED
	graphics window system
)

# }}}

# Definitions {{{

set(
	${PROJECT_NAME}_src
	./src/main.cpp
	./src/hill_climber.cpp
)

add_executable(
	${PROJECT_NAME}
	${${PROJECT_NAME}_src}
)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
		${SFML_LIBRARIES}
		${SFML_DEPENDENCIES}
)

# }}}
