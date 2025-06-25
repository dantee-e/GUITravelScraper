cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_COMPILER "gcc")
project(GUITravelScraper C)

set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Werror")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

# Add executable
add_executable(${PROJECT_NAME}
		src/main.c
		src/app_activate.c
		src/app_activate.h
		src/types/string_list.c
		src/types/string_list.h
		src/utils.c
		src/utils.h
		src/navbar/navbar.c
		src/navbar/navbar.h
		src/rust_interface/rust_interface.c
		src/rust_interface/rust_interface.h
)

# Add imported library
add_library(travel_scraper SHARED IMPORTED)
set_target_properties(travel_scraper PROPERTIES
		IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/src/lib/libtravel_scraper.so"
)


# Set include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${GTK4_INCLUDE_DIRS})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::GTK4 travel_scraper)

# Set runtime path to find the .so file
set_target_properties(${PROJECT_NAME} PROPERTIES
		INSTALL_RPATH "${CMAKE_SOURCE_DIR}/src/lib"
		BUILD_WITH_INSTALL_RPATH TRUE
)