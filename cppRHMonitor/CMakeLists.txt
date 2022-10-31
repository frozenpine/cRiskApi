# cmake最低版本需求，不加入此行会受到警告信息
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

if(WIN32)
	add_definitions(-DISLIB -DWIN32 -D_CRT_SECURE_NO_WARNINGS)
endif()

PROJECT(cppRHMonitor VERSION 0.0.1) # 项目名称

# C++11 support
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# GDB调试
# SET(CMAKE_BUILD_TYPE "Debug")
# SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
# SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(
	INCLUDE_DIRS
	${PROJECT_SOURCE_DIR}/../includes/rohon
)

set(
	LIB_DIRS
	${PROJECT_SOURCE_DIR}/../libs/rohon
)

set(ENVLD_LIBRARY_PATH ${LIB_DIRS})

set(
	PROJECT_HEADERS
	${PROJECT_SOURCE_DIR}/api.h
	${INCLUDE_DIRS}/RHMonitorApi.h
	${INCLUDE_DIRS}/RHUserApiDataType.h
	${INCLUDE_DIRS}/RHUserApiStruct.h
)

aux_source_directory(${PROJECT_SOURCE_DIR} SRCS)

set(CMAKE_SKIP_BUILD_RPATH TRUE)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)

find_library(DEP_LIBS NAMES RHMonitorApi PATHS ${LIB_DIRS} REQUIRED)

add_executable(cppRHMonitor ${SRCS} ${PROJECT_HEADERS})
target_include_directories(cppRHMonitor PUBLIC ${INCLUDE_DIRS})
target_link_libraries(cppRHMonitor ${DEP_LIBS})
