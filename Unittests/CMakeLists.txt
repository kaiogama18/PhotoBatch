set(FETCHCONTENT_QUEST OFF CACHE BOOL "Disabled FetchContent Mode" FORCE)
set(gtest_force_shared_crt ON CACHE BOLL "" FORCE)

include(FetchContent)
FetchContent_Declare(
	googlestest
	GIT_REPOSITORY  https://github.com/google/googletest.git
	GIT_TAG			release-1.12.1
)
FetchContent_MakeAvailable(googlestest)

add_executable(TestArgumentParser "TestArgumentParser.cpp")
target_link_libraries(TestArgumentParser PRIVATE gtest_main)