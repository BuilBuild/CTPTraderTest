cmake_minimum_required(VERSION 3.15)
project(src)

SET(CMAKE_CXX_STANDARD 17)

# 添加源码
file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)

set(EXECUTABLE_OUTPUT_PATH ${EXECPATH})

include_directories(${HEADERPATH})

link_directories(${LIBPATH})
# link_directories(${CTPLIBPATH})
link_directories(${LIBPATH}/../CTP6.3.15/linux)

link_libraries(ctptra_api)

add_executable(main ${SRCS} ${HDRS})

target_link_libraries(main PUBLIC thosttraderapi_se)

