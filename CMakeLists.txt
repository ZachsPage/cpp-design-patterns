cmake_minimum_required(VERSION 3.12)

project("DesignPatterns" CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# DIR_NAME - directory containing a `main.cc` to build an executable for. Reuses
#  DIR_NAME as the exe name and builds into a bin/<subdir>/ taking the dir name
#  from the current CMakeLists.txt file
# - Avoids having a CMakeLists.txt per directory with a single src file -> exe
function( create_exec_from_dir DIR_NAME )
    add_executable( ${DIR_NAME} ${DIR_NAME}/main.cc )
    get_filename_component( build_subdir ${CMAKE_CURRENT_SOURCE_DIR} NAME )
    set_target_properties( ${DIR_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${build_subdir}" )
endfunction()

add_subdirectory( behavioral )
add_subdirectory( creational )
add_subdirectory( structural )