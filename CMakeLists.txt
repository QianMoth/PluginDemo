cmake_minimum_required(VERSION 3.5)

# 添加版本号
set(MO_VERSION_MAJOR 0)
set(MO_VERSION_MINOR 0)
set(MO_VERSION_PATCH 1)
set(MO_VERSION  ${MO_VERSION_MAJOR}.${MO_VERSION_MINOR}.${MO_VERSION_PATCH})

# 工程名称
project(plugindemo VERSION ${MO_VERSION})
message(STATUS ${PROJECT_NAME} v${MO_VERSION})

#设置输出路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # 静态库的文件夹位置
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # 动态库的文件夹位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # 可执行软件的文件夹位置

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

#这个就是定义各个版本对应的后缀，例如d，debug版本后缀，当然你想定义为其他，	#自己修改这块就可以了。
SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
SET(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_MINSIZEREL_POSTFIX "s" CACHE STRING "add a postfix, usually empty on windows")

if(MSVC)
    # 设置MSVC编译编码
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
endif()

add_subdirectory(include)

add_definitions(-DNODE_EDITOR_SHARED)
add_definitions(-DNODE_EDITOR_EXPORTS)
add_definitions(-DFLOW_EDITOR_SHARED)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets) # 识别是Qt6还是Qt5
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
message(STATUS "QT_VERSION_MAJOR : " ${QT_VERSION_MAJOR})
message(STATUS "QT_DIR : " ${QT_DIR})

# include_directories("D:/proj/NodeEditorAndPlugins/nodeeditor-p/include")
# include_directories("D:/proj/NodeEditorAndPlugins/nodeeditor-p/3rdparty/nodeeditor/include")
include_directories("./include/")

file(GLOB_RECURSE CPP_SOURCE_FILES  src/*.cpp src/*.cxx src/*.cc)
file(GLOB_RECURSE CPP_INCLUDE_FILES  src/*.hpp src/*.h)
file(GLOB_RECURSE RESOURCES  src/*.qrc src/*.rc)

set(PROJECT_SOURCES ${CPP_SOURCE_FILES} ${CPP_INCLUDE_FILES} ${RESOURCES})

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
# 支持动态库和静态库同时存在
set_target_properties(${PROJECT_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        debug ${CMAKE_CURRENT_SOURCE_DIR}/lib/nodesd.lib
        debug ${CMAKE_CURRENT_SOURCE_DIR}/lib/nodes2d.lib
        optimized ${CMAKE_CURRENT_SOURCE_DIR}/lib/nodes.lib
        optimized ${CMAKE_CURRENT_SOURCE_DIR}/lib/nodes2.lib
        Qt${QT_VERSION_MAJOR}::Widgets
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION CMAKE_RUNTIME_OUTPUT_DIRECTORY
    LIBRARY DESTINATION CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ARCHIVE DESTINATION CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    BUNDLE  DESTINATION CMAKE_RUNTIME_OUTPUT_DIRECTORY
)