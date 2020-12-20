cmake_minimum_required(VERSION 3.5)
project (EBFN_PARSER VERSION 1.0.0 LANGUAGES CXX )

#=== FINDING PACKAGES ===#

#--------------------------------
# This is for old cmake versions
# set (CMAKE_CXX_STANDARD 17)
#--------------------------------

#=== SETTING VARIABLES ===#
# Compiling flags
set( GCC_COMPILE_FLAGS "-Wall" )


#=== Main App ===

include_directories( "include" )

add_executable( bares   "src/main.cpp"
                        "src/evaluate_posfix.cpp"   
                        "src/infix2posfix.cpp"
                        "src/parser.cpp" )

target_compile_features( bares PUBLIC cxx_std_17 )
