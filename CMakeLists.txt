cmake_minimum_required(VERSION 3.15)
project(top.weak-ptr.cqpy LANGUAGES CXX VERSION 0.1.0)

include_directories(src)
aux_source_directory(src SOURCES)
set(CMAKE_CXX_STANDARD 17)

# 添加编译参数
add_compile_definitions(APP_ID="${PROJECT_NAME}")
add_definitions(-DAPP_ID="top.weak-ptr.cqpy")
if (MSVC)
    add_compile_options(/utf-8)
    add_definitions(-DNOMINMAX)

    # 设置静态链接
    set(VCPKG_CRT_LINKAGE STATIC)
    set(VCPKG_LIBRARY_LINKAGE STATIC)
else ()
    add_link_options(-static -Wl,--kill-at,--enable-stdcall-fixup)
endif (MSVC)

# 引入 pybind11
find_package(pybind11 CONFIG REQUIRED)

# 添加 target
set(OUT_NAME "app")
add_library(${OUT_NAME} SHARED ${SOURCES})
set_target_properties(${OUT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${OUT_NAME} PRIVATE pybind11::embed)

# 添加安装脚本, 将在指定构建目标构建完成后运行, 可用于拷贝 app.dll 和 app.json 到酷Q应用目录
set(ACTUAL_SHARED_OUTPUT "${CMAKE_BINARY_DIR}/app.dll")
if (NOT MSVC)
    add_custom_command(TARGET ${OUT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/libapp.dll ${ACTUAL_SHARED_OUTPUT})
endif ()

if (MSVC)
    install(
            TARGETS ${OUT_NAME}
            RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/dev/${PROJECT_NAME}"
    )
else ()
    install(FILES ${ACTUAL_SHARED_OUTPUT} DESTINATION "${CMAKE_INSTALL_PREFIX}/dev/${PROJECT_NAME}")
endif ()

install(
        FILES "app.json" DESTINATION "${CMAKE_INSTALL_PREFIX}/dev/${PROJECT_NAME}"
)
install(
        DIRECTORY "cqpy" DESTINATION "${CMAKE_INSTALL_PREFIX}/data/app/${PROJECT_NAME}"
)
