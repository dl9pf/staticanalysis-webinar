cmake_minimum_required(VERSION 3.1)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 14) # C++14
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROJECT_NAME "rba")
project(${PROJECT_NAME})

if(USE_GCOV)
  set(LIB_NAME ${PROJECT_NAME}_gcov)
else()
  set(LIB_NAME ${PROJECT_NAME})
endif(USE_GCOV)

set(SRC_DIR src)
set(INCLUDE_DIR include)
file(GLOB_RECURSE SRC ${SRC_DIR}/*.cpp)
include_directories(
  ${INCLUDE_DIR}/rba
  ${SRC_DIR}/core/logic
  ${SRC_DIR}/core/model
  ${SRC_DIR}/core/expression
  ${SRC_DIR}/factory
  ${SRC_DIR}/log
  ${SRC_DIR}/optimize
  ${SRC_DIR}/public
  ${SRC_DIR}/sound
  ${SRC_DIR}/view
  ${SRC_DIR}/animation
  )

if(NOLOG)
  # compile without log
else()
  add_definitions(-DRBA_USE_LOG)
endif(NOLOG)

if(WIN32)
  # for Windows
  add_definitions(-D_WINDLL)
  add_definitions(-D_USRDLL)
  add_definitions(-DNDEBUG)
  add_definitions(-DRBA_EXPORTS)
  add_definitions(/source-charset:utf-8)
  add_definitions(/MP9)
  set(CMAKE_SHARED_LINKER_FLAGS "/SUBSYSTEM:WINDOWS")
  set(rba_BINARY_DIR ${PROJECT_SOURCE_DIR})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE  ${CMAKE_CURRENT_SOURCE_DIR}/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG  ${CMAKE_CURRENT_SOURCE_DIR}/lib)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE  ${CMAKE_CURRENT_SOURCE_DIR}/lib)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG  ${CMAKE_CURRENT_SOURCE_DIR}/lib)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/lib)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/lib)

else()
  # for Linux
  add_definitions("-Wall")

  if(RELEASE)
    add_definitions("-O2")
  else()
    if(USE_GPROF)
      add_definitions("-pg")
    else()
      add_definitions("-g")
    endif(USE_GPROF)
  endif(RELEASE)

  if(USE_GCOV)
    add_definitions(-fprofile-arcs -ftest-coverage -fno-exceptions)
    set(CMAKE_SHARED_LINKER_FLAGS "--coverage")
  else()
    if(USE_GPROF)
      set(CMAKE_SHARED_LINKER_FLAGS "-pg")
    endif(USE_GPROF)
  endif(USE_GCOV)

  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

endif(WIN32)

add_library(rba_shared SHARED ${SRC})
set_target_properties(rba_shared PROPERTIES OUTPUT_NAME ${LIB_NAME})

if(WIN32)
else()
  add_library(rba_static STATIC ${SRC})
  set_target_properties(rba_static PROPERTIES OUTPUT_NAME ${LIB_NAME})
endif(WIN32)

if(WIN32)
  target_link_libraries(rba_shared
    kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib
    shell32.lib ole32.lib oleaut32.lib uuid.lib
    )
endif(WIN32)

if(DEBUG_CMAKE)
message(STATUS "*** dump start cmake variables ***")
get_cmake_property(_variableNames VARIABLES)
foreach(_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
endforeach()
message(STATUS "*** dump end ***")
endif(DEBUG_CMAKE)

# end of file
