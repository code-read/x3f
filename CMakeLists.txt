cmake_minimum_required(VERSION 3.6)
project(x3f)

set(CMAKE_VERBOSE_MAKEFILE TRUE)  # Verbose output from 'make' during the build

#  Global x3f project version number.
# todo: tie this to `git describe --always --dirty --tags` as Roland (now) has in makefile:
set (x3f_extract_VERSION_MAJOR  0)
set (x3f_extract_VERSION_MINOR  56)

#  Header file to pass project version number and other CMake settings to the source code:
configure_file  ( "x3f_config.h.in" "x3f_config.h" )

# Include directory where CMake will deposit x3f_config.h:
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Point this to your libtiff directory:
include_directories(C:/Users/Carson/.CLion2016.3/system/cmake/generated/tiff-4_0_6-830719ae/830719ae/Release/libtiff)

# Point this to your libtiff library:
link_libraries(C:/Users/Carson/.CLion2016.3/system/cmake/generated/tiff-4_0_6-830719ae/830719ae/Release/libtiff/libtiff.a)

# Point this to your OpenCV "build" sub directory (where OpenCVConfig.cmake lives):
set(OpenCV_DIR C:/Users/Carson/.CLion2016.3/system/cmake/generated/opencv-97388285/97388285/Release)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -v")

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

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_executable(x3f_extract ${SOURCE_FILES})

add_executable(x3f_io_test ${SOURCE_FILES})

add_executable(x3f_matrix_test src/x3f_matrix_test.c src/x3f_matrix.c
        src/x3f_matrix.h src/x3f_printf.h src/x3f_printf.c)

find_package( OpenCV COMPONENTS core imgproc photo )

TARGET_LINK_LIBRARIES(x3f_extract ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(x3f_io_test ${OpenCV_LIBS})
