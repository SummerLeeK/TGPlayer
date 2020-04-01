# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

include_directories(src/main/cpp/include)
include_directories(src/main/cpp)
include_directories(src/main/cpp/audio)
include_directories(src/main/cpp/video)
set(distribution_DIR ${CMAKE_SOURCE_DIR}/../../../libs)

#添加libavcodec-57.so
add_library( avcodec
        SHARED
        IMPORTED)
set_target_properties( avcodec
        PROPERTIES IMPORTED_LOCATION
        ../../../../libs/${ANDROID_ABI}/libavcodec.so)

#添加libavdevice-57.so
add_library( avdevice
        SHARED
        IMPORTED)
set_target_properties( avdevice
        PROPERTIES IMPORTED_LOCATION
        ../../../../libs/${ANDROID_ABI}/libavdevice.so)

add_library(avfilter
        SHARED
        IMPORTED)
set_target_properties( avfilter
        PROPERTIES IMPORTED_LOCATION
        ../../../../libs/${ANDROID_ABI}/libavfilter.so)

add_library( avformat
        SHARED
        IMPORTED)
set_target_properties( avformat
        PROPERTIES IMPORTED_LOCATION
        ../../../../libs/${ANDROID_ABI}/libavformat.so)

add_library( avutil
        SHARED
        IMPORTED)
set_target_properties( avutil
        PROPERTIES IMPORTED_LOCATION
        ../../../../libs/${ANDROID_ABI}/libavutil.so)

add_library( swresample
        SHARED
        IMPORTED)
set_target_properties( swresample
        PROPERTIES IMPORTED_LOCATION
        ../../../../libs/${ANDROID_ABI}/libswresample.so)

add_library( swscale
        SHARED
        IMPORTED)
set_target_properties( swscale
        PROPERTIES IMPORTED_LOCATION
        ../../../../libs/${ANDROID_ABI}/libswscale.so)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")


aux_source_directory(src/main/cpp/video NATVIE_SOURCE_VIDEO)
aux_source_directory(src/main/cpp/audio NATVIE_SOURCE_AUDIO)
aux_source_directory(src/main/cpp NATVIE_SOURCE)

add_library( # Sets the name of the library.
        tgplayer

        # Sets the library as a shared library.
        SHARED

        ${NATVIE_SOURCE}
        ${NATVIE_SOURCE_VIDEO}
        ${NATVIE_SOURCE_AUDIO}

)


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


# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        tgplayer
        avcodec
        avdevice
        avfilter
        avformat
        avutil
        swresample
        swscale
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        ${android}
        OpenSLES
        )