cmake_minimum_required(VERSION 3.5)
project (bcr VERSION 1.0.0 LANGUAGES CXX )

#--------------------------------
# This is for old cmake versions
#set (CMAKE_CXX_STANDARD 11)
#--------------------------------

#=== SETTING VARIABLES ===#
# Compiling flags
set( GCC_COMPILE_FLAGS "-Wall" )

# Include dir
include_directories( "src" "include" )

#=== BCR target ===

add_executable( bcr "src/app.cpp" )

target_compile_features( bcr PUBLIC cxx_std_11 )
