cmake_minimum_required (VERSION 3.0)
project (timestep)

set (CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O3")
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native -mtune=native\
       -fstrict-aliasing -ftree-vectorize -fopenmp-simd\
       -fopt-info-vec-optimized -fopt-info-vec-missed\
       -fno-trapping-math -fno-math-errno -mprefer-vector-width=256")
endif()

add_executable(timestep_opt1 main.c timestep_opt1.c)
target_link_libraries(timestep_opt1 m)

add_executable(timestep_opt2 main.c timestep_opt2.c)
target_link_libraries(timestep_opt2 m)

add_executable(timestep_opt3 main.c timestep_opt3.c)
target_link_libraries(timestep_opt3 m)

add_custom_target(distclean COMMAND rm -rf CMakeCache.txt CMakeFiles
                  Makefile cmake_install.cmake timestep.dSYM ipo_out.optrpt)
