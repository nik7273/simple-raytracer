cmake_minimum_required(VERSION 3.0)

# Set the project name
project(RayTracerInOneWeekend)

# Add an executable with the above sources
add_executable(in_one_weekend main.cc)

# Set the C++ standard
set_target_properties(in_one_weekend PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
)
