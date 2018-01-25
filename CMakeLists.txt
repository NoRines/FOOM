cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(foom)

find_package(SDL2 REQUIRED)

file(GLOB code "code/*.cpp")
file(GLOB entities "code/Entities/*.cpp")
file(GLOB graphics "code/Graphics/*.cpp")
file(GLOB frameBuffers "code/Graphics/FrameBuffers/*.cpp")
file(GLOB maths "code/Maths/*.cpp")
file(GLOB states "code/States/*.cpp")
file(GLOB world "code/World/*.cpp")

add_executable(
	foom
	${code}
	${entities}
	${graphics}
	${frameBuffers}
	${maths}
	${states}
	${world}
)

target_link_libraries(foom ${SDL2_LIBRARIES})
