cmake_minimum_required(VERSION 3.11)
project(LinearRegression C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(StringHandling)

add_executable(LinearRegression
	Main.c
	File.h File.c
	Parser.h Parser.c
	LinearRegression.h LinearRegression.c
)

target_link_libraries(LinearRegression PRIVATE StringHandling)
