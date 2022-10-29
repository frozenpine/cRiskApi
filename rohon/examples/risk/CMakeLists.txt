# cmake最低版本需求，不加入此行会受到警告信息
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

if(WIN32)
	add_definitions(-DISLIB -DWIN32)
endif()

PROJECT(cppRohonRisk VERSION 0.0.1) # 项目名称

# C++11 support
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# GDB调试
# SET(CMAKE_BUILD_TYPE "Debug")
# SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
# SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(
	INCLUDE_DIRS
	${PROJECT_SOURCE_DIR}/../../include
)

set(
	LIB_DIRS
	${PROJECT_SOURCE_DIR}/../../libs
)

aux_source_directory(${PROJECT_SOURCE_DIR} SRCS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

find_library(DEP_LIBS NAMES RHMonitorApi PATHS ${LIB_DIRS})

add_executable(cppRohonRisk ${SRCS})
target_include_directories(cppRohonRisk PUBLIC ${INCLUDE_DIRS})
target_link_libraries(cppRohonRisk ${DEP_LIBS})
