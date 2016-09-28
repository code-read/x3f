cmake_minimum_required(VERSION 3.6)
project(x3f)

#set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
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

include_directories(C:/Users/Carson/.CLion2016.3/system/cmake/generated/tiff-4_0_6-830719ae/830719ae/Release/libtiff)

link_libraries(C:/Users/Carson/.CLion2016.3/system/cmake/generated/tiff-4_0_6-830719ae/830719ae/Release/libtiff/libtiff.a)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -v")

#set(OpenCV_DIR C:/Users/Carson/AppData/Local/opencv-3.0.0/build)
set(OpenCV_DIR C:/Users/Carson/.CLion2016.3/system/cmake/generated/opencv-97388285/97388285/Release)

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

add_executable(x3f_extract ${SOURCE_FILES})

add_executable(x3f_io_test ${SOURCE_FILES})

add_executable(x3f_matrix_test src/x3f_matrix_test.c src/x3f_matrix.c
        src/x3f_matrix.h src/x3f_printf.h src/x3f_printf.c)

find_package( OpenCV COMPONENTS core imgproc photo )

TARGET_LINK_LIBRARIES(x3f_extract ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(x3f_io_test ${OpenCV_LIBS})
