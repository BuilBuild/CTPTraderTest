cmake_minimum_required(VERSION 3.15)

project(ctptra_api)

# 搜索源文件
aux_source_directory(./ SRC)

include_directories(${HEADERPATH})

set(LIBRARY_OUTPUT_PATH ${LIBPATH})

link_directories(${CTPLIBDIR})

add_library(ctptra_api STATIC ${SRC})
target_link_libraries(ctptra_api PUBLIC thosttraderapi_se)


