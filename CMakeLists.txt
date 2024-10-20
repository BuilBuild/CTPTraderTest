cmake_minimum_required(VERSION 3.15)

project(ctpproject)
SET(CMAKE_CXX_STANDARD 17)

# 静态库生成路经
set(LIBPATH ${PROJECT_SOURCE_DIR}/lib)
# 可执行文件程序储存路径
set(EXECPATH ${PROJECT_SOURCE_DIR}/bin)
# 头文件路径
set(HEADERPATH ${PROJECT_SOURCE_DIR}/include)

list(APPEND HEADERPATH  ${PROJECT_SOURCE_DIR}/CTP6.3.15
                        ${PROJECT_SOURCE_DIR}/comm
                        ${PROJECT_SOURCE_DIR}/CTPTraAPI
    )
set(CTPLIBDIR ${PROJECT_SOURCE_DIR}/CTP6.3.15/linux)

# 库文件名字
# set(SRCLIB src)

# 可执行文件名字
# set(APPNAME1 app1)
# 添加子目录
add_subdirectory(src)
add_subdirectory(CTPTraAPI)