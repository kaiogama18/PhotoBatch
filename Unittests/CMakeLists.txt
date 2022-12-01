
set(gtest_force_shared_crt ON CACHE BOLL "" FORCE)

FetchContent_Declare(
	googlestest
	GIT_REPOSITORY  https://github.com/google/googletest.git
	GIT_TAG			release-1.12.1
)
FetchContent_MakeAvailable(googlestest)

add_executable(TestArgumentParser 
	"TestArgumentParser.cpp"
	"${CMAKE_SOURCE_DIR}/ArgumentParser.cpp" 
	"${CMAKE_SOURCE_DIR}/Utils.cpp" 
)

target_include_directories(TestArgumentParser PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(TestArgumentParser PRIVATE gtest_main)