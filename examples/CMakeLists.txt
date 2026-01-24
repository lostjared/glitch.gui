cmake_minimum_required(VERSION 3.16)
project(acidcam_plugins)

cmake_policy(SET CMP0177 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Add system cmake directory to CMAKE_PREFIX_PATH
list(APPEND CMAKE_PREFIX_PATH "/usr/local/lib/cmake")

# Find required packages using CMake config files
find_package(acidcam CONFIG REQUIRED)
find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs highgui)

# List of all plugin directories
set(PLUGIN_DIRS
    alpha_diamond1
    alpha_diamond2
    alpha_diamond3
    alpha_diamond4
    alpha_diamond5
    alphatrails
    color_fade_ex1
    color_fade_ex2
    color_shift
    colorxor01
    colorxor02
    colorxor03
    colorxor04
    colorxor05
    colorxor06
    colorxor07
    colorxor08
    colorxor09
    colorxor10
    colorxor11
    colorxor12
    colorxor13
    colorxor14
    colorxor15
    colorxor16
    colorxor17
    colorxor18
    colorxor19
    colorxor20
    distort_picture
    fast_monocolortrails
    frame_pixels
    frame_resize_stretch
    frame_skip
    frame_skip_resize
    frame_skip_shadow
    frame_skip_shadow_x2
    frame_slide01
    frame_slide02
    frame_slide03
    frame_slide04
    frame_square_col
    frame_stutter_filter
    glitch_x1
    gpt1
    gpt2
    invertflash
    line_across_side01
    line_across_side02
    line_across_side03
    line_across_side04
    line_across_side05
    line_across_side06
    line_collection01
    line_collection02
    line_collection03
    line_collection04
    line_collection05
    line_collection06
    line_collection07
    line_offset_inout
    line_offset_inout2
    line_offset_inout3
    newrandblend
    newstretchlines
    newvarlines
    outoforder
    pic_adjust1
    pic_adjust2
    picture_jump01
    picture_jump02
    picture_jump03
    picture_jump04
    picture_jump05
    picture_jump06
    picture_jump07
    picture_jump08
    picture_jump09
    picture_jump10
    picture_jump11
    picture_jump12
    picture_jump13
    picture_jump14
    picture_jump15
    picture_jump16
    picture_jump17
    picture_jump18
    picture_jump19
    picture_jump20
    picture_jump21
    picture_jump22
    picture_jump23
    picture_jump24
    picture_jump25
    picture_jump26
    picture_jump27
    picture_jump28
    picture_jump29
    picture_jump30
    picture_jump31
    rect_size
    rsquare2
    rsquare3
    rsquare4
    rsquare5
    slice_frame
    slice_frame_w
    square_block_v2a
    square_block_v2b
    square_block_v2c
    square_block_v2d
    square_block_v2e
    square_block_v2f
    square_block_v2g
    square_block_v2h
    square_xor
    store_frame10
    stuckframe
    stutter_long
    stutter_sbrv
)

# Install destination
set(PLUGIN_INSTALL_DIR "${CMAKE_SOURCE_DIR}/../glitch.gui/plugins" CACHE PATH "Plugin installation directory")

# Create a shared library for each plugin
foreach(PLUGIN_DIR ${PLUGIN_DIRS})
    set(PLUGIN_SOURCE "${CMAKE_SOURCE_DIR}/${PLUGIN_DIR}/plugin.cpp")
    
    # Check if plugin.cpp exists
    if(EXISTS ${PLUGIN_SOURCE})
        # Create shared library with .acidcam suffix
        add_library(${PLUGIN_DIR} SHARED ${PLUGIN_SOURCE})
        
        # Set output name and properties
        set_target_properties(${PLUGIN_DIR} PROPERTIES
            PREFIX ""
            SUFFIX ".acidcam"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PLUGIN_DIR}"
            OUTPUT_NAME "${PLUGIN_DIR}"
        )
        
        # Link libraries from find_package
        target_link_libraries(${PLUGIN_DIR} PRIVATE acidcam::acidcam ${OpenCV_LIBRARIES})
        
        # Compiler flags
        target_compile_options(${PLUGIN_DIR} PRIVATE -O3)
        
        # Install rule for this plugin
        install(FILES "${CMAKE_BINARY_DIR}/${PLUGIN_DIR}/${PLUGIN_DIR}.acidcam"
                DESTINATION ${PLUGIN_INSTALL_DIR})
    else()
        message(WARNING "Plugin source not found: ${PLUGIN_SOURCE}")
    endif()
endforeach()

# Print build info
message(STATUS "Configured ${CMAKE_PROJECT_NAME}")
message(STATUS "Plugin install directory: ${PLUGIN_INSTALL_DIR}")
message(STATUS "Number of plugins: ${CMAKE_INSTALL_PREFIX}")
