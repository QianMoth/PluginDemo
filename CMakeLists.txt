cmake_minimum_required(VERSION 3.5)

# 添加版本号
set(MO_VERSION_MAJOR 0) # 主版本号
set(MO_VERSION_MINOR 0) # 子版本号
set(MO_VERSION_PATCH 1) # 阶段版本号
string(TIMESTAMP MO_VERSION_TIME %y%m%d) # 日期版本号
set(MO_VERSION_ALPHABET "alpha")# 希腊字母版本号
set(MO_VERSION  ${MO_VERSION_MAJOR}.${MO_VERSION_MINOR}.${MO_VERSION_PATCH}.${MO_VERSION_TIME})

#Base版:    此版本表示该软件仅仅是一个假页面链接，通常包括所有的功能和页面布局，但是页面中的功能都没有做完整的实现，只是做为整体网站的一个基础架构。
#Alpha版:   此版本表示该软件在此阶段主要是以实现软件功能为主，通常只在软件开发者内部交流，一般而言，该版本软件的Bug较多，需要继续修改。
#Beta版:    该版本相对于α版已有了很大的改进，消除了严重的错误，但还是存在着一些缺陷，需要经过多次测试来进一步消除，此版本主要的修改对像是软件的UI。
#RC版:      (Release Candidate)该版本已经相当成熟了，基本上不存在导致错误的BUG，与即将发行的正式版相差无几。
#Release版: 该版本意味“最终版本”，在前面版本的一系列测试版之后，终归会有一个正式版本，是最终交付用户使用的一个版本。该版本有时也称为标准版。一般情况下，Release不会以单词形式出现在软件封面上，取而代之的是符号(Ｒ)。


# 工程名称
project(plugindemo VERSION ${MO_VERSION})
message(STATUS "${PROJECT_NAME} v${MO_VERSION}")

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

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

INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})

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

        # debug D:/proj/NodeEditorAndPlugins/nodeeditor-p/build/lib/Debug/nodesd.lib
        # debug D:/proj/NodeEditorAndPlugins/nodeeditor-p/build/lib/Debug/nodes2d.lib
        # optimized D:/proj/NodeEditorAndPlugins/nodeeditor-p/build/lib/Release/nodes.lib
        # optimized D:/proj/NodeEditorAndPlugins/nodeeditor-p/build/lib/Release/nodes2.lib

        Qt${QT_VERSION_MAJOR}::Widgets
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION CMAKE_RUNTIME_OUTPUT_DIRECTORY
    LIBRARY DESTINATION CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ARCHIVE DESTINATION CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    BUNDLE  DESTINATION CMAKE_RUNTIME_OUTPUT_DIRECTORY
)