cmake_minimum_required(VERSION 3.5)
project(device_status)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

# Project global directory 
set (ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(LIBDEVICESTATUS "libdevicestatus")
set(LIBDEVICESTATUS_CC_FILES "${ROOT_DIR}/device_metrics.cc")
add_library(${LIBDEVICESTATUS} SHARED ${LIBDEVICESTATUS_CC_FILES})
target_include_directories(${LIBDEVICESTATUS} PUBLIC ${ROOT_DIR} )

add_executable(main main.cc)
target_include_directories(main PUBLIC ${ROOT_DIR})
target_link_libraries(main ${LIBDEVICESTATUS})