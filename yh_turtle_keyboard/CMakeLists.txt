cmake_minimum_required(VERSION 3.0.2)
project(yh_turtle_keyboard)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  
)

##################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
  LIBRARIES yh_turtle_keyboard
  CATKIN_DEPENDS geometry_msgs roscpp
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/yh_turtle_keyboard.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(yh_turtle_circle_v1 src/yh_turtle_circle_v1.cpp)
add_executable(yh_turtle_rectangle src/yh_turtle_rectangle.cpp)
add_executable(yh_turtle_triangle src/yh_turtle_triangle.cpp)
add_executable(yh_turtle_circle_v2 src/yh_turtle_circle_v2.cpp)
add_executable(yh_turtle_pen_v1 src/yh_turtle_pen_v1.cpp)
add_executable(yh_turtle_pen_v2 src/yh_turtle_pen_v2.cpp)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(yh_turtle PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
add_dependencies(yh_turtle_circle_v1 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(yh_turtle_rectangle ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(yh_turtle_triangle ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(yh_turtle_circle_v2 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(yh_turtle_pen_v1 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(yh_turtle_pen_v2 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(yh_turtle_circle_v1
  ${catkin_LIBRARIES}
)
target_link_libraries(yh_turtle_rectangle
  ${catkin_LIBRARIES}
)
target_link_libraries(yh_turtle_triangle
  ${catkin_LIBRARIES}
)
target_link_libraries(yh_turtle_circle_v2
  ${catkin_LIBRARIES}
)
target_link_libraries(yh_turtle_pen_v1
  ${catkin_LIBRARIES}
)
target_link_libraries(yh_turtle_pen_v2
  ${catkin_LIBRARIES}
)
