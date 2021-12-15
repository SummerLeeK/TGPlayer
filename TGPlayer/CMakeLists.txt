# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(distribution_DIR ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI})
set(src_DIR ${CMAKE_SOURCE_DIR}/src/main/cpp )

include_directories(${src_DIR} ${src_DIR}/include ${src_DIR}/audio ${src_DIR}/video ${src_DIR}/libyuv ${src_DIR}/libyuv/libyuv)



# 3. 添加ffmpeg相关的so库
add_library( avutil
        SHARED
        IMPORTED )
set_target_properties( avutil
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/libavutil.so )

add_library( swresample
        SHARED
        IMPORTED )
set_target_properties( swresample
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/libswresample.so )

add_library( avcodec
        SHARED
        IMPORTED )
set_target_properties( avcodec
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/libavcodec.so )

add_library( avfilter
        SHARED
        IMPORTED)
set_target_properties( avfilter
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/libavfilter.so )

add_library( swscale
        SHARED
        IMPORTED)
set_target_properties( swscale
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/libswscale.so )

add_library( avformat
        SHARED
        IMPORTED)
set_target_properties( avformat
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/libavformat.so )

add_library( avdevice
        SHARED
        IMPORTED)
set_target_properties( avdevice
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/libavdevice.so )

add_library(yuv
        SHARED
        IMPORTED)
set_target_properties( yuv
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/libyuv.so )



# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)




find_library( # Sets the name of the path variable.
        android

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        android)





aux_source_directory(${src_DIR}/video NATVIE_SOURCE_VIDEO)
aux_source_directory(${src_DIR}/audio NATVIE_SOURCE_AUDIO)
aux_source_directory(${src_DIR} NATVIE_SOURCE)

add_library( # Sets the name of the library.
        tgplayer

        # Sets the library as a shared library.
        SHARED

        ${NATVIE_SOURCE}
        ${NATVIE_SOURCE_VIDEO}
        ${NATVIE_SOURCE_AUDIO}

        )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        tgplayer
        yuv
        avutil
        swresample
        avcodec
        avfilter
        swscale
        avformat
        avdevice
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        ${android}
        OpenSLES
        jnigraphics
        )