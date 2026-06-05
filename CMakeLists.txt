cmake_minimum_required (VERSION 3.16)
project(mskpp_c CXX C)

get_filename_component(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR} ABSOLUTE)
get_filename_component(THIRD_PARTY_DIR thirdparty ABSOLUTE)
get_filename_component(MSKPP_CORE_DIR ${ROOT_DIR}/csrc/core ABSOLUTE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 检查是否可用 ccache
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "Using ccache: ${CCACHE_PROGRAM}")
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
else()
    message(STATUS "ccache not found, using native compiler.")
endif()

# 检查是否可用 python
find_program(PYTHON NAMES python3 python)
if(NOT PYTHON)
    message(FATAL_ERROR "Could not find python3 or python in PATH!")
else()
    message(STATUS "Found Python: ${PYTHON}")
endif()

find_package(Python REQUIRED COMPONENTS Development)
message(STATUS "Found Python: ${Python_VERSION}")
message(STATUS "Python include directories: ${Python_INCLUDE_DIRS}")
message(STATUS "Python libraries: ${Python_LIBRARIES}")

include_directories(${Python_INCLUDE_DIRS})

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${ROOT_DIR}/output CACHE STRING "install prefix" FORCE)
    message(STATUS "No install prefix selected, default to ${CMAKE_INSTALL_PREFIX}")
endif()

# 提供给测试的插桩，统计测试覆盖率
if (DEFINED HITEST AND HITEST STREQUAL "ON")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE hitestwrapper)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK hitestwrapper)
endif()

add_library(mskpp_c SHARED)

target_compile_options(mskpp_c PRIVATE
    -std=c++11
    -Wall
    -fPIC
    -fstack-protector-all
    -D_FORTIFY_SOURCE=2
    -fvisibility=hidden
    -ftrapv
    -fstack-check
    -O
)

target_link_options(mskpp_c PRIVATE
    -Wl,-z,relro
    -Wl,-z,now
    -Wl,-z,noexecstack
)

if (NOT BUILD_TESTS)
    target_link_options(mskpp_c PRIVATE -s)
endif()

set_target_properties(mskpp_c PROPERTIES OUTPUT_NAME "_C" PREFIX "")
install(TARGETS mskpp_c LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib64)
install(TARGETS mskpp_c LIBRARY DESTINATION ${ROOT_DIR}/mskpp)

set(INSTALL_GTEST OFF)
if (BUILD_TESTS)
    set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage -lgcov")
    include_directories(thirdparty/boost/)
    include_directories(thirdparty/boost/libs/type_traits/include)
    include_directories(thirdparty/boost/libs/config/include)
    include_directories(thirdparty/boost/libs/typeof/include)
    add_subdirectory(thirdparty)
    add_subdirectory(test)
endif ()
add_subdirectory(csrc)

set(PACKAGE_DIR ${CMAKE_CURRENT_BINARY_DIR}/package)
add_custom_command(
    OUTPUT ${PACKAGE_DIR}/package.flag
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PACKAGE_DIR}/mskpp ${CMAKE_INSTALL_PREFIX}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ROOT_DIR}/mskpp ${PACKAGE_DIR}/mskpp
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:mskpp_c> ${PACKAGE_DIR}/mskpp/
    COMMAND ${CMAKE_COMMAND} -E copy ${ROOT_DIR}/README.md ${PACKAGE_DIR}/
    COMMAND ${CMAKE_COMMAND} -E copy ${ROOT_DIR}/setup.py ${PACKAGE_DIR}/
    COMMAND ${CMAKE_COMMAND} -E copy ${ROOT_DIR}/MANIFEST.in ${PACKAGE_DIR}/
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_INSTALL_PREFIX}/*.whl
    COMMAND cd ${PACKAGE_DIR} && ${PYTHON} setup.py bdist_wheel --dist-dir ${CMAKE_INSTALL_PREFIX}/
    COMMAND chmod 550 ${CMAKE_INSTALL_PREFIX}/*.whl
    COMMAND touch ${PACKAGE_DIR}/package.flag
    COMMENT "Copying mskpp folder and so to output dir, and make mskpp whl package"
)

add_custom_target(package_mskpp ALL DEPENDS
                    mskpp_c
                    ${ROOT_DIR}/MANIFEST.in
                    ${ROOT_DIR}/README.md
                    ${ROOT_DIR}/setup.py
                    ${PACKAGE_DIR}/package.flag)
