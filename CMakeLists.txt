cmake_minimum_required(VERSION 3.8)
project(robot_state)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ── Dependencias ──────────────────────────────────────────────────────────────
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)

# ── Ejecutable ────────────────────────────────────────────────────────────────
add_executable(state_node
  src/state_node.cpp
  src/main.cpp
)

target_include_directories(state_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

target_compile_features(state_node PUBLIC cxx_std_17)

ament_target_dependencies(state_node
  rclcpp
  nav_msgs
  geometry_msgs
  tf2
  tf2_geometry_msgs
)

install(TARGETS state_node
  DESTINATION lib/${PROJECT_NAME})

# ── Tests ─────────────────────────────────────────────────────────────────────
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
