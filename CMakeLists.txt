cmake_minimum_required(VERSION 3.6)
project(x3f)

set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_VERBOSE_MAKEFILE TRUE)

#  The version number.
set (x3f_extract_VERSION_MAJOR  0)
set (x3f_extract_VERSION_MINOR  56)

#  Configure a header file to pass some of the CMake settings
#  to the source code
configure_file  (
"x3f_config.h.in"
"x3f_config.h"
)

# Include directory where CMake will deposit x3f_config.h:
include_directories(${CMAKE_CURRENT_BINARY_DIR})


#include_directories(C:/Users/Carson/AppData/Local/opencv-2.4.13/build/include)
#include_directories(C:/Users/Carson/AppData/Local/opencv-3.0.0/build/include)
#include_directories(C:/Users/Carson/ClionProjects/opencv/include)

#include_directories(C:/Users/Carson/AppData/Local/tiff-3.8.2-1-lib/include)

# Note: copied files manually from here to following include_directory as kludge b/c haven't figured out
# ..how CMake build script accomplishes that and/or if it's a problem with CLion - crw:
#include_directories(C:/Users/Carson/ClionProjects/tiff-4.0.6/libtiff)
include_directories(C:/Users/Carson/.CLion2016.3/system/cmake/generated/tiff-4_0_6-830719ae/830719ae/Release/libtiff)

#link_directories(C:/Users/Carson/AppData/Local/tiff-3.8.2-1-lib/lib)
#link_libraries(C:/Users/Carson/AppData/Local/tiff-3.8.2-1-lib/lib/libtiff.lib)
link_libraries(C:/Users/Carson/.CLion2016.3/system/cmake/generated/tiff-4_0_6-830719ae/830719ae/Release/libtiff/libtiff.a)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -v -Wl,--verbose,--trace")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -v -Wl,--verbose,--cref")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -v -Wl,-Bstatic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -v")

#set(MSVC true)
#set(MSVC_VERSION 1800)
#set(OpenCV_DIR C:/Users/Carson/AppData/Local/opencv-3.0.0/build)

#set(OpenCV_DIR C:/Users/Carson/.CLion2016.2/system/cmake/generated/opencv-97388285/97388285/Release)
set(OpenCV_DIR C:/Users/Carson/.CLion2016.3/system/cmake/generated/opencv-97388285/97388285/Release)
#set (OpenCV_STATIC TRUE)
#SET(OpenCV_USE_STATIC_LIBS ON)

set(SOURCE_FILES
    src/mingw_dowildcard.c
    src/x3f_denoise.cpp
    src/x3f_denoise.h
    src/x3f_denoise_aniso.cpp
    src/x3f_denoise_aniso.h
    src/x3f_denoise_utils.cpp
    src/x3f_denoise_utils.h
    src/x3f_dngtags.c
    src/x3f_dngtags.h
    src/x3f_dump.c
    src/x3f_dump.h
    src/x3f_extract.c
    src/x3f_histogram.c
    src/x3f_histogram.h
    src/x3f_image.c
    src/x3f_image.h
    src/x3f_io.c
    src/x3f_io.h
    src/x3f_matrix.c
    src/x3f_matrix.h
    src/x3f_meta.c
    src/x3f_meta.h
    src/x3f_output_dng.c
    src/x3f_output_dng.h
    src/x3f_output_ppm.c
    src/x3f_output_ppm.h
    src/x3f_output_tiff.c
    src/x3f_output_tiff.h
    src/x3f_print.c
    src/x3f_print.h
    src/x3f_printf.c
    src/x3f_printf.h
    src/x3f_process.c
    src/x3f_process.h
    src/x3f_spatial_gain.c
    src/x3f_spatial_gain.h)

add_executable(x3f ${SOURCE_FILES})

# May be optional if we link with 32 bit only:
#set_target_properties(x3f PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
#set_target_properties(x3f PROPERTIES COMPILE_FLAGS "-Wl,Bstatic" LINK_FLAGS "-m32")
#set_target_properties(x3f PROPERTIES LINK_FLAGS "-static -static-libgcc -static-libstdc++")

#FIND_PACKAGE( OpenCV REQUIRED core highgui imgproc)
#FIND_PACKAGE( OpenCV REQUIRED core imgproc) # trouble building highgui; workaround for now - crw
#find_package( OpenCV REQUIRED ) # only looked for core and imgproc; trouble building highgui; workaround for now - crw
find_package( OpenCV COMPONENTS core imgproc photo )

TARGET_LINK_LIBRARIES(x3f ${OpenCV_LIBS})
#TARGET_LINK_LIBRARIES(x3f INTERFACE ${OpenCV_LIBS})
