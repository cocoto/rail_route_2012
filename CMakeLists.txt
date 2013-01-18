#Déclaration du projet
project(RailRoute2012)
cmake_minimum_required(VERSION 2.6)
set(EXECUTABLE_OUTPUT_PATH bin)


#Recherche de gtkmm
find_package(PkgConfig)
pkg_check_modules(gtkmm gtkmm-3.0 )
link_directories(${gtkmm_LIBRARY_DIRS})
include_directories(${gtkmm_INCLUDE_DIRS})



#Recherche des fichiers sources
include_directories($(FOO_SOURCE_DIR)/include)
file(GLOB_RECURSE sources_gtk_file src/gtk*)
file(GLOB_RECURSE main_files src/*main*)
file(GLOB_RECURSE source_files src/*)
list(REMOVE_ITEM source_files ${main_files} ${sources_gtk_file})

add_library(
	lib_rail_route SHARED
	${source_files}
)

#Déclaration du premier exécutable
add_executable(
	bin_console
	src/main.cpp
)

add_executable(
	generateur
	src/main_generateur.cpp
)

add_executable(
	bin_gui
	${sources_gtk_file}
)

#liaison dynamique de la librairie gtkmm
target_link_libraries(bin_gui   ${gtkmm_LIBRARIES} )
target_link_libraries(bin_console lib_rail_route)
target_link_libraries(generateur lib_rail_route)
target_link_libraries(bin_gui lib_rail_route)