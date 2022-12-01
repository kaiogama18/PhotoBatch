cmake_minimum_required(VERSION 3.12)

project(PhotoBatch)

add_executable( PhotoBatch 
	"PhotoBatch.cpp" 
	"ArgumentParser.h" 
	"ArgumentParser.cpp" 
	"Utils.h" 
	"Utils.cpp"
	"RenameMode.cpp"
 "Mode.h" "Mode.cpp")

set_target_properties(PhotoBatch PROPERTIES CXX_STANDARD 17)

set(FETCHCONTENT_QUEST OFF CACHE BOOL "Disabled FetchContent Mode" FORCE)
include(FetchContent)

add_subdirectory(Unittests)
add_subdirectory(External)

target_link_libraries(PhotoBatch PRIVATE stb) 
