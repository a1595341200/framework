cmake_minimum_required(VERSION 3.15)
set(PROJECT_N framework)
project(${PROJECT_N} LANGUAGES CXX)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake)
# add_compilation_options_check()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

file(GLOB root_header_files "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
     "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)
file(GLOB root_src_files "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s")
else()
    add_compile_options("-g3")
endif()

add_library(${PROJECT_N} SHARED ${root_header_files} ${root_src_files})

target_include_directories(
    ${PROJECT_N} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                        $<INSTALL_INTERFACE:include/${PROJECT_N}>
)

option(BUILD_TESTS "Build Tests" ON)

if(BUILD_TESTS)
include(CTest)
enable_testing()
add_subdirectory(tests)

endif()
install(
    TARGETS ${PROJECT_N}
    EXPORT ${PROJECT_N}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)

install(FILES ${root_header_files} DESTINATION include/${PROJECT_N})

install(
    EXPORT ${PROJECT_N}
    NAMESPACE "framework::"
    DESTINATION lib/cmake/${PROJECT_N}
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_N}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_N}Config.cmake INSTALL_DESTINATION lib/cmake
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_N}Config.cmake
        DESTINATION lib/cmake/${PROJECT_N}
)
