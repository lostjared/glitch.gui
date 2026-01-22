cmake_minimum_required(VERSION 3.16)
project(glitch_gui VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS Core Gui Widgets OpenGL Network QUIET)
if(NOT Qt6_FOUND)
    find_package(Qt5 5.15 REQUIRED COMPONENTS Core Gui Widgets OpenGL Network)
    set(QT_VERSION_MAJOR 5)
else()
    set(QT_VERSION_MAJOR 6)
endif()


find_package(OpenGL REQUIRED)


find_package(PkgConfig REQUIRED)
set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:/usr/local/lib/pkgconfig")

pkg_check_modules(ACIDCAM REQUIRED acidcam)
pkg_check_modules(OPENCV4 REQUIRED opencv4)


set(SOURCES
    main.cpp
    main_window.cpp
    record_window.cpp
    about_window.cpp
    control_window.cpp
    custom_edit.cpp
    custom_window.cpp
    debug_window.cpp
    display_window.cpp
    layer.cpp
    layers_window.cpp
    mux_window.cpp
    new_filter.cpp
    new_image.cpp
    pref_window.cpp
    plugin_program.cpp
    rotate_window.cpp
    toolbox_window.cpp
    cat_vec.cpp
    ffmpeg_write.cpp
    filters/colorxor2.cpp
    filters/filters.cpp
    filters/frame_collection.cpp
    filters/glitch.cpp
    filters/layer_filter.cpp
    filters/trails.cpp
)

set(HEADERS
    main_window.hpp
    record_window.hpp
    about_window.hpp
    control_window.hpp
    custom_edit.hpp
    custom_window.hpp
    cv_fractal.hpp
    debug_window.hpp
    display_window.hpp
    layer.hpp
    layers_window.hpp
    lfo.hpp
    mux_window.hpp
    new_filter.hpp
    new_image.hpp
    pref_window.hpp
    plugin_program.hpp
    rotate_window.hpp
    toolbox_window.hpp
    cat_vec.hpp
    version_info.hpp
    ffmpeg_write.h
)


set(RESOURCES
    resources.qrc
)


add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)


target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ACIDCAM_INCLUDE_DIRS}
    ${OPENCV4_INCLUDE_DIRS}
)


target_link_directories(${PROJECT_NAME} PRIVATE
    ${ACIDCAM_LIBRARY_DIRS}
    ${OPENCV4_LIBRARY_DIRS}
)


target_compile_options(${PROJECT_NAME} PRIVATE
    ${ACIDCAM_CFLAGS_OTHER}
    ${OPENCV4_CFLAGS_OTHER}
)


if(QT_VERSION_MAJOR EQUAL 6)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::OpenGL
        Qt6::Network
        OpenGL::GL
        ${ACIDCAM_LIBRARIES}
        ${OPENCV4_LIBRARIES}
    )
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::OpenGL
        Qt5::Network
        OpenGL::GL
        ${ACIDCAM_LIBRARIES}
        ${OPENCV4_LIBRARIES}
    )
endif()


install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
