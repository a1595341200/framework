find_package(GTest CONFIG REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLOG REQUIRED libglog)

macro(BUILD curdir)
    file(GLOB children ${curdir}/*.cpp)
    message("Building ${children}")
    foreach(child ${children})
    get_filename_component(FILENAME ${child} NAME_WE)
    add_executable(${FILENAME} ${child})
    target_link_libraries(${FILENAME} 
        ${PROJECT_N}
        GTest::gtest
        GTest::gmock
        ${GLOG_LIBRARIES}
    )
    add_test(NAME ${FILENAME} COMMAND ${FILENAME})
    endforeach()
endmacro()
      
BUILD(${CMAKE_CURRENT_SOURCE_DIR})
