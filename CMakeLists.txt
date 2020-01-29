cmake_minimum_required(VERSION 3.14)
set(PROJECT_NAME top.weak-ptr.frejya)
project(top.weak-ptr.frejya LANGUAGES CXX VERSION 0.1.0)

include_directories(src)
aux_source_directory(src SOURCES)
set(CMAKE_CXX_STANDARD 17)

# 添加编译参数
add_compile_definitions(APP_ID="${PROJECT_NAME}")
add_compile_options(/utf-8)
add_definitions(-DAPP_ID="top.weak-ptr.cqpy" -DNOMINMAX)

# 引入 pybind11
find_package(pybind11 REQUIRED)
include_directories(${PYBIND11_INCLUDE_DIRS})
link_directories(${PYBIND11_LIBRARY_DIRS})

# 添加 target
add_library(${PROJECT_NAME} SHARED ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${PROJECT_NAME} PRIVATE pybind11::embed)

# 添加安装脚本, 将在指定构建目标构建完成后运行, 可用于拷贝 app.dll 和 app.json 到酷Q应用目录
set(INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/scripts/install.ps1")
if(EXISTS ${INSTALL_SCRIPT})
    add_custom_command(TARGET ${PROJECT_NAME}
                        POST_BUILD
                        COMMAND
                        powershell -ExecutionPolicy Bypass -NoProfile -File ${INSTALL_SCRIPT} "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
endif()