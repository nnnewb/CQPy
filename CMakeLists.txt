cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME top.weak-ptr.frejya)
project(top.weak-ptr.frejya LANGUAGES CXX VERSION 0.1.0)

include_directories(src)
aux_source_directory(src SOURCES)
set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(APP_ID="${PROJECT_NAME}")
add_compile_options(/utf-8)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


set(INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/scripts/install.ps1")
# 添加安装脚本, 将在指定构建目标构建完成后运行, 可用于拷贝 app.dll 和 app.json 到酷Q应用目录
if(EXISTS ${INSTALL_SCRIPT})
    add_custom_command(TARGET ${PROJECT_NAME}
                        POST_BUILD
                        COMMAND
                        powershell -ExecutionPolicy Bypass -NoProfile -File ${INSTALL_SCRIPT} "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
endif()