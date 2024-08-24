cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  # hello_test
  # hello_test.cc
	parse_test
  tests/parse_test.cc
	# srcs/calc/calc_calc_horizontal_inter_pos.c
  # srcs/calc/calc_calc_vertical_inter_pos.c
  # srcs/calc/calc_intersection.c
  # srcs/calc/calc_utils.c
  # srcs/calc/calc_utils2.c
	# srcs/draw/draw_background.c
	# srcs/draw/draw_rect.c
	# srcs/draw/draw_utils.c
	# srcs/draw/draw_wall.c
	srcs/parse/parse.c
  srcs/parse/parse_add_color.c
  srcs/parse/parse_load_map_list_to_data.c
  srcs/parse/parse_load_map_str_to_list.c
  srcs/parse/parse_load_textures.c
  srcs/parse/parse_trim_map_list.c
  srcs/parse/parse_utils.c
  srcs/parse/parse_utils_bool.c
  srcs/parse/parse_utils_free.c
  srcs/parse/parse_utils_load.c
  srcs/parse/parse_utils_print.c
  srcs/parse/parse_validate_map_data.c
  srcs/parse/parse_validate_map_data_utils.c
  library/libft/get_next_line.c
  library/libft/get_next_line_utils.c
)

include_directories(
	${CMAKE_SOURCE_DIR}/includes
	${CMAKE_SOURCE_DIR}/library
)

target_link_libraries(
  parse_test
  GTest::gtest_main
	${CMAKE_SOURCE_DIR}/library/libft/libft.a
)

include(GoogleTest)
gtest_discover_tests(parse_test)
