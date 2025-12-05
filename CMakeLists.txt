# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(jellyfin-pi)

# Set C++ Standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)

pkg_check_modules(MPV REQUIRED mpv)
pkg_check_modules(LIBCURL REQUIRED libcurl)
pkg_check_modules(GBM REQUIRED gbm)
pkg_check_modules(DRM REQUIRED libdrm)
pkg_check_modules(EGL REQUIRED egl)

add_executable(jellyfin-pi
    src/main.cpp
)

target_include_directories(jellyfin-pi PRIVATE
    ${MPV_INCLUDE_DIRS}
    ${LIBCURL_INCLUDE_DIRS}
    ${GBM_INCLUDE_DIRS}
    ${DRM_INCLUDE_DIRS}
    ${EGL_INCLUDE_DIRS}
)

target_link_libraries(jellyfin-pi PRIVATE
    ${MPV_LIBRARIES}
    ${LIBCURL_LIBRARIES}
    ${GBM_LIBRARIES}
    ${DRM_LIBRARIES}
    ${EGL_LIBRARIES}
    mpv
    curl
    gbm
    drm
    EGL
)

target_compile_options(jellyfin-pi PRIVATE
    ${MPV_CFLAGS_OTHER}
    ${LIBCURL_CFLAGS_OTHER}
)